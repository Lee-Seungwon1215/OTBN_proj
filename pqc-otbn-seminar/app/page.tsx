"use client";

import { useCallback, useEffect, useMemo, useRef, useState } from "react";

const slideMeta = [
  ["OPEN", "RISC-V × OTBN"],
  ["QUESTION", "무엇을 가속할까"],
  ["FOUNDATION", "RISC-V는 호스트"],
  ["FOUNDATION", "OTBN은 보안 코프로세서"],
  ["COMPARE", "둘은 무엇이 다른가"],
  ["HARDWARE", "OpenTitan 전체 구조"],
  ["BUS", "TL-UL 버스 해부"],
  ["EXECUTION", "사람이 실행하면"],
  ["DATAPATH", "OTBN 내부에서는"],
  ["KMAC", "KMAC은 별도 HWIP"],
  ["SYSTEM", "전송도 실행시간이다"],
  ["PQC", "세 알고리즘의 얼굴"],
  ["PROFILE", "3 × 3 병목 지도"],
  ["FRODO", "행렬보다 SHAKE"],
  ["HQC", "vect_mul 1순위"],
  ["McELIECE", "단계마다 다른 답"],
  ["CUSTOM", "명령어 확장의 의미"],
  ["DECISION", "어디부터 시작할까"],
  ["ROADMAP", "측정 가능한 구현 순서"],
  ["SECURITY", "빠르고 안전하게"],
  ["CLOSE", "한 장으로 정리"],
] as const;

const profileRows = [
  { name: "FrodoKEM", color: "violet", cells: [["SHAKE", "90.48%"], ["SHAKE", "89.28%"], ["SHAKE", "88.38%"]] },
  { name: "HQC", color: "lime", cells: [["vect_mul", "97.8%"], ["vect_mul", "97.7%"], ["vect_mul", "95.857%"]] },
  { name: "McEliece", color: "cyan", cells: [["GE", "60.0%"], ["syndrome", "46.96%"], ["GF decoder", "88.08%"]] },
];

function Arrow({ label, vertical = false }: { label?: string; vertical?: boolean }) {
  return <div className={vertical ? "flow-arrow vertical" : "flow-arrow"}><i />{label && <span>{label}</span>}</div>;
}

function Badge({ children, tone = "violet" }: { children: React.ReactNode; tone?: string }) {
  return <span className={`badge ${tone}`}>{children}</span>;
}

function SlideHeading({ kicker, title, note }: { kicker: string; title: React.ReactNode; note?: string }) {
  return (
    <header className="slide-heading">
      <p>{kicker}</p>
      <h2>{title}</h2>
      {note && <span>{note}</span>}
    </header>
  );
}

function MiniTopology() {
  return (
    <div className="mini-topology" aria-label="RISC-V 호스트, TL-UL 버스, OTBN 및 KMAC 구조">
      <div className="topo-node host"><small>32-bit CPU</small><b>RISC-V</b><span>HOST</span></div>
      <Arrow label="TL-UL" />
      <div className="topo-fanout">
        <div className="topo-node otbn"><small>256-bit</small><b>OTBN</b><span>CO-PROCESSOR</span></div>
        <div className="topo-node kmac"><small>Keccak</small><b>KMAC</b><span>HASH HWIP</span></div>
      </div>
    </div>
  );
}

