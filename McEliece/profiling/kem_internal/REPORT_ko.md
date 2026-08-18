# Classic McEliece 캡슐화·디캡슐화 병목 분석

## 1. 결론부터

대상은 `Classic McEliece 348864 / vec` 구현이다.

| 단계 | 코드상 1순위 예상 | 실측 1순위 | 핵심 결론 |
|---|---|---|---|
| 캡슐화 | syndrome 공개키 행렬 스캔 | syndrome 공개키 행렬 스캔, **46.96%** | 코드상·실측상 1순위가 같다. 다만 오류벡터 생성 전체도 **39.43%**여서 격차가 작다. |
| 디캡슐화 | `vec_mul`이 반복되는 FFT·BM 디코더 | Berlekamp–Massey, **24.91%** | 개별 함수 1순위는 BM이며, `vec_mul` 중심 디코더 여섯 구간을 합치면 **88.08%**다. |

따라서 Classic McEliece 전체를 하나의 “큰 정수 연산”으로 보면 안 된다.

```text
캡슐화  : 261 KB 공개키 스트리밍 + GF(2) AND/XOR/parity
디캡슐화: bitsliced GF(2^12) vec_mul + FFT/FFT^T + BM
```

두 단계는 같은 명령 하나로 최적화하기 어렵다. 캡슐화는 메모리 대역폭과 GF(2) 내적, 디캡슐화는 carry 없는 비트평면 곱셈과 데이터 재배열이 핵심이다.

---

## 2. 측정 범위와 방법

- 구현: libmceliece의 `crypto_kem/348864/vec`
- 실행 환경: Apple Silicon ARM64, Apple clang 21.0.0, `-O2`
- 입력: 정상 캡슐화가 만든 **유효 ciphertext**
- 키 사용: 실행 한 번마다 새 키를 만들고, 같은 실행 안에서는 그 키로 KEM을 반복
- 표본: 독립 실행 2회 × 9 trials × 10,000회 = **180,000회**
- 워밍업: 실행당 200회, 총 400회
- 정확성: 워밍업을 포함한 **180,400회 KEM round-trip 전부 일치**
- 시간: `CLOCK_MONOTONIC`으로 전체 단계와 내부 구간을 직접 계측

세부 구간 계측이 아주 짧은 캡슐화에 미치는 영향을 확인하기 위해 먼저 큰 구간만 잰 별도 180,000회 측정과도 비교했다.

| 계측 방식 | 캡슐화 | 디캡슐화 |
|---|---:|---:|
| 큰 구간 계측 | 8.125 µs | 108.086 µs |
| 세부 구간 계측 | 8.291 µs | 108.660 µs |

세부 계측에서 캡슐화가 약 2.0% 길어졌지만 상위 병목의 순위와 비중은 거의 같았다. 아래 표는 더 자세한 **세부 구간 계측 180,000회 합산값**이다.

주의할 점:

1. 이 수치는 현재 Mac ARM64의 `vec C1` 소프트웨어 구현 결과다. RISC-V/OTBN에서 절대 시간은 달라진다.
2. 디캡슐화는 유효 ciphertext 경로를 측정했다. 핵심 디코더는 상수시간 성격이 강하지만, 실패 입력을 별도로 섞은 프로파일은 아니다.
3. 타이머 호출보다 짧은 하위 구간은 절대값보다 “상위 병목이 아니다”라는 판단에 쓰는 편이 안전하다.

---

## 3. 캡슐화: 코드상 병목

### 3.1 실행 흐름

```text
난수 후보 128개
      │ 범위 필터
      ▼
오류 위치 64개 ── 정렬·중복 검사 ── 실패 시 처음부터 반복
      │
      ▼
3488-bit 오류벡터 e 생성
      │
      ▼
공개키 768행과 e를 GF(2) 내적 → 768-bit syndrome c
      │
      ▼
SHAKE256(1 || e || c) → 공유키
```

### 3.2 코드만 보고 세는 반복량

