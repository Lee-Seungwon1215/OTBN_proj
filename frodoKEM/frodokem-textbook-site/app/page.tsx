"use client";

import { useEffect, useMemo, useState } from "react";

type StageKey = "keygen" | "encaps" | "decaps";
type ImplKey = "reference" | "fast";
type GroupKey = "keccak" | "matrix" | "serialization" | "sampler" | "security" | "other";

const stageOrder: StageKey[] = ["keygen", "encaps", "decaps"];
const stageLabels: Record<StageKey, string> = { keygen: "키 생성", encaps: "캡슐화", decaps: "디캡슐화" };
const groupLabels: Record<GroupKey, string> = {
  keccak: "SHAKE / Keccak",
  matrix: "16-bit 행렬 MAC",
  serialization: "Pack / unpack",
  sampler: "CDF sampler",
  security: "검증 / 지우기",
  other: "기타·잔여",
};

const chapters = [
  { id: "scope", no: "00", label: "설계 기준 확정" },
  { id: "flow", no: "01", label: "함수 흐름" },
  { id: "profile", no: "02", label: "프로파일링" },
  { id: "loops", no: "03", label: "병목 반복문" },
  { id: "primitives", no: "04", label: "공통 primitive" },
  { id: "isa", no: "05", label: "RISC-V / OTBN" },
  { id: "model", no: "06", label: "비용 모델" },
  { id: "method", no: "07", label: "측정 경계" },
];

const profileData: Record<ImplKey, Record<StageKey, { total: number; groups: Record<GroupKey, number> }>> = {
  reference: {
    keygen: { total: 1.380, groups: { keccak: 88.31, matrix: 7.37, serialization: 1.78, sampler: 1.62, security: 0.49, other: 0.43 } },
    encaps: { total: 3.558, groups: { keccak: 36.14, matrix: 61.25, serialization: 1.42, sampler: 0.65, security: 0.19, other: 0.35 } },
    decaps: { total: 3.499, groups: { keccak: 34.84, matrix: 62.39, serialization: 1.47, sampler: 0.68, security: 0.30, other: 0.32 } },
  },
  fast: {
    keygen: { total: 1.340, groups: { keccak: 90.48, matrix: 4.96, serialization: 1.86, sampler: 1.63, security: 0.52, other: 0.55 } },
    encaps: { total: 1.443, groups: { keccak: 89.28, matrix: 4.80, serialization: 3.48, sampler: 1.65, security: 0.47, other: 0.32 } },
    decaps: { total: 1.380, groups: { keccak: 88.38, matrix: 5.13, serialization: 3.71, sampler: 1.80, security: 0.76, other: 0.22 } },
  },
};

const regionHeat: Record<ImplKey, Record<StageKey, Record<string, number>>> = {
  reference: {
    keygen: { "A 생성": 1177.6, "큰 MAC": 101.7, "작은 MAC": 0, "샘플 SHAKE": 27.8, "CDF": 22.3, "직렬화": 24.6 },
    encaps: { "A 생성": 1180.7, "큰 MAC": 2172.9, "작은 MAC": 6.2, "샘플 SHAKE": 54.2, "CDF": 23.1, "직렬화": 50.2 },
    decaps: { "A 생성": 1176.4, "큰 MAC": 2174.6, "작은 MAC": 7.8, "샘플 SHAKE": 27.7, "CDF": 23.7, "직렬화": 51.4 },
  },
  fast: {
    keygen: { "A 생성": 1172.4, "큰 MAC": 66.4, "작은 MAC": 0, "샘플 SHAKE": 28.0, "CDF": 21.8, "직렬화": 24.9 },
    encaps: { "A 생성": 1183.9, "큰 MAC": 63.1, "작은 MAC": 6.3, "샘플 SHAKE": 53.0, "CDF": 23.8, "직렬화": 50.2 },
    decaps: { "A 생성": 1178.4, "큰 MAC": 63.3, "작은 MAC": 7.5, "샘플 SHAKE": 27.4, "CDF": 24.8, "직렬화": 51.3 },
  },
};

const workloadShares = {
  balanced: {
    label: "균형 1 : 1 : 1",
    detail: "KeyGen 1회 + Encaps 1회 + Decaps 1회",
    reference: { total: 8.436, keccak: 44.14, matrix: 52.91, serialization: 1.50, sampler: 0.82, security: 0.29, other: 0.34 },
    fast: { total: 4.163, keccak: 89.37, matrix: 4.96, serialization: 3.04, sampler: 1.69, security: 0.58, other: 0.36 },
  },
  reuse: {
    label: "키 재사용 1 : 100 : 100",
    detail: "KeyGen 1회 + Encaps 100회 + Decaps 100회",
    reference: { total: 707.023, keccak: 35.60, matrix: 61.70, serialization: 1.44, sampler: 0.67, security: 0.25, other: 0.34 },
    fast: { total: 283.615, keccak: 88.85, matrix: 4.96, serialization: 3.59, sampler: 1.72, security: 0.61, other: 0.27 },
  },
};

