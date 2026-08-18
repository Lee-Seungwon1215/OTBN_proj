# 학교 Ubuntu에서 OTBN CLMUL 작업을 이어가기 위한 프롬프트

아래 내용 전체를 학교 Ubuntu PC에서 사용하는 Codex/AI 에이전트에게 전달한다. 이 문서는 단순 설명문이 아니라 실제 코드 수정과 검증을 요청하는 작업 지시서다.

---

## 역할과 최종 목표

너는 OpenTitan OTBN의 ISA, Python ISS(OTBNSim), SystemVerilog RTL 및 Verilator 검증을 담당하는 하드웨어·소프트웨어 공동설계 엔지니어다.

현재 저장소에는 HQC의 GF(2) schoolbook 곱셈을 가속하기 위해 제안한 다음 두 명령어의 ISA 및 ISS 프로토타입이 들어 있다.

```text
BN.CLMULVL4.LO wrd, wrs1, wrs2, lane
BN.CLMULVL4.HI wrd, wrs1, wrs2, lane
```

이번 작업의 목표는 다음과 같다.

1. Ubuntu에서 현재 ISA/ISS 프로토타입을 실제 ELF까지 포함해 검증한다.
2. 두 명령어를 OTBN RTL에 기능적으로 구현한다.
3. standalone OTBN Verilator에서 RTL과 ISS의 결과를 교차 검증한다.
4. 기존 명령어만 사용한 기준 구현과 새 명령어 구현의 명령어 수 및 사이클 수를 비교한다.
5. 수행한 명령, 결과, 실패 원인, 성능 수치를 재현 가능한 Markdown 보고서로 남긴다.

단순히 방법만 설명하지 말고, 안전한 범위 안에서 저장소를 직접 조사하고 코드를 수정하고 테스트하라. 다만 아래 단계별 통과 조건을 지켜라.

## 반드시 유지할 설계 계약

명령어의 의미와 인코딩은 ISS 프로토타입과 동일하게 유지한다.

- `wrs1`을 64비트 lane 4개 `a[0]..a[3]`으로 해석한다.
- `wrs2`에서 즉시값 `lane`이 선택한 64비트 값 `b = wrs2[lane]`을 읽는다.
- 네 개의 `a[i] × b`를 GF(2) carry-less multiplication으로 병렬 계산한다.
- 각 곱은 128비트이며 carry propagation은 절대 하지 않는다.
- `LO`는 네 곱의 하위 64비트를 하나의 256비트 WDR에 lane별로 pack한다.
- `HI`는 네 곱의 상위 64비트를 같은 방식으로 pack한다.
- `ACC`, `MOD`, 플래그는 변경하지 않는다.
- 실행 시간과 제어 흐름은 입력 데이터와 무관해야 한다.
- WDR 결과는 기존 OTBN의 정상적인 writeback 및 integrity 경로를 사용해야 한다.
- 한 명령어는 WDR 하나만 기록한다. `LO/HI` 분할을 임의로 하나의 512비트 결과 명령어로 바꾸지 않는다.

현재 정한 인코딩은 다음과 같다.

```text
opcode     = custom4
operand    = wdr3(wrd, wrs1, wrs2)
funct3     = 3'b001
bit 30     = high_half: LO=0, HI=1
bits 29:28 = lane: 0..3
bits 31, 27:25 = 0
```

대표 raw encoding은 다음과 같다.

```text
LO lane 0..3: 0x0010115b, 0x1010115b, 0x2010115b, 0x3010115b
HI lane 0..3: 0x401011db, 0x501011db, 0x601011db, 0x701011db
```

## 현재 저장소 상태

작업 기준 OpenTitan commit은 다음과 같다.

```text
b9d39c6c9c3e10e7363613a3054132f154e21037
```

현재 프로토타입에서 수정되거나 추가된 파일은 다음과 같다.

```text
hw/ip/otbn/data/bignum-insns.yml
hw/ip/otbn/data/enc-schemes.yml
hw/ip/otbn/dv/otbnsim/sim/insn.py
hw/ip/otbn/dv/otbnsim/test/clmulvl4_test.py
hw/ip/otbn/dv/otbnsim/test/simple/insns/bn_clmulvl4.s
hw/ip/otbn/dv/otbnsim/test/simple/insns/bn_clmulvl4.exp
hw/ip/otbn/dv/otbnsim/test/simple/insns/bn_clmulvl4_schoolbook.s
hw/ip/otbn/dv/otbnsim/test/simple/insns/bn_clmulvl4_schoolbook.exp
sw/otbn/code-snippets/clmul256.s
sw/otbn/code-snippets/BUILD
sw/otbn/code-snippets/README.md
```

