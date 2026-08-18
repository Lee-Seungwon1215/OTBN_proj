const chapters = [
  ["chapter-1", "1. HQC가 하는 일"],
  ["chapter-2", "2. 비트와 XOR"],
  ["chapter-3", "3. 희소 벡터"],
  ["chapter-4", "4. 순환 곱셈"],
  ["chapter-5", "5. 오류정정부호"],
  ["chapter-6", "6. 키 생성"],
  ["chapter-7", "7. 캡슐화"],
  ["chapter-8", "8. 디캡슐화"],
  ["chapter-9", "9. 안전성 검사"],
  ["chapter-10", "10. 파라미터와 코드"],
  ["chapter-11", "11. 실측 프로파일링"],
  ["chapter-12", "12. 병목 반복문"],
  ["chapter-13", "13. 공통 primitive"],
];

const terms = [
  ["KEM", "두 사람이 인터넷을 통해 같은 공유키를 만드는 방식"],
  ["캡슐화", "공개키로 암호문과 공유키를 만드는 과정"],
  ["디캡슐화", "비밀키로 암호문에서 공유키를 복구하는 과정"],
  ["벡터", "0과 1이 길게 나열된 비트열"],
  ["해밍 무게", "비트열 안에 들어 있는 1의 개수"],
  ["희소 벡터", "길이에 비해 1이 매우 적은 비트열"],
  ["부호어", "오류가 생겨도 복구할 수 있도록 여분 정보를 붙인 메시지"],
  ["QCSD", "공개된 준순환 관계에서 작은 오류 또는 희소 비밀을 찾는 어려운 문제"],
  ["Seed", "긴 무작위 값을 똑같이 다시 만드는 짧은 초기값"],
  ["Implicit rejection", "잘못된 암호문에 오류 대신 대체 공유키를 돌려주는 방식"],
  ["프로파일링", "프로그램이 실제로 어느 함수에서 시간을 쓰는지 측정하는 작업"],
  ["Primitive", "여러 상위 함수가 공통으로 사용하는 작고 기본적인 연산 블록"],
  ["Carry-less 곱셈", "자리올림 없이 비트 AND와 XOR로 계산하는 GF(2) 다항식 곱셈"],
];

const kemTimings = [
  { variant: "HQC-1", keygen: 0.8, encaps: 1.58, decaps: 2.41 },
  { variant: "HQC-3", keygen: 2.4, encaps: 4.76, decaps: 7.21 },
  { variant: "HQC-5", keygen: 5.97, encaps: 12.08, decaps: 18.21 },
];

const mulShares = [
  { variant: "HQC-1", keygen: 97.8, encaps: 97.7, decaps: 95.9 },
  { variant: "HQC-3", keygen: 98.3, encaps: 98.3, decaps: 97.4 },
  { variant: "HQC-5", keygen: 98.8, encaps: 98.7, decaps: 98.0 },
];

const decapsProfiles = [
  { variant: "HQC-1", mul: 95.857, sampling: 0.98, decode: 1.75, hash: 1.002, other: 0.405 },
  { variant: "HQC-3", mul: 97.442, sampling: 0.793, decode: 0.819, hash: 0.687, other: 0.262 },
  { variant: "HQC-5", mul: 98.005, sampling: 0.63, decode: 0.727, hash: 0.435, other: 0.19 },
];

const multiplicationLoops = [
  { variant: "HQC-1", words: 277, leaves: 243, iterations: "1,219,456" },
  { variant: "HQC-3", words: 561, leaves: 729, iterations: "3,708,416" },
  { variant: "HQC-5", words: 901, leaves: 729, iterations: "9,471,232" },
];

const samplingLoops = [
  { variant: "HQC-1", keygen: 36564, encaps: 62325, decaps: 80607 },
  { variant: "HQC-3", keygen: 112200, encaps: 191862, decaps: 247962 },
  { variant: "HQC-5", keygen: 236062, encaps: 402747, decaps: 520778 },
];

function ChapterHeader({
  number,
  eyebrow,
  title,
  children,
}: {
  number: string;
  eyebrow: string;
  title: string;
  children: React.ReactNode;
}) {
  return (
    <header className="chapter-heading">
      <div className="chapter-number" aria-hidden="true">
        {number}
      </div>
      <div>
        <p className="eyebrow">{eyebrow}</p>
        <h2>{title}</h2>
        <p className="chapter-lead">{children}</p>
      </div>
    </header>
  );
}

function BitRow({ label, bits, tone = "plain" }: { label: string; bits: string; tone?: string }) {
  return (
    <div className={`bit-row ${tone}`}>
      <span className="bit-label">{label}</span>
      <span className="bits" aria-label={`${label}: ${bits.split("").join(" ")}`}>
        {bits.split("").map((bit, index) => (
          <span className={`bit bit-${bit}`} key={`${label}-${index}`}>
            {bit}
          </span>
        ))}
      </span>
    </div>
  );
}

function Formula({ children, caption }: { children: React.ReactNode; caption?: string }) {
  return (
    <figure className="formula-card">
      <div className="formula">{children}</div>
      {caption ? <figcaption>{caption}</figcaption> : null}
    </figure>
  );
}