#### A. syndrome 공개키 스캔

파라미터는 다음과 같다.

```text
GFBITS      = 12
SYS_T       = 64
SYS_N       = 3488
PK_NROWS    = 64 × 12 = 768
PK_NCOLS    = 3488 - 768 = 2720
PK_ROW_BYTES= 340
공개키 크기 = 768 × 340 = 261,120 bytes
```

각 공개키 행마다 다음 작업을 한다.

- 64-bit 단위 `pk_word & e_word`, XOR 누적: `floor(2720/64) = 42회`
- 남은 32-bit tail 처리: 1회
- XOR-fold parity 축약: 6회 shift-XOR

캡슐화 1회 전체로 보면 64-bit AND-XOR만 `768 × 42 = 32,256회`이고, 공개키 **261,120 bytes 전체를 매번 읽는다**. 따라서 코드상 가장 먼저 의심할 병목은 syndrome이다.

#### B. 오류벡터 생성

코드상 한 시도는 다음과 같다.

- 12-bit 후보 최대 128개 생성·범위 필터
- 유효 위치 64개 정렬
- 인접 값 중복 검사
- 중복이면 전체 시도 반복
- 확정된 64개 위치를 3488-bit 상수시간 벡터로 변환

선택된 `bitwrite16/64` 구현은 출력 436 bytes를 54개의 64-bit word로 보고, 위치 64개 각각에 대해 모든 word를 마스킹하며 돈다. 즉 핵심 scatter만 대략 `64 × 54 = 3,456회`의 masked word 갱신이다.

단순 반복문 크기는 syndrome보다 작지만, 정렬·상수시간 scatter·재시도가 섞여 있어 코드 줄 수보다 비싸다.

#### C. SHAKE256

SHAKE 입력은 `1 + 436 + 96 = 533 bytes`다. Keccak이 들어가지만 533 bytes 한 번이므로, 261 KB 공개키 스캔보다 먼저 1순위로 잡을 근거는 약하다.

### 3.3 캡슐화 코드상 순위

1. syndrome 공개키 스캔
2. 오류벡터 생성 전체
3. SHAKE256
4. preimage 복사

---

## 4. 캡슐화: 실측 병목

전체 시간은 **8.291 µs/op**이고 trial 중앙값은 8.174 µs/op이다.

| 순위 | 구간 | 시간/op | 캡슐화 비중 | 호출/op |
|---:|---|---:|---:|---:|
| 1 | syndrome 공개키 스캔 | 3.893 µs | **46.96%** | 1.000 |
| 2 | 오류벡터 materialize | 1.693 µs | **20.43%** | 1.000 |
| 3 | SHAKE256 공유키 생성 | 0.898 µs | **10.84%** | 1.000 |
| 4 | 오류 위치 정렬·중복 검사 | 0.796 µs | **9.60%** | **1.791** |
| 5 | RNG·범위 필터 | 0.780 µs | **9.40%** | **1.791** |
| 6 | preimage 복사 | 0.030 µs | 0.36% | 1.000 |
| - | 미분류/계측 경계 | 0.200 µs | 2.41% | - |

오류벡터 생성 세 구간을 합치면:

```text
20.43 + 9.60 + 9.40 = 39.43%
```

즉 단일 함수 1순위는 syndrome 46.96%지만, 오류벡터 생성 전체는 39.43%로 거의 따라온다.

### 4.1 코드상 예상과 실측이 다른 부분

1. **1순위 자체는 같다.** 공개키 261 KB 전체를 스트리밍하며 768개의 parity를 만드는 syndrome이 실제로도 가장 크다.
2. **오류 생성은 코드 외형보다 크다.** 오류 위치가 겹치면 다시 뽑아야 하며, 실측상 난수·정렬 구간은 캡슐화당 평균 1.791회 실행됐다.
3. **materialize의 한 반복이 무겁다.** 위치 64개만 쓰는 것처럼 보여도 비밀 위치를 직접 인덱싱하지 않기 위해 출력 word 전체를 상수시간 마스킹한다.
4. **SHAKE는 존재하지만 1순위가 아니다.** 캡슐화에서 10.84%이며, syndrome 하나의 약 23%에 불과하다.

