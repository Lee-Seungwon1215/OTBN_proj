"use client";

import { useMemo, useState } from "react";

type AlgorithmKey = "frodo" | "hqc" | "mceliece";
type FlowMode = "naive" | "stream";

const algorithms = {
  frodo: {
    short: "FrodoKEM",
    title: "SHAKE로 행렬을 만들고, 곧바로 MAC에 먹인다",
    formula: "B = A·S + E  (mod q)",
    share: "SHAKE / Keccak 89.4%",
    color: "coral",
    naive: [
      ["RISC-V", "seedA·S 전송", "host"],
      ["KMAC", "A 전체 생성", "kmac"],
      ["OTBN DMEM", "A 저장 시도\n약 800 KiB", "danger"],
      ["OTBN WDR", "다시 읽기", "otbn"],
      ["MAC", "16-bit 누산", "compute"],
    ],
    stream: [
      ["RISC-V", "seedA·S 한 번", "host"],
      ["KMAC", "A 한 행 생성", "kmac"],
      ["WDR 버퍼", "64b×4 → 256b", "otbn"],
      ["MAC", "즉시 소비", "compute"],
      ["다음 행", "저장 없이 반복", "success"],
    ],
    naiveNote:
      "A 전체는 약 819,200바이트라 OTBN 로컬 메모리에 둘 수 없다. 저장 후 재로딩하면 전송이 계산을 가린다.",
    streamNote:
      "KMAC이 만든 A 조각을 WDR에 모아 바로 MAC에 사용한다. A 전체를 저장하지 않는 행 단위 스트리밍이 핵심이다.",
  },
  hqc: {
    short: "HQC",
    title: "입력은 한 번 옮기고, CLMUL은 OTBN 안에서 오래 돌린다",
    formula: "c(X) = a(X)·b(X) mod (Xⁿ − 1)",
    share: "vect_mul 95.9–98.8%",
    color: "violet",
    naive: [
      ["RISC-V", "64-bit word", "host"],
      ["OTBN", "작은 CLMUL 요청", "otbn"],
      ["RISC-V", "부분곱 회수", "host"],
      ["OTBN", "다음 word 요청", "otbn"],
      ["반복", "경계를 계속 왕복", "danger"],
    ],
    stream: [
      ["RISC-V", "a·b 한 번 전송", "host"],
      ["OTBN DMEM", "operand·scratch", "otbn"],
      ["CLMULQACC", "부분곱 XOR 누산", "compute"],
      ["Reduction", "Xⁿ−1로 접기", "compute"],
      ["RISC-V", "결과 한 번 회수", "success"],
    ],
    naiveNote:
      "연산 하나마다 OTBN을 호출하면 호출·복사 비용이 CLMUL보다 커질 수 있다. 명령이 빨라도 offload 단위가 너무 작다.",
    streamNote:
      "vect_mul 전체를 하나의 OTBN 작업으로 보낸다. 데이터 한 바이트당 계산량이 커 전송비를 상쇄하기 좋은 구조다.",
  },
  mceliece: {
    short: "Classic McEliece",
    title: "큰 행렬은 타일로 나누고, 가져온 행을 최대한 재사용한다",
    formula: "dst ← dst ⊕ (src ∧ mask)",
    share: "pk_gen 행 갱신 수백만 회",
    color: "blue",
    naive: [
      ["Host RAM", "큰 행렬", "host"],
      ["OTBN DMEM", "한 블록 복사", "otbn"],
      ["AND+XOR", "계산 1회", "compute"],
      ["Host RAM", "즉시 반환", "host"],
      ["반복", "전송량 폭증", "danger"],
    ],
    stream: [
      ["Host RAM", "행렬 타일", "host"],
      ["Double buffer", "전송·계산 중첩", "otbn"],
      ["Pivot WDR", "레지스터에 유지", "compute"],
      ["여러 행 갱신", "반복 재사용", "compute"],
      ["Host RAM", "완료 타일 반환", "success"],
    ],
    naiveNote:
      "AND+XOR는 계산이 짧고 읽기·쓰기가 많다. 2개 명령을 1개로 합쳐도 큰 행렬을 계속 왕복하면 효과가 작다.",
    streamNote:
      "pivot과 mask를 WDR에 유지하고 여러 행에 재사용한다. 계산/바이트 비율을 높이는 타일링이 명령 융합보다 먼저다.",
  },
} as const;