export default function Home() {
  return (
    <main>
      <header className="book-cover" id="top">
        <nav className="topbar" aria-label="상단 메뉴">
          <a className="brand" href="#top" aria-label="HQC 첫걸음 맨 위로">
            <span className="brand-mark">H</span>
            <span>HQC 첫걸음</span>
          </a>
          <div className="topbar-links">
            <a href="#chapter-11">성능 분석</a>
            <a href="#quick-summary">한 장 요약</a>
            <a href="#glossary">용어 사전</a>
          </div>
        </nav>

        <div className="cover-grid">
          <div className="cover-copy">
            <p className="volume">POST-QUANTUM CRYPTOGRAPHY · BEGINNER SERIES 01</p>
            <h1>
              그림과 비유로 배우는
              <span>HQC 알고리즘</span>
            </h1>
            <p className="cover-subtitle">
              긴 비트열, 희소 벡터, 잡음 상쇄에서 KEM까지. 수학을 처음 접하는 사람도 코드의 큰 흐름을
              따라갈 수 있도록 만든 입문 교재입니다.
            </p>
            <div className="cover-actions">
              <a className="primary-button" href="#chapter-1">
                1장부터 읽기 <span aria-hidden="true">→</span>
              </a>
              <span className="reading-time">약 40분 · 13개 장</span>
            </div>
          </div>

          <div className="cover-visual" aria-label="희소 비트열과 순환 구조를 표현한 표지 그림">
            <div className="orbit orbit-one" />
            <div className="orbit orbit-two" />
            <div className="core-disc">
              <span>HQC</span>
              <small>Hamming<br />Quasi-Cyclic</small>
            </div>
            <div className="floating-bits bits-a">0 · 0 · 1 · 0</div>
            <div className="floating-bits bits-b">XOR</div>
            <div className="floating-bits bits-c">1 · 0 · 0 · 1</div>
          </div>
        </div>

        <div className="learning-goals">
          <p className="eyebrow">이 교재를 읽고 나면</p>
          <div className="goal-grid">
            <div><b>01</b><span>희소 벡터와 오류의 차이를 설명할 수 있습니다.</span></div>
            <div><b>02</b><span>키 생성·캡슐화·디캡슐화 흐름을 따라갈 수 있습니다.</span></div>
            <div><b>03</b><span>실측값에서 병목 반복문을 찾고 공통 primitive를 고를 수 있습니다.</span></div>
          </div>
        </div>
      </header>

      <div className="page-shell">
        <aside className="contents" aria-label="목차">
          <p className="contents-title">차례</p>
          <ol>
            {chapters.map(([id, label]) => (
              <li key={id}><a href={`#${id}`}>{label}</a></li>
            ))}
          </ol>
          <div className="contents-note">
            <span aria-hidden="true">✦</span>
            <p><b>읽는 방법</b><br />노란 상자는 꼭 기억할 핵심, 초록 상자는 코드와 연결되는 부분입니다.</p>
          </div>
        </aside>

        <article className="textbook">
          <section className="chapter" id="chapter-1">
            <ChapterHeader number="01" eyebrow="출발점" title="HQC는 무엇을 하는 알고리즘일까요?">
              HQC는 실제 문서를 직접 암호화하는 도구가 아니라, 두 사람이 같은 비밀 열쇠를 안전하게 만드는
              KEM입니다.
            </ChapterHeader>

            <div className="story-strip" aria-label="HQC KEM의 세 단계">
              <div className="story-person alice">
                <span className="person-icon" aria-hidden="true">A</span>
                <strong>Alice</strong>
                <small>공개키를 사용하는 사람</small>
              </div>
              <div className="story-step">
                <span className="step-index">1</span>
                <b>KeyGen</b>
                <p>Bob이 공개키와 비밀키를 만듭니다.</p>
              </div>
              <div className="story-step">
                <span className="step-index">2</span>
                <b>Encaps</b>
                <p>Alice가 공개키로 암호문과 공유키를 만듭니다.</p>
              </div>
              <div className="story-step">
                <span className="step-index">3</span>
                <b>Decaps</b>
                <p>Bob이 비밀키로 같은 공유키를 복구합니다.</p>
              </div>
              <div className="story-person bob">
                <span className="person-icon" aria-hidden="true">B</span>
                <strong>Bob</strong>
                <small>비밀키를 가진 사람</small>
              </div>
            </div>

            <div className="key-equality">
              <span>Alice의 32바이트 공유키</span>
              <b>=</b>
              <span>Bob의 32바이트 공유키</span>
            </div>

            <div className="note important">
              <span className="note-label">핵심</span>
              <p>이 공유키로 AES나 ChaCha20을 사용해 실제 데이터를 빠르게 암호화합니다. HQC는 그 출발점인 열쇠 교환을 담당합니다.</p>
            </div>
          </section>

          <section className="chapter" id="chapter-2">
            <ChapterHeader number="02" eyebrow="준비물 1" title="HQC의 언어: 비트와 XOR">
              HQC가 만지는 대부분의 데이터는 0과 1로 이루어진 긴 비트열입니다. 비트열을 더할 때는 XOR이라는
              규칙을 사용합니다.
            </ChapterHeader>

            <div className="two-column">
              <div className="lesson-card">
                <p className="card-kicker">BIT VECTOR</p>
                <h3>비트 벡터</h3>
                <p>0과 1이 순서대로 놓인 배열입니다. 실제 HQC-1의 핵심 벡터는 17,669비트나 됩니다.</p>
                <BitRow label="예시" bits="10110010" />
              </div>
              <div className="lesson-card xor-table-card">
                <p className="card-kicker">BINARY ADDITION</p>
                <h3>XOR</h3>
                <div className="xor-table" role="table" aria-label="XOR 진리표">
                  <span>0 ⊕ 0</span><b>0</b>
                  <span>0 ⊕ 1</span><b>1</b>
                  <span>1 ⊕ 0</span><b>1</b>
                  <span>1 ⊕ 1</span><b>0</b>
                </div>
              </div>
            </div>

            <div className="worked-example">
              <div className="worked-heading"><span>예제 2-1</span><h3>두 비트열을 XOR해 봅시다</h3></div>
              <BitRow label="A" bits="10110010" tone="blue" />
              <BitRow label="B" bits="00110101" tone="orange" />
              <div className="xor-divider"><span>⊕</span></div>
              <BitRow label="결과" bits="10000111" tone="result" />
              <p className="margin-note"><b>관찰</b> 같은 값 두 개는 사라집니다. 그래서 언제나 A ⊕ A = 0입니다.</p>
            </div>
          </section>

          <section className="chapter" id="chapter-3">
            <ChapterHeader number="03" eyebrow="준비물 2" title="해밍 무게, 희소 벡터, 오류">
              세 용어는 가까이 있지만 같은 뜻은 아닙니다. 이 차이를 잡으면 HQC가 훨씬 쉽게 보입니다.
            </ChapterHeader>

            <div className="definition-stack">
              <div className="definition-row">
                <span className="definition-index">A</span>
                <div><h3>해밍 무게</h3><p>비트열 안에 들어 있는 <b>1의 개수</b>입니다.</p></div>
                <div className="mini-demo"><BitRow label="무게 3" bits="0010001000000010" /></div>
              </div>
              <div className="definition-row">
                <span className="definition-index">B</span>
                <div><h3>희소 벡터</h3><p>길이는 길지만 1이 매우 적은 비트열입니다. 이것은 <b>모양을 설명하는 말</b>입니다.</p></div>
                <span className="ratio-badge">17,669비트 중<br /><b>66개만 1</b></span>
              </div>
              <div className="definition-row">
                <span className="definition-index">C</span>
                <div><h3>오류 벡터</h3><p>정상 부호어와 XOR되어 <b>비트를 뒤집는 역할</b>을 하는 벡터입니다.</p></div>
                <span className="flip-demo">0→1&nbsp;&nbsp; 1→0</span>
              </div>
            </div>

            <div className="concept-equation">
              <div><b>희소</b><span>데이터의 형태</span></div>
              <span className="not-equal">≠</span>
              <div><b>오류</b><span>그 데이터가 맡는 역할</span></div>
            </div>

            <div className="role-grid">
              <div><code>x, y</code><b>비밀키 재료</b><p>희소하지만 그 자체를 오류라고 부르지는 않습니다.</p></div>
              <div><code>r₁, r₂</code><b>암호화 난수</b><p>암호문을 매번 다르게 만드는 희소 벡터입니다.</p></div>
              <div><code>e</code><b>직접 오류</b><p>부호어에 의도적으로 추가하는 희소 오류입니다.</p></div>
            </div>

            <div className="note important">
              <span className="note-label">한 줄 정리</span>
              <p>모든 희소 벡터가 오류인 것은 아닙니다. 다만 디코더의 눈에는 마지막에 남는 <b>r₂x ⊕ yr₁ ⊕ e</b> 전체가 오류입니다.</p>
            </div>
          </section>

          <section className="chapter" id="chapter-4">
            <ChapterHeader number="04" eyebrow="준비물 3" title="원형 테이프처럼 계산하는 순환 곱셈">
              ‘다항식 곱셈’이라는 이름은 어렵지만, 희소 벡터의 1 위치만큼 비트열을 회전하고 XOR한다고 생각하면 됩니다.
            </ChapterHeader>

            <div className="cycle-lesson">
              <div className="tape-panel">
                <p className="panel-label">긴 비트열 h</p>
                <div className="circular-tape" aria-label="원형 비트열 1 0 1 1 0 0 1 0">
                  {"10110010".split("").map((bit, index) => <span key={index}>{bit}</span>)}
                </div>
                <p>끝을 넘어가면 다시 처음으로 돌아옵니다.</p>
              </div>
              <div className="rotate-panel">
                <div><span className="rotate-count">2칸</span><p>h를 회전</p></div>
                <span className="big-xor">⊕</span>
                <div><span className="rotate-count">5칸</span><p>h를 회전</p></div>
                <span className="equals-arrow">→</span>
                <div className="product-box"><small>결과</small><b>y · h</b></div>
              </div>
            </div>

            <Formula caption="HQC의 주된 계산 공간. 어렵게 외우기보다 ‘길이 n의 원형 비트열 규칙’으로 기억하세요.">
              R = F<sub>2</sub>[X] / (X<sup>n</sup> − 1)
            </Formula>

            <div className="note code-note">
              <span className="note-label">코드 연결</span>
              <p>이 큰 순환 곱셈을 담당하는 함수가 <code>vect_mul()</code>입니다. KeyGen에서 1회, Encaps에서 2회, Decaps에서 3회 호출됩니다.</p>
            </div>
          </section>

          <section className="chapter" id="chapter-5">
            <ChapterHeader number="05" eyebrow="복구 장치" title="Reed–Solomon과 Reed–Muller">
              잡음이 조금 남아도 메시지를 되찾도록, HQC는 두 오류정정부호를 겹쳐 사용합니다.
            </ChapterHeader>

            <div className="encoding-pipeline">
              <div className="pipeline-node message-node"><small>입력</small><b>메시지 m</b><span>16·24·32바이트</span></div>
              <span className="pipeline-arrow">→</span>
              <div className="pipeline-node rs-node"><small>바깥 부호</small><b>Reed–Solomon</b><span>잘못된 바이트 복구</span></div>
              <span className="pipeline-arrow">→</span>
              <div className="pipeline-node rm-node"><small>안쪽 부호</small><b>Reed–Muller</b><span>비트 잡음 복구</span></div>
              <span className="pipeline-arrow">→</span>
              <div className="pipeline-node codeword-node"><small>출력</small><b>부호어 C(m)</b><span>여분 정보 포함</span></div>
            </div>

            <div className="decoder-grid">
              <div>
                <span className="decoder-icon">RS</span>
                <h3>Reed–Solomon</h3>
                <p>GF(2<sup>8</sup>)에서 동작합니다. 한 원소는 한 바이트이며, 여러 바이트가 잘못돼도 원래 메시지를 복구합니다.</p>
              </div>
              <div>
                <span className="decoder-icon">RM</span>
                <h3>Duplicated Reed–Muller</h3>
                <p>한 바이트를 128비트 부호어로 바꾸고 여러 번 반복합니다. Hadamard 변환으로 가장 가능성 높은 바이트를 찾습니다.</p>
              </div>
            </div>

            <div className="note important">
              <span className="note-label">오해 방지</span>
              <p>RS/RM 디코더는 비밀이 아닙니다. 비밀키 <code>y</code>로 큰 잡음을 먼저 없앤 사람만 이 공개 디코더를 성공적으로 사용할 수 있습니다.</p>
            </div>
          </section>

          <section className="chapter" id="chapter-6">
            <ChapterHeader number="06" eyebrow="KEM 1단계" title="키 생성: 공개 퍼즐 만들기">
              Bob은 랜덤 비트열 h와 희소 비밀 x, y를 고른 뒤, 둘을 섞은 s를 공개합니다.
            </ChapterHeader>

            <div className="keygen-board">
              <div className="keygen-inputs">
                <div><span className="symbol public">h</span><p><b>랜덤 비트열</b><br />누구나 알아도 됨</p></div>
                <div><span className="symbol secret">x</span><p><b>희소 벡터</b><br />비밀</p></div>
                <div><span className="symbol secret">y</span><p><b>희소 벡터</b><br />비밀</p></div>
              </div>
              <Formula caption="⊕는 XOR, ·는 순환 곱셈입니다.">
                s = x ⊕ y · h
              </Formula>
              <div className="key-output-grid">
                <div className="public-key"><span>공개키</span><b>(seed<sub>h</sub>, s)</b><p>h는 32바이트 seed에서 다시 만듭니다.</p></div>
                <div className="secret-key"><span>비밀키</span><b>seed<sub>dk</sub>, σ, …</b><p>x와 y를 다시 만들 수 있는 비밀 정보입니다.</p></div>
              </div>
            </div>

            <div className="attacker-box">
              <div className="attacker-face" aria-hidden="true">?</div>
              <div><p className="eyebrow">공격자가 보는 퍼즐</p><h3>h와 s는 알지만, 작은 x와 y는 모릅니다.</h3><p><code>s = x ⊕ y·h</code>를 만족하는 희소 x, y를 찾는 것이 어렵다는 QCSD 문제가 HQC 보안의 중심입니다.</p></div>
            </div>
          </section>

          <section className="chapter" id="chapter-7">
            <ChapterHeader number="07" eyebrow="KEM 2단계" title="캡슐화: 메시지에 큰 잡음 섞기">
              Alice는 공개키를 사용해 내부 메시지 m을 숨기고, 암호문과 32바이트 공유키 K를 함께 만듭니다.
            </ChapterHeader>

            <div className="encaps-flow">
              <div className="flow-row"><span className="flow-index">1</span><div><b>무작위 내부 메시지와 salt 생성</b><p>m은 사용자 문서가 아니라 공유키를 만들기 위한 랜덤 값입니다.</p></div><code>m, salt</code></div>
              <div className="flow-row"><span className="flow-index">2</span><div><b>공유키와 재현 가능한 난수 생성</b><p>해시 함수 G가 K와 θ를 한 번에 만듭니다.</p></div><code>G → K ∥ θ</code></div>
              <div className="flow-row"><span className="flow-index">3</span><div><b>θ에서 희소 벡터 생성</b><p>같은 θ라면 r₁, r₂, e도 똑같이 다시 만들 수 있습니다.</p></div><code>r₁, r₂, e</code></div>
              <div className="flow-row"><span className="flow-index">4</span><div><b>두 부분으로 된 암호문 생성</b><p>u는 나중에 잡음을 상쇄할 실마리, v는 잡음에 가려진 부호어입니다.</p></div><code>c = (u, v, salt)</code></div>
            </div>

            <div className="formula-pair">
              <Formula caption="첫 번째 암호문 조각">
                u = r<sub>1</sub> ⊕ r<sub>2</sub> · h
              </Formula>
              <Formula caption="두 번째 암호문 조각">
                v = C(m) ⊕ r<sub>2</sub> · s ⊕ e
              </Formula>
            </div>

            <div className="noise-visual">
              <div className="signal clean"><span>C(m)</span><small>정상 부호어</small></div>
              <span className="noise-plus">+</span>
              <div className="signal noise"><span>r₂·s</span><small>큰 방해 신호</small></div>
              <span className="noise-plus">+</span>
              <div className="signal error"><span>e</span><small>추가 오류</small></div>
              <span className="noise-plus">=</span>
              <div className="signal hidden"><span>v</span><small>메시지가 가려짐</small></div>
            </div>

            <p className="explain-paragraph">공격자도 RS/RM 디코더는 알고 있지만, <code>r₂·s</code>가 만드는 잡음이 너무 커서 v를 곧바로 디코딩할 수 없습니다.</p>
          </section>

          <section className="chapter" id="chapter-8">
            <ChapterHeader number="08" eyebrow="KEM 3단계" title="디캡슐화: 같은 항을 두 번 만들어 지우기">
              Bob은 비밀 벡터 y를 사용해 암호문 속 큰 잡음을 상쇄합니다. 이것이 HQC의 가장 중요한 장면입니다.
            </ChapterHeader>

            <div className="cancellation-board">
              <div className="equation-line">
                <span className="equation-name">v</span>
                <span>=</span>
                <span className="term message">C(m)</span>
                <span>⊕</span>
                <span className="term residual">r₂x</span>
                <span>⊕</span>
                <span className="term cancel">r₂yh</span>
                <span>⊕</span>
                <span className="term residual">e</span>
              </div>
              <div className="equation-line">
                <span className="equation-name">y·u</span>
                <span>=</span>
                <span className="term spacer">·</span>
                <span>⊕</span>
                <span className="term residual">yr₁</span>
                <span>⊕</span>
                <span className="term cancel">yr₂h</span>
                <span>⊕</span>
                <span className="term spacer">·</span>
              </div>
              <div className="cancel-rule"><span>같은 항</span><b>r₂yh ⊕ yr₂h = 0</b><span>서로 사라짐</span></div>
              <div className="equation-line final-line">
                <span className="equation-name">결과</span>
                <span>=</span>
                <span className="term message">C(m)</span>
                <span>⊕</span>
                <span className="term residual">r₂x</span>
                <span>⊕</span>
                <span className="term residual">yr₁</span>
                <span>⊕</span>
                <span className="term residual">e</span>
              </div>
            </div>

            <div className="decaps-steps">
              <div><span>01</span><b>큰 잡음 상쇄</b><p>비밀 y로 v ⊕ y·u를 계산합니다.</p></div>
              <div><span>02</span><b>Reed–Muller 복호</b><p>비트 잡음을 줄여 RS 심벌을 복구합니다.</p></div>
              <div><span>03</span><b>Reed–Solomon 복호</b><p>남은 심벌 오류를 고쳐 m′을 얻습니다.</p></div>
              <div><span>04</span><b>공유키 재생성</b><p>m′과 salt로 K′와 θ′를 만듭니다.</p></div>
            </div>

            <div className="note important">
              <span className="note-label">왜 Bob만 가능한가?</span>
              <p>공격자에게도 u와 v는 있지만 y가 없습니다. 따라서 큰 잡음을 지우는 <code>y·u</code>를 올바르게 만들 수 없습니다.</p>
            </div>
          </section>

          <section className="chapter" id="chapter-9">
            <ChapterHeader number="09" eyebrow="마지막 자물쇠" title="복호화 후 암호문을 다시 만드는 이유">
              공격자가 변조한 암호문에서 유용한 정보를 얻지 못하도록, HQC는 복구한 값으로 암호문을 재생성해 검사합니다.
            </ChapterHeader>

            <div className="verification-flow">
              <div className="verify-node"><small>복호화</small><b>m′ 복구</b></div>
              <span>→</span>
              <div className="verify-node"><small>해시 G</small><b>K′ ∥ θ′</b></div>
              <span>→</span>
              <div className="verify-node"><small>재암호화</small><b>c′ 생성</b></div>
              <span>→</span>
              <div className="verify-node decision"><small>상수시간 비교</small><b>c ?= c′</b></div>
            </div>

            <div className="branch-grid">
              <div className="valid-branch"><span>일치</span><h3>정상 암호문</h3><p>복구한 공유키 K′를 출력합니다.</p><code>output = K′</code></div>
              <div className="invalid-branch"><span>불일치</span><h3>잘못된 암호문</h3><p>오류 메시지 대신 대체 키 K̄를 출력합니다.</p><code>output = K̄</code></div>
            </div>

            <p className="explain-paragraph">이 방식을 <b>implicit rejection</b>이라고 합니다. 외부에서는 정상과 실패가 비슷하게 보이므로 공격자가 복호화 성공 여부를 관찰하기 어려워집니다.</p>
          </section>

          <section className="chapter" id="chapter-10">
            <ChapterHeader number="10" eyebrow="구현으로 연결" title="파라미터와 함수 지도를 읽는 법">
              세 파라미터 세트는 흐름은 같고, 비트열 길이와 희소 벡터의 무게, 오류정정부호 크기가 다릅니다.
            </ChapterHeader>

            <div className="table-wrap">
              <table>
                <thead><tr><th>항목</th><th>HQC-1</th><th>HQC-3</th><th>HQC-5</th></tr></thead>
                <tbody>
                  <tr><th>목표 보안 강도</th><td>128비트</td><td>192비트</td><td>256비트</td></tr>
                  <tr><th>순환 벡터 길이 n</th><td>17,669</td><td>35,851</td><td>57,637</td></tr>
                  <tr><th>비밀 벡터 무게 ω</th><td>66</td><td>100</td><td>131</td></tr>
                  <tr><th>암호화 벡터 무게 ωᵣ, ωₑ</th><td>75</td><td>114</td><td>149</td></tr>
                  <tr><th>내부 메시지 m</th><td>16 B</td><td>24 B</td><td>32 B</td></tr>
                  <tr><th>공개키</th><td>2,241 B</td><td>4,514 B</td><td>7,237 B</td></tr>
                  <tr><th>암호문</th><td>4,433 B</td><td>8,978 B</td><td>14,421 B</td></tr>
                </tbody>
              </table>
            </div>

            <div className="code-map">
              <div><span className="file-tag">KEM</span><code>crypto_kem_keypair()</code><p>seed를 만들고 PKE 키 생성을 호출</p></div>
              <div><span className="file-tag">KEM</span><code>crypto_kem_enc()</code><p>m, salt, K, θ를 만들고 암호화</p></div>
              <div><span className="file-tag">KEM</span><code>crypto_kem_dec()</code><p>복호화·재암호화·암호문 검사</p></div>
              <div><span className="file-tag pke">PKE</span><code>hqc_pke_keygen()</code><p>x, y, h를 만들고 s 계산</p></div>
              <div><span className="file-tag pke">PKE</span><code>hqc_pke_encrypt()</code><p>u와 v 계산</p></div>
              <div><span className="file-tag pke">PKE</span><code>hqc_pke_decrypt()</code><p>y·u 계산 후 코드 디코딩</p></div>
              <div><span className="file-tag primitive">연산</span><code>vect_mul()</code><p>큰 순환 이진 다항식 곱셈</p></div>
              <div><span className="file-tag primitive">부호</span><code>code_encode/decode()</code><p>RS와 RM 연결 부호 처리</p></div>
            </div>

            <div className="note code-note">
              <span className="note-label">프로파일링 예고</span>
              <p>함수 흐름을 이해한 다음에는 KeyGen·Encaps·Decaps를 따로 측정하고, <code>vect_mul</code>, 고정 무게 샘플링, RS/RM 디코딩, SHA3/SHAKE의 시간을 분리해서 봅니다.</p>
            </div>
          </section>

          <section className="chapter" id="chapter-11">
            <ChapterHeader number="11" eyebrow="측정으로 확인" title="프로파일링: 실제로 어디에서 시간이 걸릴까요?">
              함수 호출표만 보고 병목을 짐작하지 않고, KEM 전체 시간과 내부 primitive 시간을 같은 실행에서
              재어 보았습니다. 결론부터 말하면 큰 순환 곱셈이 거의 전부입니다.
            </ChapterHeader>

            <div className="benchmark-context">
              <div><span>CPU</span><b>Apple Silicon · ARM64</b><p>현재 작업 머신</p></div>
              <div><span>빌드</span><b>ref · Release -O3</b><p>Apple Clang 21.0.0</p></div>
              <div><span>반복</span><b>독립 실행 3회</b><p>HQC-1/3은 60회, HQC-5는 40회 평균 후 중앙값</p></div>
              <div><span>코드</span><b>HQC v5.0.0-3</b><p>commit 161cd4f</p></div>
            </div>

            <div className="chart-card timing-chart">
              <div className="chart-heading">
                <div><p className="card-kicker">END-TO-END LATENCY</p><h3>KEM 단계별 실행시간</h3></div>
                <span>공통 축 · 최대 18.21 ms</span>
              </div>
              <div className="chart-legend" aria-label="그래프 범례">
                <span className="keygen-dot">KeyGen</span><span className="encaps-dot">Encaps</span><span className="decaps-dot">Decaps</span>
              </div>
              {kemTimings.map((row) => (
                <div className="timing-group" key={row.variant}>
                  <b>{row.variant}</b>
                  {([
                    ["KeyGen", row.keygen, "keygen"],
                    ["Encaps", row.encaps, "encaps"],
                    ["Decaps", row.decaps, "decaps"],
                  ] as const).map(([label, value, tone]) => (
                    <div className="timing-row" key={label}>
                      <span>{label}</span>
                      <div className="bar-track" aria-label={`${row.variant} ${label} ${value.toFixed(2)} 밀리초`}>
                        <i className={`bar-fill ${tone}`} style={{ width: `${(value / 18.21) * 100}%` }} />
                      </div>
                      <strong>{value.toFixed(2)} ms</strong>
                    </div>
                  ))}
                </div>
              ))}
              <div className="chart-axis" aria-hidden="true"><span>0</span><span>4.5</span><span>9.1</span><span>13.7</span><span>18.2 ms</span></div>
            </div>

            <div className="finding-grid">
              <div><span>약 1×</span><b>KeyGen</b><p><code>vect_mul()</code> 1회</p></div>
              <div><span>약 2×</span><b>Encaps</b><p><code>vect_mul()</code> 2회</p></div>
              <div><span>약 3×</span><b>Decaps</b><p>복호 1회 + 재암호화 2회</p></div>
            </div>

            <div className="chart-card share-chart">
              <div className="chart-heading">
                <div><p className="card-kicker">IN-CONTEXT PROFILE</p><h3>전체 시간 중 vect_mul 비중</h3></div>
                <span>함수 경계 계측값</span>
              </div>
              <div className="share-table" role="table" aria-label="단계별 vect_mul 실행시간 비율">
                <div className="share-head" role="row"><span>세트</span><span>KeyGen</span><span>Encaps</span><span>Decaps</span></div>
                {mulShares.map((row) => (
                  <div className="share-row" role="row" key={row.variant}>
                    <b>{row.variant}</b>
                    {[row.keygen, row.encaps, row.decaps].map((value, index) => (
                      <div className="share-cell" key={index}>
                        <div><i style={{ width: `${value}%` }} /></div><strong>{value.toFixed(1)}%</strong>
                      </div>
                    ))}
                  </div>
                ))}
              </div>
            </div>

            <div className="chart-card profile-card">
              <div className="chart-heading">
                <div><p className="card-kicker">DECAPS BREAKDOWN</p><h3>가장 느린 디캡슐화의 내부 비중</h3></div>
                <span>반올림 때문에 합계에 ±0.1% 오차가 있을 수 있음</span>
              </div>
              <div className="profile-legend">
                <span className="profile-mul">순환 곱셈</span><span className="profile-sampling">샘플링</span><span className="profile-decode">코드 복호</span><span className="profile-hash">해시</span><span className="profile-other">기타</span>
              </div>
              {decapsProfiles.map((row) => (
                <div className="profile-row" key={row.variant}>
                  <b>{row.variant}</b>
                  <div className="profile-stack" aria-label={`${row.variant} 디캡슐화 내부 시간 비율`}>
                    <i className="profile-mul" style={{ width: `${row.mul}%` }} />
                    <i className="profile-sampling" style={{ width: `${row.sampling}%` }} />
                    <i className="profile-decode" style={{ width: `${row.decode}%` }} />
                    <i className="profile-hash" style={{ width: `${row.hash}%` }} />
                    <i className="profile-other" style={{ width: `${row.other}%` }} />
                  </div>
                  <strong>{row.mul.toFixed(1)}% 곱셈</strong>
                </div>
              ))}
            </div>

            <div className="note important">
              <span className="note-label">해석 주의</span>
              <p>이 수치는 현재 ARM64 머신의 <code>ref</code> 구현에서 병목의 <b>위치</b>를 찾기 위한 값입니다. x86 최적화 구현이나 다른 컴파일러에서는 절대 시간과 세부 비율이 달라질 수 있지만, 이 측정에서는 곱셈 우선순위가 압도적으로 분명합니다.</p>
            </div>
          </section>

          <section className="chapter" id="chapter-12">
            <ChapterHeader number="12" eyebrow="소스 안으로 한 단계" title="병목 반복문: 무엇이 얼마나 반복될까요?">
              느린 함수를 찾은 다음에는 그 안의 반복문을 셉니다. 실행시간과 반복 횟수를 함께 보면 어떤 연산을
              ISA로 밀어야 할지 훨씬 선명해집니다.
            </ChapterHeader>

            <div className="loop-anatomy">
              <div className="loop-stage"><span>1</span><div><b>Karatsuba 재귀 분할</b><p>큰 입력을 세 개의 작은 곱셈으로 계속 나눕니다.</p></div></div>
              <div className="loop-arrow">↓</div>
              <div className="loop-stage hot"><span>2</span><div><b>schoolbook_mul 잎 연산</b><p>64비트 word의 각 bit를 검사하고 상대 word들을 XOR 누적합니다.</p></div></div>
              <div className="loop-arrow">↓</div>
              <div className="loop-stage"><span>3</span><div><b>mod (Xⁿ − 1) reduction</b><p>높은 절반을 낮은 절반으로 원형 접기합니다.</p></div></div>
            </div>

            <pre className="loop-code" aria-label="schoolbook multiplication 반복문 의사 코드"><code>{`for each word i
  for each bit = 0 ... 63
    for each word j
      result[i+j] ^= shifted(input[j]) & mask`}</code></pre>

            <div className="table-wrap loop-table">
              <table>
                <thead><tr><th>한 번의 vect_mul</th><th>입력 64-bit word</th><th>schoolbook 잎 개수</th><th>가장 안쪽 j 본문 실행</th></tr></thead>
                <tbody>
                  {multiplicationLoops.map((row) => (
                    <tr key={row.variant}><th>{row.variant}</th><td>{row.words}</td><td>{row.leaves}</td><td><b>{row.iterations}회</b></td></tr>
                  ))}
                </tbody>
              </table>
            </div>
            <p className="source-count-note">소스의 Karatsuba 임계값 16 word와 실제 홀수 분할을 그대로 적용한 정적 계산입니다. “본문 실행 횟수”는 기계어 명령 수가 아니라 가장 안쪽 <code>j</code> 반복 횟수입니다.</p>

            <div className="repeat-call-board">
              <div className="repeat-title"><p className="card-kicker">MULTIPLY CALLS</p><h3>KEM 한 번당 큰 곱셈 호출 수</h3></div>
              <div className="repeat-phases">
                <div><b>KeyGen</b><span className="call-chips"><i>MUL</i></span><strong>1회</strong></div>
                <div><b>Encaps</b><span className="call-chips"><i>MUL</i><i>MUL</i></span><strong>2회</strong></div>
                <div><b>Decaps</b><span className="call-chips"><i>MUL</i><i>MUL</i><i>MUL</i></span><strong>3회</strong></div>
              </div>
            </div>

            <div className="chart-card sampling-chart">
              <div className="chart-heading">
                <div><p className="card-kicker">FIXED-WEIGHT MATERIALIZATION</p><h3>희소 벡터 쓰기 내부 비교 횟수</h3></div>
                <span>단계별 n-word × weight 누적</span>
              </div>
              {samplingLoops.map((row) => (
                <div className="sampling-group" key={row.variant}>
                  <b>{row.variant}</b>
                  {([
                    ["KeyGen", row.keygen, "keygen"],
                    ["Encaps", row.encaps, "encaps"],
                    ["Decaps", row.decaps, "decaps"],
                  ] as const).map(([label, value, tone]) => (
                    <div className="sampling-row" key={label}>
                      <span>{label}</span><div className="bar-track"><i className={`bar-fill ${tone}`} style={{ width: `${(value / 520778) * 100}%` }} /></div><strong>{value.toLocaleString()}회</strong>
                    </div>
                  ))}
                </div>
              ))}
            </div>

            <div className="decoder-counts">
              <div className="decoder-count-heading"><p className="card-kicker">DECODER LOOPS</p><h3>디캡슐화에서만 실행되는 복호 반복문</h3></div>
              <div className="table-wrap">
                <table>
                  <thead><tr><th>반복 본문 / KEM 1회</th><th>HQC-1</th><th>HQC-3</th><th>HQC-5</th></tr></thead>
                  <tbody>
                    <tr><th>RM Hadamard butterfly</th><td>20,608</td><td>25,088</td><td>40,320</td></tr>
                    <tr><th>RM peak 비교</th><td>5,888</td><td>7,168</td><td>11,520</td></tr>
                    <tr><th>RS syndrome GF(2⁸) 곱셈</th><td>1,350</td><td>1,760</td><td>5,162</td></tr>
                  </tbody>
                </table>
              </div>
            </div>

            <div className="concept-equation loop-conclusion">
              <div><b>반복 횟수</b><span>얼마나 자주 도는가</span></div>
              <span className="not-equal">×</span>
              <div><b>한 번의 비용</b><span>연산·메모리가 얼마나 무거운가</span></div>
              <span className="equals-arrow">→</span>
              <div><b>실측 시간</b><span>최종 우선순위를 결정</span></div>
            </div>

            <div className="note important">
              <span className="note-label">중요한 결론</span>
              <p>고정 무게 샘플링도 최대 52만 회 넘게 반복되지만 실측 비중은 약 0.6~1.3%입니다. 반면 <code>vect_mul</code>의 schoolbook 잎은 한 호출에 최대 947만 번의 안쪽 본문을 실행하고, KEM당 최대 3회 호출되므로 전체 시간을 지배합니다.</p>
            </div>
          </section>

          <section className="chapter" id="chapter-13">
            <ChapterHeader number="13" eyebrow="가속기의 출발점" title="공통 primitive: 무엇부터 ISA로 만들까요?">
              좋은 primitive는 단순히 반복 횟수가 많은 연산이 아닙니다. 실측 비중, 여러 단계에서의 재사용,
              규칙적인 데이터 흐름, 구현 비용을 함께 보고 고릅니다.
            </ChapterHeader>

            <div className="selection-rule">
              <div><span>①</span><b>실측 비중</b><p>전체 시간에서 큰가?</p></div>
              <div><span>②</span><b>재사용성</b><p>KeyGen·Encaps·Decaps에 공통인가?</p></div>
              <div><span>③</span><b>규칙성</b><p>상수시간·고정 반복으로 만들기 쉬운가?</p></div>
              <div><span>④</span><b>구현 효율</b><p>명령 하나가 충분한 일을 줄이는가?</p></div>
            </div>

            <div className="table-wrap priority-table">
              <table>
                <thead><tr><th>후보 primitive</th><th>이번 실측 근거</th><th>재사용</th><th>판정</th></tr></thead>
                <tbody>
                  <tr className="priority-zero"><th>GF(2) 순환 곱셈 + reduction</th><td>전체의 95.9~98.8%</td><td>세 단계 모두</td><td><b>P0 · 최우선</b></td></tr>
                  <tr><th>wide XOR · shift · load/store</th><td>곱셈의 분할·결합·reduction 내부</td><td>세 단계 모두</td><td><b>P0 · 기반</b></td></tr>
                  <tr><th>Keccak/SHA3/SHAKE</th><td>H/G/I/J 계측은 최대 약 1.0%</td><td>다른 PQC에도 폭넓음</td><td><b>P1 · 공통성</b></td></tr>
                  <tr><th>RS/RM 복호</th><td>Decaps의 약 0.7~1.8%</td><td>Decaps만</td><td><b>P2 · 후순위</b></td></tr>
                  <tr><th>고정 무게 샘플링</th><td>약 0.6~1.3%</td><td>세 단계 모두</td><td><b>P3 · 전용 ISA 보류</b></td></tr>
                </tbody>
              </table>
            </div>

            <div className="primitive-winner">
              <div className="winner-rank">P0</div>
              <div><p className="eyebrow">선정 결과</p><h3>Carry-less multiply-accumulate + 원형 reduction</h3><p>64비트 또는 넓은 lane 두 개를 GF(2) 다항식으로 곱해 XOR 누적하고, 마지막에 <code>Xⁿ − 1</code> 규칙으로 접는 조합이 HQC 전용 가속의 중심입니다.</p></div>
            </div>

            <div className="primitive-pipeline" aria-label="선정된 곱셈 primitive 흐름">
              <div><small>입력</small><b>wide words</b><span>aᵢ, bⱼ</span></div><i>→</i>
              <div className="hot"><small>P0-A</small><b>CLMUL + XOR</b><span>자리올림 없는 부분곱 누적</span></div><i>→</i>
              <div><small>P0-B</small><b>Karatsuba combine</b><span>넓은 XOR 결합</span></div><i>→</i>
              <div className="hot"><small>P0-C</small><b>cyclic fold</b><span>mod (Xⁿ − 1)</span></div>
            </div>

            <div className="architecture-grid">
              <div>
                <p className="card-kicker">RISC-V CANDIDATE</p>
                <h3>작은 CLMUL 명령을 조립</h3>
                <ul>
                  <li>먼저 Zbc의 <code>clmul/clmulh</code> 활용 가능성을 기준선으로 측정</li>
                  <li>XOR 누적과 cyclic fold의 명령·load/store 수를 함께 줄이기</li>
                  <li>스칼라 64비트와 vector 확장안을 같은 primitive 의미로 비교</li>
                </ul>
              </div>
              <div>
                <p className="card-kicker">OTBN CANDIDATE</p>
                <h3>256비트 wide datapath에 맞춰 묶기</h3>
                <ul>
                  <li>wide register 단위 XOR·shift·load/store를 기본 재료로 사용</li>
                  <li>word-sliced CLMUL macro 또는 새 부분곱 명령의 손익 비교</li>
                  <li>DMEM 이동과 Karatsuba 임시 버퍼까지 포함해 스케줄 설계</li>
                </ul>
              </div>
            </div>

            <div className="amdahl-card">
              <div><p className="card-kicker">AMDAHL&apos;S LAW</p><h3>병목을 8배 빠르게 만든다면?</h3><p>전체 가속도 = 1 ÷ ((1 − 병목 비중) + 병목 비중 ÷ 8)</p></div>
              <div className="amdahl-result"><span>곱셈 가속</span><b>약 6.2~7.4×</b><small>측정된 95.9~98.8% 구간의 이론값</small></div>
              <div className="amdahl-result muted"><span>샘플링만 가속</span><b>&lt; 1.02×</b><small>무한히 빨라도 전체 개선은 약 1.3% 이하</small></div>
            </div>

            <div className="note code-note">
              <span className="note-label">다음 단계</span>
              <p>이제 P0 primitive에 대해 RISC-V는 명령 형식·레지스터 폭·latency/throughput을, OTBN은 256비트 operand 배치·DMEM 트래픽·constant-time 스케줄을 각각 설계하면 됩니다. 같은 테스트 벡터로 소프트웨어 기준선과 새 ISA 결과를 비교해야 합니다.</p>
            </div>
          </section>

          <section className="comparison-section" id="mceliece-comparison">
            <p className="eyebrow">헷갈리기 쉬운 비교</p>
            <h2>McEliece와 HQC는 어디가 다른가요?</h2>
            <div className="comparison-grid">
              <div><span>Classic McEliece</span><h3>비밀 오류정정기</h3><p>숨겨진 Goppa 부호 구조와 전용 디코더로 오류를 직접 고칩니다.</p></div>
              <div><span>HQC</span><h3>비밀 노이즈 캔슬러</h3><p>비밀 희소 벡터 y로 큰 잡음을 지운 뒤 공개 RS/RM 디코더로 잔여 오류를 고칩니다.</p></div>
            </div>
            <p className="comparison-summary">둘 다 코드 기반 암호이지만, 보안을 만드는 비밀 구조와 오류를 없애는 순서가 다릅니다.</p>
          </section>

          <section className="summary-section" id="quick-summary">
            <p className="eyebrow">QUICK REVIEW</p>
            <h2>한 장으로 다시 보는 HQC</h2>
            <div className="summary-flow">
              <div><span>1</span><b>키 생성</b><p>희소 x, y와 랜덤 h로<br /><code>s = x ⊕ y·h</code></p></div>
              <div><span>2</span><b>캡슐화</b><p>부호어 C(m)에 큰 잡음을 섞어<br /><code>u, v, salt</code> 생성</p></div>
              <div><span>3</span><b>디캡슐화</b><p>비밀 y로 큰 잡음을 상쇄하고<br />RS/RM으로 m′ 복구</p></div>
              <div><span>4</span><b>검증</b><p>암호문을 다시 만들어 비교하고<br />공유키를 안전하게 선택</p></div>
            </div>
            <div className="performance-summary"><span>성능 한 줄</span><p><code>vect_mul()</code>이 전체 시간의 약 95.9~98.8%를 차지하므로, 첫 ISA 후보는 GF(2) carry-less 곱셈과 순환 reduction입니다.</p></div>
            <blockquote>HQC는 비밀 희소 벡터로 큰 잡음을 없애고, 공개 오류정정부호로 남은 작은 오류를 고쳐 공유키를 복구합니다.</blockquote>
          </section>

          <section className="glossary-section" id="glossary">
            <p className="eyebrow">찾아보기</p>
            <h2>초심자 용어 사전</h2>
            <div className="glossary-grid">
              {terms.map(([term, description]) => (
                <div key={term}><dt>{term}</dt><dd>{description}</dd></div>
              ))}
            </div>
          </section>

          <section className="quiz-section" id="quiz">
            <p className="eyebrow">SELF CHECK</p>
            <h2>읽은 내용을 확인해 봅시다</h2>
            <div className="quiz-list">
              <details><summary><span>01</span>희소 벡터와 오류 벡터는 같은 뜻일까요?</summary><p>아닙니다. 희소는 ‘1이 적다’는 형태이고, 오류는 ‘부호어의 비트를 뒤집는다’는 역할입니다.</p></details>
              <details><summary><span>02</span>공격자가 공개 RS/RM 디코더로 v를 바로 복호화할 수 없는 이유는?</summary><p>v에는 r₂·s라는 큰 잡음이 섞여 있어 디코더의 오류 교정 범위를 벗어나기 때문입니다.</p></details>
              <details><summary><span>03</span>정상 수신자는 어떤 비밀 값으로 큰 잡음을 상쇄하나요?</summary><p>희소 비밀 벡터 y입니다. v ⊕ y·u를 계산하면 양쪽에 들어 있던 r₂·y·h 항이 사라집니다.</p></details>
              <details><summary><span>04</span>HQC에서 가장 큰 비트열 곱셈을 담당하는 함수는?</summary><p>vect_mul()입니다. F₂ 위의 순환 다항식 곱셈과 reduction을 수행합니다.</p></details>
              <details><summary><span>05</span>반복 횟수가 많으면 무조건 첫 ISA 후보일까요?</summary><p>아닙니다. 실측 시간 비중, 한 반복의 비용, 여러 단계에서의 재사용성, 구현 비용을 함께 봐야 합니다.</p></details>
              <details><summary><span>06</span>이번 ref 프로파일에서 가장 먼저 가속할 primitive는?</summary><p>전체 시간의 약 95.9~98.8%를 차지한 GF(2) 순환 곱셈입니다. carry-less 부분곱, XOR 결합, mod (Xⁿ−1) reduction으로 나눠 설계할 수 있습니다.</p></details>
            </div>
          </section>
        </article>
      </div>

      <footer>
        <div><span className="brand-mark">H</span><div><b>HQC 첫걸음</b><p>코드 기반 양자내성암호 입문 교재</p></div></div>
        <a href="#top">맨 위로 ↑</a>
      </footer>
    </main>
  );
}