const loops = [
  { label: "큰 행렬 MAC", unit: "16-bit MAC", keygen: 3_276_800, encaps: 3_276_800, decaps: 3_276_800, source: "8 × 640 × 640" },
  { label: "CDF 상수시간 비교", unit: "compare", keygen: 122_880, encaps: 123_648, decaps: 123_648, source: "sample 수 × 12" },
  { label: "Keccak-f round", unit: "round", keygen: 122_880, encaps: 122_880, decaps: 122_880, source: "640행 × 8 permutation × 24" },
  { label: "작은 행렬 MAC", unit: "16-bit MAC", keygen: 0, encaps: 40_960, decaps: 81_920, source: "8 × 8 × 640" },
  { label: "A 행 XOF 세션", unit: "SHAKE128 row", keygen: 640, encaps: 640, decaps: 640, source: "행마다 seedA ∥ row index" },
];

const issueModels = [
  { id: "rv32", name: "RV32IM + Zbb", note: "scalar baseline", total: 116_123_136, parts: { keccak: 82.54, matrix: 17.14, sampler: 0.32 }, detail: "64-bit Keccak를 32-bit pair로, MAC은 mul + add" },
  { id: "rvv", name: "RVV128", note: "standard vector", total: 25_252_032, parts: { keccak: 94.89, matrix: 4.93, sampler: 0.18 }, detail: "SEW=16에서 8-lane vmacc, Keccak 2-state 병렬" },
  { id: "otbn", name: "OTBN + KMAC", note: "current interfaces", total: 3_456_192, parts: { keccak: 26.67, matrix: 72.00, sampler: 1.33 }, detail: "KMAC HWIP offload, BN.MULV.8S + BN.ADDV.8S" },
  { id: "custom", name: "OTBN + MAC16", note: "proposed extension", total: 1_566_816, parts: { keccak: 58.82, matrix: 39.70, sampler: 1.48 }, detail: "KMAC offload + 가상 16-lane fused MAC" },
];

const presets = [
  { id: "base", label: "RV32 baseline", shake: 1, mac: 1 },
  { id: "rvv", label: "RVV128 model", shake: 4, mac: 16 },
  { id: "otbn", label: "OTBN + KMAC", shake: 104, mac: 8 },
  { id: "custom", label: "OTBN + MAC16", shake: 104, mac: 32 },
];

function formatCompact(value: number) {
  return new Intl.NumberFormat("ko-KR", { notation: value >= 1_000_000 ? "compact" : "standard", maximumFractionDigits: 2 }).format(value);
}

function StackedBar({ parts, label }: { parts: Partial<Record<GroupKey, number>>; label: string }) {
  const keys: GroupKey[] = ["keccak", "matrix", "serialization", "sampler", "security", "other"];
  return (
    <div className="stacked-bar" role="img" aria-label={label}>
      {keys.map((key) => parts[key] ? <span key={key} className={`seg ${key}`} style={{ width: `${parts[key]}%` }} title={`${groupLabels[key]} ${parts[key]?.toFixed(1)}%`} /> : null)}
    </div>
  );
}

function GroupLegend() {
  return <div className="legend">{(["keccak", "matrix", "serialization", "sampler", "security", "other"] as GroupKey[]).map((key) => <span key={key}><i className={key} />{groupLabels[key]}</span>)}</div>;
}

function StatusTag({ kind, children }: { kind: "measured" | "modeled" | "exact"; children: React.ReactNode }) {
  return <span className={`status-tag ${kind}`}>{children}</span>;
}

