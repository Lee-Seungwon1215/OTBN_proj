# Classic McEliece-348864 프로파일링 결과

측정일: 2026-08-18  
대상 구현: `crypto_kem/348864/vec`  
실행 환경: Apple Silicon ARM64, Apple clang 21.0.0, 기존 계측 빌드 `-O2`

## 1. 결론

Classic McEliece는 KEM 단계마다 병목의 성격이 다르다.

| 단계 | 전체 시간 | 가장 큰 병목 | 비중 |
|---|---:|---|---:|
| 키 생성 | 30.292 ms | `pk_gen`의 피벗 탐색·전방·후방 소거 | 전체 KeyGen의 **59.60%** |
| 캡슐화 | 9.382 µs | syndrome 공개키 스캔 | Encaps의 **47.52%** |
| 디캡슐화 | 117.856 µs | `vec_mul` 기반 BM·FFT·batch inverse 연산군 | Decaps의 **87.91%** |

따라서 McEliece 전체를 하나의 명령어로 최적화하기는 어렵다.

```text
KeyGen : 큰 행렬의 masked AND-XOR + 402 KiB 수준의 작업 집합
Encaps : 261 KiB 공개키 스트리밍 + GF(2) 내적/parity
Decaps : bitsliced GF(2^12) vec_mul + FFT/FFT^T + BM
```

OTBN용 계산 명령어를 먼저 설계할 대상을 하나만 고르면 **디캡슐화의 bitsliced `vec_mul`**이 가장 명확하다. 반면 키 생성과 캡슐화는 연산기뿐 아니라 OTBN DMEM과 데이터 전송 구조를 먼저 해결해야 한다.

## 2. 측정 방법과 정확성

### 캡슐화·디캡슐화

- 9 trials × trial당 10,000회 = 90,000회 측정
- 워밍업 200회
- 유효한 ciphertext를 사용한 Encaps/Decaps round-trip
- 워밍업 포함 **90,200회 공유키 일치**
- `CLOCK_MONOTONIC` 함수 경계 계측
- 원시 결과: `kem_internal/kem_internal_profile_2026-08-18.csv`

### 키 생성

- 11 trials × trial당 30회 = 성공 키 330개 측정
- 워밍업 10회
- 각 키에 대해 Encaps/Decaps까지 실행하여 정확성 확인
- 워밍업 포함 **340회 KEM round-trip 일치**
- 성공 키 330개를 얻기 위해 `pk_gen()` 총 1,131회 호출
- 원시 결과: `pk_gen_internal/pk_gen_profile_2026-08-18.csv`

짧은 함수에 타이머가 들어가므로 절대시간에는 계측 오버헤드가 포함된다. 그러나 상위 병목 순위와 비중은 2026-08-02의 독립 측정 결과와 일치한다.

## 3. 키 생성 프로파일

### 3.1 전체 KeyGen

| 지표 | 결과 |
|---|---:|
| 전체 KeyGen | 30.292 ms/key |
| trial 중앙값 | 29.293 ms/key |
| 키 하나당 `pk_gen` 총시간 | 22.318 ms |
| 전체 KeyGen 중 `pk_gen` | **73.67%** |
| 성공 키 하나당 `pk_gen` 호출 | 3.427회 |
| 실패 호출 비율 | **70.82%** |
| 피벗 실패 | 797회 |
| 중복 순열 실패 | 4회 |

대부분의 실패 호출이 피벗 검사 도중 끝난다. 따라서 성공한 `pk_gen` 하나만 볼 때와 실제 키 하나를 얻을 때의 누적 병목 순위가 달라진다.

### 3.2 실패·재시도를 포함한 실제 `pk_gen` 누적 비중

| 순위 | 구간 | 시간/key | `pk_gen` 비중 | 전체 KeyGen 비중 |
|---:|---|---:|---:|---:|
| 1 | 피벗 탐색·조건부 행 결합 | 8.651 ms | **38.76%** | **28.55%** |
| 2 | 전방 소거 | 8.495 ms | **38.06%** | **28.04%** |
| 3 | 선형맵 적용 | 3.224 ms | **14.44%** | **10.64%** |
| 4 | 후방 소거 | 0.914 ms | **4.09%** | **3.01%** |
| 5 | 순열 정렬 | 0.407 ms | 1.82% | 1.34% |