따라서 “Classic McEliece 캡슐화는 Keccak 병목”이라고 결론 내리면 이 구현에서는 틀린다.

---

## 5. 디캡슐화: 코드상 병목

### 5.1 실행 흐름

```text
ciphertext syndrome
        │ preprocess
        ▼
역 Benes 순열
        ▼
Goppa 다항식 FFT → batch inverse → syndrome FFT^T
        ▼
Berlekamp–Massey로 error-locator 계산
        ▼
locator FFT → root 추출
        ▼
재암호화 FFT^T → syndrome 비교
        ▼
정 Benes 순열 → weight 검사
        ▼
성공 e / 실패용 s를 상수시간 선택 → SHAKE256
```

코드를 함수 이름만 보고 보면 FFT, BM, Benes, weight check가 모두 커 보인다. 실제 우선순위를 잡으려면 공통 내부 primitive인 `vec_mul()`까지 내려가서 호출 수를 세어야 한다.

### 5.2 `vec_mul()`이 하는 일

`vec` 하나는 64-bit word이고, 12개 word가 64개의 GF(2^12) 원소를 bit-sliced 형태로 담는다.

```text
f[0..11] × g[0..11]
       │
       ├─ 12 × 12 = 144개의 64-bit AND-XOR 곱항
       └─ 11단계 × 2 XOR의 기약다항식 reduction
       ▼
64개의 GF(2^12) 곱을 병렬 계산
```

이 곱셈은 정수 `MUL`처럼 carry가 전파되는 큰 정수 곱셈이 아니다. AND와 XOR로 구성된 **carry-less bitsliced 유한체 곱셈**이다.

### 5.3 디코더의 정적 `vec_mul` 호출 수

| 구간 | 계산 근거 | `vec_mul` 수 | 1,389회 중 비중 |
|---|---|---:|---:|
| Berlekamp–Massey | 128 iterations × 3 + 마지막 1 | **385** | **27.72%** |
| syndrome FFT^T | butterfly 192 + radix 10 + beta 6 | **208** | **14.97%** |
| 재암호화 FFT^T | 동일 | **208** | **14.97%** |
| scaling FFT | radix 5 + butterfly 192 | **197** | **14.18%** |
| locator FFT | 동일 | **197** | **14.18%** |
| batch inverse | prefix 63 + `vec_inv` 5 + suffix 126 | **194** | **13.97%** |
| 합계 |  | **1,389** | 100% |

batch inverse에는 위 곱셈 외에도 `vec_sq`가 75회 있다. FFT/FFT^T에는 XOR butterfly, broadcast, 64×64 transpose와 radix 변환이 추가된다.

기타 구간의 정적 특징:

- Benes: 23개 layer × layer당 32개 conditional swap = 736개 swap, 64×64 transpose 포함. 정·역 방향으로 각각 한 번.
- weight check: 4096개 전체 field 위치와 실제 길이 3488개 위치를 세므로 총 7,584 bit-count iteration.
- SHAKE256: 캡슐화와 같은 크기의 preimage 한 번.

### 5.4 디캡슐화 코드상 순위

공통 primitive까지 세면 다음과 같이 예상된다.

1. Berlekamp–Massey
2. syndrome FFT^T와 재암호화 FFT^T
3. scaling FFT와 locator FFT
4. batch inverse
5. weight check
6. Benes 정·역 순열
7. SHAKE256 및 나머지

---

## 6. 디캡슐화: 실측 병목

전체 시간은 **108.660 µs/op**이고 trial 중앙값은 107.793 µs/op이다. 캡슐화보다 약 **13.1배** 느리다.

