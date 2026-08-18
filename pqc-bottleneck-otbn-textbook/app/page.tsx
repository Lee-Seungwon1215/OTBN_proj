"use client";

import { useMemo, useState } from "react";

type AlgorithmKey = "frodo" | "hqc" | "mceliece";
type StageKey = "keygen" | "encaps" | "decaps";
type Tone = "violet" | "cyan" | "lime" | "amber" | "coral" | "slate";

const stages: { key: StageKey; label: string; short: string }[] = [
  { key: "keygen", label: "키 생성", short: "KEYGEN" },
  { key: "encaps", label: "캡슐화", short: "ENCAPS" },
  { key: "decaps", label: "디캡슐화", short: "DECAPS" },
];

const algorithms = {
  frodo: {
    name: "FrodoKEM",
    variant: "640-SHAKE · fast_generic",
    mark: "FR",
    color: "violet" as Tone,
    thesis: "반복량 1위는 행렬, 시간 1위는 SHAKE",
    stages: {
      keygen: {
        total: "1.340 ms",
        code: ["큰 행렬 MAC · 3,276,800", "A 생성 Keccak-f · 122,880 rounds", "CDF 샘플링 · 122,880 compares"],
        measured: [
          { label: "SHAKE / Keccak", value: 90.48, tone: "violet" as Tone },
          { label: "행렬 MAC", value: 4.96, tone: "cyan" as Tone },
          { label: "직렬화", value: 1.86, tone: "amber" as Tone },
          { label: "CDF 샘플링", value: 1.63, tone: "lime" as Tone },
        ],
        region: "단일 region 1위 · A 생성 87.47%",
        why: "행렬 루프는 데이터 재사용으로 짧아졌지만 A의 640개 행을 만드는 SHAKE는 약 1.17 ms로 남았습니다.",
      },
      encaps: {
        total: "1.443 ms",
        code: ["큰 행렬 MAC · 3,276,800", "A 생성 Keccak-f · 122,880 rounds", "CDF 123,648 + 작은 MAC 40,960"],
        measured: [
          { label: "SHAKE / Keccak", value: 89.28, tone: "violet" as Tone },
          { label: "행렬 MAC", value: 4.8, tone: "cyan" as Tone },
          { label: "직렬화", value: 3.48, tone: "amber" as Tone },
          { label: "CDF 샘플링", value: 1.65, tone: "lime" as Tone },
        ],
        region: "단일 region 1위 · A 생성 82.05%",
        why: "reference의 큰 MAC은 2.17 ms지만 fast_generic에서는 약 0.063 ms입니다. 같은 수학도 루프 순서가 병목을 바꿉니다.",
      },
      decaps: {
        total: "1.380 ms",
        code: ["큰 행렬 MAC · 3,276,800", "A 생성 Keccak-f · 122,880 rounds", "CDF 123,648 + 작은 MAC 81,920"],
        measured: [
          { label: "SHAKE / Keccak", value: 88.38, tone: "violet" as Tone },
          { label: "행렬 MAC", value: 5.13, tone: "cyan" as Tone },
          { label: "직렬화", value: 3.71, tone: "amber" as Tone },
          { label: "CDF 샘플링", value: 1.8, tone: "lime" as Tone },
        ],
        region: "단일 region 1위 · A 생성 85.40%",
        why: "복구 뒤 재암호화가 캡슐화 경로를 다시 실행합니다. 그래도 최적화된 MAC보다 A 재생성 SHAKE가 압도적입니다.",
      },
    },
  },
  hqc: {
    name: "HQC",
    variant: "HQC-1 · ref",
    mark: "HQ",
    color: "lime" as Tone,
    thesis: "코드와 시계가 같은 곳을 가리킨다",
    stages: {
      keygen: {
        total: "0.80 ms",
        code: ["vect_mul · 1회 / 1,219,456 inner bodies", "고정무게 샘플링 · 36,564 compares", "SHA3 / SHAKE"],
        measured: [
          { label: "GF(2) 순환 vect_mul", value: 97.8, tone: "lime" as Tone },
          { label: "샘플링·해시·기타", value: 2.2, tone: "slate" as Tone },
        ],
        region: "단일 함수 1위 · vect_mul 97.8%",
        why: "277개의 64-bit word를 Karatsuba로 분할하고 schoolbook carry-less 곱과 순환 reduction을 수행합니다.",
      },
      encaps: {
        total: "1.58 ms",
        code: ["vect_mul · 2회 / 2,438,912 inner bodies", "고정무게 샘플링 · 62,325 compares", "SHA3 / SHAKE + 부호화"],
        measured: [
          { label: "GF(2) 순환 vect_mul", value: 97.7, tone: "lime" as Tone },
          { label: "샘플링·해시·기타", value: 2.3, tone: "slate" as Tone },
        ],
        region: "단일 함수 1위 · vect_mul 97.7%",
        why: "공개키 h와 s에 대해 긴 순환 곱셈을 두 번 실행합니다. 나머지를 모두 합쳐도 2.3%뿐입니다.",
      },
      decaps: {
        total: "2.41 ms",
        code: ["vect_mul · 3회 / 3,658,368 inner bodies", "샘플링 · 80,607 compares", "RS/RM decoder loops"],
        measured: [
          { label: "GF(2) 순환 vect_mul", value: 95.857, tone: "lime" as Tone },
          { label: "RS / RM 복호", value: 1.75, tone: "coral" as Tone },
          { label: "SHA3 / SHAKE", value: 1.002, tone: "violet" as Tone },
          { label: "고정무게 샘플링", value: 0.98, tone: "amber" as Tone },
        ],
        region: "단일 함수 1위 · vect_mul 95.857%",
        why: "복호 1회와 재암호화 2회가 합쳐져 vect_mul이 세 번 호출됩니다. 디코더보다 곱셈이 약 55배 큽니다.",
      },
    },
  },
  mceliece: {
    name: "Classic McEliece",
    variant: "348864 · vec",
    mark: "CM",
    color: "cyan" as Tone,
    thesis: "단계마다 병목의 성격이 달라진다",
    stages: {
      keygen: {
        total: "28.123 ms",
        code: ["선형맵 · 25,362,432 masked-XOR", "피벗 탐색 · 7,068,672", "전방 소거 · 7,068,672"],
        measured: [
          { label: "가우스 소거군", value: 60.0, tone: "cyan" as Tone },
          { label: "pk_gen 밖 · 미분해", value: 26.17, tone: "slate" as Tone },
          { label: "선형맵", value: 10.35, tone: "amber" as Tone },
          { label: "pk_gen 기타", value: 3.48, tone: "coral" as Tone },
        ],
        region: "pk_gen은 KeyGen의 73.83% · 평균 3.445회 호출",
        why: "실패 호출 70.98%가 피벗 검사 중 끝납니다. 성공할 때만 큰 선형맵으로 가므로 누적시간 1위가 소거로 바뀝니다.",
      },
      encaps: {
        total: "8.291 µs",
        code: ["syndrome · 공개키 261,120 B scan", "오류벡터 생성 · sort + scatter + retry", "SHAKE256 · 533 B preimage"],
        measured: [
          { label: "syndrome 공개키 scan", value: 46.96, tone: "cyan" as Tone },
          { label: "오류벡터 생성군", value: 39.43, tone: "coral" as Tone },
          { label: "SHAKE256", value: 10.84, tone: "violet" as Tone },
          { label: "기타", value: 2.77, tone: "slate" as Tone },
        ],
        region: "단일 region 1위 · syndrome 46.96%",
        why: "32,256개의 64-bit AND-XOR보다 더 중요한 것은 공개키 261 KB를 매번 읽는다는 점입니다.",
      },
      decaps: {
        total: "108.660 µs",
        code: ["BM · vec_mul 385회", "FFTᵀ · 각각 208회", "FFT · 각각 197회 / inverse 194회"],
        measured: [
          { label: "GF / FFT / BM 디코더", value: 88.08, tone: "cyan" as Tone },
          { label: "Benes 왕복", value: 6.0, tone: "amber" as Tone },
          { label: "weight check", value: 4.26, tone: "coral" as Tone },
          { label: "SHAKE256", value: 0.82, tone: "violet" as Tone },
        ],
        region: "단일 region 1위 · BM 24.91%",
        why: "상위 여섯 구간에서 bitsliced GF(2¹²) vec_mul이 총 1,389회 호출됩니다. 정적 호출 순서와 실측 순서가 거의 같습니다.",
      },
    },
  },
};