피벗 탐색·전방 소거만 합쳐도 `pk_gen`의 **76.82%**, 전체 KeyGen의 **56.59%**다. 후방 소거까지 포함한 가우스 소거군은 `pk_gen`의 **80.91%**, 전체 KeyGen의 **59.60%**다.

### 3.3 성공한 `pk_gen()` 한 번의 내부 비중

| 순위 | 구간 | 시간/call | 성공 `pk_gen` 비중 |
|---:|---|---:|---:|
| 1 | 선형맵 적용 | 3.224 ms | **33.53%** |
| 2 | 피벗 탐색 | 2.518 ms | **26.20%** |
| 3 | 전방 소거 | 2.481 ms | **25.81%** |
| 4 | 후방 소거 | 0.914 ms | **9.51%** |
| 5 | 오른쪽 행렬 생성 | 0.184 ms | 1.91% |

성공 호출만 보면 단일 구간 1위는 선형맵 적용이다. 하지만 실제 KeyGen에서는 실패 호출의 피벗 탐색과 전방 소거가 반복되므로 이 둘이 누적 1순위가 된다.

### 3.4 연산 구조

주요 inner loop는 다음 형태다.

```c
dst[c] ^= src[c] & mask;
```

`mask`는 피벗 bit에서 만든 all-zero 또는 all-one 64비트 값이다. 성공 호출당 주요 64비트 masked-XOR 작업량은 다음과 같다.

| 구간 | 64비트 masked-XOR 수 |
|---|---:|
| 선형맵 적용 | 25,362,432 |
| 피벗 탐색 | 7,068,672 |
| 전방 소거 | 7,068,672 |
| 후방 소거 | 3,534,336 |

`mat[768][55]`와 `ops[768][12]`를 합치면 약 402 KiB다. 현재 OTBN DMEM은 32 KiB이므로 전체 행렬을 한 번에 넣을 수 없다.

## 4. 캡슐화 프로파일

전체 캡슐화 시간은 9.382 µs/op이고 trial 중앙값은 9.210 µs/op이다.

| 순위 | 구간 | 시간/op | Encaps 비중 |
|---:|---|---:|---:|
| 1 | syndrome 공개키 스캔 | 4.458 µs | **47.52%** |
| 2 | 오류벡터 materialize | 1.819 µs | **19.38%** |
| 3 | 오류 난수·범위 필터 | 0.950 µs | **10.12%** |
| 4 | 오류 위치 정렬·중복 검사 | 0.949 µs | **10.12%** |
| 5 | SHAKE256 공유키 생성 | 0.944 µs | **10.06%** |

오류벡터 생성 세 구간의 합은 **39.62%**다. 단일 구간 1위는 syndrome이지만 오류 생성 전체와의 차이는 약 7.9%p다.

syndrome 계산의 정적 구조는 다음과 같다.

- 공개키: `768 × 340 = 261,120 bytes`
- 행마다 42개의 64비트 `AND-XOR`와 32비트 tail
- 전체 64비트 `AND-XOR`: `768 × 42 = 32,256회`
- 각 행의 누적값을 shift-XOR로 parity reduction

즉 캡슐화는 단순 계산량뿐 아니라 공개키 261 KiB 전체를 매번 읽는 메모리 스트리밍 문제다.

## 5. 디캡슐화 프로파일

전체 디캡슐화 시간은 117.856 µs/op이고 trial 중앙값은 116.654 µs/op이다.

| 순위 | 구간 | 시간/op | Decaps 비중 |
|---:|---|---:|---:|
| 1 | Berlekamp–Massey | 29.006 µs | **24.61%** |
| 2 | 재암호화 FFT^T | 17.093 µs | **14.50%** |
| 3 | syndrome FFT^T | 16.609 µs | **14.09%** |
| 4 | scaling FFT | 13.719 µs | **11.64%** |
| 5 | locator FFT | 13.616 µs | **11.55%** |
| 6 | batch inverse | 13.572 µs | **11.52%** |
| 7 | weight check | 5.015 µs | **4.26%** |
| 8 | 역 Benes | 3.669 µs | **3.11%** |
| 9 | 정 Benes | 3.599 µs | **3.05%** |
| 10 | SHAKE256 | 0.937 µs | **0.80%** |

