"use client";

import { useState } from "react";

type AlgoKey = "frodo" | "hqc" | "mceliece";

const algos = {
  frodo: {
    name: "FrodoKEM",
    tag: "LWE · dense matrix",
    color: "coral",
    oneLine: "SHAKE로 큰 행렬을 만들고, 작은 정수들을 반복 곱한다.",
    flow: ["seed", "SHAKE", "A 행", "16-bit MAC", "암호문"],
    repeats: ["A 행 640회", "큰 MAC 3,276,800회 / 단계", "Keccak round 122,880회 / 단계"],
    pick: "SHAKE / Keccak",
    share: "89.4%",
    otbn: "OTBN↔KMAC 스트리밍",
    risc: "RISC-V가 KEM·메모리·호출 제어",
    warning: "A 전체를 DMEM에 저장하지 않는다.",
  },
  hqc: {
    name: "HQC",
    tag: "code-based · bit polynomial",
    color: "violet",
    oneLine: "긴 비트열을 shift·XOR하며 자리올림 없이 곱한다.",
    flow: ["긴 비트열", "CLMUL", "XOR 결합", "순환 축약", "암호문"],
    repeats: ["vect_mul: KeyGen 1회", "Encaps 2회", "Decaps 3회"],
    pick: "GF(2) 순환곱 vect_mul",
    share: "95.9–98.8%",
    otbn: "BN.CLMULQACC 확장",
    risc: "Zbc/Zvbc가 비교 기준선",
    warning: "커널 전체를 한 번에 offload한다.",
  },
  mceliece: {
    name: "Classic McEliece",
    tag: "code-based · binary matrix",
    color: "cyan",
    oneLine: "큰 이진 행렬을 만들고, 행을 AND·XOR하며 오류를 복호한다.",
    flow: ["난수·정렬", "행렬 생성", "AND+XOR", "FFT·BM", "검증"],
    repeats: ["키 생성 기대 시도 3.47회", "256-bit 행 갱신 7,363,200회 / 완전 시도", "sort compare-swap 15,359회"],
    pick: "pk_gen masked row update",
    share: "잠정 1순위",
    otbn: "BN.AND+XOR / BN.XORAND",
    risc: "큰 메모리·타일 전송 제어",
    warning: "시간 비중 profiling 후 확정한다.",
  },
} as const;

const toc = [
  ["00", "전체 지도", "map"],
  ["01", "세 알고리즘", "algorithms"],
  ["02", "측정과 순위", "profiles"],
  ["03", "최적화 1순위", "priorities"],
  ["04", "RISC-V 교과서", "riscv"],
  ["05", "OTBN 작동 원리", "otbn"],
  ["06", "하드웨어 구조", "hardware"],
  ["07", "알고리즘 적용", "blueprints"],
  ["08", "데이터 이동", "movement"],
  ["09", "보안·검증", "security"],
  ["10", "구현 로드맵", "roadmap"],
] as const;

function ChapterTitle({ no, kicker, title }: { no: string; kicker: string; title: string }) {
  return (
    <div className="chapter-title">
      <span>{no}</span>
      <div><p>{kicker}</p><h2>{title}</h2></div>
    </div>
  );
}

function Arrow({ label }: { label?: string }) {
  return <div className="arrow" aria-hidden="true"><i>→</i>{label && <small>{label}</small>}</div>;
}

function AlgoFlow({ algo }: { algo: AlgoKey }) {
  const item = algos[algo];
  return (
    <div className={`algo-flow theme-${item.color}`} key={algo}>
      {item.flow.map((step, index) => (
        <div className="flow-unit" key={`${algo}-${index}`}>
          <div className="flow-chip"><b>{String(index + 1).padStart(2, "0")}</b><span>{step}</span></div>
          {index < item.flow.length - 1 && <Arrow />}
        </div>
      ))}
    </div>
  );
}

