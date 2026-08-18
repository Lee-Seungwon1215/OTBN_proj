#!/usr/bin/env python3
"""Build a standalone HTML report from the FrodoKEM profiling CSV files."""

from __future__ import annotations

import argparse
import csv
import html
import json
import statistics
from collections import defaultdict
from pathlib import Path


STAGES = ("keygen", "encaps", "decaps")
STAGE_LABELS = {
    "keygen": "키 생성",
    "encaps": "캡슐화",
    "decaps": "디캡슐화",
}

GROUPS = (
    ("keccak", "SHAKE / Keccak", (
        "seed_a_xof", "sample_xof", "public_key_hash", "derive_xof",
        "shared_secret_xof", "a_generation",
    )),
    ("matrix", "16-bit 행렬 MAC", ("large_matrix_mac", "small_matrix_mac")),
    ("serialization", "Pack / unpack", ("pack", "unpack")),
    ("sampler", "CDF 샘플러", ("noise_sampling",)),
    ("security", "검증 / 지우기", ("verify_select", "secret_clear")),
    ("random", "시스템 난수", ("system_random",)),
    ("other", "기타", ("a_endian", "small_arithmetic")),
)

REGION_LABELS = {
    "system_random": "시스템 난수",
    "seed_a_xof": "공개 시드 압축",
    "sample_xof": "노이즈용 SHAKE",
    "public_key_hash": "공개키 해시",
    "derive_xof": "일회용 값 파생",
    "shared_secret_xof": "공유 비밀 파생",
    "a_generation": "공개 행렬 A 생성",
    "a_endian": "A 바이트 순서 변환",
    "large_matrix_mac": "큰 행렬 MAC",
    "small_matrix_mac": "작은 행렬 MAC",
    "noise_sampling": "CDF 노이즈 샘플링",
    "pack": "패킹",
    "unpack": "언패킹",
    "small_arithmetic": "8×8 덧셈·인코딩",
    "verify_select": "상수시간 검증·선택",
    "secret_clear": "비밀 메모리 지우기",
}


def load_csv(path: Path) -> dict:
    raw: dict[str, dict[int, dict[str, dict[str, dict[str, float]]]]] = defaultdict(
        lambda: defaultdict(lambda: defaultdict(dict))
    )
    with path.open(newline="", encoding="utf-8") as stream:
        for row in csv.DictReader(stream):
            raw[row["implementation"]][int(row["trial"])][row["stage"]][row["region"]] = {
                "calls": float(row["calls"]),
                "total_ns": float(row["total_ns"]),
                "stage_total_ns": float(row["stage_total_ns"]),
            }
    if len(raw) != 1:
        raise ValueError(f"{path}: expected exactly one implementation")
    implementation = next(iter(raw))
    trials = raw[implementation]
    for trial, stages in trials.items():
        for stage in STAGES:
            if stage not in stages or "total" not in stages[stage]:
                raise ValueError(f"{path}: missing {stage}/total in trial {trial}")
    return {"name": implementation, "trials": trials}


def summarize(dataset: dict) -> dict:
    trials = dataset["trials"]
    summary = {"name": dataset["name"], "stages": {}}
    all_regions = sorted({
        region
        for stages in trials.values()
        for stage in stages.values()
        for region in stage
        if region != "total"
    })
    for stage in STAGES:
        trial_totals = []
        trial_regions = defaultdict(list)
        trial_groups = defaultdict(list)
        for trial in sorted(trials):
            rows = trials[trial][stage]
            stage_calls = rows["total"]["calls"]
            total_ns = rows["total"]["total_ns"] / stage_calls
            trial_totals.append(total_ns)
            accounted = 0.0
            for region in all_regions:
                value = rows.get(region, {"total_ns": 0.0})["total_ns"] / stage_calls
                trial_regions[region].append(value)
                accounted += value
            for key, _, regions in GROUPS:
                group_value = sum(
                    rows.get(region, {"total_ns": 0.0})["total_ns"] / stage_calls
                    for region in regions
                )
                trial_groups[key].append(group_value)
            trial_groups["residual"].append(max(0.0, total_ns - accounted))
        total_median = statistics.median(trial_totals)
        summary["stages"][stage] = {
            "total_ns": total_median,
            "trial_total_ns": trial_totals,
            "min_ns": min(trial_totals),
            "max_ns": max(trial_totals),
            "regions": {key: statistics.median(values) for key, values in trial_regions.items()},
            "groups": {key: statistics.median(values) for key, values in trial_groups.items()},
        }
    return summary