const toc = [
  ["00", "한눈에 보기", "overview"],
  ["01", "세 블록의 역할", "roles"],
  ["02", "OTBN 내부", "inside"],
  ["03", "왜 전송이 느린가", "transfer"],
  ["04", "KMAC ↔ OTBN", "kmac-flow"],
  ["05", "Host ↔ DMEM", "host-flow"],
  ["06", "알고리즘 실험실", "lab"],
  ["07", "설계 체크리스트", "checklist"],
] as const;

function Arrow({ label }: { label?: string }) {
  return (
    <div className="arrow" aria-hidden="true">
      {label && <span>{label}</span>}
      <i>→</i>
    </div>
  );
}

function FlowDiagram({ algorithm, mode }: { algorithm: AlgorithmKey; mode: FlowMode }) {
  const data = algorithms[algorithm];
  const steps = data[mode];
  return (
    <div className={`flow-diagram theme-${data.color}`}>
      <div className="flow-track">
        {steps.map((step, index) => (
          <div className="flow-pair" key={`${algorithm}-${mode}-${index}`}>
            <div className={`flow-node node-${step[2]}`}>
              <strong>{step[0]}</strong>
              <span>{step[1]}</span>
            </div>
            {index < steps.length - 1 && <Arrow />}
          </div>
        ))}
      </div>
      <p className={`flow-note ${mode === "naive" ? "warning" : "positive"}`}>
        <span aria-hidden="true">{mode === "naive" ? "!" : "✓"}</span>
        {mode === "naive" ? data.naiveNote : data.streamNote}
      </p>
    </div>
  );
}