| 순위 | 구간 | 시간/op | 디캡슐화 비중 |
|---:|---|---:|---:|
| 1 | Berlekamp–Massey | 27.063 µs | **24.91%** |
| 2 | syndrome FFT^T | 15.487 µs | **14.25%** |
| 3 | 재암호화 FFT^T | 15.386 µs | **14.16%** |
| 4 | scaling FFT | 12.846 µs | **11.82%** |
| 5 | locator FFT | 12.506 µs | **11.51%** |
| 6 | scaling batch inverse | 12.414 µs | **11.43%** |
| 7 | weight check | 4.634 µs | **4.26%** |
| 8 | 역 Benes | 3.263 µs | **3.00%** |
| 9 | 정 Benes | 3.263 µs | **3.00%** |
| 10 | SHAKE256 공유키 생성 | 0.886 µs | **0.82%** |
| - | 나머지 7개 세부 구간 | 0.496 µs | 0.45% |
| - | 미분류/계측 경계 | 0.416 µs | 0.38% |

상위 여섯 개 GF/FFT/BM 구간을 합치면:

```text
24.91 + 14.25 + 14.16 + 11.82 + 11.51 + 11.43 = 88.08%
```

### 6.1 코드상 예상과 실측이 다른 부분

이번에는 코드상 반복량과 실측 순위가 매우 잘 맞는다.

| 구간 | 정적 `vec_mul` 비중 | 실측 전체 시간 비중 |
|---|---:|---:|
| BM | 27.72% | 24.91% |
| syndrome FFT^T | 14.97% | 14.25% |
| 재암호화 FFT^T | 14.97% | 14.16% |
| scaling FFT | 14.18% | 11.82% |
| locator FFT | 14.18% | 11.51% |
| batch inverse | 13.97% | 11.43% |

비율이 완전히 같지는 않은 이유는 다음과 같다.

- `vec_mul` 호출 한 번의 비용만 있는 것이 아니라 함수별 XOR, shift, transpose, broadcast, load/store가 다르다.
- 정적 비중의 분모는 상위 여섯 구간의 1,389회뿐이지만, 실측 비중의 분모는 Benes·weight check·SHAKE까지 포함한 디캡슐화 전체다.
- BM에는 `vec_mul` 외에도 128회 반복되는 reduce, update, conditional move가 있다.

그럼에도 정적 `vec_mul` 횟수로 예측한 순서가 실측 순서와 거의 일치한다. 즉 디캡슐화는 소스의 바깥 함수 크기보다 **`vec_mul` 호출 구조를 기준으로 분석하는 것이 맞다.**

---

## 7. 코드상 병목과 실측상 병목의 최종 분류

### 캡슐화

```text
코드상  : syndrome > 오류 생성 > SHAKE
실측상  : syndrome 46.96% > 오류 생성 전체 39.43% > SHAKE 10.84%
판정    : 1순위 일치. 단, 재시도와 상수시간 scatter 때문에 오류 생성이 예상보다 큼.
```

### 디캡슐화

```text
코드상  : BM > FFT^T > FFT > batch inverse > weight > Benes > SHAKE
실측상  : BM 24.91% > FFT^T 각 14%대 > FFT/batch inverse 각 11%대
판정    : inner primitive(vec_mul) 기준으로 세면 순위가 강하게 일치.
```

---

## 8. RISC-V와 OTBN에 적용할 때의 의미

### 8.1 캡슐화 1순위

syndrome은 공개키 261 KB를 읽어서 wide AND-XOR와 parity reduction을 수행한다.

```text
큰 공개키 메모리 ──stream──> AND/XOR 누적 ──parity──> syndrome
```

따라서 연산기만 빠르게 만들어도 공개키 전달이 느리면 효과가 작다.

- 일반 RISC-V 쪽 후보: RVV wide load/AND/XOR, reduction, popcount/parity 계열 최적화
- 커스텀 명령 후보: 여러 word의 GF(2) dot-product/parity를 한 번에 누적하는 명령
- 하드웨어 조건: 공개키를 가속기 가까운 메모리에서 스트리밍할 수 있어야 함
- OTBN 주의점: Host가 261 KB 공개키를 작은 OTBN DMEM으로 매번 나눠 복사하면, 현재 8.3 µs짜리 캡슐화보다 전송 비용이 지배할 가능성이 높음