맥에서 이미 통과한 검증은 다음과 같다.

- ISA YAML load 및 encoding collision 검사
- LO/HI decoder 검사
- LO/HI 무작위 200건
- 전체 4×4 schoolbook schedule 무작위 200건
- 세 assembly 파일의 OTBN instruction translation
- Python compile 및 `git diff --check`

맥에는 `riscv32-unknown-elf-as`가 없어 실제 assemble/link된 ELF를 실행하는 테스트와 RTL 작업은 아직 수행하지 않았다.

## 작업 원칙

- Docker를 사용하지 않는다.
- 처음부터 full-chip OpenTitan Verilator를 빌드하지 않는다. 우선 standalone OTBN만 사용한다.
- 사용자의 기존 변경을 삭제하거나 덮어쓰지 않는다.
- `git reset --hard`, `git clean`, 강제 checkout 같은 파괴적 명령을 사용하지 않는다.
- 현재 변경분이 보이지 않으면 구현을 추측해서 다시 만들지 말고 “맥의 수정분이 학교 PC로 전달되지 않았다”고 보고하고 중단한다.
- 관련 코드를 읽고 실제 신호 경로를 확인한 뒤 RTL 구조를 결정한다.
- instruction count만 보고 속도 향상이라고 주장하지 않는다. 실제 cycle을 별도로 측정한다.
- 기능 검증과 성능 측정을 분리한다.
- 첫 RTL 목표는 기능적으로 정확한 고정시간 구현이다. timing/area 최적화는 기능 통과 뒤의 별도 단계로 다룬다.
- unrelated warning이나 기존 실패를 숨기지 말고, 이번 변경 때문에 생긴 실패와 기존 실패를 구분한다.

## 0단계: 저장소와 변경분 확인

먼저 아래 정보를 출력하고 기록한다.

```bash
pwd
git rev-parse --show-toplevel
git rev-parse HEAD
git status --short
git diff --check
uname -a
uname -m
lsb_release -a || cat /etc/os-release
df -h .
free -h
```

통과 조건:

- OpenTitan commit 또는 그 계보가 위 기준 commit과 일치해야 한다.
- 위의 CLMUL 관련 수정·추가 파일이 모두 존재해야 한다.
- `git diff --check`가 통과해야 한다.

변경분이 없다면 여기서 멈추고, 맥에서 patch·commit·USB·scp 중 한 방법으로 worktree를 옮겨야 한다고 보고하라.

## 1단계: Docker 없는 Ubuntu 환경 구축

저장소의 다음 문서를 먼저 읽고 현재 checkout에 맞는 지침을 우선한다.

```text
doc/getting_started/README.md
doc/getting_started/setup_verilator.md
hw/ip/otbn/doc/developers_guide.md
hw/ip/otbn/dv/otbnsim/README.md
```

기본 의존성과 Python 환경은 저장소 루트에서 구성한다.

```bash
sed '/^#/d' ./apt-requirements.txt | xargs sudo apt install -y
sudo apt install -y python3-venv
python3 -m venv .venv
source .venv/bin/activate
python3 -m pip install 'setuptools<66.0.0'
python3 -m pip install -r python-requirements.txt --require-hashes
```

설치 전 이미 사용할 수 있는 도구는 재설치하지 않아도 된다. 설치 명령이 현재 Ubuntu 버전에서 실패하면 원인을 기록하고, 저장소가 요구하는 버전을 만족하는 최소 변경으로 해결한다.

RISC-V GNU toolchain이 없다면 저장소의 공식 설치 스크립트를 우선 사용한다. 시스템 전체 설치 권한을 불필요하게 요구하지 않도록 저장소 내부 또는 사용자 소유 경로를 사용할 수 있다.

```bash
mkdir -p .tools
python3 util/get-toolchain.py --install-dir "$PWD/.tools/riscv" --arch "$(uname -m)"
export PATH="$PWD/.tools/riscv/bin:$PATH"
```

