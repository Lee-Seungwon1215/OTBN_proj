# Classic McEliece KeyGen OTBN 행 연산 확장 설계

작성일: 2026-08-18
대상: `crypto_kem/348864/vec/pk_gen.c`의 피벗 탐색과 전방소거
현재 단계: OTBN ISA/ISS와 4행 DMEM 타일 어셈블리 커널 구현. RTL과 전체
`pk_gen` 호스트 오프로딩은 아직 미구현.

## 1. 프로파일 근거

| 구간 | `pk_gen` 내부 비중 | 전체 KeyGen 비중 |
|---|---:|---:|
| 피벗 탐색·조건부 행 결합 | 38.76% | 28.55% |
| 전방소거 | 38.06% | 28.04% |
| 합계 | 76.82% | 56.59% |

두 구간은 각각 294,528개의 행 쌍을 처리한다. 행 쌍 하나는 `mat`의 64비트
워드 12개와 `ops`의 64비트 워드 12개, 합계 24개의 조건부 XOR 갱신을
수행한다.

## 2. 공통 기반 최적화

### 2.1 256비트 WDR 벡터화

64비트 워드 네 개를 WDR 하나에 배치한다. 행 쌍 하나의 24개 64비트
갱신을 여섯 개 256비트 갱신으로 바꾼다. 한 소거 구간의 데이터 갱신
횟수는 7,068,672회에서 1,767,168회로 줄어든다.

### 2.2 조건부 XOR 명령어 융합

`BN.AND`와 `BN.XOR`로 구성되는 여섯 쌍의 연산을 여섯 개의 조건부 XOR로
융합한다.

- `BN.XORCOND`: 선택한 플래그가 1이면 `wrs1 XOR wrs2`, 아니면 `wrs1`.
- `BN.XORCONDN`: 선택한 플래그가 0이면 `wrs1 XOR wrs2`, 아니면 `wrs1`.
- 두 명령어 모두 플래그를 변경하지 않아 한 번 계산한 조건을 행의 여섯
  WDR 조각에 재사용할 수 있다.

### 2.3 레지스터 상주형 행 스트리밍

`w0`부터 `w5`까지에 현재 행 또는 피벗 행을 유지한다. 한 행씩 처리하는
저면적 스케줄에서는 상대 행의 조각을 `w6`으로 읽고, 갱신하고, 저장한 뒤
다음 조각으로 덮어쓴다. 기준 행을 상대 행마다 다시 읽지 않으며 약 8~9개
WDR만 사용한다.

## 3. 피벗 탐색: 네 후보 prefix 검사

새 명령어 `BN.PIVOTMASK4`는 현재 피벗 `p`와 네 후보 피벗 `b0..b3`에서
다음 조건을 고정 시간에 생성한다.

| 플래그 | 후보 | XOR 조건 |
|---|---:|---|
| C | 0 | `not p` |
| M | 1 | `not (p or b0)` |
| L | 2 | `not (p or b0 or b1)` |
| Z | 3 | `not (p or b0 or b1 or b2)` |

이 마스크로 후보 행을 C, M, L, Z 순서로 조건부 XOR하면 원래 순차 코드와
완전히 같은 행을 얻는다. 후보 조건 검사 묶음은 294,528개에서 73,920개로
줄어든다. 행 데이터 읽기와 XOR의 총 비트 수는 줄지 않는다.

`BN.PIVOTMASK4`의 두 번째 입력 WDR에는 네 후보 행의 피벗 워드를 64비트
lane별로 미리 배치해야 한다. 전체 행을 전치할 필요는 없고 피벗 워드 네
개만 작은 staging buffer에 모으면 된다. 이 gather 비용은 Ubuntu의 OTBN
사이클 프로파일에서 별도로 측정한다.

## 4. 전방소거: 독립 행 네 개 batching

새 명령어 `BN.ELIMMASK4`는 네 대상 행의 피벗 워드를 담은 WDR에서 같은
비트 위치를 뽑아 C, M, L, Z에 저장한다. 이후 같은 피벗 행 조각과 네 대상
행 조각에 `BN.XORCOND`를 적용한다.