const matrixRows = [
  { algo: "Frodo", values: [90.48, 89.28, 88.38], labels: ["SHAKE", "SHAKE", "SHAKE"], tone: "violet" },
  { algo: "HQC", values: [97.8, 97.7, 95.857], labels: ["MUL", "MUL", "MUL"], tone: "lime" },
  { algo: "McEliece", values: [60.0, 46.96, 88.08], labels: ["GE", "SYN", "GF"], tone: "cyan" },
];

const otbnFit = [
  {
    algo: "FrodoKEM",
    bottleneck: "A 생성 SHAKE",
    fit: "KMAC 우선",
    className: "fit-kmac",
    direction: "KMAC HWIP로 A 행을 생성하되, KMAC↔OTBN 전달·handshake를 포함해 측정",
    risk: "KMAC만 빠르게 하면 MAC·DMEM 이동이 다음 병목",
  },
  {
    algo: "HQC",
    bottleneck: "GF(2) 순환 곱셈",
    fit: "커스텀 ISE P0",
    className: "fit-custom",
    direction: "CLMUL/CLMULH + XOR shift + Xⁿ−1 reduction을 256-bit WDR 데이터 경로에 매핑",
    risk: "BN.MUL은 carry 정수곱이므로 그대로 대체 불가",
  },
  {
    algo: "McEliece",
    bottleneck: "GE · syndrome · vec_mul",
    fit: "단계별 분리",
    className: "fit-split",
    direction: "Decaps vec_mul은 OTBN 후보, KeyGen/Encaps는 RVV 또는 memory-attached 구조 우선",
    risk: "402 KiB 행렬·261 KiB 공개키·약 18 KiB decoder working set",
  },
];