상위 여섯 GF/FFT/BM 구간의 합은 **87.91%**다. Benes 왕복은 6.16%, weight check는 4.26%다.

### 5.1 공통 primitive: `vec_mul`

`vec_mul()`은 12개의 64비트 bit-plane으로 표현한 64개의 GF(2^12) 원소를 병렬 곱한다.

```text
입력 f[0..11], g[0..11]
  → 12×12 = 144개의 64비트 AND-XOR 곱항
  → 기약다항식 reduction
  → 출력 h[0..11]
```

디캡슐화 한 번의 정적 `vec_mul` 호출 수는 1,389회다.

| 구간 | `vec_mul` 호출 |
|---|---:|
| Berlekamp–Massey | 385 |
| syndrome FFT^T | 208 |
| 재암호화 FFT^T | 208 |
| scaling FFT | 197 |
| locator FFT | 197 |
| batch inverse | 194 |

따라서 디캡슐화 한 번에 `vec_mul` 내부 곱항만 `1,389 × 144 = 200,016`개의 64비트 bitwise AND가 필요하다. 정적 호출 순서와 실측 순위도 거의 일치한다.

## 6. OTBN 명령어 관점의 판정

### 6.1 HQC용 `BN.CLMULVL4`를 그대로 사용할 수 있는가?

그대로 사용할 수 없다.

- HQC 명령은 각 64비트 값을 하나의 GF(2) polynomial로 보고 bit 위치 사이를 섞는 carry-less multiply를 수행한다.
- McEliece `vec_mul`의 각 64비트 bit 위치는 서로 독립적인 GF(2^12) 원소다.
- McEliece의 핵심 곱항은 64비트 전체의 **bitwise AND**이며 bit 위치가 서로 섞이면 안 된다.

따라서 McEliece는 HQC와 다른 연산 엔진이 필요하다.

### 6.2 후보 우선순위

#### 후보 1: bitsliced GF(2^12) multiply 가속

디캡슐화의 87.91%에 공통으로 작용하므로 계산 명령어 후보 중 우선순위가 가장 높다.

- 12개 bit-plane은 256비트 WDR 3개에 pack 가능
- 두 입력은 총 WDR 6개, 출력은 WDR 3개가 필요
- 한 명령어의 일반적인 2-read/1-write 구조로는 전체 `vec_mul`을 즉시 끝낼 수 없음
- register-group을 사용하는 multi-cycle 명령 또는 작은 AND-XOR 누산 primitive로 나누는 설계가 필요

가칭 후보는 `BN.GFMUL12`이지만, encoding을 정하기 전에 register-group 규칙, latency, stall, writeback을 먼저 설계해야 한다.

#### 후보 2: masked row XOR

키 생성의 inner loop를 겨냥한다.

```text
dst_wdr ← dst_wdr XOR (src_wdr AND replicated_mask)
```

그러나 세 WDR operand를 동시에 요구할 수 있고, 402 KiB 작업 집합이 32 KiB DMEM을 크게 넘는다. 명령어보다 행 타일링과 DMA/host 전송 구조를 먼저 정해야 한다.

#### 후보 3: GF(2) dot-product/parity accumulate

캡슐화 syndrome을 겨냥한다.

```text
acc ← acc XOR (pk_wdr AND error_wdr)
result_bit ← parity(acc)
```

공개키 261 KiB 스트리밍 비용을 포함하지 않으면 가속 효과를 과대평가하게 된다. OTBN 단독 명령어보다 메모리 공급 구조와 함께 평가해야 한다.

## 7. 다음 단계

다음 설계 단계는 디캡슐화의 `vec_mul` 하나를 OTBN assembly로 옮겨 baseline instruction/cycle을 측정하는 것이다.

1. 12개의 64비트 bit-plane을 WDR 3개에 pack한다.
2. 기존 `BN.AND`, `BN.XOR`, load/store만으로 `vec_mul` reference kernel을 작성한다.
3. Python GF(2^12) reference와 무작위 입력으로 결과를 비교한다.
4. instruction trace에서 AND, XOR, load/store 및 결과 조립 비중을 측정한다.
5. 그 결과를 바탕으로 전체 `BN.GFMUL12`과 작은 fused primitive 중 하나를 선택한다.

현재 단계에서는 **병목은 확인됐지만 새 McEliece 명령어의 encoding은 아직 확정하지 않는다.**