조건 검사와 반복 제어는 294,528개의 개별 처리에서 73,920개의 네 행
배치로 줄어든다. 현재 256비트 데이터 경로에서는 한 배치의 네 행, 여섯
WDR를 갱신하는 24개의 WDR 연산이 그대로 필요하다. 실제 데이터 연산까지
네 배 동시 처리하려면 1024비트 경로, 추가 WDR 포트 또는 다중 사이클
`BN.ELIM4`가 필요하므로 이번 ISS 프로토타입 범위에서는 제외한다.

## 5. 구현된 파일

- ISA와 인코딩: `opentitan/hw/ip/otbn/data/bignum-insns.yml`,
  `opentitan/hw/ip/otbn/data/enc-schemes.yml`
- ISS 의미 모델: `opentitan/hw/ip/otbn/dv/otbnsim/sim/insn.py`
- 실제 OTBN 행 연산 커널:
  `opentitan/sw/otbn/crypto/mceliece_keygen_row_ops.s`
- 독립 실행용 DMEM 인터페이스:
  `opentitan/sw/otbn/crypto/run_mceliece_keygen_row_ops.s`
- 랜덤·스케줄 검증:
  `opentitan/hw/ip/otbn/dv/otbnsim/test/mceliece_keygen_test.py`
- 어셈블·링크·ISS 종단간 검증:
  `opentitan/hw/ip/otbn/dv/otbnsim/test/mceliece_keygen_row_ops_asm_test.py`

추가된 명령어는 `BN.XORCOND`, `BN.XORCONDN`, `BN.PIVOTMASK4`,
`BN.ELIMMASK4`다. 인코딩 YAML 로더의 전 명령어 충돌 검사를 통과했다.

## 6. 검증 범위

테스트는 다음을 확인한다.

1. 네 명령어의 32비트 디코딩과 피연산자 추출.
2. 두 조건부 XOR의 모든 플래그 그룹·플래그·극성 조합.
3. `BN.PIVOTMASK4`와 `BN.ELIMMASK4`의 무작위 비트 위치와 lane.
4. 12개 후보를 네 개씩 처리한 prefix 스케줄과 원래 순차 피벗 탐색의
   결과 일치.
5. 독립 행 네 개 전방소거와 원래 행별 갱신의 결과 일치.
6. `w6` 하나를 덮어쓰는 단일 행 스트리밍 스케줄의 결과 일치.

Mac 환경에서는 의존성 없는 직접 실행으로 모든 랜덤 테스트를 통과했다.
정식 `pytest` 및 OTBN 어셈블리/RTL 검증은 OpenTitan 의존성이 설치된 Ubuntu
환경에서 수행한다.

## 7. 실제 어셈블리 커널의 동작

`mceliece_keygen_pivot_batch4`는 현재 행의 여섯 WDR를 `w0..w5`에 한 번
적재한다. 후보 네 행은 같은 256비트 조각끼리 `w8..w11`에 적재하고,
`BN.PIVOTMASK4`가 만든 prefix 플래그로 `BN.XORCOND`를 적용한다. 따라서
원본 C의 후보 네 번 순차 검사를 한 번의 고정 제어 배치로 실행한다.

`mceliece_keygen_elim_batch4`는 피벗 행의 여섯 WDR를 `w0..w5`에 유지한다.
네 대상 행을 조각별로 `w8..w11`에 올리고 `BN.ELIMMASK4`의 C/M/L/Z를
재사용하여 네 개의 독립적인 조건부 XOR를 수행한 뒤 DMEM에 저장한다.

한 행은 `mat[0..11] || ops[0..11]`의 24개 64비트 워드를 네 개씩 묶은
여섯 WDR다. 전체 768행은 OTBN DMEM에 동시에 들어가지 않으므로 호스트가
현재/피벗 행과 상대 행 네 개를 하나의 타일로 전달해야 한다. 현재 ISA
프로토타입의 `bit_idx`와 `current_lane`은 즉시값이므로 실행 커널은 호스트가
선택한 피벗 비트를 staging WDR의 lane별 bit 0으로 정규화해 전달받는다.
이 staging 및 DMEM 전송 비용은 Ubuntu 사이클 프로파일에 반드시 포함한다.