function SlideContent({ index }: { index: number }) {
  switch (index) {
    case 0:
      return (
        <div className="cover-layout">
          <div className="cover-copy">
            <p className="overline">PQC ACCELERATION SEMINAR</p>
            <h1>RISC‑V<br /><em>×</em> OTBN</h1>
            <p>FrodoKEM · HQC · Classic McEliece<br /><b>병목에서 명령어셋까지</b></p>
            <div className="cover-tags"><Badge>CODE</Badge><Badge tone="lime">CLOCK</Badge><Badge tone="cyan">BUS</Badge><Badge tone="coral">SECURITY</Badge></div>
          </div>
          <MiniTopology />
        </div>
      );

    case 1:
      return (
        <>
          <SlideHeading kicker="THE ONE QUESTION" title={<>“연산이 크다”만으로<br /><em>OTBN에 보내도 될까?</em></>} />
          <div className="question-chain">
            <article><span>01</span><b>코드</b><p>무엇이 가장 많이 반복되는가?</p></article>
            <Arrow />
            <article><span>02</span><b>시계</b><p>실제 시간은 어디서 사라지는가?</p></article>
            <Arrow />
            <article><span>03</span><b>구조</b><p>데이터가 어디를 건너는가?</p></article>
            <Arrow />
            <article className="accent"><span>04</span><b>결정</b><p>RISC‑V, KMAC, OTBN 중 어디인가?</p></article>
          </div>
          <div className="quote-strip">가속 대상은 <strong>연산식</strong>이 아니라 <strong>실측 병목 × 데이터 경로 × 호출 패턴</strong>이다.</div>
        </>
      );

    case 2:
      return (
        <>
          <SlideHeading kicker="GENERAL-PURPOSE CONTROL" title={<>RISC‑V는 시스템을 움직이는 <em>호스트</em></>} note="C도 되고, 직접 쓴 .S도 된다." />
          <div className="split-wide">
            <div className="code-pipeline">
              <div className="file-card"><span>main.c</span><code>hqc_decaps(ct, sk);</code><small>보통의 구현</small></div>
              <div className="or-label">OR</div>
              <div className="file-card"><span>kernel.S</span><code>clmul a0, a1, a2</code><small>직접 어셈블리</small></div>
              <Arrow label="compiler / assembler" vertical />
              <div className="isa-strip"><b>RV32I</b><b>M</b><b>Zbc</b><b>RVV</b><b className="custom">CUSTOM</b></div>
            </div>
            <div className="cpu-card">
              <div className="chip-title"><span>RISC‑V CORE</span><Badge tone="lime">32-bit</Badge></div>
              <div className="cpu-grid"><div>Fetch</div><div>Decode</div><div>ALU</div><div>GPR</div></div>
              <p>운영 · 메모리 · 주변장치 · OTBN/KMAC 제어</p>
            </div>
          </div>
          <div className="bottom-answer"><b>정리</b><span>RISC‑V 최적화는 공개 확장만 쓰는 것도, 코어에 커스텀 명령을 추가하는 것도 모두 가능하다.</span></div>
        </>
      );

    case 3:
      return (
        <>
          <SlideHeading kicker="SECURITY CO-PROCESSOR" title={<>OTBN은 256-bit 데이터 경로를 가진 <em>별도 프로세서</em></>} note="RISC‑V에서 영감을 받았지만 바이너리 호환 ISA는 아니다." />
          <div className="otbn-intro">
            <div className="assembly-sheet"><span>pqc_kernel.s</span><code>.section .text.start<br />  jal x0, main<br /><br />main:<br />  bn.lid x2, 0(x10)<br />  bn.xor w2, w0, w1<br />  ecall</code><small>OTBN 앱은 보통 어셈블리로 작성</small></div>
            <Arrow label="assemble + link" />
            <div className="otbn-chip">
              <div><span>CONTROL</span><b>32 × 32-bit GPR</b><small>분기 · 주소 · 루프</small></div>
              <div><span>DATA</span><b>32 × 256-bit WDR</b><small>큰 수 · SIMD 연산</small></div>
              <div className="hot"><span>EXECUTE</span><b>BN ALU / custom</b><small>보안 연산</small></div>
            </div>
          </div>
          <div className="three-points"><span>자체 IMEM</span><span>자체 DMEM</span><span>SCA·FI 대응 중심</span></div>
        </>
      );

    case 4:
      return (
        <>
          <SlideHeading kicker="RISC-V ≠ OTBN" title={<>같은 어셈블리처럼 보여도 <em>역할과 ISA가 다르다</em></>} />
          <div className="compare-table">
            <div className="compare-head"><span>구분</span><b>RISC‑V</b><b>OTBN</b></div>
            {[
              ["역할", "범용 호스트 CPU", "보안 연산 코프로세서"],
              ["주 데이터 폭", "32/64-bit, 선택적 Vector", "256-bit WDR"],
              ["프로그램", "C/C++ 또는 .S", "주로 OTBN .s"],
              ["메모리", "시스템 SRAM/Flash", "전용 IMEM + DMEM"],
              ["명령어", "표준 확장 + custom 가능", "OTBN 전용 base + BN"],
              ["관계", "작업 준비·시작·회수", "전달받은 커널 실행"],
            ].map((row) => <div className="compare-row" key={row[0]}><span>{row[0]}</span><p>{row[1]}</p><p>{row[2]}</p></div>)}
          </div>
          <div className="warning-note">OTBN base 명령은 RV32I에서 영감을 받았지만 <b>RISC‑V 호환 프로세서가 아니다.</b></div>
        </>
      );

    case 5:
      return (
        <>
          <SlideHeading kicker="OPENTITAN SYSTEM VIEW" title={<>코어와 가속기는 <em>TL‑UL fabric</em> 위에서 만난다</>} note="간략화한 논리 구조 — 실제 top은 더 많은 IP와 crossbar를 포함한다." />
          <div className="soc-map">
            <div className="soc-hosts">
              <div className="soc-block ibex"><small>BUS HOST</small><b>Ibex RISC‑V</b><span>instruction + data</span></div>
              <div className="soc-block debug"><small>OTHER HOST</small><b>Debug / DMA</b><span>구성에 따라</span></div>
            </div>
            <div className="tl-fabric">
              <span>TL‑UL CROSSBAR</span>
              <div className="fabric-lines"><i /><i /><i /><i /></div>
              <b>address decode · routing · response steering</b>
            </div>
            <div className="soc-devices">
              <div className="soc-block memory"><small>DEVICE</small><b>SRAM / Flash</b><span>pk · sk · ct</span></div>
              <div className="soc-block otbn"><small>DEVICE</small><b>OTBN</b><span>CSR · IMEM · DMEM</span></div>
              <div className="soc-block kmac"><small>DEVICE</small><b>KMAC</b><span>MSG_FIFO · STATE</span></div>
              <div className="soc-block peri"><small>DEVICE</small><b>Peripherals</b><span>UART · GPIO · …</span></div>
            </div>
          </div>
          <div className="bus-legend"><Badge>HOST가 요청</Badge><span>→</span><Badge tone="cyan">주소로 DEVICE 선택</Badge><span>→</span><Badge tone="lime">응답을 원래 HOST로</Badge></div>
        </>
      );

    case 6:
      return (
        <>
          <SlideHeading kicker="TL-UL BUS ANATOMY" title={<>버스는 “선”이 아니라 <em>요청과 응답의 약속</em></>} />
          <div className="bus-anatomy">
            <div className="endpoint host-end"><span>HOST</span><b>Ibex</b></div>
            <div className="channel-stack">
              <div className="channel a"><b>A · Request</b><code>a_opcode · a_address · a_data · a_mask · a_source</code><span>PutFull / PutPartial / Get →</span></div>
              <div className="channel d"><b>D · Response</b><code>d_opcode · d_data · d_error · d_source</code><span>← AccessAck / AccessAckData</span></div>
            </div>
            <div className="endpoint device-end"><span>DEVICE</span><b>OTBN</b></div>
          </div>
          <div className="bus-facts">
            <article><strong>32</strong><span>bit data width<br />현재 OpenTitan 기본</span></article>
            <article><strong>1</strong><span>request / cycle<br />최대</span></article>
            <article><strong>1</strong><span>response / cycle<br />최대</span></article>
            <article className="no-burst"><strong>×</strong><span>burst 없음<br />큰 복사는 word 반복</span></article>
          </div>
          <p className="source-note">따라서 256-bit WDR 하나의 입력도 외부 버스에서는 여러 32-bit 전송으로 채워진다.</p>
        </>
      );

    case 7:
      return (
        <>
          <SlideHeading kicker="FROM LAPTOP TO SILICON" title={<>사람이 실행 버튼을 누르면 <em>8단계</em>가 흐른다</>} />
          <div className="timeline">
            {[
              ["01", "BUILD", ".s → OTBN binary"],
              ["02", "LOAD", "binary → IMEM"],
              ["03", "INPUT", "args → DMEM"],
              ["04", "COMMAND", "CMD.EXECUTE"],
              ["05", "FETCH", "IMEM → decoder"],
              ["06", "COMPUTE", "DMEM ↔ WDR ↔ ALU"],
              ["07", "ECALL", "done + internal wipe"],
              ["08", "READ", "DMEM → RISC‑V"],
            ].map((step, i) => <div className={i === 4 || i === 5 ? "active" : ""} key={step[0]}><span>{step[0]}</span><b>{step[1]}</b><small>{step[2]}</small></div>)}
          </div>
          <div className="busy-rule">
            <div><span>IDLE</span><b>Host가 IMEM·DMEM 접근 가능</b></div>
            <Arrow />
            <div className="locked"><span>BUSY</span><b>Host 접근 금지 · OTBN이 독점 실행</b></div>
            <Arrow />
            <div><span>DONE</span><b>Host가 결과 DMEM 읽기</b></div>
          </div>
        </>
      );

    case 8:
      return (
        <>
          <SlideHeading kicker="INSIDE OTBN" title={<>IMEM은 복사 후에도 매 순간 <em>다음 명령을 공급</em>한다</>} />
          <div className="datapath">
            <div className="memory-tower imem"><span>IMEM · 4 KiB</span><b>instruction</b><i /><i /><i /><small>PC로 매 cycle fetch</small></div>
            <Arrow />
            <div className="front-end"><div><span>FETCH</span><b>PC</b></div><div><span>DECODE</span><b>control</b></div><div><span>32-bit</span><b>GPR</b></div></div>
            <Arrow />
            <div className="wide-path"><div className="wdr"><span>32 × WDR</span><b>256-bit</b></div><div className="bnalu"><span>BN / CUSTOM ALU</span><b>ADD · XOR · SHIFT · MUL</b></div></div>
            <Arrow />
            <div className="memory-tower dmem"><span>DMEM · 4 KiB</span><b>data</b><i /><i /><i /><small>Host-visible 3 KiB</small></div>
          </div>
          <div className="clarify-grid">
            <article><b>IMEM</b><p>“무엇을 할지”를 저장하고 fetch/decode에 계속 공급</p></article>
            <article><b>DMEM</b><p>“무엇으로 할지”를 저장; 스스로 연산하지 않음</p></article>
            <article><b>WDR + ALU</b><p>명령에 따라 데이터를 가져와 실제 연산</p></article>
          </div>
        </>
      );

    case 9:
      return (
        <>
          <SlideHeading kicker="KMAC IS NOT AN INSTRUCTION" title={<>KMAC은 OTBN 옆의 <em>별도 하드웨어 IP</em></>} note="SHA3 · SHAKE · cSHAKE · KMAC을 수행하는 Keccak 가속기" />
          <div className="kmac-paths">
            <div className="default-path">
              <span className="path-label">EARLGREY 기본 SW 경로</span>
              <div><b>RISC‑V</b><small>MSG_FIFO 기록</small></div><Arrow label="TL-UL" /><div className="kmac-big"><b>KMAC</b><small>Keccak sponge</small></div><Arrow label="TL-UL" /><div><b>SRAM</b><small>digest / SHAKE output</small></div><Arrow label="TL-UL" /><div><b>OTBN DMEM</b><small>필요하면 재전송</small></div>
            </div>
            <div className="custom-path">
              <span className="path-label">연구용 직접 경로</span>
              <div><b>KMAC</b></div><Arrow label="new inter-module interface" /><div><b>OTBN</b></div><p>가능하지만 <strong>OTBN 명령 하나 추가</strong>로 끝나지 않는다.<br />top-level 연결 · handshake · 보안 검증이 필요하다.</p>
            </div>
          </div>
          <div className="correction"><b>핵심 정정</b><span>“KMAC↔OTBN 전송”은 기본 직접 링크가 아니라, 일반적으로 RISC‑V가 양쪽 HWIP를 조정하며 발생하는 시스템 데이터 이동이다.</span></div>
        </>
      );

    case 10:
      return (
        <>
          <SlideHeading kicker="BOUNDARY TAX" title={<>OTBN 왕복이 이기는 조건은 <em>계산이 경계보다 클 때</em></>} />
          <div className="latency-equation">
            <div><span>①</span><b>setup</b><small>command</small></div><i>+</i><div><span>②</span><b>copy in</b><small>TL‑UL → DMEM</small></div><i>+</i><div className="compute"><span>③</span><b>compute</b><small>WDR / ALU</small></div><i>+</i><div><span>④</span><b>copy out</b><small>DMEM → TL‑UL</small></div><i>=</i><div className="total"><span>T</span><b>end-to-end</b></div>
          </div>
          <div className="offload-contrast">
            <article><span>나쁜 분할</span><div className="micro-bars">{Array.from({ length: 8 }).map((_, i) => <i key={i} />)}</div><b>작은 함수마다 8번 왕복</b><p>setup·복사 비용이 반복</p></article>
            <article className="good"><span>좋은 분할</span><div className="macro-bar"><i /></div><b>상태를 DMEM/WDR에 두고 묶어서 실행</b><p>고정 패턴으로 여러 연산 재사용</p></article>
          </div>
          <div className="rule-line">커널 cycle만 측정하면 <b>가속처럼 보일 수 있다.</b> 결론은 반드시 transfer-inclusive로 낸다.</div>
        </>
      );

    case 11:
      return (
        <>
          <SlideHeading kicker="THREE PQC PERSONALITIES" title={<>세 알고리즘은 <em>병목의 모양부터 다르다</em></>} note="수학보다 코드의 반복 구조로 본 요약" />
          <div className="algo-cards">
            <article className="frodo"><div className="algo-mark">FR</div><h3>FrodoKEM</h3><b>SHAKE로 A 생성<br />+ 정수 행렬 MAC</b><div className="motif matrix">{Array.from({ length: 16 }).map((_, i) => <i key={i} />)}</div><p>구현 최적화에 따라 SHAKE ↔ MAC 병목이 뒤집힌다.</p></article>
            <article className="hqc"><div className="algo-mark">HQ</div><h3>HQC</h3><b>긴 GF(2) 다항식<br />carry-less 순환 곱</b><div className="motif bits"><i /><i /><i /><i /><i /><i /><i /><i /></div><p>vect_mul이 모든 KEM 단계에서 압도적이다.</p></article>
            <article className="mce"><div className="algo-mark">CM</div><h3>Classic McEliece</h3><b>이진 행렬 + GF(2ᵐ)<br />오류정정 디코딩</b><div className="motif decoder"><i /><i /><i /><i /><i /></div><p>KeyGen·Encaps·Decaps의 병목이 서로 다르다.</p></article>
          </div>
        </>
      );

    case 12:
      return (
        <>
          <SlideHeading kicker="MEASURED BOTTLENECKS" title={<>3개 알고리즘 × 3개 단계의 <em>실측 1순위</em></>} note="비율은 각 단계 내부 점유율; 절대시간과는 다른 축" />
          <div className="profile-map">
            <div className="profile-head"><span>ALGORITHM</span><b>KEYGEN</b><b>ENCAPS</b><b>DECAPS</b></div>
            {profileRows.map((row) => <div className="profile-row" key={row.name}><strong>{row.name}</strong>{row.cells.map((cell, i) => <div className={row.color} key={i}><span>{cell[0]}</span><b>{cell[1]}</b><i style={{ height: cell[1] }} /></div>)}</div>)}
          </div>
          <div className="absolute-times"><span>Frodo <b>1.340 / 1.443 / 1.380 ms</b></span><span>HQC <b>0.80 / 1.58 / 2.41 ms</b></span><span>McEliece <b>28.123 ms / 8.291 µs / 108.660 µs</b></span></div>
        </>
      );

    case 13:
      return (
        <>
          <SlideHeading kicker="FRODOKEM" title={<>코드는 행렬을 가리켰지만<br /><em>fast_generic의 시계는 SHAKE</em></>} />
          <div className="code-clock">
            <div className="code-side"><span>CODE</span><strong>3,276,800</strong><b>큰 행렬 MAC</b><small>정적 반복량 1위</small></div>
            <div className="flip">≠</div>
            <div className="clock-side"><span>CLOCK</span><strong>88–90%</strong><b>SHAKE / Keccak</b><small>A의 640개 행 생성</small></div>
          </div>
          <div className="implementation-flip"><div><span>reference</span><b>MAC 61.25%</b><i><em style={{ width: "61.25%" }} /></i></div><Arrow /><div><span>fast_generic</span><b>SHAKE 89.28%</b><i><em style={{ width: "89.28%" }} /></i></div></div>
          <div className="mapping-callout"><Badge tone="violet">1차 후보 · KMAC</Badge><p>A 행을 SHAKE로 생성. 단, 출력이 OTBN 계산에 필요하면 <b>KMAC → 시스템 메모리 → OTBN DMEM</b> 이동까지 포함해 측정한다.</p></div>
        </>
      );

    case 14:
      return (
        <>
          <SlideHeading kicker="HQC" title={<>코드와 시계가 모두 <em>vect_mul</em>을 가리킨다</>} />
          <div className="hqc-hero">
            <div className="mul-wheel"><span>GF(2)</span><b>vect_mul</b><small>cyclic · carry-less</small></div>
            <div className="hqc-stages"><div><span>KEYGEN · ×1</span><b>97.8%</b></div><div><span>ENCAPS · ×2</span><b>97.7%</b></div><div><span>DECAPS · ×3</span><b>95.857%</b></div></div>
            <div className="inner-count"><span>ONE CALL</span><strong>1,219,456</strong><b>schoolbook inner bodies</b></div>
          </div>
          <div className="instruction-lane"><div><span>RISC‑V 기준선</span><b>Zbc · CLMUL/CLMULH</b></div><Arrow /><div><span>OTBN 매핑</span><b>256-bit WDR · XOR · SHIFT</b></div><Arrow /><div className="custom"><span>연구 확장</span><b>custom carry-less multiply</b></div></div>
          <div className="mapping-callout"><Badge tone="lime">최적화 1순위</Badge><p>호출 비중이 압도적이고 세 단계에서 재사용되며, 필요한 primitive가 명확하다. <b>첫 OTBN 실험으로 가장 깨끗하다.</b></p></div>
        </>
      );

    case 15:
      return (
        <>
          <SlideHeading kicker="CLASSIC McELIECE" title={<>하나의 이름, <em>세 개의 아키텍처 문제</em></>} />
          <div className="mce-stages">
            <article><span>KEYGEN</span><strong>60.0%</strong><b>가우스 소거군</b><p>pk_gen 평균 3.445회<br />pivot 실패 70.98%</p><Badge tone="cyan">RVV / memory 구조</Badge></article>
            <article><span>ENCAPS</span><strong>46.96%</strong><b>syndrome scan</b><p>공개키 약 261 KiB<br />메모리 대역폭 중심</p><Badge tone="coral">memory-attached</Badge></article>
            <article><span>DECAPS</span><strong>88.08%</strong><b>GF · FFT · BM</b><p>bitsliced GF(2¹²)<br />vec_mul 1,389회</p><Badge>OTBN 후보</Badge></article>
          </div>
          <div className="working-set"><span>OTBN DMEM</span><b>4 KiB total · host-visible 3 KiB</b><i>vs</i><span>McEliece data</span><b>행렬 ≈402 KiB · pk ≈261 KiB · decoder ≈18 KiB</b></div>
          <p className="source-note">그래서 “McEliece 전체를 OTBN으로”가 아니라, <b>Decaps의 작고 반복적인 GF primitive</b>부터 분리한다.</p>
        </>
      );

    case 16:
      return (
        <>
          <SlideHeading kicker="CUSTOM INSTRUCTION ≠ ONE LINE" title={<>“CLMUL 확장 OTBN”은 <em>공식 명령 이름이 아니라 연구 설계</em></>} />
          <div className="extension-stack">
            {[
              ["01", "연산 의미", "carry-less product · lane · latency · flags"],
              ["02", "ISA encoding", "opcode / operand / WDR mapping"],
              ["03", "RTL datapath", "decoder + CLMUL unit + writeback"],
              ["04", "toolchain", "assembler · objdump · linker metadata"],
              ["05", "models", "ISS · simulator · reference model"],
              ["06", "verification", "DV · formal · constant-time · SCA"],
            ].map((row) => <div key={row[0]}><span>{row[0]}</span><b>{row[1]}</b><p>{row[2]}</p></div>)}
          </div>
          <div className="two-extensions"><div><Badge tone="lime">RISC‑V custom</Badge><p>호스트 코어의 RTL·compiler intrinsic까지 확장</p></div><div><Badge tone="cyan">OTBN custom</Badge><p>OTBN WDR 데이터 경로와 전용 assembler/ISS까지 확장</p></div></div>
        </>
      );

    case 17:
      return (
        <>
          <SlideHeading kicker="DECISION MATRIX" title={<>첫 타깃은 <em>HQC vect_mul</em></>} note="단, 최종 선택은 실제 workload 횟수까지 곱해서 결정" />
          <div className="decision-matrix">
            <div className="decision-head"><span>후보</span><b>병목 집중</b><b>OTBN 적합</b><b>전송 위험</b><b>결정</b></div>
            <div><strong>Frodo SHAKE</strong><i className="dots"><em /><em /><em /></i><i className="dots"><em /><em /></i><i className="dots danger"><em /><em /><em /></i><Badge>KMAC 먼저</Badge></div>
            <div className="winner"><strong>HQC vect_mul</strong><i className="dots"><em /><em /><em /></i><i className="dots"><em /><em /><em /></i><i className="dots"><em /></i><Badge tone="lime">P0 · 시작</Badge></div>
            <div><strong>McE Decaps GF</strong><i className="dots"><em /><em /><em /></i><i className="dots"><em /><em /></i><i className="dots danger"><em /><em /></i><Badge tone="cyan">P1 · 다음</Badge></div>
          </div>
          <div className="workload-switch"><div><span>1 : 1 : 1</span><b>McEliece KeyGen 절대시간이 큼</b></div><Arrow /><div><span>1 : 100 : 100</span><b>HQC/Frodo 통신 경로가 누적</b></div></div>
        </>
      );

    case 18:
      return (
        <>
          <SlideHeading kicker="IMPLEMENTATION ROADMAP" title={<>가속률이 아니라 <em>증거를 한 층씩 쌓는다</em></>} />
          <div className="roadmap">
            {[
              ["01", "RISC‑V baseline", "scalar → Zbc/RVV", "cycles · bytes"],
              ["02", "OTBN vanilla", "WDR + 기존 ISA", "kernel only"],
              ["03", "custom CLMUL", "RTL + toolchain", "primitive gain"],
              ["04", "transfer included", "IMEM/DMEM + CMD", "end-to-end"],
              ["05", "full KEM", "Key/Enc/Dec", "system gain"],
              ["06", "security", "CT + SCA + wipe", "accept / reject"],
            ].map((row, i) => <article key={row[0]}><span>{row[0]}</span><div><small>{row[1]}</small><b>{row[2]}</b><p>{row[3]}</p></div>{i < 5 && <i>→</i>}</article>)}
          </div>
          <div className="measurement-formula"><b>보고할 숫자</b><span>cycles / call</span><span>bytes transferred</span><span>calls / KEM</span><span>total cycles / KEM</span><span>area + leakage</span></div>
        </>
      );

    case 19:
      return (
        <>
          <SlideHeading kicker="SECURITY GUARDRAILS" title={<>재사용이 위험한 것이 아니라<br /><em>비밀 의존 패턴이 위험하다</em></>} />
          <div className="security-split">
            <div className="safe"><h3>✓ 가능한 재사용</h3><div><b>고정 반복 수</b><span>공개 파라미터에만 의존</span></div><div><b>고정 주소 패턴</b><span>같은 타일·같은 순서</span></div><div><b>DMEM/WDR 상태 유지</b><span>왕복을 줄이고 마지막에 wipe</span></div></div>
            <div className="unsafe"><h3>! 피해야 할 패턴</h3><div><b>secret-dependent branch</b><span>비밀에 따라 조기 종료</span></div><div><b>secret-dependent address</b><span>테이블 접근 위치 변화</span></div><div><b>가변 retry / tile count</b><span>실행시간·전력 흔적 변화</span></div></div>
          </div>
          <div className="security-footer"><span>상수시간</span><i>+</i><span>OTBN INSN_CNT</span><i>+</i><span>internal secure wipe</span><i>+</i><span>TVLA / leakage test</span></div>
        </>
      );

    default:
      return (
        <>
          <SlideHeading kicker="TAKEAWAY" title={<>연산을 고르지 말고<br /><em>데이터 경로를 고른다</em></>} />
          <div className="final-flow"><div><span>1</span><b>PROFILE</b><small>코드상 ≠ 실측상</small></div><Arrow /><div><span>2</span><b>PLACE</b><small>RISC‑V · KMAC · OTBN</small></div><Arrow /><div><span>3</span><b>MOVE</b><small>TL‑UL · IMEM · DMEM</small></div><Arrow /><div><span>4</span><b>VERIFY</b><small>end-to-end · CT · SCA</small></div></div>
          <div className="final-answer"><span>FIRST MOVE</span><h3>HQC `vect_mul`</h3><p>RISC‑V Zbc 기준선 → OTBN WDR 매핑 → custom CLMUL → 전송 포함 KEM 비교</p></div>
          <div className="sources">
            <span>PRIMARY REFERENCES</span>
            <a href="https://opentitan.org/book/hw/ip/otbn/" target="_blank" rel="noreferrer">OTBN Technical Specification ↗</a>
            <a href="https://opentitan.org/book/hw/ip/otbn/doc/developers_guide.html" target="_blank" rel="noreferrer">OTBN Developer’s Guide ↗</a>
            <a href="https://opentitan.org/book/hw/ip/tlul/" target="_blank" rel="noreferrer">TL‑UL Bus Specification ↗</a>
            <a href="https://opentitan.org/book/hw/ip/kmac/" target="_blank" rel="noreferrer">KMAC Technical Specification ↗</a>
          </div>
        </>
      );
  }
}

