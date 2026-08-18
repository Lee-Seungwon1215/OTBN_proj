# OTBN 프로젝트 작업 공간

Mac의 `/Users/leeseungwon/RISC-V:OTBN` 작업 폴더를 학교 Ubuntu에서 그대로
이어가기 위한 소스 스냅샷이다.

## 폴더 구조

```text
HQC/
McEliece/
frodoKEM/
opentitan/
otbn-riscv-dataflow-textbook/
pqc-bottleneck-otbn-textbook/
pqc-otbn-codesign-textbook/
pqc-otbn-seminar/
SCHOOL_UBUNTU_OTBN_CLMUL_PROMPT.md
THREE_PQC_BOTTLENECK_RANKING_ko.md
```

`opentitan/`에는 `BN.CLMULVL4.LO/HI` ISA 정의, OTBNSim 구현, 무작위 테스트,
assembly 테스트와 `clmul256.s`가 이미 적용되어 있다. 별도의 overlay 적용이나
bootstrap 작업은 필요 없다.

## 학교 Ubuntu에서 시작

```bash
git clone https://github.com/Lee-Seungwon1215/OTBN_proj.git
cd OTBN_proj
```

그다음 [`SCHOOL_UBUNTU_OTBN_CLMUL_PROMPT.md`](SCHOOL_UBUNTU_OTBN_CLMUL_PROMPT.md)
전체를 학교 Codex에 전달한다.

## 제외된 로컬 전용 파일

- 중첩 저장소의 `.git` 메타데이터
- `node_modules`
- `.DS_Store`
- Python bytecode cache

`node_modules`에는 GitHub의 단일 파일 100MB 제한을 넘는 macOS ARM 바이너리가
포함되어 있어 제외했다. 각 웹 프로젝트에서 `npm install`로 Ubuntu용 의존성을
다시 설치할 수 있다. 실제 소스·프로파일링 결과·문서·OpenTitan 작업 트리는 원래
경로를 유지한다.