`.tools/riscv`가 이미 존재할 때는 삭제하지 말고 먼저 내용을 확인하고, 필요하면 스크립트의 `--update` 동작을 검토한다.

다음을 모두 확인한다.

```bash
command -v riscv32-unknown-elf-as
command -v riscv32-unknown-elf-ld
command -v riscv32-unknown-elf-objdump
riscv32-unknown-elf-as --version
python3 --version
pytest --version
fusesoc --version
ninja --version
verilator --version
python3 hw/check_tool_requirements.py verilator
```

Verilator가 없거나 최소 버전보다 낮으면 `doc/getting_started/setup_verilator.md`와 `hw/tool_requirements.py`를 기준으로 설치한다. 임의의 최신 버전으로 바꾸기 전에 이 checkout과 호환되는지 확인한다.

통과 조건:

- `riscv32-unknown-elf-as`와 `ld`가 실행된다.
- 저장소 Python requirements가 설치된다.
- FuseSoC, Ninja, Verilator가 저장소 최소 버전을 만족한다.

## 2단계: RTL 수정 전 ISA/ISS 전체 검증

먼저 새 명령어에 집중한 테스트를 실행한다.

```bash
cd hw/ip/otbn/dv/otbnsim
python3 -m pytest -vv test/clmulvl4_test.py
python3 -m pytest -vv test/simple_test.py -k 'bn_clmulvl4'
cd -
```

그다음 snippet을 실제로 build한다.

```bash
./bazelisk.sh build //sw/otbn/code-snippets:clmul256
```

Bazel target 이름이나 산출물 경로가 checkout에서 달라졌다면 `sw/otbn/code-snippets/BUILD`과 `./bazelisk.sh query`로 확인해서 정확한 target을 사용한다.

가능하면 ISS 전체 회귀 테스트도 실행한다.

```bash
cd hw/ip/otbn/dv/otbnsim
make test
cd -
```

이 단계의 통과 조건:

- `clmulvl4_test.py`의 decoder 및 무작위 400건이 모두 통과한다.
- `bn_clmulvl4.s`가 실제 ELF로 assemble/link되고 기대 레지스터 값과 instruction count 17을 만족한다.
- `bn_clmulvl4_schoolbook.s`가 실제 ELF로 assemble/link되고 다음 결과와 instruction count 31을 만족한다.

```text
w10 = 0x3f5e8362c726fb193df83175bcf93074fc9a30576503a9ce0123456789abcdef
w11 = 0x7fffffffffffffffc0e13cdd789944a5ff1ec3228766bb5b7ead20f3da098457
```

이 테스트가 실패하면 RTL을 수정하지 말고 ISA/assembler/ISS 문제를 먼저 해결한다.

## 3단계: RTL 구조 조사

RTL을 수정하기 전에 최소한 다음 파일과 연결 관계를 조사한다.

```text
hw/ip/otbn/rtl/otbn_pkg.sv
hw/ip/otbn/rtl/otbn_predecode.sv
hw/ip/otbn/rtl/otbn_decoder.sv
hw/ip/otbn/rtl/otbn_controller.sv
hw/ip/otbn/rtl/otbn_core.sv
hw/ip/otbn/rtl/otbn_alu_bignum.sv
hw/ip/otbn/rtl/otbn_mac_bignum.sv
hw/ip/otbn/rtl/otbn_rf_bignum.sv
hw/ip/otbn/otbn.core
```

특히 다음을 코드 근거와 함께 정리한다.

1. custom4 opcode와 `funct3=001`이 RTL에서 어디서 illegal instruction으로 처리되는가?
2. 두 WDR source operand의 주소와 read data는 어떤 경로로 전달되는가?
3. 기존 bignum ALU/MAC 결과가 WDR writeback mux로 들어가는 경로는 무엇인가?
4. instruction valid, commit, stall, secure wipe, integrity error가 어떻게 전파되는가?
5. 새 연산기를 ALU 내부에 넣는 것과 별도 `otbn_clmul_bignum` 모듈로 두는 것 중 어느 쪽이 기존 구조를 덜 침범하는가?
6. 조합형 4-lane CLMUL을 단일 cycle로 넣을 때 예상되는 critical path 위험은 무엇인가?

이 조사 내용을 구현 전에 짧게 보고하되, 명백한 구조가 확인되면 불필요한 사용자 질문 없이 다음 단계로 진행한다.