export default function Home() {
  const [slide, setSlide] = useState(0);
  const [outline, setOutline] = useState(false);
  const touchStart = useRef<number | null>(null);
  const last = slideMeta.length - 1;
  const go = useCallback((next: number) => setSlide(Math.max(0, Math.min(last, next))), [last]);

  useEffect(() => {
    const onKeyDown = (event: KeyboardEvent) => {
      if (["ArrowRight", "ArrowDown", "PageDown", " "].includes(event.key)) { event.preventDefault(); go(slide + 1); }
      if (["ArrowLeft", "ArrowUp", "PageUp"].includes(event.key)) { event.preventDefault(); go(slide - 1); }
      if (event.key === "Home") go(0);
      if (event.key === "End") go(last);
      if (event.key.toLowerCase() === "o") setOutline((value) => !value);
    };
    window.addEventListener("keydown", onKeyDown);
    return () => window.removeEventListener("keydown", onKeyDown);
  }, [go, last, slide]);

  const progress = useMemo(() => `${((slide + 1) / slideMeta.length) * 100}%`, [slide]);

  return (
    <main className="deck-shell" onTouchStart={(event) => { touchStart.current = event.touches[0]?.clientX ?? null; }} onTouchEnd={(event) => { if (touchStart.current === null) return; const delta = (event.changedTouches[0]?.clientX ?? touchStart.current) - touchStart.current; if (Math.abs(delta) > 55) go(slide + (delta < 0 ? 1 : -1)); touchStart.current = null; }}>
      <div className="progress" style={{ width: progress }} />
      <header className="deck-topbar">
        <button className="deck-brand" onClick={() => go(0)}><i /><span>PQC / RISC‑V × OTBN</span></button>
        <div className="deck-status"><span>{slideMeta[slide][0]}</span><b>{String(slide + 1).padStart(2, "0")} / {slideMeta.length}</b></div>
        <button className="outline-toggle" onClick={() => setOutline(!outline)} aria-expanded={outline}>목차 <span>⌘ O</span></button>
      </header>

      <aside className={outline ? "outline open" : "outline"} aria-label="발표 목차">
        <div className="outline-head"><span>SEMINAR OUTLINE</span><button onClick={() => setOutline(false)}>닫기 ×</button></div>
        <div className="outline-grid">{slideMeta.map((item, index) => <button key={`${item[0]}-${index}`} className={slide === index ? "active" : ""} onClick={() => { go(index); setOutline(false); }}><span>{String(index + 1).padStart(2, "0")}</span><small>{item[0]}</small><b>{item[1]}</b></button>)}</div>
      </aside>

      <section className={`slide slide-${slide}`} aria-live="polite" aria-label={`${slide + 1}번 슬라이드 ${slideMeta[slide][1]}`}>
        <SlideContent index={slide} />
      </section>

      <footer className="deck-controls">
        <div className="key-hint"><span>←</span><span>→</span><p>키보드 · 화면 스와이프</p></div>
        <div className="slide-dots">{slideMeta.map((_, index) => <button key={index} className={slide === index ? "active" : ""} onClick={() => go(index)} aria-label={`${index + 1}번 슬라이드로 이동`} />)}</div>
        <div className="nav-buttons"><button onClick={() => go(slide - 1)} disabled={slide === 0}>←</button><button onClick={() => go(slide + 1)} disabled={slide === last}>다음 <span>→</span></button></div>
      </footer>
    </main>
  );
}