export default function Home() {
  const [activeAlgo, setActiveAlgo] = useState<AlgoKey>("frodo");
  const [profileAlgo, setProfileAlgo] = useState<AlgoKey>("frodo");
  const [otbnStep, setOtbnStep] = useState(0);
  const active = algos[activeAlgo];

  return (
    <main id="top">
      <header className="topbar">
        <a href="#top" className="brand" aria-label="맨 위로">
          <span className="brand-mark">PQ</span>
          <span><b>PQC Co-Design Atlas</b><small>RISC-V · OTBN · KMAC</small></span>
        </a>
        <nav aria-label="주요 장"><a href="#algorithms">알고리즘</a><a href="#riscv">RISC-V</a><a href="#otbn">OTBN</a><a href="#blueprints">적용 설계</a></nav>
        <span className="version">FIELD BOOK · 2026</span>
      </header>

      <section className="hero">
        <div className="hero-copy">
          <p className="eyebrow">POST-QUANTUM CRYPTOGRAPHY · HARDWARE / SOFTWARE CO-DESIGN</p>
          <h1>세 알고리즘을<br /><em>OTBN에 태우는 법</em></h1>
          <p>연산 비중에서 시작해 RISC‑V, OTBN, KMAC의 역할과 커스텀 명령 설계까지 한 번에 연결한다.</p>
          <div className="hero-pills"><span>수학식 최소화</span><span>실측·반복 횟수</span><span>그림 중심</span></div>
          <a className="start-button" href="#map">지도부터 보기 <b>↓</b></a>
        </div>
        <div className="hero-board" aria-label="RISC-V, OTBN, KMAC 시스템 구조">
          <div className="board-label"><span>SYSTEM MAP</span><b>한 칩, 세 역할</b></div>
          <div className="system-orbit">
            <div className="orbit-node rv-node"><i>RV</i><b>RISC-V</b><small>지휘 · 메모리</small></div>
            <div className="orbit-link link-one"><span className="moving-dot" /><em>APP + DATA</em></div>
            <div className="orbit-node bn-node"><i>BN</i><b>OTBN</b><small>256-bit 계산</small></div>
            <div className="orbit-link link-two"><span className="moving-dot" /><em>MESSAGE + DIGEST</em></div>
            <div className="orbit-node km-node"><i>K</i><b>KMAC</b><small>SHA3 · SHAKE</small></div>
          </div>
          <div className="hero-legend"><span><i className="dot lime" />프로그램 실행</span><span><i className="dot coral" />고정 기능 회로</span><span><i className="dot blue" />데이터 이동</span></div>
        </div>
      </section>

      <div className="toc-strip" aria-label="교재 목차">
        {toc.map(([no, label, id]) => <a href={`#${id}`} key={id}><span>{no}</span>{label}</a>)}
      </div>

      <div className="book">
        <aside className="rail">
          <p>READING PATH</p>
          {toc.map(([no, label, id]) => <a href={`#${id}`} key={id}><span>{no}</span>{label}</a>)}
          <div className="rail-note"><b>읽는 규칙</b><span>실측 %</span><span className="modeled">정적 횟수</span><small>서로 섞지 않는다.</small></div>
        </aside>

        <article className="content">
          <section className="chapter" id="map">
            <ChapterTitle no="00" kicker="THE WHOLE PICTURE" title="계산과 이동을 한 장에 놓자" />
            <div className="big-map">
              <div className="world host-world">
                <p>HOST WORLD</p><h3>RISC-V</h3>
                <div className="world-stack"><span>C / C++</span><span>Compiler</span><span>RISC-V ISA</span><span>Cache · RAM · Bus</span></div>
                <small>전체 KEM · 큰 데이터 · 주변장치</small>
              </div>
              <div className="bridge"><i>⇄</i><b>Host ↔ DMEM</b><span>복사 · 시작 · 대기 · 회수</span></div>
              <div className="world secure-world">
                <p>CRYPTO WORLD</p><h3>OTBN</h3>
                <div className="world-stack"><span>OTBN .s</span><span>32-bit GPR</span><span>256-bit WDR</span><span>Local IMEM · DMEM</span></div>
                <small>격리된 wide 암호 커널</small>
              </div>
              <div className="bridge short"><i>⇄</i><b>OTBN ↔ KMAC</b><span>입력 · digest · 상태</span></div>
              <div className="world kmac-world">
                <p>FIXED ENGINE</p><h3>KMAC</h3>
                <div className="keccak-disc">1600<span>bit state</span></div>
                <small>SHA3 · SHAKE · KMAC</small>
              </div>
            </div>
            <div className="map-rule"><span>핵심</span><b>RISC-V는 지휘자</b><i>+</i><b>OTBN은 계산 작업자</b><i>+</i><b>KMAC은 SHAKE 전용 기계</b></div>
          </section>

          <section className="chapter" id="algorithms">
            <ChapterTitle no="01" kicker="NO EQUATIONS, JUST WORK" title="세 알고리즘은 무엇을 반복할까?" />
            <div className="algo-selector" role="tablist" aria-label="알고리즘 선택">
              {(Object.keys(algos) as AlgoKey[]).map((key) => <button type="button" role="tab" aria-selected={activeAlgo === key} className={activeAlgo === key ? "active" : ""} onClick={() => setActiveAlgo(key)} key={key}>{algos[key].name}</button>)}
            </div>
            <div className={`algo-stage border-${active.color}`} key={activeAlgo}>
              <div className="algo-intro"><span>{active.tag}</span><h3>{active.name}</h3><p>{active.oneLine}</p></div>
              <AlgoFlow algo={activeAlgo} />
              <div className="repeat-board">
                <p>REPEAT COUNTER</p>
                {active.repeats.map((item, i) => <div key={`${activeAlgo}-repeat-${i}`}><span>{String(i + 1).padStart(2, "0")}</span><b>{item}</b></div>)}
              </div>
            </div>
            <div className="three-summaries">
              <div className="sum-frodo"><span>F</span><b>많은 작은 정수</b><small>SHAKE + 16-bit MAC</small></div>
              <div className="sum-hqc"><span>H</span><b>아주 긴 비트열</b><small>CLMUL + XOR + shift</small></div>
              <div className="sum-mc"><span>M</span><b>큰 이진 행렬</b><small>AND + XOR + decoder</small></div>
            </div>
          </section>

          <section className="chapter" id="profiles">
            <ChapterTitle no="02" kicker="MEASURE BEFORE DESIGN" title="연산 비중을 숫자로 세운다" />
            <div className="measurement-rule">
              <div><span className="badge measured">실측</span><b>시간 비중</b><small>같은 실행에서 측정</small></div>
              <div><span className="badge counted">정적</span><b>반복 횟수</b><small>연산 단위가 다르면 시간과 다름</small></div>
              <div><span className="badge modeled">모델</span><b>예상 cycle</b><small>가정을 반드시 표시</small></div>
            </div>
            <div className="profile-tabs" role="tablist" aria-label="프로파일 선택">
              {(Object.keys(algos) as AlgoKey[]).map((key) => <button type="button" role="tab" aria-selected={profileAlgo === key} className={profileAlgo === key ? "active" : ""} onClick={() => setProfileAlgo(key)} key={key}>{algos[key].name}</button>)}
            </div>

            <div className="profile-stage" key={profileAlgo}>
              {profileAlgo === "frodo" && <>
                <div className="profile-head"><div><span className="badge measured">FAST_GENERIC · 1:1:1</span><h3>FrodoKEM-640-SHAKE</h3></div><strong>4.163 ms</strong></div>
                <div className="stacked-bar" aria-label="FrodoKEM 연산 비중"><span className="seg shake" style={{ width: "89.4%" }}>89.4</span><span className="seg mac" style={{ width: "5%" }}>5.0</span><span className="seg pack" style={{ width: "3%" }} /><span className="seg sample" style={{ width: "1.7%" }} /><span className="seg other" style={{ width: ".9%" }} /></div>
                <div className="rank-list"><div><i>1</i><b>SHAKE / Keccak</b><strong>89.4%</strong></div><div><i>2</i><b>16-bit 행렬 MAC</b><strong>5.0%</strong></div><div><i>3</i><b>Pack / unpack</b><strong>3.0%</strong></div><div><i>4</i><b>CDF sampler</b><strong>1.7%</strong></div><div><i>5</i><b>검증·기타</b><strong>≈1.0%</strong></div></div>
              </>}
              {profileAlgo === "hqc" && <>
                <div className="profile-head"><div><span className="badge measured">HQC-1 / 3 / 5 · ARM64 ref</span><h3>HQC vect_mul 지배 구간</h3></div><strong>95.9–98.8%</strong></div>
                <div className="range-chart"><div className="range-track"><span className="range-fill" /><i className="min-mark">95.9</i><i className="max-mark">98.8</i></div><div className="range-axis"><span>0%</span><span>50%</span><span>100%</span></div></div>
                <div className="hqc-grid"><div><span>HQC-1</span><b>97.8</b><b>97.7</b><b>95.9</b></div><div><span>HQC-3</span><b>98.3</b><b>98.3</b><b>97.4</b></div><div><span>HQC-5</span><b>98.8</b><b>98.7</b><b>98.0</b></div><div className="hqc-label"><span>SET</span><small>KeyGen</small><small>Encaps</small><small>Decaps</small></div></div>
                <div className="rank-list"><div><i>1</i><b>GF(2) 순환곱 vect_mul</b><strong>95.9–98.8%</strong></div><div><i>2</i><b>RS/RM decoder</b><strong>약 0.7–1.8%</strong></div><div><i>3</i><b>고정 무게 sampling</b><strong>약 0.6–1.3%</strong></div><div><i>4</i><b>SHA3 / SHAKE</b><strong>최대 약 1.0%</strong></div></div>
              </>}
              {profileAlgo === "mceliece" && <>
                <div className="profile-head"><div><span className="badge counted">348864 / AVX · 완전한 키 생성 시도</span><h3>Classic McEliece 반복 규모</h3></div><strong>실측 보강 필요</strong></div>
                <div className="log-bars"><div><span>256-bit 행 갱신</span><i style={{ width: "100%" }} /><b>7,363,200</b></div><div><span>sort compare-swap</span><i style={{ width: "58%" }} /><b>15,359</b></div><div><span>vec_mul_gf_using_64</span><i style={{ width: "54%" }} /><b>8,254</b></div><div><span>vec256_mul</span><i style={{ width: "38%" }} /><b>980</b></div><div><span>Keccak-f</span><i style={{ width: "24%" }} /><b>125</b></div><div><span>vec_GF_mul</span><i style={{ width: "19%" }} /><b>63</b></div></div>
                <div className="caution"><b>!</b><span>로그 스케일 · 반복 단위가 다르다</span><p>행 갱신을 잠정 1순위로 두되 cycle profiling으로 확정한다.</p></div>
              </>}
            </div>
          </section>

          <section className="chapter" id="priorities">
            <ChapterTitle no="03" kicker="PICK ONLY ONE" title="각 알고리즘의 최적화 1순위" />
            <div className="priority-grid">
              {(Object.keys(algos) as AlgoKey[]).map((key, i) => {
                const a = algos[key];
                return <div className={`priority-card p-${a.color}`} key={key}><div className="priority-top"><span>0{i + 1}</span><small>{a.name}</small></div><strong>{a.share}</strong><h3>{a.pick}</h3><div className="priority-path"><span>RISC-V</span><i>→</i><b>{a.otbn}</b></div><p>{a.warning}</p></div>;
              })}
            </div>
            <div className="selection-rule"><span>선정 공식</span><div><b>시간 비중</b><i>×</i><b>세 단계 재사용</b><i>×</i><b>규칙적 데이터</b><i>÷</i><b>전송·면적</b></div></div>
          </section>

          <section className="chapter" id="riscv">
            <ChapterTitle no="04" kicker="RISC-V MINI TEXTBOOK" title="RISC-V는 ISA이자 시스템의 중심이다" />
            <div className="isa-layers">
              <div className="layer source"><span>01</span><b>C / C++</b><small>알고리즘·호스트 제어</small></div><Arrow label="compiler" /><div className="layer asm"><span>02</span><b>RISC-V Assembly</b><small>add · load · clmul · vector</small></div><Arrow label="encoding" /><div className="layer rtl"><span>03</span><b>CPU RTL</b><small>decode · ALU · pipeline</small></div><Arrow label="execute" /><div className="layer silicon"><span>04</span><b>Hardware</b><small>register · cache · bus</small></div>
            </div>
            <div className="extension-board">
              <div className="ext-core"><p>BASE</p><b>RV32I / RV64I</b><span>정수·분기·메모리</span></div>
              <div className="ext-item"><p>M</p><b>MUL / DIV</b><span>일반 정수 곱셈</span></div>
              <div className="ext-item"><p>B · Zbc</p><b>bitmanip / CLMUL</b><span>HQC 기준선</span></div>
              <div className="ext-item"><p>V · Zvbc</p><b>vector / vector CLMUL</b><span>여러 lane 병렬</span></div>
              <div className="ext-custom"><p>CUSTOM</p><b>직접 정의</b><span>opcode · RTL · toolchain</span></div>
            </div>
            <div className="risc-otbn-compare">
              <div><span>RISC-V</span><h3>메인 CPU</h3><ul><li>시스템 RAM·cache</li><li>C compiler·ABI</li><li>표준 확장 + custom</li><li>전체 KEM 실행</li></ul></div>
              <div className="versus"><i>+</i><small>대체 관계가 아님</small></div>
              <div><span>OTBN</span><h3>암호 코프로세서</h3><ul><li>로컬 IMEM·DMEM</li><li>OTBN 전용 assembly</li><li>32 × 256-bit WDR</li><li>선택한 kernel 실행</li></ul></div>
            </div>
            <div className="code-bridge">
              <div><span>HOST · C</span><pre>{`otbn_load_app(app);\notbn_write(input);\notbn_execute();\notbn_read(output);`}</pre></div>
              <Arrow label="job" />
              <div><span>OTBN · .s</span><pre>{`bn.lid  x2, 0(x10)\nbn.and  w4, w2, w3\nbn.xor  w0, w0, w4\nbn.sid  x5, 0(x12)\necall`}</pre></div>
            </div>
          </section>

          <section className="chapter" id="otbn">
            <ChapterTitle no="05" kicker="PROGRAMMABLE CRYPTO ENGINE" title="OTBN은 여섯 단계로 움직인다" />
            <div className="step-picker" role="tablist" aria-label="OTBN 실행 단계">
              {["앱 적재", "입력 복사", "실행 요청", "WDR 계산", "결과 저장", "완료·삭제"].map((label, i) => <button type="button" role="tab" aria-selected={otbnStep === i} className={otbnStep === i ? "active" : ""} onClick={() => setOtbnStep(i)} key={`step-${i}`}><span>{i + 1}</span>{label}</button>)}
            </div>
            <div className="otbn-step-stage" key={otbnStep}>
              <div className="step-graphic">
                <div className={`step-box ${otbnStep === 0 ? "hot" : ""}`}><span>RISC-V</span><b>OTBN app</b></div><Arrow /><div className={`step-box ${otbnStep <= 2 ? "hot" : ""}`}><span>IMEM / DMEM</span><b>local state</b></div><Arrow /><div className={`step-box ${otbnStep === 3 ? "hot" : ""}`}><span>WDR + BN unit</span><b>256-bit compute</b></div><Arrow /><div className={`step-box ${otbnStep >= 4 ? "hot" : ""}`}><span>RISC-V</span><b>result / status</b></div>
              </div>
              <div className="step-caption"><b>{String(otbnStep + 1).padStart(2, "0")}</b><p>{[
                "RISC-V가 OTBN 전용 프로그램을 IMEM에 넣는다.",
                "입력과 상수를 DMEM에 배치한다.",
                "호스트가 EXECUTE를 요청하고 완료를 기다린다.",
                "OTBN이 .s를 실행하며 DMEM↔WDR 사이에서 계산한다.",
                "결과를 DMEM에 쓰고 호스트가 회수한다.",
                "상태를 확인하고 비밀 WDR·DMEM을 지운다.",
              ][otbnStep]}</p></div>
            </div>
            <div className="register-board">
              <div><p>CONTROL</p><b>x0–x31</b><span>32-bit GPR</span><small>주소 · loop · branch</small></div>
              <div className="wide"><p>CRYPTO DATA</p><b>w0–w31</b><span>256-bit WDR</span><small>BN.ADD · XOR · MULQACC</small></div>
              <div><p>LOCAL MEMORY</p><b>IMEM / DMEM</b><span>격리된 저장소</span><small>app · operand · scratch</small></div>
            </div>
          </section>

          <section className="chapter" id="hardware">
            <ChapterTitle no="06" kicker="HARDWARE ANATOMY" title="커스텀 명령은 어디에 들어갈까?" />
            <div className="hardware-map">
              <div className="hw-host"><span>HOST</span><b>RISC-V CPU</b><small>cache · RAM · bus</small></div>
              <div className="hw-bus"><i>⇄</i><b>register / memory window</b></div>
              <div className="hw-otbn">
                <div className="hw-head"><span>OTBN</span><b>Controller + Decoder</b></div>
                <div className="hw-memory"><div><b>IMEM</b><span>instruction</span></div><div><b>DMEM</b><span>operand·scratch</span></div></div>
                <div className="hw-registers"><div><b>GPR</b><span>32 × 32-bit</span></div><div><b>WDR</b><span>32 × 256-bit</span></div></div>
                <div className="hw-units"><div><b>BN ALU</b><span>add·sub·logic</span></div><div><b>BN MAC</b><span>integer multiply</span></div><div className="custom-unit"><b>CUSTOM</b><span>CLMULQACC<br />XORAND · MAC16</span></div></div>
              </div>
              <div className="hw-link"><i>⇄</i><b>message / digest</b></div>
              <div className="hw-kmac"><span>HWIP</span><b>KMAC</b><small>Keccak-f[1600]</small></div>
            </div>
            <div className="custom-path"><span>새 명령</span><b>encoding</b><i>→</i><b>decoder</b><i>→</i><b>execution unit</b><i>→</i><b>WDR / ACC write-back</b><i>→</i><b>simulator·tests</b></div>
          </section>

          <section className="chapter" id="blueprints">
            <ChapterTitle no="07" kicker="THREE ACCELERATION BLUEPRINTS" title="최적화 1순위를 OTBN에 연결한다" />
            <div className="blueprint-grid">
              <div className="blueprint bp-frodo"><div className="bp-head"><span>F</span><div><small>FrodoKEM · P0</small><h3>SHAKE streaming</h3></div><b>89.4%</b></div><div className="bp-flow"><i>RISC-V</i><em>seedA·S 1회</em><i>KMAC</i><em>A 한 행</em><i>WDR buffer</i><em>즉시</em><i>MAC</i></div><div className="bp-bottom"><span>핵심</span><b>A 전체 저장 금지</b><small>후속 후보: BN.MAC16</small></div></div>
              <div className="blueprint bp-hqc"><div className="bp-head"><span>H</span><div><small>HQC · P0</small><h3>Carry-less multiply</h3></div><b>95.9–98.8%</b></div><div className="bp-flow"><i>RISC-V</i><em>a·b 1회</em><i>DMEM</i><em>kernel</em><i>CLMULQACC</i><em>fold</em><i>result</i></div><div className="bp-bottom"><span>핵심</span><b>vect_mul 전체 offload</b><small>standard Zbc/Zvbc와 비교</small></div></div>
              <div className="blueprint bp-mc"><div className="bp-head"><span>M</span><div><small>Classic McEliece · P0?</small><h3>Masked row update</h3></div><b>잠정</b></div><div className="bp-flow"><i>Host RAM</i><em>tile</em><i>DMEM</i><em>pivot 유지</em><i>AND+XOR</i><em>반복</em><i>tile 반환</i></div><div className="bp-bottom"><span>핵심</span><b>고정 스케줄 + 재사용</b><small>power/EM masking 별도</small></div></div>
            </div>
            <div className="instruction-cards">
              <div><span>EXISTING</span><code>bn.and + bn.xor</code><small>McEliece baseline</small></div>
              <div><span>PROPOSED</span><code>bn.clmulqacc</code><small>HQC: ACC ^= CLMUL64(a,b)</small></div>
              <div><span>PROPOSED</span><code>bn.xorand</code><small>McE: dst ^= src & mask</small></div>
              <div><span>SECONDARY</span><code>bn.mac16</code><small>Frodo: 16×16-bit fused MAC</small></div>
            </div>
          </section>

          <section className="chapter" id="movement">
            <ChapterTitle no="08" kicker="THE BORDER HAS A COST" title="빠른 명령도 전송을 이기지 못할 수 있다" />
            <div className="time-equation"><span>T<sub>total</sub></span><i>=</i><b>T<sub>in</sub><small>입력</small></b><i>+</i><b>T<sub>wait</sub><small>호출</small></b><i>+</i><b className="compute">T<sub>compute</sub><small>계산</small></b><i>+</i><b>T<sub>out</sub><small>출력</small></b></div>
            <div className="movement-comparison">
              <div className="movement-bad"><span>작은 offload</span><div className="ping-row">{[0,1,2,3,4].map(i => <i key={`ping-${i}`}>RV ⇄ BN</i>)}</div><b>호출 5회</b></div>
              <div className="movement-good"><span>큰 offload</span><div className="big-job"><i>RV</i><em>입력 1회</em><b>OTBN kernel × N</b><em>출력 1회</em><i>RV</i></div><b>경계 2회</b></div>
            </div>
            <div className="movement-rules"><div><span>01</span><b>Frodo</b><small>produce → consume</small></div><div><span>02</span><b>HQC</b><small>kernel 단위 offload</small></div><div><span>03</span><b>McEliece</b><small>tile · double buffer</small></div><div><span>04</span><b>공통</b><small>compute-only ≠ end-to-end</small></div></div>
          </section>

          <section className="chapter" id="security">
            <ChapterTitle no="09" kicker="FAST IS NOT YET SECURE" title="성능 최적화에 보안 조건을 붙인다" />
            <div className="security-board">
              <div><span>TIME</span><b>고정 cycle</b><small>비밀 branch 금지</small></div><div><span>ADDRESS</span><b>고정 접근</b><small>비밀 index 금지</small></div><div><span>POWER / EM</span><b>mask · refresh</b><small>반복 재사용 누설</small></div><div><span>FAULT</span><b>integrity · alert</b><small>오류 주입 검출</small></div><div><span>LIFETIME</span><b>secure wipe</b><small>WDR·DMEM 삭제</small></div><div><span>EVIDENCE</span><b>TVLA · KAT</b><small>주장과 실측 분리</small></div>
            </div>
            <div className="reuse-warning"><div className="secret-pulse"><span>secret</span>{[0,1,2,3,4,5].map(i => <i key={`pulse-${i}`} />)}</div><Arrow /><div><b>같은 비밀 반복</b><span>타이밍은 일정해도 전력 상관은 커질 수 있다.</span></div><Arrow /><div className="countermeasure"><b>share refresh</b><span>fixed schedule · masked AND · wipe</span></div></div>
          </section>

          <section className="chapter" id="roadmap">
            <ChapterTitle no="10" kicker="FROM BOOK TO RTL" title="공부와 구현을 같은 길에 놓는다" />
            <div className="roadmap">
              {[
                ["01", "OTBN 실행", "기존 example · IMEM/DMEM · WDR"],
                ["02", "세 baseline", "Frodo KMAC · HQC CLMUL SW · McE AND-XOR"],
                ["03", "전송 계측", "T_in · T_compute · T_out"],
                ["04", "P0 확정", "McEliece는 cycle profile gate"],
                ["05", "ISA 명세", "operand · output · latency · flags"],
                ["06", "model", "golden model · assembler · simulator"],
                ["07", "RTL", "decoder · unit · write-back"],
                ["08", "평가", "cycle · area · Fmax · DMEM · leakage"],
              ].map(([n,t,d],i) => <div key={`road-${n}`}><span>{n}</span><b>{t}</b><small>{d}</small>{i < 7 && <i>↓</i>}</div>)}
            </div>
            <div className="baseline-matrix"><div><span>A</span><b>RISC-V optimized SW</b></div><div><span>B</span><b>unmodified OTBN</b></div><div><span>C</span><b>OTBN + KMAC</b></div><div><span>D</span><b>OTBN + KMAC + custom ISE</b></div></div>
            <div className="finish"><span>FINAL QUESTION</span><h3>명령 수를 줄였는가?<br /><em>아니면 전체 시간을 줄였는가?</em></h3><p>답은 end-to-end cycle, 데이터 이동, 면적, 보안 검증을 함께 놓았을 때만 나온다.</p></div>
          </section>

          <section className="references">
            <div><span>SOURCES</span><h2>측정과 구조의 출처</h2></div>
            <div className="source-links"><a href="https://frodokem-fieldbook.nmqnqcwn5s.chatgpt.site" target="_blank" rel="noreferrer">FrodoKEM profiling book</a><a href="https://hqc-textbook-ko.nmqnqcwn5s.chatgpt.site" target="_blank" rel="noreferrer">HQC textbook</a><a href="https://classic-mceliece-study-book.nmqnqcwn5s.chatgpt.site" target="_blank" rel="noreferrer">Classic McEliece study book</a><a href="https://opentitan.org/book/hw/ip/otbn/index.html" target="_blank" rel="noreferrer">OpenTitan OTBN overview</a><a href="https://opentitan.org/book/hw/ip/otbn/doc/isa.html" target="_blank" rel="noreferrer">OTBN ISA</a><a href="https://opentitan.org/book/hw/ip/kmac/" target="_blank" rel="noreferrer">OpenTitan KMAC</a><a href="https://docs.riscv.org/reference/isa/unpriv/b-st-ext.html" target="_blank" rel="noreferrer">RISC-V bit manipulation</a><a href="https://docs.riscv.org/reference/isa/unpriv/vector-crypto" target="_blank" rel="noreferrer">RISC-V vector crypto</a></div>
            <p>구현·파라미터·CPU가 바뀌면 비중도 바뀐다. 모든 최적화 판단은 같은 구현의 end-to-end profiling으로 다시 확인한다.</p>
          </section>
        </article>
      </div>
    </main>
  );
}