## 4단계: 기능 우선 RTL 구현

실제 코드 구조에 맞춰 구현하되 다음 항목은 반드시 만족한다.

### Decode 및 제어

- 위에서 고정한 raw encoding을 정확히 decode한다.
- `wrd`, `wrs1`, `wrs2`, `lane`, `high_half`를 올바르게 전달한다.
- legal instruction으로 인정하되 다른 reserved encoding까지 넓게 허용하지 않는다.
- 필요한 WDR read/write enable을 기존 명령어와 같은 방식으로 발생시킨다.
- 다른 ALU/MAC/LSU 결과와 writeback 충돌이 생기지 않도록 한다.
- illegal instruction, predecode consistency 및 secure wipe 검사를 약화하지 않는다.

### Carry-less multiplier

- 64×64→128비트 carry-less multiplier 네 개를 구현한다.
- 각 lane의 계산은 다음 수학적 정의와 동일해야 한다.

```text
product = XOR over j=0..63 of (b[j] ? (a << j) : 0)
```

- 합성 가능한 고정 반복 구조를 사용한다.
- 입력값에 따른 조기 종료나 variable-latency 동작을 사용하지 않는다.
- `LO/HI` 선택 뒤 네 개의 64비트 결과를 정확한 lane 순서로 pack한다.
- ACC와 flags는 건드리지 않는다.
- 가능하면 계산 블록을 작은 독립 모듈로 만들어 unit-level lint 및 검토가 쉽도록 한다.

### 파이프라인 결정

우선 단일-cycle 조합형 기능 구현을 검토한다. 하지만 timing이나 OTBN controller 구조상 multi-cycle이 필요하다면 임의로 지연을 끼워 넣지 말고 다음을 명시적으로 설계한다.

- start/busy/done handshake
- controller stall
- operand/result 보존
- commit 및 secure wipe 중단 동작
- ISS와 RTL의 cycle 모델 차이 처리

기능만 통과한 조합형 구현이라면 “성능 최종안”이라고 부르지 말고 timing/area 평가 전의 baseline RTL이라고 기록한다.

## 5단계: RTL 검증

먼저 lint/build를 수행하고 정확한 명령과 결과를 기록한다. 저장소 버전에 맞는 lint target을 조사해서 사용한다.

standalone OTBN Verilator build의 기본 명령은 다음과 같다.

```bash
fusesoc --cores-root=. run --target=sim --setup --build \
  --mapping=lowrisc:prim_generic:all:0.1 lowrisc:ip:otbn_top_sim \
  --make_options="-j$(nproc)"
```

직접 테스트 ELF를 만든다.

```bash
hw/ip/otbn/util/otbn_as.py \
  -o /tmp/bn_clmulvl4.o \
  hw/ip/otbn/dv/otbnsim/test/simple/insns/bn_clmulvl4.s
hw/ip/otbn/util/otbn_ld.py \
  -o /tmp/bn_clmulvl4.elf \
  /tmp/bn_clmulvl4.o

hw/ip/otbn/util/otbn_as.py \
  -o /tmp/bn_clmulvl4_schoolbook.o \
  hw/ip/otbn/dv/otbnsim/test/simple/insns/bn_clmulvl4_schoolbook.s
hw/ip/otbn/util/otbn_ld.py \
  -o /tmp/bn_clmulvl4_schoolbook.elf \
  /tmp/bn_clmulvl4_schoolbook.o
```

RTL/ISS co-simulation을 실행한다.

```bash
OTBN_SIM=./build/lowrisc_ip_otbn_top_sim_0.1/sim-verilator/Votbn_top_sim
"$OTBN_SIM" --load-elf=/tmp/bn_clmulvl4.elf
"$OTBN_SIM" --load-elf=/tmp/bn_clmulvl4_schoolbook.elf \
  --otbn-trace-file=/tmp/bn_clmulvl4_schoolbook.trace
```

실제 simulator CLI가 다르면 `--help`와 개발자 문서를 확인해 같은 의미의 정확한 옵션으로 수정한다.

필수 통과 조건:

- RTL이 새 opcode를 illegal instruction으로 처리하지 않는다.
- direct LO/HI 테스트의 `w2..w9`가 `.exp`와 일치한다.
- schoolbook 결과 `w11:w10`이 ISS 및 위 고정값과 일치한다.
- Verilator가 RTL과 ISS trace/state mismatch를 보고하지 않는다.
- lane 0, 1, 2, 3과 LO, HI가 모두 실행된다.
- 기존 OTBN smoke test가 회귀하지 않는다.

가능하면 다음 회귀도 실행한다.

```bash
hw/ip/otbn/dv/smoke/run_smoke.sh
hw/ip/otbn/dv/smoke/run_smoke.sh vectorized
```

## 6단계: baseline과 성능 비교

새 명령어의 효과를 과장하지 않도록 동일한 256×256 GF(2) polynomial multiplication을 기존 OTBN 명령어만으로 계산하는 기준 assembly를 추가한다.

요구사항:

- 입력 및 출력 형식은 `clmul256.s`와 동일하게 한다.
- 같은 고정 test vector를 사용한다.
- 데이터 의존 branch나 table lookup 없이 고정시간 schoolbook/shift-XOR 방식으로 작성한다.
- 기준 코드와 새 명령어 코드가 정확히 같은 512비트 결과를 내는지 확인한다.
- ISS 통계와 RTL trace에서 instruction 및 cycle을 측정한다.

ISS 통계는 assemble/link된 ELF에 대해 다음 형태로 수집할 수 있다.

```bash
hw/ip/otbn/dv/otbnsim/standalone.py --dump-stats=- program.elf
```

최소한 다음 표를 작성한다.

| 구현 | 동적 명령어 수 | RTL cycle | CLMUL 명령어 수 | 결과 일치 |
|---|---:|---:|---:|---|
| 기존 OTBN 명령어 baseline | 측정값 | 측정값 | 0 | Yes/No |
| `BN.CLMULVL4.LO/HI` | 측정값 | 측정값 | 8 | Yes/No |

현재 custom schoolbook 커널은 operand load 이후 커널 본체 기준으로 커스텀 CLMUL 8개와 결과 조립용 기존 명령어를 사용한다. 그러나 최종 수치는 실제 trace에서 다시 세어라.

합성 도구가 준비되어 있지 않다면 area, gate count, LUT, Fmax를 추측하지 않는다. 가능할 때만 같은 조건의 합성 결과로 다음을 추가한다.

- 추가 area 또는 cell/LUT 수
- critical path 변화
- 최대 주파수 변화
- 조합형 4-lane 구조와 향후 multi-cycle/공유 multiplier 구조의 trade-off

## 7단계: 결과 보고서

저장소 루트에 다음 파일을 작성한다.

```text
OTBN_CLMULVL4_UBUNTU_RESULTS.md
```

보고서에는 다음을 포함한다.

1. OS, CPU architecture, RAM, 남은 disk
2. OpenTitan commit과 작업 시작 전 `git status`
3. 설치한 핵심 tool과 버전
4. 변경한 파일과 각 파일의 역할
5. instruction encoding 및 RTL 데이터 경로 요약
6. 실행한 테스트 명령과 PASS/FAIL
7. ISS 기대값과 RTL 결과
8. baseline/custom instruction·cycle 비교표
9. 실패하거나 실행하지 못한 항목과 정확한 이유
10. timing/area를 아직 측정하지 않았다면 그 사실
11. 다음 단계: HQC의 실제 `vect_mul` 호출 경로에 적용하기 전에 필요한 작업

마지막 응답은 다음 형식으로 간결하게 작성한다.

```text
완료한 내용:
- ...

검증 결과:
- ...

성능 비교:
- baseline ... instructions / ... cycles
- custom ... instructions / ... cycles

남은 위험 또는 다음 단계:
- ...
```

## 완료 판정

다음 조건을 모두 만족해야 “RTL 구현 완료”라고 말할 수 있다.

- ISA/ISS ELF 테스트 통과
- SystemVerilog decode 및 datapath 구현
- standalone OTBN Verilator build 통과
- direct LO/HI RTL/ISS co-simulation 통과
- 256×256 schoolbook RTL/ISS co-simulation 통과
- 기존 smoke regression 통과
- baseline과 custom의 실제 instruction/cycle 결과 기록
- `OTBN_CLMULVL4_UBUNTU_RESULTS.md` 작성

하나라도 빠지면 완료라고 하지 말고, 완료된 범위와 막힌 지점을 구분해서 보고하라.