def weighted_coverage(summary: dict, group: str, weights: dict[str, float]) -> float:
    numerator = sum(summary["stages"][stage]["groups"][group] * weights[stage] for stage in STAGES)
    denominator = sum(summary["stages"][stage]["total_ns"] * weights[stage] for stage in STAGES)
    return numerator / denominator


def fmt_ms(ns: float) -> str:
    return f"{ns / 1_000_000:.3f}"


def fmt_pct(value: float) -> str:
    return f"{value * 100:.1f}%"


def stacked_bar(stage_data: dict) -> str:
    pieces = []
    total = stage_data["total_ns"]
    for key, label, _ in GROUPS:
        fraction = max(0.0, stage_data["groups"].get(key, 0.0) / total)
        if fraction < 0.0005:
            continue
        pieces.append(
            f'<span class="segment {key}" style="width:{fraction * 100:.4f}%" '
            f'aria-label="{html.escape(label)} {fmt_pct(fraction)}"></span>'
        )
    residual = max(0.0, stage_data["groups"].get("residual", 0.0) / total)
    if residual >= 0.0005:
        pieces.append(
            f'<span class="segment residual" style="width:{residual * 100:.4f}%" '
            f'aria-label="계측 잔여 {fmt_pct(residual)}"></span>'
        )
    return "".join(pieces)