즉 캡슐화는 **OTBN 연산 명령보다 메모리 구조를 먼저 검토**해야 한다.

### 8.2 디캡슐화 1순위

디캡슐화는 `vec_mul`을 직접 빠르게 하는 것이 가장 넓은 효과를 낸다. BM 하나만 전용화하는 것보다 FFT·FFT^T·batch inverse까지 같은 primitive를 재사용할 수 있기 때문이다.

필요한 기능은 다음과 같다.

- 12개의 64-bit bitplane 사이 144개 AND-XOR 곱항
- GF(2^12) 기약다항식 reduction
- XOR butterfly와 64×64 transpose/bit permutation 지원
- 중간 배열을 가속기 안에 오래 유지할 수 있는 local memory

주의: OTBN의 일반적인 `BN.MUL`은 carry가 있는 정수 곱셈이므로 현재 `vec_mul`을 그대로 대체하지 못한다. OTBN을 쓴다면 `BN.MUL` 재사용보다는 **carry-less/bitsliced GF 전용 확장**이 필요하다.

또한 `inv`, `scaled`, `eval`은 배열 하나당 `64 × 12 × 8 = 6,144 bytes`이고 세 개만 합쳐도 약 18 KB다. OTBN DMEM 용량과 타일링·재사용 계획을 함께 설계해야 한다. 작은 함수 하나씩 Host↔OTBN으로 왕복하면 전송 비용 때문에 이득을 잃을 수 있다.

### 8.3 Keccak/KMAC의 우선순위

- 캡슐화 SHAKE: 10.84%
- 디캡슐화 SHAKE: 0.82%

Classic McEliece 캡슐화·디캡슐화만 놓고 보면 KMAC/SHAKE 오프로딩은 1순위가 아니다. 특히 디캡슐화는 GF 디코더 최적화가 압도적으로 먼저다.

---

## 9. 다음 구현 순서 제안

1. `vec_mul` microbenchmark를 RISC-V scalar, RVV, OTBN 기존 명령으로 각각 구현해 cycle/호출을 측정한다.
2. OTBN 기존 `BN.MUL`이 아니라 AND/XOR 기반 `vec_mul` 매핑이 가능한지 확인한다.
3. 디캡슐화 전체 working set과 OTBN DMEM 사이의 타일링 및 전송량을 계산한다.
4. 캡슐화는 공개키 261 KB를 기준으로 Host 메모리 대역폭과 OTBN 전달 시간을 먼저 측정한다.
5. 전송을 포함한 end-to-end 시간으로 판단한다. 연산 kernel 시간만 비교하면 잘못된 결론이 날 수 있다.

연구용 커스텀 명령 우선순위를 하나 고른다면, Classic McEliece에서는 먼저 **bitsliced GF(2^12) `vec_mul` 가속**을 고르는 편이 타당하다. 캡슐화 syndrome보다 디캡슐화 절대 시간이 13배 크고, `vec_mul` 기반 여섯 구간이 디캡슐화의 88.08%를 차지하기 때문이다.

---

## 10. 재현 자료

- `profile_main.c`: KEM 반복·정확성 검증·CSV 생성
- `kem_profile.c`, `kem_profile.h`: 구간 타이머
- `analyze_profile.py`: 여러 CSV 합산 및 순위 계산
- `kem_internal_profile_detailed_2026-08-02.csv`: 독립 실행 1
- `kem_internal_profile_detailed_2026-08-02_run2.csv`: 독립 실행 2

재분석 명령:

```sh
python3 McEliece/profiling/kem_internal/analyze_profile.py \
  McEliece/profiling/kem_internal/kem_internal_profile_detailed_2026-08-02.csv \
  McEliece/profiling/kem_internal/kem_internal_profile_detailed_2026-08-02_run2.csv
```