export default function Home() {
  const [active, setActive] = useState("scope");
  const [implementation, setImplementation] = useState<ImplKey>("fast");
  const [workload, setWorkload] = useState<keyof typeof workloadShares>("balanced");
  const [shakeSpeed, setShakeSpeed] = useState(104);
  const [macSpeed, setMacSpeed] = useState(8);

  useEffect(() => {
    const observer = new IntersectionObserver((entries) => {
      const visible = entries.filter((entry) => entry.isIntersecting).sort((a, b) => b.intersectionRatio - a.intersectionRatio)[0];
      if (visible) setActive(visible.target.id);
    }, { rootMargin: "-18% 0px -70% 0px", threshold: [0.05, 0.25] });
    chapters.forEach(({ id }) => { const node = document.getElementById(id); if (node) observer.observe(node); });
    return () => observer.disconnect();
  }, []);

  const amdahl = useMemo(() => {
    const source = workloadShares[workload].fast;
    const k = source.keccak / 100;
    const m = source.matrix / 100;
    const other = Math.max(0, 1 - k - m);
    const denominator = other + k / shakeSpeed + m / macSpeed;
    return {
      speedup: 1 / denominator,
      keccak: (k / shakeSpeed) / denominator * 100,
      matrix: (m / macSpeed) / denominator * 100,
      other: other / denominator * 100,
      ceiling: 1 / other,
    };
  }, [workload, shakeSpeed, macSpeed]);

  const maxStageTime = 3.6;
  const maxLoop = 3_276_800;
  const maxIssue = issueModels[0].total;
  const heatMax = Math.max(...Object.values(regionHeat[implementation]).flatMap((stage) => Object.values(stage)));

  return (
    <main>
      <header className="topbar">
        <a className="brand" href="#top"><span>FK</span><b>Co-Design Atlas</b></a>
        <nav aria-label="주요 단원">
          {chapters.slice(2, 7).map((chapter) => <a key={chapter.id} href={`#${chapter.id}`} className={active === chapter.id ? "active" : ""}>{chapter.no}</a>)}
        </nav>
        <div className="top-scope"><i />640-SHAKE · 100 × 9</div>
      </header>

      <section className="hero" id="top">
        <div className="hero-copy">
          <div className="overline">FRODOKEM PERFORMANCE & ISA CO-DESIGN WORKBOOK</div>
          <h1>측정에서<br /><em>명령어까지</em></h1>
          <p>알고리즘의 함수 호출을 실제 실행시간과 반복횟수로 분해하고, 공통 primitive를 RISC‑V와 OTBN의 ISA 후보에 매핑합니다.</p>
          <div className="hero-scope">
            <StatusTag kind="measured">HOST MEASURED</StatusTag>
            <span>Apple arm64 · clang -O3</span>
            <StatusTag kind="modeled">ISA MODELED</StatusTag>
            <span>issue-slot lower bound</span>
          </div>
        </div>
        <div className="hero-dashboard">
          <div className="hero-metric primary"><span>FAST_GENERIC · 1:1:1</span><strong>4.163<small> ms</small></strong><p>세 KEM 단계 합계 중앙값</p></div>
          <div className="hero-metric"><span>TOP REGION</span><strong>89.4<small>%</small></strong><p>SHAKE / Keccak</p></div>
          <div className="hero-metric"><span>HOTTEST LOOP</span><strong>3.28<small>M</small></strong><p>16-bit MAC / 단계</p></div>
          <div className="hero-stack">
            <div><span>Measured time share</span><b>FAST_GENERIC</b></div>
            <StackedBar parts={workloadShares.balanced.fast} label="FAST_GENERIC 균형 workload 시간 비중" />
            <GroupLegend />
          </div>
        </div>
      </section>

      <div className="page-shell">
        <aside className="rail">
          <p>READING PATH</p>
          <nav>{chapters.map((chapter) => <a key={chapter.id} href={`#${chapter.id}`} className={active === chapter.id ? "active" : ""}><span>{chapter.no}</span>{chapter.label}</a>)}</nav>
          <div className="rail-note"><b>두 종류의 숫자</b><StatusTag kind="measured">실측</StatusTag><span>CSV 중앙값</span><StatusTag kind="modeled">모델</StatusTag><span>명시된 ISA 가정</span></div>
        </aside>

        <article className="book">
          <section className="chapter" id="scope">
            <div className="chapter-head"><span>00</span><div><p>LOCK THE TARGET</p><h2>알고리즘·파라미터·구현체 확정</h2></div></div>
            <p className="lead">ISA를 먼저 고르지 않습니다. 프로토콜과 파라미터를 고정하고, 정답성이 같은 두 구현체가 어디서 시간을 쓰는지 비교하는 데서 시작합니다.</p>

            <div className="decision-strip">
              <div><span>PROTOCOL</span><strong>Standard FrodoKEM</strong><small>공개키 재사용 가능</small></div>
              <div><span>PARAMETER</span><strong>640-SHAKE</strong><small>n=640 · n̄=8 · q=2¹⁵</small></div>
              <div><span>LEARN</span><strong>REFERENCE</strong><small>수식 ↔ 반복문</small></div>
              <div><span>MEASURE</span><strong>FAST_GENERIC</strong><small>이식 가능한 최적화</small></div>
            </div>

            <div className="parameter-layout">
              <div className="parameter-matrix" aria-label="FrodoKEM 행렬 차원">
                <div className="matrix-box a"><b>A</b><span>640 × 640</span><small>SHAKE128로 행별 생성</small></div>
                <i>×</i>
                <div className="matrix-box s"><b>S</b><span>640 × 8</span><small>비밀·오차</small></div>
                <i>→</i>
                <div className="matrix-box b"><b>B</b><span>640 × 8</span><small>공개키 본체</small></div>
              </div>
              <div className="parameter-table">
                <div><code>n</code><strong>640</strong><span>큰 루프의 두 축</span></div>
                <div><code>n̄</code><strong>8</strong><span>병렬 출력 폭</span></div>
                <div><code>q</code><strong>2¹⁵</strong><span>16-bit wrap 활용</span></div>
                <div><code>B</code><strong>2</strong><span>셀당 메시지 비트</span></div>
              </div>
            </div>

            <div className="boundary-note"><StatusTag kind="exact">FIXED</StatusTag><p>이후 그래프의 모든 연산량은 FrodoKEM-640-SHAKE에만 해당합니다. 976/1344 또는 AES 변형으로 바꾸면 행렬량·XOF 비용·비중이 함께 바뀝니다.</p></div>
          </section>

          <section className="chapter" id="flow">
            <div className="chapter-head"><span>01</span><div><p>TRACE THE CALLS</p><h2>함수 흐름에 계측 구간을 꽂습니다</h2></div></div>
            <p className="lead">세 API를 동일한 region ID로 잘라야 구현체와 ISA가 달라도 같은 항목을 비교할 수 있습니다. 디캡슐화는 내부에서 캡슐화를 재계산한다는 점이 핵심입니다.</p>

            <div className="flow-columns">
              <article>
                <div className="flow-title"><span>01</span><h3>KeyGen</h3><b>1.340 ms</b></div>
                <ol>
                  <li><span>randombytes</span><i>system_random</i></li>
                  <li><span>SHAKE(seedSE)</span><i>sample_xof</i></li>
                  <li><span>frodo_sample_n ×2</span><i>noise_sampling</i></li>
                  <li className="hot"><span>A 생성 + A·S+E</span><i>a_generation / large_mac</i></li>
                  <li><span>pack + H(pk)</span><i>pack / public_key_hash</i></li>
                </ol>
              </article>
              <article>
                <div className="flow-title"><span>02</span><h3>Encaps</h3><b>1.443 ms</b></div>
                <ol>
                  <li><span>H(pk), G₂ 파생</span><i>public / derive_xof</i></li>
                  <li><span>S′·E′·E″ 샘플</span><i>sample / noise</i></li>
                  <li className="hot"><span>S′·A + E′</span><i>a_generation / large_mac</i></li>
                  <li><span>S′·B + E″</span><i>small_matrix_mac</i></li>
                  <li><span>encode + pack + F</span><i>serialization / ss_xof</i></li>
                </ol>
              </article>
              <article>
                <div className="flow-title"><span>03</span><h3>Decaps</h3><b>1.380 ms</b></div>
                <ol>
                  <li><span>unpack + B′·S</span><i>small_matrix_mac</i></li>
                  <li><span>μ′ 복구 + G₂</span><i>derive_xof</i></li>
                  <li className="hot"><span>Encaps 경로 재계산</span><i>A + large + small MAC</i></li>
                  <li><span>ct_verify / ct_select</span><i>verify_select</i></li>
                  <li><span>최종 F(ct ∥ k)</span><i>shared_secret_xof</i></li>
                </ol>
              </article>
            </div>

            <div className="flow-insight"><span>DECAPS = RECOVER + RE-ENCRYPT + VERIFY</span><p>따라서 작은 MAC은 Encaps에서 1회, Decaps에서 2회 실행됩니다. 반면 큰 A 생성·MAC은 세 단계 모두 정확히 한 번씩 나타나 공통 primitive가 됩니다.</p></div>
          </section>

          <section className="chapter" id="profile">
            <div className="chapter-head"><span>02</span><div><p>MEASURE BEFORE DESIGN</p><h2>프로파일링: 병목은 구현체에 종속됩니다</h2></div></div>
            <p className="lead">같은 수학 연산량이라도 루프 순서와 메모리 지역성 때문에 시간 비중은 완전히 달라집니다. 아래는 단계당 100회, 9 trials의 중앙값입니다.</p>

            <div className="toolbar" aria-label="프로파일 그래프 설정">
              <div><span>구현체 구성</span><button className={implementation === "reference" ? "active" : ""} onClick={() => setImplementation("reference")}>REFERENCE</button><button className={implementation === "fast" ? "active" : ""} onClick={() => setImplementation("fast")}>FAST_GENERIC</button></div>
              <div><span>workload</span><button className={workload === "balanced" ? "active" : ""} onClick={() => setWorkload("balanced")}>1:1:1</button><button className={workload === "reuse" ? "active" : ""} onClick={() => setWorkload("reuse")}>1:100:100</button></div>
            </div>

            <div className="chart-card">
              <div className="chart-heading"><div><StatusTag kind="measured">MEASURED</StatusTag><h3>단계별 실행시간</h3></div><span>ms / operation · median</span></div>
              <div className="compare-bars">
                {stageOrder.map((stage) => {
                  const ref = profileData.reference[stage].total;
                  const fast = profileData.fast[stage].total;
                  return <div className="compare-group" key={stage}>
                    <div className="compare-label"><strong>{stageLabels[stage]}</strong><span>{(ref / fast).toFixed(2)}×</span></div>
                    <div className="bar-line"><b>REFERENCE</b><div><i className="ref" style={{ width: `${ref / maxStageTime * 100}%` }} /></div><span>{ref.toFixed(3)}</span></div>
                    <div className="bar-line"><b>FAST_GENERIC</b><div><i className="fast" style={{ width: `${fast / maxStageTime * 100}%` }} /></div><span>{fast.toFixed(3)}</span></div>
                  </div>;
                })}
              </div>
            </div>

            <div className="chart-card composition-card">
              <div className="chart-heading"><div><StatusTag kind="measured">MEASURED</StatusTag><h3>{implementation === "fast" ? "FAST_GENERIC" : "REFERENCE"} 시간 구성</h3></div><span>구간 시간 / 단계 전체</span></div>
              <div className="composition-list">
                {stageOrder.map((stage) => <div key={stage}><div><strong>{stageLabels[stage]}</strong><span>{profileData[implementation][stage].total.toFixed(3)} ms</span></div><StackedBar parts={profileData[implementation][stage].groups} label={`${implementation} ${stageLabels[stage]} 시간 구성`} /><p><b>SHAKE {profileData[implementation][stage].groups.keccak.toFixed(1)}%</b><b>MAC {profileData[implementation][stage].groups.matrix.toFixed(1)}%</b></p></div>)}
              </div>
              <GroupLegend />
            </div>

            <div className="profile-split">
              <div className="workload-card">
                <div><StatusTag kind="measured">WORKLOAD</StatusTag><h3>{workloadShares[workload].label}</h3><p>{workloadShares[workload].detail}</p></div>
                <strong>{workloadShares[workload][implementation].total.toFixed(3)}<small> ms</small></strong>
                <StackedBar parts={workloadShares[workload][implementation]} label={`${workload} ${implementation} 시간 비중`} />
                <p className="verdict-text">{implementation === "fast" ? `SHAKE가 ${workloadShares[workload].fast.keccak.toFixed(1)}%로 1순위` : `행렬 MAC이 ${workloadShares[workload].reference.matrix.toFixed(1)}%로 1순위`}</p>
              </div>
              <div className="heat-card">
                <div className="chart-heading"><div><h3>region heatmap</h3></div><span>μs / op</span></div>
                <div className="heat-grid">
                  <div className="heat-head"><span>region</span>{stageOrder.map((s) => <b key={s}>{stageLabels[s]}</b>)}</div>
                  {Object.keys(regionHeat[implementation].keygen).map((region) => <div className="heat-row" key={region}><span>{region}</span>{stageOrder.map((stage) => { const value = regionHeat[implementation][stage][region]; const intensity = value / heatMax; return <b key={stage} style={{ background: `color-mix(in srgb, var(--hot) ${Math.max(4, intensity * 92)}%, var(--panel-2))` }}>{value ? value.toFixed(value > 100 ? 0 : 1) : "–"}</b>; })}</div>)}
                </div>
              </div>
            </div>
          </section>

          <section className="chapter" id="loops">
            <div className="chapter-head"><span>03</span><div><p>COUNT THE INNER LOOPS</p><h2>병목 반복문: 어디가 가장 많이 도는가</h2></div></div>
            <p className="lead">실행시간은 플랫폼에 따라 달라지지만 trip count는 파라미터가 같으면 변하지 않습니다. 로그 축으로 보면 큰 MAC의 327만 회가 가장 위에 있고, Keccak round와 CDF 비교가 약 12만 회로 뒤를 잇습니다.</p>

            <div className="chart-card loop-chart">
              <div className="chart-heading"><div><StatusTag kind="exact">ALGORITHMIC</StatusTag><h3>단계별 primitive 반복횟수</h3></div><span>log₁₀ scale</span></div>
              <div className="loop-head"><span>primitive</span>{stageOrder.map((s) => <b key={s}>{stageLabels[s]}</b>)}</div>
              {loops.map((loop) => <div className="loop-row" key={loop.label}>
                <div><strong>{loop.label}</strong><small>{loop.source}</small></div>
                {stageOrder.map((stage) => { const value = loop[stage]; const width = value ? Math.log10(value) / Math.log10(maxLoop) * 100 : 0; return <div className="log-cell" key={stage}><i style={{ width: `${width}%` }} /><span>{value ? formatCompact(value) : "–"}</span></div>; })}
              </div>)}
            </div>

            <div className="loop-anatomy">
              <article className="code-card">
                <div><span>HOT LOOP #1</span><b>REFERENCE</b></div>
                <pre><code>{`for (i = 0; i < 640; i++)
  for (k = 0; k < 8; k++)
    for (j = 0; j < 640; j++)
      sum += A[i][j] * S[k][j];`}</code></pre>
                <p><strong>640 × 8 × 640 = 3,276,800</strong> 곱-누산. 루프 순서가 캐시와 벡터화 가능성을 결정합니다.</p>
              </article>
              <article className="code-card">
                <div><span>FAST_GENERIC</span><b>4-row block</b></div>
                <pre><code>{`for (i = 0; i < 640; i += 4)
  generate_A_rows(i..i+3)
  for (k = 0; k < 8; k++)
    for (j = 0; j < 640; j++)
      sum[0..3] += A[0..3][j] * S[k][j];`}</code></pre>
                <p>MAC 수는 같지만 S 원소 하나를 네 행에 재사용합니다. Encaps/Decaps의 MAC 시간이 약 <strong>2.17 ms → 0.063 ms</strong>로 줄어듭니다.</p>
              </article>
            </div>

            <div className="trip-summary">
              <div><span>1:1:1 전체</span><strong>9,830,400</strong><small>큰 MAC</small></div>
              <div><span>1:1:1 전체</span><strong>370,176</strong><small>CDF 비교</small></div>
              <div><span>1:1:1 전체</span><strong>368,640</strong><small>Keccak rounds</small></div>
              <div><span>1:1:1 전체</span><strong>122,880</strong><small>작은 MAC</small></div>
            </div>
          </section>

          <section className="chapter" id="primitives">
            <div className="chapter-head"><span>04</span><div><p>SELECT COMMON PRIMITIVES</p><h2>함수명이 아니라 반복되는 계산을 고릅니다</h2></div></div>
            <p className="lead">한 단계만 빠르게 하는 명령보다 KeyGen·Encaps·Decaps에 모두 나타나는 primitive가 투자 회수 범위가 큽니다. 정답성·상수시간 성질도 함께 유지해야 합니다.</p>

            <div className="primitive-rank">
              <article className="rank-card winner"><span>01</span><div><small>MEASURED · FAST_GENERIC</small><h3>SHAKE / Keccak</h3><strong>89.4%</strong><p>A 생성 640행과 KEM 내부 해시를 모두 덮습니다.</p></div></article>
              <article className="rank-card"><span>02</span><div><small>ALGORITHMIC · ALL STAGES</small><h3>16-bit MAC</h3><strong>3.28M</strong><p>단계마다 같은 큰 MAC 수. REFERENCE에서는 52.9%.</p></div></article>
              <article className="rank-card"><span>03</span><div><small>CONSTANT-TIME</small><h3>CDF compare</h3><strong>370K</strong><p>균형 workload 전체 비교 횟수. 12회/샘플.</p></div></article>
              <article className="rank-card"><span>04</span><div><small>DATA MOVEMENT</small><h3>Pack / unpack</h3><strong>3.0%</strong><p>FAST_GENERIC에서 MAC 다음으로 드러나는 데이터 경로.</p></div></article>
            </div>

            <div className="coverage-matrix">
              <div className="coverage-head"><span>primitive</span><b>KeyGen</b><b>Encaps</b><b>Decaps</b><b>선정</b></div>
              {[
                ["SHAKE / Keccak", "A·sample·hash", "A·derive·hash", "A·derive·hash", "필수"],
                ["Large MAC16", "A·S", "S′·A", "S′·A 재계산", "필수"],
                ["Small MAC16", "–", "S′·B", "B′·S + S′·B", "공통"],
                ["CDF sampler", "S, E", "S′, E′, E″", "동일 재계산", "후순위"],
                ["Pack / unpack", "pk pack", "pk unpack + ct pack", "ct·pk unpack", "후순위"],
                ["CT verify/select", "–", "–", "검증·선택", "보안 필수"],
              ].map((row) => <div className="coverage-row" key={row[0]}>{row.map((cell, i) => i === 0 ? <strong key={cell}>{cell}</strong> : <span key={`${cell}-${i}`} className={cell === "–" ? "empty" : ""}>{cell}</span>)}</div>)}
            </div>

            <div className="selection-verdict"><div><span>PRIMITIVE SET v0</span><h3>SHAKE engine + MAC16 datapath</h3></div><p>SHAKE를 먼저 빼면 FAST_GENERIC의 현재 1순위가 사라지고, 그 순간 MAC과 데이터 이동이 새 병목으로 올라옵니다. 따라서 단일 명령이 아니라 <b>해시 경로와 행렬 경로를 함께 설계</b>해야 합니다.</p></div>
          </section>

          <section className="chapter" id="isa">
            <div className="chapter-head"><span>05</span><div><p>MAP TO THE ISA</p><h2>RISC‑V와 OTBN에서 병목이 어떻게 이동하는가</h2></div></div>
            <p className="lead">아래는 cycle 실측이 아니라 정적 issue-slot 하한 모델입니다. 메모리 stall·파이프라인·KMAC handshake는 제외하고, 명령어가 한 번에 처리하는 lane 수만 비교합니다.</p>

            <div className="isa-platforms">
              <article><div><StatusTag kind="modeled">RISC-V</StatusTag><h3>RV32IM + Zbb → RVV128</h3></div><ul><li>RV32 M: scalar MUL</li><li>Zbb: rotate / andn으로 Keccak 논리 단축</li><li>RVV SEW=16: 8-lane <code>vmacc</code></li><li>Keccak는 독립 state 병렬화</li></ul></article>
              <article><div><StatusTag kind="modeled">OTBN</StatusTag><h3>256-bit WDR + KMAC HWIP</h3></div><ul><li>32 × 256-bit wide registers</li><li><code>BN.MULV.8S</code> + <code>BN.ADDV.8S</code></li><li><code>LOOPI</code> 하드웨어 루프</li><li>SHAKE는 KMAC interface로 offload</li></ul></article>
            </div>

            <div className="isa-map-table">
              <div className="isa-map-head"><span>primitive</span><b>RV32IM+Zbb</b><b>RVV128</b><b>OTBN 현재</b><b>OTBN 제안</b></div>
              {[
                ["큰 MAC16", "MUL + ADD / 1 lane", "vmacc.vx / 8×16", "BN.MULV+ADDV / 8×32", "bn.mac16 / 16×16 fused"],
                ["Keccak-f", "32-bit lane pair + ror", "2 states / 128-bit", "KMAC HWIP offload", "KMAC HWIP 유지"],
                ["CDF compare", "sub + shift + add", "8×16 compare/acc", "8×32 SIMD", "16×16 CT compare"],
                ["루프 제어", "branch + counter", "vsetvl strip-mine", "LOOP / LOOPI", "LOOPI 유지"],
                ["A stream", "load/store row", "vector row blocks", "64-bit shared digest beat", "digest→MAC direct feed"],
              ].map((row) => <div className="isa-map-row" key={row[0]}>{row.map((cell, i) => i === 0 ? <strong key={cell}>{cell}</strong> : <span key={`${cell}-${i}`}>{cell}</span>)}</div>)}
            </div>

            <div className="chart-card issue-chart">
              <div className="chart-heading"><div><StatusTag kind="modeled">STATIC MODEL</StatusTag><h3>1:1:1 정적 core-work 비교</h3></div><span>issue equivalents · log scale</span></div>
              <div className="issue-bars">
                {issueModels.map((model) => <div key={model.id}>
                  <div className="issue-label"><strong>{model.name}</strong><span>{model.note}</span><b>{formatCompact(model.total)}</b></div>
                  <div className="issue-track"><i style={{ width: `${Math.log10(model.total) / Math.log10(maxIssue) * 100}%` }} /></div>
                  <p>{model.detail}</p>
                </div>)}
              </div>
            </div>

            <div className="chart-card">
              <div className="chart-heading"><div><StatusTag kind="modeled">BOTTLENECK SHIFT</StatusTag><h3>ISA별 계산 비중</h3></div><span>모델에 포함된 세 primitive 내 비중</span></div>
              <div className="isa-share-list">
                {issueModels.map((model) => <div key={model.id}><div><strong>{model.name}</strong><span>{model.parts.keccak.toFixed(1)}% K · {model.parts.matrix.toFixed(1)}% M</span></div><div className="isa-stacked" aria-label={`${model.name} 계산 비중`}><i className="keccak" style={{ width: `${model.parts.keccak}%` }} /><i className="matrix" style={{ width: `${model.parts.matrix}%` }} /><i className="sampler" style={{ width: `${model.parts.sampler}%` }} /></div></div>)}
              </div>
              <div className="mini-legend"><span><i className="keccak" />Keccak 또는 KMAC 전송</span><span><i className="matrix" />MAC</span><span><i className="sampler" />CDF</span></div>
            </div>

            <div className="isa-verdicts">
              <article><span>RISC-V 판단</span><h3>RVV만 추가하면 SHAKE가 더 선명한 병목</h3><p>MAC issue 수는 scalar 대비 16배 압축되지만 128-bit RVV의 Keccak state 병렬화는 4배 모델입니다. 따라서 vector MAC 뒤에는 Keccak 가속 또는 다중-state 스케줄이 필요합니다.</p></article>
              <article><span>OTBN 판단</span><h3>KMAC offload 뒤에는 MAC·전송이 병목</h3><p>현재 8×32 SIMD는 곱과 덧셈이 분리됩니다. 가상 16×16 fused MAC과 digest→MAC 직접 공급 경로를 함께 두면 core-work가 다시 KMAC 전송 쪽으로 이동합니다.</p></article>
            </div>

            <div className="assumption-ledger">
              <div className="chart-heading"><div><StatusTag kind="modeled">ASSUMPTIONS</StatusTag><h3>정적 issue 모델의 산식</h3></div><span>cycle·memory 제외</span></div>
              <div><span>RV32 Keccak</span><code>130 × 64-bit ops/round × 2 words = 260 issue/round</code></div>
              <div><span>RVV128 Keccak</span><code>2 independent states/vector → 65 issue/state-round</code></div>
              <div><span>RVV128 MAC</span><code>SEW=16 → 8 MAC lanes / vmacc instruction</code></div>
              <div><span>OTBN current MAC</span><code>8 lanes × (BN.MULV.8S + BN.ADDV.8S) = 2 issue / 8 MAC</code></div>
              <div><span>OTBN KMAC readout</span><code>640 rows × 160 digest beats × (S0 read + S1 read + XOR) = 307,200 issue/A</code></div>
              <div><span>OTBN MAC16 proposal</span><code>16 lanes × fused multiply-add = 1 issue / 16 MAC</code></div>
            </div>
          </section>

          <section className="chapter" id="model">
            <div className="chapter-head"><span>06</span><div><p>EXPLORE THE CEILING</p><h2>가속 배수보다 시간 점유율이 먼저입니다</h2></div></div>
            <p className="lead">FAST_GENERIC 실측 비중에 Amdahl 법칙을 적용한 상한 모델입니다. ISA의 실제 cycle이 아니라, 특정 primitive가 N배 빨라졌을 때 전체가 어디까지 줄어드는지를 봅니다.</p>

            <div className="preset-row">{presets.map((preset) => <button key={preset.id} className={shakeSpeed === preset.shake && macSpeed === preset.mac ? "active" : ""} onClick={() => { setShakeSpeed(preset.shake); setMacSpeed(preset.mac); }}>{preset.label}</button>)}</div>
            <div className="model-grid">
              <div className="sliders">
                <label><span><b>SHAKE / KMAC 가속</b><output>{shakeSpeed}×</output></span><input type="range" min="1" max="128" value={shakeSpeed} onChange={(e) => setShakeSpeed(Number(e.target.value))} /></label>
                <label><span><b>MAC16 가속</b><output>{macSpeed}×</output></span><input type="range" min="1" max="64" value={macSpeed} onChange={(e) => setMacSpeed(Number(e.target.value))} /></label>
                <div className="model-source"><span>입력 프로파일</span><strong>FAST_GENERIC · {workloadShares[workload].label}</strong><small>SHAKE {workloadShares[workload].fast.keccak.toFixed(2)}% · MAC {workloadShares[workload].fast.matrix.toFixed(2)}%</small></div>
              </div>
              <div className="model-output">
                <div className="speedup-orbit"><span>이론상 전체</span><strong>{amdahl.speedup.toFixed(2)}×</strong><small>무한 가속 ceiling {amdahl.ceiling.toFixed(2)}×</small></div>
                <div className="after-bars"><div><span>가속 후 SHAKE</span><b>{amdahl.keccak.toFixed(1)}%</b></div><div className="after-track"><i className="keccak" style={{ width: `${amdahl.keccak}%` }} /><i className="matrix" style={{ width: `${amdahl.matrix}%` }} /><i className="other" style={{ width: `${amdahl.other}%` }} /></div><p>MAC {amdahl.matrix.toFixed(1)}% · 기타/전송/직렬화 {amdahl.other.toFixed(1)}%</p></div>
              </div>
            </div>
            <div className="model-warning"><StatusTag kind="modeled">MODEL ≠ SILICON</StatusTag><p>KMAC handshake, WSR share recombination, DMEM bandwidth, vector setup, pipeline latency를 포함하지 않았습니다. 이 그래프는 설계 우선순위와 이론상 ceiling을 보여주며 cycle 예측값은 아닙니다.</p></div>
          </section>

          <section className="chapter" id="method">
            <div className="chapter-head"><span>07</span><div><p>MEASUREMENT BOUNDARY</p><h2>실측·정적 모델·다음 실험을 분리합니다</h2></div></div>
            <div className="method-grid">
              <article><StatusTag kind="measured">MEASURED</StatusTag><h3>호스트 프로파일</h3><ul><li>Apple arm64 · macOS 26.5.2</li><li>Apple clang 21.0.0 · <code>-O3</code></li><li>100 iterations × 9 trials</li><li>trial 중앙값 · wall-clock ns/op</li><li>REFERENCE / FAST_GENERIC KAT 통과</li></ul></article>
              <article><StatusTag kind="exact">EXACT</StatusTag><h3>알고리즘 trip count</h3><ul><li>n=640, n̄=8에서 식으로 계산</li><li>MAC·샘플·CDF 비교·Keccak round</li><li>플랫폼과 무관, 파라미터에는 종속</li><li>소스 반복문과 교차 확인</li></ul></article>
              <article><StatusTag kind="modeled">MODELED</StatusTag><h3>ISA 정적 비용</h3><ul><li>issue-slot lower bound</li><li>RVV128: 8×16 MAC</li><li>OTBN: 8×32 SIMD + KMAC interface</li><li>메모리·stall·handshake 제외</li></ul></article>
            </div>

            <div className="next-experiment">
              <div><span>NEXT MEASUREMENT</span><h3>같은 region ID를 target counter로 옮기기</h3></div>
              <ol><li><b>RISC-V</b><span>mcycle / minstret + vector instruction mix</span></li><li><b>OTBN</b><span>INSN_CNT + KMAC session/beat + DMEM load/store</span></li><li><b>비교</b><span>region별 cycle, instruction, bytes moved를 동일 CSV schema로 수집</span></li></ol>
            </div>

            <div className="source-cards">
              <a href="https://docs.riscv.org/reference/isa/unpriv/v-st-ext" target="_blank" rel="noreferrer"><span>OFFICIAL SPEC</span><strong>RISC‑V Vector v1.0</strong><small>vmacc, widening MAC, VLEN/SEW</small></a>
              <a href="https://opentitan.org/book/hw/ip/otbn/doc/isa.html" target="_blank" rel="noreferrer"><span>OFFICIAL SPEC</span><strong>OTBN ISA Guide</strong><small>BN SIMD, LOOPI, WDR</small></a>
              <a href="https://opentitan.org/book/hw/ip/otbn/doc/theory_of_operation.html" target="_blank" rel="noreferrer"><span>OFFICIAL SPEC</span><strong>OTBN KMAC interface</strong><small>SHAKE offload, WSR data path</small></a>
            </div>

            <footer><div><span>FRODOKEM CO-DESIGN ATLAS</span><p>source profile commit 7a4e721 · web edition</p></div><a href="#top">처음으로 ↑</a></footer>
          </section>
        </article>
      </div>
    </main>
  );
}