def build_html(reference: dict, fast: dict, output: Path) -> None:
    balanced = {stage: 1.0 for stage in STAGES}
    reused = {"keygen": 1.0, "encaps": 100.0, "decaps": 100.0}
    group_labels = {key: label for key, label, _ in GROUPS}
    ranking = []
    for key, label, _ in GROUPS:
        balanced_share = weighted_coverage(fast, key, balanced)
        reused_share = weighted_coverage(fast, key, reused)
        ranking.append((balanced_share, key, label, reused_share))
    ranking.sort(reverse=True)

    fast_total = sum(fast["stages"][stage]["total_ns"] for stage in STAGES)
    reference_total = sum(reference["stages"][stage]["total_ns"] for stage in STAGES)
    keccak_share = weighted_coverage(fast, "keccak", balanced)
    matrix_share = weighted_coverage(fast, "matrix", balanced)
    top_two_share = keccak_share + matrix_share

    comparison_rows = []
    comparison_chart = []
    max_total = max(
        data["stages"][stage]["total_ns"]
        for data in (reference, fast)
        for stage in STAGES
    )
    for stage in STAGES:
        ref_ns = reference["stages"][stage]["total_ns"]
        fast_ns = fast["stages"][stage]["total_ns"]
        comparison_rows.append(
            f"<tr><th scope=\"row\">{STAGE_LABELS[stage]}</th>"
            f"<td>{fmt_ms(ref_ns)} ms</td><td>{fmt_ms(fast_ns)} ms</td>"
            f"<td>{ref_ns / fast_ns:.2f}×</td></tr>"
        )
        comparison_chart.append(f"""
          <div class="compare-group">
            <div class="compare-title">{STAGE_LABELS[stage]}</div>
            <div class="compare-line"><span class="impl-label">REFERENCE</span><div class="time-track"><span class="time-fill reference-fill" style="width:{ref_ns / max_total * 100:.3f}%"></span></div><strong>{fmt_ms(ref_ns)} ms</strong></div>
            <div class="compare-line"><span class="impl-label">FAST_GENERIC</span><div class="time-track"><span class="time-fill fast-fill" style="width:{fast_ns / max_total * 100:.3f}%"></span></div><strong>{fmt_ms(fast_ns)} ms</strong></div>
          </div>""")

    stage_bars = []
    for stage in STAGES:
        stage_data = fast["stages"][stage]
        stage_bars.append(f"""
          <div class="stage-row">
            <div class="stage-heading"><strong>{STAGE_LABELS[stage]}</strong><span>{fmt_ms(stage_data['total_ns'])} ms/op</span></div>
            <div class="stacked" role="img" aria-label="{STAGE_LABELS[stage]} 연산 시간 구성">{stacked_bar(stage_data)}</div>
            <div class="stage-notes"><span>SHAKE {fmt_pct(stage_data['groups']['keccak'] / stage_data['total_ns'])}</span><span>행렬 MAC {fmt_pct(stage_data['groups']['matrix'] / stage_data['total_ns'])}</span><span>직렬화 {fmt_pct(stage_data['groups']['serialization'] / stage_data['total_ns'])}</span></div>
          </div>""")

    legend = "".join(
        f'<span><i class="swatch {key}"></i>{html.escape(label)}</span>'
        for key, label, _ in GROUPS[:4]
    ) + '<span><i class="swatch residual"></i>기타·계측 잔여</span>'

    ranking_rows = []
    rank = 0
    for share, key, label, reuse_share in ranking:
        if key in {"random", "other"}:
            continue
        rank += 1
        common = "3/3" if key in {"keccak", "matrix", "sampler", "security"} else "3/3*"
        note = {
            "keccak": "A 생성 640행과 KEM 내부 해시를 함께 덮음",
            "matrix": "큰 MAC 327만 회/단계; 루프 순서 영향이 큼",
            "serialization": "15-bit 계수 패킹·언패킹",
            "sampler": "샘플당 12회 상수시간 CDF 비교",
            "security": "성능 비중은 작지만 상수시간 성질 유지 필수",
        }[key]
        ranking_rows.append(
            f'<tr><td class="rank">{rank}</td><th scope="row">{html.escape(label)}</th>'
            f'<td>{fmt_pct(share)}</td><td>{fmt_pct(reuse_share)}</td><td>{common}</td><td>{html.escape(note)}</td></tr>'
        )

    region_rows = []
    for stage in STAGES:
        total = fast["stages"][stage]["total_ns"]
        ordered = sorted(fast["stages"][stage]["regions"].items(), key=lambda item: item[1], reverse=True)
        for index, (region, value) in enumerate(ordered[:6]):
            region_rows.append(
                f'<tr><td>{STAGE_LABELS[stage] if index == 0 else ""}</td>'
                f'<td>{html.escape(REGION_LABELS.get(region, region))}</td>'
                f'<td>{value / 1000:.1f} μs</td><td>{fmt_pct(value / total)}</td></tr>'
            )

    trial_rows = []
    for implementation in (reference, fast):
        for stage in STAGES:
            data = implementation["stages"][stage]
            trial_rows.append(
                f'<tr><td>{html.escape(implementation["name"])}</td><td>{STAGE_LABELS[stage]}</td>'
                f'<td>{fmt_ms(data["total_ns"])} ms</td><td>{fmt_ms(data["min_ns"])}–{fmt_ms(data["max_ns"])} ms</td></tr>'
            )

    projection_data = json.dumps({
        "keccak": keccak_share,
        "matrix": matrix_share,
        "combined": top_two_share,
    })

    document = f"""<!doctype html>
<html lang="ko">
<head>
  <meta charset="utf-8">
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <title>FrodoKEM-640-SHAKE 프로파일링과 공통 primitive 선정</title>
  <style>
    :root {{
      color-scheme: light dark;
      --bg: #f5f7fb; --surface: #ffffff; --surface-2: #edf1f7; --text: #172033;
      --muted: #5f6b7c; --line: #d7deea; --accent: #3258d3; --accent-soft: #dce5ff;
      --keccak: #3559d5; --matrix: #d66a35; --serialization: #2c8b76; --sampler: #9a58ba;
      --security: #738096; --random: #a7b0bf; --other: #c0c6d0; --residual: #d9dee7;
      --reference: #a4adbd; --fast: #3559d5; --shadow: 0 16px 42px rgba(31, 42, 68, .08);
    }}
    @media (prefers-color-scheme: dark) {{
      :root {{
        --bg: #0e1320; --surface: #161d2c; --surface-2: #20293a; --text: #edf2fb;
        --muted: #a9b4c6; --line: #313d52; --accent: #8da8ff; --accent-soft: #28375f;
        --keccak: #7796ff; --matrix: #f09566; --serialization: #67bea9; --sampler: #c887e1;
        --security: #9eabc0; --random: #737f92; --other: #596579; --residual: #394458;
        --reference: #778399; --fast: #7796ff; --shadow: none;
      }}
    }}
    * {{ box-sizing: border-box; }}
    html {{ scroll-behavior: smooth; }}
    body {{ margin: 0; background: var(--bg); color: var(--text); font-family: -apple-system, BlinkMacSystemFont, "Segoe UI", sans-serif; line-height: 1.55; }}
    main {{ width: min(1160px, calc(100% - 32px)); margin: 0 auto; padding: 44px 0 72px; }}
    h1, h2, h3 {{ line-height: 1.25; margin: 0; }}
    h1 {{ font-size: clamp(2rem, 5vw, 4.2rem); max-width: 900px; letter-spacing: -.04em; }}
    h2 {{ font-size: clamp(1.45rem, 3vw, 2.15rem); margin-bottom: 18px; }}
    h3 {{ font-size: 1.05rem; }}
    p {{ margin: 0; }}
    a {{ color: var(--accent); }}
    code {{ font-family: ui-monospace, SFMono-Regular, Menlo, monospace; font-size: .92em; }}
    .eyebrow {{ color: var(--accent); font-weight: 700; letter-spacing: .08em; text-transform: uppercase; margin-bottom: 14px; }}
    .lead {{ color: var(--muted); font-size: 1.08rem; max-width: 820px; margin-top: 18px; }}
    .hero {{ padding: 34px 0 20px; }}
    .scope {{ margin-top: 26px; display: flex; flex-wrap: wrap; gap: 9px; }}
    .chip {{ background: var(--surface-2); border: 1px solid var(--line); border-radius: 999px; padding: 7px 11px; font-size: .88rem; }}
    section {{ margin-top: 58px; }}
    .card {{ background: var(--surface); border: 1px solid var(--line); border-radius: 18px; box-shadow: var(--shadow); padding: 22px; }}
    .verdict {{ display: grid; grid-template-columns: 1.15fr .85fr; gap: 18px; }}
    .verdict-main {{ background: var(--accent); color: white; border: 0; }}
    @media (prefers-color-scheme: dark) {{ .verdict-main {{ color: #0d1423; }} }}
    .big-number {{ font-size: clamp(2.8rem, 8vw, 5.8rem); line-height: 1; letter-spacing: -.06em; font-weight: 750; margin: 12px 0; }}
    .verdict-main p {{ max-width: 570px; }}
    .callout-list {{ display: grid; gap: 14px; }}
    .callout {{ padding-bottom: 14px; border-bottom: 1px solid var(--line); }}
    .callout:last-child {{ border-bottom: 0; padding-bottom: 0; }}
    .callout strong {{ display: block; margin-bottom: 4px; }}
    .muted {{ color: var(--muted); }}
    .compare-chart {{ display: grid; gap: 24px; }}
    .compare-group {{ display: grid; gap: 8px; }}
    .compare-title {{ font-weight: 700; }}
    .compare-line {{ display: grid; grid-template-columns: 110px minmax(80px, 1fr) 82px; align-items: center; gap: 10px; font-size: .9rem; }}
    .impl-label {{ color: var(--muted); font-size: .78rem; }}
    .time-track, .stacked {{ height: 21px; background: var(--surface-2); border-radius: 999px; overflow: hidden; }}
    .time-fill {{ display: block; height: 100%; border-radius: inherit; }}
    .reference-fill {{ background: var(--reference); }} .fast-fill {{ background: var(--fast); }}
    .table-wrap {{ overflow-x: auto; }}
    table {{ width: 100%; border-collapse: collapse; min-width: 620px; }}
    th, td {{ border-bottom: 1px solid var(--line); padding: 11px 10px; text-align: left; vertical-align: top; }}
    thead th {{ color: var(--muted); font-size: .82rem; }}
    tbody tr:last-child th, tbody tr:last-child td {{ border-bottom: 0; }}
    .stage-bars {{ display: grid; gap: 26px; }}
    .stage-row {{ display: grid; gap: 8px; }}
    .stage-heading, .stage-notes {{ display: flex; justify-content: space-between; gap: 12px; flex-wrap: wrap; }}
    .stage-heading span, .stage-notes {{ color: var(--muted); }}
    .stage-notes {{ font-size: .82rem; justify-content: flex-start; gap: 16px; }}
    .stacked {{ display: flex; height: 28px; background: var(--residual); }}
    .segment {{ display: block; height: 100%; min-width: 1px; }}
    .keccak {{ background: var(--keccak); }} .matrix {{ background: var(--matrix); }}
    .serialization {{ background: var(--serialization); }} .sampler {{ background: var(--sampler); }}
    .security {{ background: var(--security); }} .random {{ background: var(--random); }}
    .other {{ background: var(--other); }} .residual {{ background: var(--residual); }}
    .legend {{ display: flex; flex-wrap: wrap; gap: 10px 18px; color: var(--muted); font-size: .84rem; margin-top: 18px; }}
    .legend span {{ display: inline-flex; align-items: center; gap: 7px; }}
    .swatch {{ width: 11px; height: 11px; border-radius: 3px; display: inline-block; }}
    .flow-grid {{ display: grid; grid-template-columns: repeat(3, 1fr); gap: 14px; }}
    .flow-card {{ display: grid; gap: 15px; align-content: start; }}
    .flow-card ol {{ margin: 0; padding-left: 22px; display: grid; gap: 12px; }}
    .flow-card li::marker {{ color: var(--accent); font-weight: 700; }}
    .tag {{ display: inline-block; border-radius: 999px; background: var(--surface-2); color: var(--muted); padding: 2px 7px; font-size: .75rem; margin-left: 4px; }}
    .loop-grid {{ display: grid; grid-template-columns: repeat(2, 1fr); gap: 15px; }}
    .loop-card {{ min-height: 230px; }}
    .loop-metric {{ font-size: 2rem; font-weight: 750; letter-spacing: -.04em; margin: 14px 0 4px; }}
    .loop-path {{ display: flex; flex-wrap: wrap; gap: 7px; align-items: center; margin-top: 18px; color: var(--muted); font-size: .85rem; }}
    .loop-path b {{ color: var(--text); background: var(--surface-2); border-radius: 8px; padding: 6px 9px; }}
    .rank {{ font-weight: 800; color: var(--accent); width: 44px; }}
    .decision {{ border-left: 5px solid var(--keccak); }}
    .projection {{ display: grid; grid-template-columns: 1fr 1fr; gap: 22px; align-items: center; }}
    .range-wrap label {{ display: flex; justify-content: space-between; gap: 12px; font-weight: 700; }}
    input[type=range] {{ width: 100%; margin-top: 14px; accent-color: var(--accent); }}
    .projection-results {{ display: grid; grid-template-columns: repeat(3, 1fr); gap: 10px; }}
    .projection-result {{ background: var(--surface-2); border-radius: 13px; padding: 14px; }}
    .projection-result strong {{ display: block; font-size: 1.5rem; margin-top: 4px; }}
    details {{ border-top: 1px solid var(--line); padding: 15px 0; }}
    details:last-child {{ border-bottom: 1px solid var(--line); }}
    summary {{ cursor: pointer; font-weight: 700; }}
    .method-body {{ margin-top: 11px; color: var(--muted); }}
    .footnote {{ font-size: .85rem; color: var(--muted); margin-top: 14px; }}
    .source-list {{ margin: 12px 0 0; padding-left: 20px; }}
    @media (max-width: 780px) {{
      main {{ width: min(100% - 22px, 1160px); padding-top: 22px; }}
      .verdict, .projection, .flow-grid, .loop-grid {{ grid-template-columns: 1fr; }}
      .compare-line {{ grid-template-columns: 92px minmax(70px, 1fr) 70px; gap: 7px; }}
      .projection-results {{ grid-template-columns: 1fr; }}
      .card {{ padding: 18px; border-radius: 15px; }}
      section {{ margin-top: 44px; }}
    }}
    @media (prefers-reduced-motion: reduce) {{ html {{ scroll-behavior: auto; }} }}
  </style>
</head>
<body>
<main>
  <header class="hero">
    <div class="eyebrow">Measured bottleneck map</div>
    <h1>FrodoKEM-640-SHAKE에서 무엇을 가속해야 하는가</h1>
    <p class="lead">함수 이름을 외우는 대신, 키 생성·캡슐화·디캡슐화의 실제 시간을 계측해 반복문과 공통 primitive 후보를 연결한 보고서입니다.</p>
    <div class="scope" aria-label="측정 범위">
      <span class="chip">n = 640 · n̄ = 8</span><span class="chip">SHAKE128로 A 생성</span>
      <span class="chip">Apple arm64 · clang -O3</span><span class="chip">100회 × 9 trials · 중앙값</span>
      <span class="chip">REFERENCE ↔ FAST_GENERIC</span>
    </div>
  </header>

  <section class="verdict" aria-labelledby="verdict-title">
    <article class="card verdict-main">
      <h2 id="verdict-title">첫 번째 공통 primitive</h2>
      <div class="big-number">SHAKE</div>
      <p>FAST_GENERIC의 세 단계 시간을 같은 비중으로 합치면 SHAKE/Keccak 계열이 <strong>{fmt_pct(keccak_share)}</strong>를 차지합니다. 공개 행렬 A 생성만으로 각 단계에서 SHAKE128을 640번 호출합니다.</p>
    </article>
    <aside class="card callout-list">
      <div class="callout"><strong>두 번째: 16-bit 행렬 MAC</strong><span class="muted">FAST_GENERIC {fmt_pct(matrix_share)} · REFERENCE에서는 캡슐화/디캡슐화의 약 61–62%</span></div>
      <div class="callout"><strong>상위 2개 합계</strong><span class="muted">FAST_GENERIC 균형 workload의 {fmt_pct(top_two_share)}</span></div>
      <div class="callout"><strong>여기서 멈추는 경계</strong><span class="muted">primitive 우선순위까지만 선정. RISC-V/OTBN 명령 형식은 다음 단계에서 결정합니다.</span></div>
    </aside>
  </section>

  <section aria-labelledby="comparison-title">
    <h2 id="comparison-title">구현체가 바뀌면 병목의 모양도 바뀐다</h2>
    <div class="card compare-chart" role="img" aria-label="REFERENCE와 FAST_GENERIC 단계별 실행 시간 비교">
      {''.join(comparison_chart)}
    </div>
    <div class="table-wrap">
      <table>
        <thead><tr><th>단계</th><th>REFERENCE</th><th>FAST_GENERIC</th><th>FAST_GENERIC 속도 향상</th></tr></thead>
        <tbody>{''.join(comparison_rows)}</tbody>
      </table>
    </div>
    <p class="footnote">키 생성은 두 구현체가 비슷하지만, 캡슐화와 디캡슐화는 FAST_GENERIC이 약 2.5배 빠릅니다. 같은 327만 MAC이라도 행렬을 순회하는 순서와 블로킹이 메모리 지역성을 크게 바꾼다는 뜻입니다.</p>
  </section>

  <section aria-labelledby="composition-title">
    <h2 id="composition-title">FAST_GENERIC 단계별 시간 구성</h2>
    <div class="card stage-bars">
      {''.join(stage_bars)}
      <div class="legend">{legend}</div>
    </div>
  </section>

  <section aria-labelledby="flow-title">
    <h2 id="flow-title">함수 흐름과 병목을 한 장에 연결하기</h2>
    <div class="flow-grid">
      <article class="card flow-card"><h3>키 생성</h3><ol>
        <li>난수에서 공개 시드·비밀·오차 재료 생성 <span class="tag">SHAKE</span></li>
        <li>오차 분포로 변환 <span class="tag">CDF sampler</span></li>
        <li>A를 행별로 즉석 생성 <span class="tag">SHAKE 640회</span></li>
        <li>A × 비밀 + 오차 <span class="tag">3,276,800 MAC</span></li>
        <li>공개키 패킹·해시</li>
      </ol></article>
      <article class="card flow-card"><h3>캡슐화</h3><ol>
        <li>일회용 내부 값과 salt 생성·파생 <span class="tag">SHAKE</span></li>
        <li>일회용 비밀·오차 샘플링 <span class="tag">CDF sampler</span></li>
        <li>일회용 비밀 × A + 오차 <span class="tag">A + 큰 MAC</span></li>
        <li>일회용 비밀 × 공개키 + 오차 <span class="tag">40,960 MAC</span></li>
        <li>메시지 표현을 더해 패킹, 공유 비밀 파생</li>
      </ol></article>
      <article class="card flow-card"><h3>디캡슐화</h3><ol>
        <li>암호문 언패킹, 비밀로 내부 값 복구 <span class="tag">작은 MAC</span></li>
        <li>복구값으로 캡슐화 계산을 다시 수행 <span class="tag">A + 큰 MAC</span></li>
        <li>예상 암호문과 입력 암호문 비교 <span class="tag">constant-time</span></li>
        <li>정상/실패용 값을 상수시간 선택</li>
        <li>최종 공유 비밀 파생 <span class="tag">SHAKE</span></li>
      </ol></article>
    </div>
  </section>

  <section aria-labelledby="loops-title">
    <h2 id="loops-title">병목 반복문 해부</h2>
    <div class="loop-grid">
      <article class="card loop-card">
        <h3>① 공개 행렬 A 생성</h3><div class="loop-metric">5,120 permutations</div>
        <p class="muted">640행 × 행당 SHAKE128 squeeze 8블록. 행마다 1,280바이트를 만들어 총 819,200바이트를 생성합니다.</p>
        <div class="loop-path"><b>16-byte seed</b><span>→</span><b>row index</b><span>→</span><b>SHAKE128</b><span>→</span><b>640 coefficients</b></div>
      </article>
      <article class="card loop-card">
        <h3>② 큰 행렬 곱-누산</h3><div class="loop-metric">3,276,800 MACs</div>
        <p class="muted">8 × 640 × 640의 16-bit 곱-누산입니다. 결과는 16-bit wraparound로 누산되고 이후 패킹에서 q = 2¹⁵ 범위가 취해집니다.</p>
        <div class="loop-path"><b>secret 8×640</b><span>×</span><b>A 640×640</b><span>+</span><b>error</b></div>
      </article>
      <article class="card loop-card">
        <h3>③ 작은 행렬 곱-누산</h3><div class="loop-metric">40,960 MACs</div>
        <p class="muted">8 × 8 × 640. 캡슐화에서는 한 번, 디캡슐화에서는 복구와 재계산 때문에 두 번 수행됩니다.</p>
        <div class="loop-path"><b>8×640</b><span>×</span><b>640×8</b><span>→</span><b>8×8</b></div>
      </article>
      <article class="card loop-card">
        <h3>④ CDF 노이즈 샘플러</h3><div class="loop-metric">12 compares/sample</div>
        <p class="muted">키 생성 10,240개, 캡슐화·디캡슐화 각각 10,304개 샘플. 각 샘플은 분기 없는 비교 12회와 부호 처리를 수행합니다.</p>
        <div class="loop-path"><b>16-bit random</b><span>→</span><b>12 CT compares</b><span>→</span><b>signed noise</b></div>
      </article>
    </div>
  </section>

  <section aria-labelledby="ranking-title">
    <h2 id="ranking-title">공통 primitive 후보 순위</h2>
    <div class="table-wrap card">
      <table>
        <thead><tr><th>#</th><th>후보</th><th>균형 1:1:1</th><th>키 재사용 1:100:100</th><th>단계 공통성</th><th>선정 근거</th></tr></thead>
        <tbody>{''.join(ranking_rows)}</tbody>
      </table>
    </div>
    <article class="card decision" style="margin-top:15px">
      <h3>선정안</h3>
      <p style="margin-top:8px"><strong>필수 후보:</strong> Keccak-f[1600]/SHAKE squeeze, 16-bit multiply-accumulate. <strong>후순위 후보:</strong> 15-bit pack/unpack, 상수시간 CDF 비교·누산. 검증·선택은 보안상 중요하지만 이 측정에서는 성능 가속 우선순위가 낮습니다.</p>
    </article>
  </section>

  <section aria-labelledby="projection-title">
    <h2 id="projection-title">가속 배수보다 시간 점유율이 먼저다</h2>
    <div class="card projection">
      <div class="range-wrap">
        <label for="speedup-range"><span>primitive 자체 가속</span><output id="speedup-value">10×</output></label>
        <input id="speedup-range" type="range" min="1" max="50" step="1" value="10">
        <p class="footnote">Amdahl 법칙으로 FAST_GENERIC 균형 workload의 이론상 전체 속도 향상을 계산합니다.</p>
      </div>
      <div class="projection-results" aria-live="polite">
        <div class="projection-result"><span>SHAKE만</span><strong id="keccak-projection">–</strong></div>
        <div class="projection-result"><span>행렬 MAC만</span><strong id="matrix-projection">–</strong></div>
        <div class="projection-result"><span>둘 다</span><strong id="combined-projection">–</strong></div>
      </div>
    </div>
  </section>

  <section aria-labelledby="detail-title">
    <h2 id="detail-title">세부 계측값</h2>
    <div class="table-wrap">
      <table>
        <thead><tr><th>단계</th><th>상위 구간</th><th>FAST_GENERIC 시간</th><th>단계 비중</th></tr></thead>
        <tbody>{''.join(region_rows)}</tbody>
      </table>
    </div>
  </section>

  <section aria-labelledby="method-title">
    <h2 id="method-title">측정 방법과 해석 경계</h2>
    <details open><summary>어떻게 측정했나</summary><div class="method-body">각 KEM 단계 전체와 SHAKE, A 생성, 큰/작은 행렬 MAC, 샘플러, pack/unpack, 검증·선택 구간에 저비용 단조 시계를 삽입했습니다. 구현별로 워밍업 후 단계당 100회씩 실행하는 trial을 9회 반복했고, 스케줄링 이상치 영향을 줄이기 위해 trial 중앙값을 사용했습니다.</div></details>
    <details><summary>정답성은 확인했나</summary><div class="method-body">REFERENCE와 FAST_GENERIC 모두 저장소의 FrodoKEM-640-SHAKE Known Answer Test를 통과했고, 프로파일 러너도 매 trial마다 캡슐화/디캡슐화 공유 비밀 일치를 검사합니다.</div></details>
    <details><summary>이 결과를 RISC-V/OTBN 수치로 봐도 되나</summary><div class="method-body">아닙니다. 이것은 Apple arm64 호스트에서 병목 후보를 좁히는 1차 계측입니다. RISC-V/OTBN에서는 동일한 region ID로 cycle counter와 instruction counter를 다시 수집해야 합니다. 특히 Keccak 구현, 메모리 폭, 곱셈기 지연에 따라 비중이 바뀔 수 있습니다.</div></details>
    <details><summary>A 생성 시간은 정확히 무엇인가</summary><div class="method-body">선택한 SHAKE 변형에서 행 인덱스와 16-byte 공개 시드를 입력으로 SHAKE128 출력을 만드는 시간입니다. 별도의 byte-order 변환은 따로 계측했습니다. FAST_GENERIC의 A 생성과 MAC은 행 블록을 만들자마자 소비하므로 전체 A를 메모리에 보관하지 않습니다.</div></details>
    <div class="table-wrap" style="margin-top:20px"><table>
      <thead><tr><th>구현</th><th>단계</th><th>중앙값</th><th>trial 범위</th></tr></thead>
      <tbody>{''.join(trial_rows)}</tbody>
    </table></div>
    <p class="footnote">환경: Apple arm64, macOS 26.5.2, Apple clang 21.0.0, <code>-O3</code>, 저장소 commit <code>7a4e721</code>. 계측 단위는 wall-clock ns/op이며 CPU cycle이 아닙니다.</p>
  </section>

  <section aria-labelledby="source-title">
    <h2 id="source-title">재현 파일</h2>
    <div class="card">
      <ul class="source-list">
        <li><a href="PQCrypto-LWEKE/FrodoKEM/profiling/profile_runner.c">profile_runner.c</a> — 반복 실행과 정답성 검사</li>
        <li><a href="PQCrypto-LWEKE/FrodoKEM/profiling/profile.c">profile.c</a> — 구간별 시간 누적과 CSV 출력</li>
        <li><a href="PQCrypto-LWEKE/FrodoKEM/profiling/results/reference.csv">reference.csv</a> — REFERENCE 원시 결과</li>
        <li><a href="PQCrypto-LWEKE/FrodoKEM/profiling/results/fast-generic.csv">fast-generic.csv</a> — FAST_GENERIC 원시 결과</li>
      </ul>
    </div>
  </section>
</main>
<script>
  const coverage = {projection_data};
  const slider = document.getElementById('speedup-range');
  const speedupValue = document.getElementById('speedup-value');
  const targets = {{
    keccak: document.getElementById('keccak-projection'),
    matrix: document.getElementById('matrix-projection'),
    combined: document.getElementById('combined-projection')
  }};
  function amdahl(fraction, acceleration) {{
    return 1 / ((1 - fraction) + fraction / acceleration);
  }}
  function updateProjection() {{
    const acceleration = Number(slider.value);
    speedupValue.textContent = acceleration + '×';
    Object.entries(targets).forEach(([key, element]) => {{
      element.textContent = amdahl(coverage[key], acceleration).toFixed(2) + '×';
    }});
  }}
  slider.addEventListener('input', updateProjection);
  updateProjection();
</script>
</body>
</html>
"""
    output.write_text(document, encoding="utf-8")


def main() -> None:
    parser = argparse.ArgumentParser()
    parser.add_argument("--reference", type=Path, required=True)
    parser.add_argument("--fast", type=Path, required=True)
    parser.add_argument("--output", type=Path, required=True)
    args = parser.parse_args()
    reference = summarize(load_csv(args.reference))
    fast = summarize(load_csv(args.fast))
    build_html(reference, fast, args.output)
    print(f"wrote {args.output}")


if __name__ == "__main__":
    main()