function StackedBar({ parts, label }: { parts: { label: string; value: number; tone: Tone }[]; label: string }) {
  return (
    <div className="stacked-bar" role="img" aria-label={label}>
      {parts.map((part) => (
        <i key={part.label} className={`tone-${part.tone}`} style={{ width: `${part.value}%` }} title={`${part.label} ${part.value}%`} />
      ))}
    </div>
  );
}

export default function Home() {
  const [algorithm, setAlgorithm] = useState<AlgorithmKey>("frodo");
  const [stage, setStage] = useState<StageKey>("keygen");
  const [lens, setLens] = useState<"measured" | "code">("measured");
  const [workload, setWorkload] = useState<"balanced" | "reuse">("balanced");

  const activeAlgorithm = algorithms[algorithm];
  const activeStage = activeAlgorithm.stages[stage];

  const priority = useMemo(() => {
    if (workload === "balanced") {
      return [
        ["1", "McEliece KeyGen", "가우스 소거", "16.87 ms"],
        ["2", "HQC Decaps", "vect_mul", "2.31 ms"],
        ["3", "HQC Encaps", "vect_mul", "1.54 ms"],
        ["4", "Frodo Encaps", "SHAKE", "1.29 ms"],
      ];
    }
    return [
      ["1", "HQC Decaps ×100", "vect_mul", "≈231 ms"],
      ["2", "HQC Encaps ×100", "vect_mul", "≈154 ms"],
      ["3", "Frodo Enc/Dec ×100", "SHAKE", "≈251 ms 합계"],
      ["4", "McEliece KeyGen ×1", "가우스 소거", "16.87 ms"],
    ];
  }, [workload]);

  return (
    <main id="top">
      <header className="topbar">
        <a className="brand" href="#top" aria-label="PQC 병목 지도 처음으로">
          <span className="brand-mark"><i /><i /><i /></span>
          <span>PQC BOTTLENECK ATLAS</span>
        </a>
        <nav aria-label="교재 목차">
          <a href="#map">병목 지도</a>
          <a href="#lab">분석 실험실</a>
          <a href="#otbn">OTBN 연결</a>
          <a href="#roadmap">로드맵</a>
        </nav>
      </header>

      <section className="hero">
        <div className="hero-copy">
          <p className="eyebrow">CODE × CLOCK × ARCHITECTURE</p>
          <h1>코드를 읽고,<br /><em>시간을 재고,</em><br />OTBN을 고른다.</h1>
          <p className="hero-lead">FrodoKEM·HQC·Classic McEliece의 9개 KEM 경로를 같은 눈금으로 비교하는 시각 교재</p>
          <div className="hero-actions">
            <a className="primary-action" href="#lab">분석 시작 <span>↘</span></a>
            <span className="scope-chip">ARM64 HOST PROFILE</span>
          </div>
        </div>

        <div className="hero-visual" aria-label="세 알고리즘의 대표 병목">
          <div className="orb orb-a" />
          <div className="orb orb-b" />
          <div className="core-card">
            <div className="core-head"><span>BOTTLENECK CORE</span><b>3 / 9</b></div>
            <div className="core-lanes">
              <div><span className="lane-mark violet">FR</span><b>SHAKE</b><small>A row generation</small><i style={{ width: "90%" }} /></div>
              <div><span className="lane-mark lime">HQ</span><b>VECT_MUL</b><small>cyclic GF(2)</small><i style={{ width: "98%" }} /></div>
              <div><span className="lane-mark cyan">CM</span><b>GF DECODER</b><small>bitsliced GF(2¹²)</small><i style={{ width: "88%" }} /></div>
            </div>
            <div className="core-foot"><span>정적 반복량</span><i>→</i><span>실측 비중</span><i>→</i><span>데이터 이동</span></div>
          </div>
        </div>
      </section>

      <section className="chapter" id="map">
        <div className="chapter-head">
          <span className="chapter-no">01</span>
          <div><p>THE 3 × 3 MAP</p><h2>9개 경로, 세 종류의 답</h2></div>
          <p>칸의 높이는 “1순위 병목이 단계 전체에서 차지하는 비중”입니다.</p>
        </div>

        <div className="matrix-map">
          <div className="matrix-head"><span>ALGORITHM</span>{stages.map((item) => <b key={item.key}>{item.short}<small>{item.label}</small></b>)}</div>
          {matrixRows.map((row) => (
            <div className="matrix-row" key={row.algo}>
              <strong>{row.algo}</strong>
              {row.values.map((value, index) => (
                <button
                  key={`${row.algo}-${stages[index].key}`}
                  onClick={() => {
                    setAlgorithm(row.algo === "Frodo" ? "frodo" : row.algo === "HQC" ? "hqc" : "mceliece");
                    setStage(stages[index].key);
                    document.querySelector("#lab")?.scrollIntoView({ behavior: "smooth" });
                  }}
                  aria-label={`${row.algo} ${stages[index].label} ${row.labels[index]} ${value}% 자세히 보기`}
                >
                  <i className={`fill-${row.tone}`} style={{ height: `${Math.max(16, value)}%` }} />
                  <span>{row.labels[index]}</span><b>{value}<small>%</small></b>
                </button>
              ))}
            </div>
          ))}
        </div>

        <div className="map-legend">
          <span><i className="dot violet" />SHAKE / Keccak</span>
          <span><i className="dot lime" />GF(2) cyclic mul</span>
          <span><i className="dot cyan" />matrix / GF decoder</span>
          <p>숫자가 크다고 절대시간이 긴 것은 아닙니다. 여기서는 <b>병목 집중도</b>만 비교합니다.</p>
        </div>
      </section>

      <section className="chapter lab-section" id="lab">
        <div className="chapter-head">
          <span className="chapter-no">02</span>
          <div><p>INTERACTIVE PROFILE LAB</p><h2>코드의 예상과 시계의 대답</h2></div>
          <p>알고리즘과 단계를 고르고 두 관점을 번갈아 보세요.</p>
        </div>

        <div className="lab-controls">
          <div className="algorithm-tabs" role="tablist" aria-label="알고리즘 선택">
            {(Object.keys(algorithms) as AlgorithmKey[]).map((key) => (
              <button key={key} className={algorithm === key ? "active" : ""} onClick={() => setAlgorithm(key)} role="tab" aria-selected={algorithm === key}>
                <span className={`lane-mark ${algorithms[key].color}`}>{algorithms[key].mark}</span>
                <span><b>{algorithms[key].name}</b><small>{algorithms[key].variant}</small></span>
              </button>
            ))}
          </div>
          <div className="stage-tabs" role="tablist" aria-label="KEM 단계 선택">
            {stages.map((item) => <button key={item.key} className={stage === item.key ? "active" : ""} onClick={() => setStage(item.key)} role="tab" aria-selected={stage === item.key}>{item.label}</button>)}
          </div>
        </div>

        <div className="lab-board">
          <div className="lab-title">
            <div><p>{activeAlgorithm.variant}</p><h3>{activeAlgorithm.name} · {stages.find((item) => item.key === stage)?.label}</h3><span>{activeAlgorithm.thesis}</span></div>
            <div className="lens-toggle" aria-label="분석 관점 선택">
              <button className={lens === "code" ? "active" : ""} onClick={() => setLens("code")}>CODE</button>
              <button className={lens === "measured" ? "active" : ""} onClick={() => setLens("measured")}>CLOCK</button>
            </div>
          </div>

          <div className={`lens-panel lens-${lens}`}>
            <div className="code-ranking">
              <p className="panel-label">STATIC WORKLOAD</p>
              <h4>코드상 후보 순위</h4>
              <ol>{activeStage.code.map((item, index) => <li key={item}><span>0{index + 1}</span><b>{item}</b><i /></li>)}</ol>
              <div className="code-warning">서로 다른 primitive의 반복 1회는 같은 비용이 아닙니다.</div>
            </div>

            <div className="measured-ranking">
              <div className="measured-top"><div><p className="panel-label">WALL-CLOCK PROFILE</p><h4>실측 시간 구성</h4></div><strong>{activeStage.total}</strong></div>
              <StackedBar parts={activeStage.measured} label={`${activeAlgorithm.name} ${stage} 실측 시간 구성`} />
              <div className="bar-list">
                {activeStage.measured.map((part, index) => (
                  <div key={part.label}><span>{index + 1}</span><b>{part.label}</b><i><em className={`tone-${part.tone}`} style={{ width: `${part.value}%` }} /></i><strong>{part.value}%</strong></div>
                ))}
              </div>
              <p className="region-note">{activeStage.region}</p>
            </div>
          </div>

          <div className="why-strip"><span>WHY?</span><p>{activeStage.why}</p></div>
        </div>
      </section>

      <section className="chapter" id="mismatch">
        <div className="chapter-head compact">
          <span className="chapter-no">03</span>
          <div><p>WHY THE RANKING MOVES</p><h2>차이는 연산식 밖에서 생긴다</h2></div>
        </div>

        <div className="cause-grid">
          <article className="cause-card frodo-cause">
            <div className="cause-top"><span>FRODO</span><b>병목 역전</b></div>
            <div className="before-after">
              <div><small>REFERENCE</small><strong>MAC 61.25%</strong><i><em style={{ width: "61%" }} /></i></div>
              <span>→</span>
              <div><small>FAST_GENERIC</small><strong>SHAKE 89.28%</strong><i><em style={{ width: "89%" }} /></i></div>
            </div>
            <p>루프 순서와 S 원소 재사용이 MAC 시간을 줄이자, A 생성 SHAKE가 수면 위로 올라옵니다.</p>
          </article>

          <article className="cause-card hqc-cause">
            <div className="cause-top"><span>HQC</span><b>순위 고정</b></div>
            <div className="repeat-rail"><i>MUL</i><i>MUL</i><i>MUL</i><span>DECAPS</span></div>
            <strong className="big-share">95.857<small>%</small></strong>
            <p>한 호출이 너무 무겁습니다. 샘플링·해시·RS/RM 복호를 모두 더해도 곱셈을 넘지 못합니다.</p>
          </article>

          <article className="cause-card mceliece-cause">
            <div className="cause-top"><span>McELIECE</span><b>재시도 누적</b></div>
            <div className="retry-loop"><span>PK_GEN</span><i>×</i><strong>3.445</strong><em>평균 호출</em></div>
            <div className="failure-meter"><i style={{ width: "70.98%" }} /><span>70.98% pivot failure</span></div>
            <p>실패 호출이 선형맵 전에 끝나므로, 코드상 1위와 실제 누적시간 1위가 달라집니다.</p>
          </article>
        </div>
      </section>

      <section className="chapter otbn-section" id="otbn">
        <div className="chapter-head">
          <span className="chapter-no">04</span>
          <div><p>FROM PROFILE TO OTBN</p><h2>연산보다 먼저, 경계를 그린다</h2></div>
          <p>OTBN 명령만 빠르게 해도 데이터가 경계를 넘지 못하면 전체 KEM은 빨라지지 않습니다.</p>
        </div>

        <div className="architecture-board" aria-label="RISC-V 호스트, OTBN, KMAC 데이터 흐름">
          <div className="host-zone">
            <div className="zone-title"><span>HOST DOMAIN</span><b>RISC‑V CORE</b></div>
            <div className="host-memory"><span>SRAM / FLASH</span><b>pk · sk · ct</b><small>큰 원본 데이터</small></div>
            <div className="host-flow"><span>1</span><p>명령과 입력 타일 준비</p></div>
            <div className="host-flow"><span>5</span><p>완료 확인 · 결과 읽기</p></div>
          </div>

          <div className="bus-zone">
            <span>Host ↔ OTBN</span>
            <div className="bus-lines"><i /><i /><i /></div>
            <b>copy + setup + wait</b>
          </div>

          <div className="otbn-zone">
            <div className="zone-title"><span>ACCELERATOR DOMAIN</span><b>OTBN</b></div>
            <div className="otbn-grid">
              <div className="memory-cell"><span>IMEM</span><b>.s program</b><small>명령 공급</small></div>
              <div className="memory-cell"><span>DMEM</span><b>input · state</b><small>데이터 타일</small></div>
              <div className="compute-cell"><span>32 × WDR</span><b>256-bit</b><small>wide state</small></div>
              <div className="compute-cell hot"><span>BN / CUSTOM ALU</span><b>AND · XOR · SHIFT</b><small>후보 primitive</small></div>
            </div>
            <div className="otbn-flow"><span>2</span><p>DMEM → WDR</p><span>3</span><p>연산·재사용</p><span>4</span><p>결과 저장</p></div>
          </div>

          <div className="kmac-zone">
            <div className="zone-title"><span>HASH HWIP</span><b>KMAC</b></div>
            <div className="sponge"><i /><i /><i /><i /><i /><i /></div>
            <p>SHA3 · SHAKE</p>
            <span className="kmac-link">KMAC ↔ OTBN<br />handshake · words</span>
          </div>
        </div>

        <div className="boundary-equation">
          <div><span>KERNEL GAIN</span><b>빠른 명령</b></div><i>−</i><div><span>BOUNDARY TAX</span><b>복사 + 대기</b></div><i>=</i><div className="result"><span>REAL GAIN</span><b>End-to-end</b></div>
        </div>

        <div className="fit-board">
          <div className="fit-head"><span>ALGORITHM</span><span>MEASURED TARGET</span><span>OTBN DIRECTION</span><span>PRIMARY RISK</span></div>
          {otbnFit.map((row) => (
            <article key={row.algo}>
              <div><b>{row.algo}</b><span className={row.className}>{row.fit}</span></div>
              <strong>{row.bottleneck}</strong>
              <p>{row.direction}</p>
              <small>{row.risk}</small>
            </article>
          ))}
        </div>
      </section>

      <section className="chapter" id="decision">
        <div className="chapter-head">
          <span className="chapter-no">05</span>
          <div><p>WORKLOAD CHANGES PRIORITY</p><h2>한 번의 순위와 시스템의 순위</h2></div>
          <p>키를 몇 번 재사용하는지에 따라 연구 우선순위도 달라집니다.</p>
        </div>

        <div className="decision-board">
          <div className="workload-toggle">
            <button className={workload === "balanced" ? "active" : ""} onClick={() => setWorkload("balanced")}><span>1 : 1 : 1</span><b>균형 실험</b><small>KeyGen + Encaps + Decaps</small></button>
            <button className={workload === "reuse" ? "active" : ""} onClick={() => setWorkload("reuse")}><span>1 : 100 : 100</span><b>키 재사용</b><small>통신 누적 workload</small></button>
          </div>
          <div className="priority-list">
            {priority.map((row) => <div key={row[0]}><span>{row[0]}</span><b>{row[1]}</b><p>{row[2]}</p><strong>{row[3]}</strong></div>)}
          </div>
          <div className="decision-note"><b>읽는 법</b><p>비중이 큰 병목은 ISA 실험이 깔끔합니다. 절대시간이 큰 병목은 1회 개선폭이 큽니다. 반복 workload는 둘을 다시 곱합니다.</p></div>
        </div>
      </section>

      <section className="chapter" id="roadmap">
        <div className="chapter-head compact">
          <span className="chapter-no">06</span>
          <div><p>IMPLEMENTATION ROADMAP</p><h2>측정 가능한 순서로 구현한다</h2></div>
        </div>

        <div className="roadmap">
          <article><span>01</span><div><small>HOST BASELINE</small><h3>primitive를 격리</h3><p>RISC‑V scalar/RVV에서 cycle·byte·호출 수를 고정합니다.</p></div><b>MEASURE</b></article>
          <article><span>02</span><div><small>OTBN KERNEL</small><h3>DMEM 안에서 재사용</h3><p>작은 함수 왕복 대신 여러 호출을 한 OTBN 프로그램에 묶습니다.</p></div><b>KEEP STATE</b></article>
          <article><span>03</span><div><small>TRANSFER-INCLUSIVE</small><h3>경계세를 더한다</h3><p>Host↔DMEM, KMAC↔OTBN, command setup을 모두 포함합니다.</p></div><b>END-TO-END</b></article>
          <article><span>04</span><div><small>SECURITY CHECK</small><h3>상수시간을 다시 검증</h3><p>retry·memory access·tile reuse가 비밀에 의존하지 않는지 확인합니다.</p></div><b>CT + SCA</b></article>
        </div>

        <div className="final-verdict">
          <div><p>FIRST EXPERIMENT</p><h2>HQC `vect_mul`부터</h2><span>세 단계 재사용 · 95.9~97.8% · 명확한 carry-less primitive</span></div>
          <div className="verdict-flow"><span>RV Zbc<br /><b>baseline</b></span><i>→</i><span>OTBN WDR<br /><b>mapping</b></span><i>→</i><span>custom CLMUL<br /><b>extension</b></span></div>
          <p>그다음 Frodo는 KMAC 데이터 경로, McEliece는 디캡슐화 `vec_mul`을 실험합니다. KeyGen/Encaps의 큰 데이터는 메모리 구조 연구로 분리합니다.</p>
        </div>
      </section>

      <section className="method-note">
        <div><span>MEASURED</span><p>Apple ARM64 host profile · 구현별 컴파일 옵션과 파라미터가 다르므로 절대시간은 직접 성능 비교가 아니라 방향성 자료입니다.</p></div>
        <div><span>STATIC</span><p>반복 횟수는 기계어 명령 수가 아닙니다. 연산 1회의 비용과 메모리 접근을 실측으로 보정해야 합니다.</p></div>
        <div><span>NEXT</span><p>RISC‑V/OTBN에서 동일한 구간 계측을 다시 수행하고 전송 포함 end-to-end 시간으로 결론을 갱신합니다.</p></div>
      </section>

      <footer>
        <div><span>PQC BOTTLENECK ATLAS</span><p>FrodoKEM · HQC · Classic McEliece</p></div>
        <a href="#top">처음으로 ↑</a>
      </footer>
    </main>
  );
}