export default function Home() {
  const [algorithm, setAlgorithm] = useState<AlgorithmKey>("frodo");
  const [mode, setMode] = useState<FlowMode>("naive");
  const selected = useMemo(() => algorithms[algorithm], [algorithm]);

  return (
    <main>
      <header className="topbar">
        <a className="brand" href="#top" aria-label="맨 위로">
          <span className="brand-mark">IO</span>
          <span>
            <strong>Crypto Dataflow Book</strong>
            <small>RISC-V · OTBN · KMAC</small>
          </span>
        </a>
        <nav aria-label="주요 장">
          <a href="#roles">구조</a>
          <a href="#transfer">전송 병목</a>
          <a href="#lab">실험실</a>
        </nav>
        <span className="edition">2026 · OTBN 학습노트</span>
      </header>

      <section className="hero" id="top">
        <div className="hero-copy">
          <p className="eyebrow">그림으로 이해하는 하드웨어·소프트웨어 경계</p>
          <h1>
            계산은 빨라졌는데,
            <br />왜 전체는 안 빨라질까?
          </h1>
          <p className="hero-lead">
            RISC-V가 일을 맡기고, OTBN과 KMAC이 계산한다. 이때 데이터가 블록의 경계를 넘을 때마다
            복사·대기·조립 비용이 생긴다. 이 교재는 그 경계를 눈으로 따라간다.
          </p>
          <div className="hero-actions">
            <a className="primary-button" href="#overview">교재 시작하기</a>
            <a className="text-button" href="#lab">데이터 흐름 비교하기 →</a>
          </div>
        </div>

        <div className="hero-visual" aria-label="RISC-V, OTBN, KMAC 연결 구조">
          <div className="visual-caption">
            <span>OpenTitan SoC</span>
            <b>한 칩 안의 세 역할</b>
          </div>
          <div className="hero-map">
            <div className="map-card host-card">
              <span className="map-icon">RV</span>
              <strong>RISC-V</strong>
              <small>전체 흐름·메모리·호출</small>
            </div>
            <div className="map-link">
              <span className="packet p1" />
              <span className="packet p2" />
              <i>Host ↔ DMEM</i>
            </div>
            <div className="map-card otbn-card">
              <span className="map-icon">BN</span>
              <strong>OTBN</strong>
              <small>256-bit 암호 계산</small>
            </div>
            <div className="map-link short-link">
              <span className="packet p3" />
              <i>KMAC ↔ OTBN</i>
            </div>
            <div className="map-card kmac-card">
              <span className="map-icon">K</span>
              <strong>KMAC</strong>
              <small>SHA3 · SHAKE · KMAC</small>
            </div>
          </div>
          <p className="hero-rule">
            <span>핵심 규칙</span>
            블록 안의 연산보다 블록 사이 화살표가 더 비쌀 수 있다.
          </p>
        </div>
      </section>

      <div className="book-shell">
        <aside className="toc" aria-label="교재 목차">
          <p>READING PATH</p>
          {toc.map(([number, label, id]) => (
            <a href={`#${id}`} key={id}>
              <span>{number}</span>
              {label}
            </a>
          ))}
          <div className="toc-note">
            <b>먼저 기억할 것</b>
            <span>OTBN은 RISC-V의 대체 CPU가 아니라 암호 작업을 맡는 코프로세서다.</span>
          </div>
        </aside>

        <article className="book-content">
          <section className="chapter" id="overview">
            <div className="chapter-head">
              <span>00</span>
              <div>
                <p>START WITH THE BOUNDARY</p>
                <h2>먼저 한 장으로 전체 구조를 잡자</h2>
              </div>
            </div>
            <p className="chapter-intro">
              RISC-V, OTBN, KMAC은 서로 경쟁하는 세 CPU가 아니다. RISC-V가 지휘하고, OTBN은 wide 암호
              연산을, KMAC은 Keccak 계열 연산을 맡는다.
            </p>

            <div className="relationship-board">
              <div className="memory-column">
                <span className="mini-label">SYSTEM WORLD</span>
                <div className="memory-stack large-memory">
                  <b>System RAM / Flash</b>
                  <span>큰 프로그램·공개키·행렬</span>
                  <i>수백 KiB 이상</i>
                </div>
                <div className="role-card risc-card">
                  <b>RISC-V CPU</b>
                  <ul>
                    <li>C 코드와 전체 KEM 실행</li>
                    <li>시스템 메모리·주변장치 관리</li>
                    <li>OTBN/KMAC에 작업 요청</li>
                  </ul>
                </div>
              </div>

              <div className="boundary-column" aria-hidden="true">
                <span>주소·데이터 복사</span>
                <div>⇄</div>
                <em>경계 ①</em>
              </div>

              <div className="secure-column">
                <span className="mini-label">CRYPTO WORLD</span>
                <div className="role-card otbn-role">
                  <b>OTBN</b>
                  <div className="otbn-mini-grid">
                    <span>IMEM<br /><small>어셈블리</small></span>
                    <span>DMEM<br /><small>로컬 데이터</small></span>
                    <span>WDR<br /><small>32 × 256-bit</small></span>
                  </div>
                </div>
                <div className="inner-boundary">
                  <em>경계 ②</em>
                  <span>요청·결과 ⇄</span>
                </div>
                <div className="role-card kmac-role">
                  <b>KMAC HWIP</b>
                  <span>Keccak-f[1600] · SHA3 · SHAKE</span>
                </div>
              </div>
            </div>

            <div className="definition-strip">
              <div><b>RISC-V</b><span>범용 ISA와 이를 구현한 메인 CPU</span></div>
              <div><b>OTBN</b><span>전용 ISA·메모리를 가진 암호 코프로세서</span></div>
              <div><b>KMAC</b><span>Keccak 계열을 처리하는 별도 하드웨어 IP</span></div>
            </div>
          </section>

          <section className="chapter" id="roles">
            <div className="chapter-head">
              <span>01</span>
              <div>
                <p>WHO DOES WHAT?</p>
                <h2>세 블록은 맡은 일이 다르다</h2>
              </div>
            </div>

            <div className="role-comparison">
              <div className="role-panel role-rv">
                <div className="role-number">01</div>
                <p className="role-kicker">GENERAL-PURPOSE</p>
                <h3>RISC-V는 지휘자</h3>
                <p>일반 C 프로그램을 실행하고, 큰 메모리를 관리하며, 어느 계산을 어디에 맡길지 결정한다.</p>
                <div className="code-card">
                  <code>otbn_load_app();</code>
                  <code>otbn_copy_data();</code>
                  <code>otbn_execute();</code>
                </div>
              </div>
              <div className="role-panel role-bn">
                <div className="role-number">02</div>
                <p className="role-kicker">SECURE COPROCESSOR</p>
                <h3>OTBN은 계산 작업자</h3>
                <p>격리된 IMEM·DMEM에서 OTBN 어셈블리를 실행하고 256비트 WDR로 암호 연산을 처리한다.</p>
                <div className="code-card">
                  <code>bn.lid x2, 0(x10)</code>
                  <code>bn.xor w0, w1, w2</code>
                  <code>loopi 64, 2</code>
                </div>
              </div>
              <div className="role-panel role-km">
                <div className="role-number">03</div>
                <p className="role-kicker">KECCAK ENGINE</p>
                <h3>KMAC은 전용 기계</h3>
                <p>1600비트 Keccak 상태를 전용 데이터 경로에서 갱신해 SHA3·SHAKE·KMAC을 처리한다.</p>
                <div className="sponge-visual" aria-label="Keccak sponge 구조">
                  <span>입력</span><i>흡수</i><b>KECCAK<br />1600 bit</b><i>짜내기</i><span>출력</span>
                </div>
              </div>
            </div>

            <div className="callout neutral-callout">
              <b>관계의 핵심</b>
              <p>RISC-V와 OTBN 중 하나만 고르는 구조가 아니다. 보통 RISC-V가 전체를 실행하고 계산 집약적·보안 민감한 커널만 OTBN에 맡긴다.</p>
            </div>
          </section>

          <section className="chapter" id="inside">
            <div className="chapter-head">
              <span>02</span>
              <div>
                <p>LOOK INSIDE OTBN</p>
                <h2>OTBN 안에는 작은 독립 컴퓨터가 있다</h2>
              </div>
            </div>

            <div className="otbn-anatomy">
              <div className="anatomy-top">
                <span>Host command</span><i>START</i><span>DONE / ERROR</span>
              </div>
              <div className="anatomy-body">
                <div className="anatomy-control">
                  <p>CONTROL SIDE</p>
                  <div><b>32-bit GPR</b><span>x0–x31</span></div>
                  <div><b>Instruction control</b><span>branch · LOOP · LOOPI</span></div>
                  <div><b>IMEM</b><span>OTBN .s 프로그램</span></div>
                </div>
                <div className="anatomy-core">
                  <div className="wdr-row">
                    {Array.from({ length: 8 }).map((_, i) => <span key={i}>w{i}</span>)}
                  </div>
                  <b>32 × 256-bit Wide Data Registers</b>
                  <div className="datapath-row">
                    <span>BN ALU</span>
                    <span>BN MAC</span>
                    <span className="dashed">Custom<br />CLMUL/MAC16</span>
                  </div>
                </div>
                <div className="anatomy-memory">
                  <p>LOCAL DATA</p>
                  <div className="dmem-box">
                    <b>DMEM</b>
                    <strong>32 KiB</strong>
                    <span>current master 기준</span>
                  </div>
                  <small>큰 시스템 메모리와 분리되어 있으므로 host가 데이터를 복사해야 한다.</small>
                </div>
              </div>
            </div>

            <div className="scale-row">
              <div><span className="scale-block system-scale" /><b>System memory</b><small>크지만 멀다</small></div>
              <div><span className="scale-block dmem-scale" /><b>OTBN DMEM</b><small>작고 가깝다</small></div>
              <div><span className="scale-block wdr-scale" /><b>WDR</b><small>가장 작고 빠르다</small></div>
            </div>
          </section>

          <section className="chapter" id="transfer">
            <div className="chapter-head">
              <span>03</span>
              <div>
                <p>THE BORDER HAS A TOLL</p>
                <h2>전송은 단순 복사가 아니라 작은 프로토콜이다</h2>
              </div>
            </div>
            <p className="chapter-intro">
              데이터가 경계를 넘을 때는 주소 설정, 버스 접근, 동기화, 결과 확인이 따라온다. 커스텀 명령이 계산을 줄여도 이 고정비는 남는다.
            </p>

            <div className="toll-road">
              <div className="road-end"><b>System RAM</b><span>큰 데이터</span></div>
              <div className="road-segment"><i>①</i><span>복사 요청</span></div>
              <div className="toll-gate"><b>BUS / WINDOW</b><span>주소·폭·대기</span></div>
              <div className="road-segment"><i>②</i><span>완료 확인</span></div>
              <div className="road-end secure"><b>OTBN DMEM</b><span>로컬 데이터</span></div>
            </div>

            <div className="cost-equation">
              <span>T<sub>total</sub></span><b>=</b>
              <div><em>T<sub>in</sub></em><small>입력 복사</small></div><b>+</b>
              <div><em>T<sub>wait</sub></em><small>호출·대기</small></div><b>+</b>
              <div className="accent-term"><em>T<sub>compute</sub></em><small>커스텀 계산</small></div><b>+</b>
              <div><em>T<sub>out</sub></em><small>결과 복사</small></div>
            </div>

            <div className="why-grid">
              <div><span>01</span><b>호출 고정비</b><p>작업을 시작하고 완료 상태를 확인하는 비용은 데이터가 작아도 발생한다.</p></div>
              <div><span>02</span><b>폭 맞추기</b><p>64비트 결과 네 개를 256비트 WDR 하나로 조립하는 명령과 임시 상태가 필요하다.</p></div>
              <div><span>03</span><b>중복 이동</b><p>DMEM에 썼다가 곧바로 WDR로 다시 읽으면 같은 데이터를 두 번 움직인다.</p></div>
              <div><span>04</span><b>기다림</b><p>생산자 KMAC과 소비자 OTBN의 속도가 다르면 빠른 쪽이 멈춰 기다린다.</p></div>
            </div>

            <div className="callout danger-callout">
              <b>명령을 10배 빠르게 만들었는데 전체가 1.2배만 빨라질 수 있는 이유</b>
              <p>계산 외의 입력·출력·대기 시간이 그대로 남기 때문이다. 성능 평가는 반드시 compute-only와 end-to-end를 따로 측정해야 한다.</p>
            </div>
          </section>

          <section className="chapter" id="kmac-flow">
            <div className="chapter-head">
              <span>04</span>
              <div>
                <p>KMAC ↔ OTBN</p>
                <h2>64비트 네 조각이 모여 WDR 하나가 된다</h2>
              </div>
            </div>
            <p className="chapter-intro">
              아래는 64비트 결과 beat를 사용하는 인터페이스를 가정한 데이터 조립 모델이다. 인터페이스 폭이 작을수록 한 WDR을 채우는 횟수가 늘어난다.
            </p>

            <div className="packing-board">
              <div className="beat-source">
                <p>KMAC OUTPUT</p>
                <b>64-bit beat</b>
                <span>8 bytes</span>
              </div>
              <div className="beat-lane" aria-label="64비트 조각 네 개">
                <span>beat 0</span><span>beat 1</span><span>beat 2</span><span>beat 3</span>
              </div>
              <div className="packing-arrow"><span>4회 읽기</span>→</div>
              <div className="wdr-pack">
                <p>OTBN WDR</p>
                <div><span>63:0</span><span>127:64</span><span>191:128</span><span>255:192</span></div>
                <b>256 bits · 32 bytes</b>
              </div>
            </div>

            <div className="frodo-math">
              <div><span>A 한 행</span><b>640 × 16-bit</b><strong>1,280 B</strong></div>
              <i>÷</i>
              <div><span>KMAC 한 beat</span><b>64-bit</b><strong>8 B</strong></div>
              <i>=</i>
              <div className="result-card"><span>한 행당</span><b>160 beats</b><strong>WDR 40개</strong></div>
            </div>

            <div className="compare-flow">
              <div className="compare-card bad">
                <span>STORE THEN LOAD</span>
                <h3>저장형</h3>
                <div className="mini-flow"><b>KMAC</b><i>→</i><b>DMEM</b><i>→</i><b>WDR</b><i>→</i><b>MAC</b></div>
                <p>쓰기와 다시 읽기가 추가된다. A 전체 저장은 용량상 불가능하다.</p>
              </div>
              <div className="compare-card good">
                <span>PRODUCE AND CONSUME</span>
                <h3>스트리밍형</h3>
                <div className="mini-flow"><b>KMAC</b><i>→</i><b>WDR</b><i>→</i><b>MAC</b></div>
                <p>한 조각을 만들자마자 소비한다. 메모리 왕복과 저장 공간을 함께 줄인다.</p>
              </div>
            </div>
          </section>

          <section className="chapter" id="host-flow">
            <div className="chapter-head">
              <span>05</span>
              <div>
                <p>HOST ↔ OTBN DMEM</p>
                <h2>오프로드 단위를 크게 잡아야 한다</h2>
              </div>
            </div>

            <div className="granularity-board">
              <div className="grain bad-grain">
                <div className="grain-title"><span>나쁜 예</span><b>연산 하나씩 호출</b></div>
                <div className="pingpong">
                  {Array.from({ length: 5 }).map((_, i) => (
                    <div key={i}><span>Host</span><i>⇄</i><span>OTBN</span></div>
                  ))}
                </div>
                <p>호출·복사·상태 확인이 매 연산마다 반복된다.</p>
              </div>
              <div className="grain good-grain">
                <div className="grain-title"><span>좋은 예</span><b>커널 전체를 호출</b></div>
                <div className="kernel-offload">
                  <span>입력 1회</span><i>→</i>
                  <div><b>OTBN 내부 반복</b><small>CLMUL · XOR · reduction</small></div>
                  <i>→</i><span>출력 1회</span>
                </div>
                <p>경계를 두 번만 넘고 내부 계산을 충분히 길게 수행한다.</p>
              </div>
            </div>

            <div className="reuse-meter">
              <div className="meter-copy">
                <p>OFFLOAD RULE</p>
                <h3>가져온 데이터는 여러 번 써야 한다</h3>
                <p>연산 집약도는 이동한 바이트당 수행한 유효 연산 수다. 이 값이 높을수록 OTBN offload가 유리하다.</p>
              </div>
              <div className="meter-scale">
                <span>낮음</span>
                <div><i style={{ width: "25%" }} /><em className="mark-mc">McE XOR</em><em className="mark-hqc">HQC CLMUL</em></div>
                <span>높음</span>
              </div>
            </div>
          </section>

          <section className="chapter" id="lab">
            <div className="chapter-head">
              <span>06</span>
              <div>
                <p>INTERACTIVE DATAFLOW LAB</p>
                <h2>세 알고리즘의 데이터 흐름을 비교하자</h2>
              </div>
            </div>

            <div className="lab-card">
              <div className="lab-tabs" role="tablist" aria-label="알고리즘 선택">
                {(Object.keys(algorithms) as AlgorithmKey[]).map((key) => (
                  <button
                    key={key}
                    type="button"
                    role="tab"
                    aria-selected={algorithm === key}
                    className={algorithm === key ? "active" : ""}
                    onClick={() => setAlgorithm(key)}
                  >
                    {algorithms[key].short}
                  </button>
                ))}
              </div>
              <div className="lab-summary">
                <div>
                  <p>{selected.share}</p>
                  <h3>{selected.title}</h3>
                </div>
                <code>{selected.formula}</code>
              </div>
              <div className="mode-switch" role="group" aria-label="데이터 흐름 방식">
                <button type="button" className={mode === "naive" ? "active bad-mode" : ""} onClick={() => setMode("naive")}>나쁜 흐름</button>
                <button type="button" className={mode === "stream" ? "active good-mode" : ""} onClick={() => setMode("stream")}>개선 흐름</button>
              </div>
              <FlowDiagram key={`${algorithm}-${mode}`} algorithm={algorithm} mode={mode} />
            </div>

            <div className="algorithm-lessons">
              <div><span className="dot coral" /><b>FrodoKEM</b><p>KMAC 출력 스트리밍이 핵심. A 전체를 만들지 않는다.</p></div>
              <div><span className="dot violet" /><b>HQC</b><p>CLMUL 커널 전체를 offload해 전송을 한 번으로 줄인다.</p></div>
              <div><span className="dot blue" /><b>McEliece</b><p>타일과 pivot을 재사용해 낮은 연산 집약도를 보완한다.</p></div>
            </div>
          </section>

          <section className="chapter" id="checklist">
            <div className="chapter-head">
              <span>07</span>
              <div>
                <p>BEFORE ADDING AN INSTRUCTION</p>
                <h2>RTL 수정 전에 답해야 할 질문</h2>
              </div>
            </div>

            <div className="check-grid">
              {[
                ["01", "작업 경계", "명령 하나인가, 커널 전체인가? 경계를 넘는 횟수를 먼저 센다."],
                ["02", "작업 집합", "operand·결과·scratch가 DMEM에 들어가는가? 타일 크기는 얼마인가?"],
                ["03", "재사용", "한 번 읽은 WDR 값을 몇 번의 계산에 사용하는가?"],
                ["04", "생산자와 소비자", "KMAC 출력 속도와 OTBN 소비 속도가 맞는가? backpressure는 있는가?"],
                ["05", "두 가지 시간", "compute-only와 host 전송 포함 end-to-end를 모두 측정했는가?"],
                ["06", "보안 경계", "고정 latency, 데이터 독립 주소, secure wipe와 무결성을 유지하는가?"],
              ].map(([n, title, text]) => (
                <div key={n}><span>{n}</span><b>{title}</b><p>{text}</p></div>
              ))}
            </div>

            <div className="final-principle">
              <span>DESIGN PRINCIPLE</span>
              <h3>좋은 가속은 빠른 명령 하나가 아니라,<br />적게 움직이고 오래 계산하는 데이터 흐름이다.</h3>
              <div className="principle-pills"><i>큰 offload 단위</i><i>WDR 재사용</i><i>스트리밍</i><i>이중 버퍼</i><i>고정 시간</i></div>
            </div>
          </section>

          <section className="sources" aria-label="참고 자료">
            <div><span>REFERENCE</span><h2>더 깊게 읽기</h2></div>
            <ul>
              <li><a href="https://opentitan.org/book/hw/ip/otbn/index.html" target="_blank" rel="noreferrer">OpenTitan OTBN Overview</a></li>
              <li><a href="https://opentitan.org/book/hw/ip/otbn/doc/theory_of_operation.html" target="_blank" rel="noreferrer">OTBN Theory of Operation</a></li>
              <li><a href="https://opentitan.org/book/hw/ip/otbn/doc/isa.html" target="_blank" rel="noreferrer">OTBN Instruction Set</a></li>
              <li><a href="https://opentitan.org/book/hw/ip/kmac/" target="_blank" rel="noreferrer">OpenTitan KMAC HWIP</a></li>
            </ul>
            <p>수치 예시는 current master 문서와 FrodoKEM-640-SHAKE 데이터 흐름 모델을 기준으로 설명했다. 실제 구현 버전에서는 IMEM/DMEM 크기와 인터페이스를 다시 확인해야 한다.</p>
          </section>
        </article>
      </div>
    </main>
  );
}
