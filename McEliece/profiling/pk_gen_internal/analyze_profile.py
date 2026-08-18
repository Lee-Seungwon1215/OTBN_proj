#!/usr/bin/env python3

import csv
import statistics
import sys
from collections import defaultdict


def main() -> int:
    paths = sys.argv[1:] if len(sys.argv) > 1 else ["pk_gen_profile.csv"]
    rows = []
    for file_index, path in enumerate(paths):
        with open(path, newline="", encoding="utf-8") as handle:
            for row in csv.DictReader(handle):
                row["_file_index"] = file_index
                rows.append(row)

    if not rows:
        raise SystemExit("empty profile")

    trials = defaultdict(list)
    for row in rows:
        trials[(int(row["_file_index"]), int(row["trial"]))].append(row)

    first_rows = [trials[index][0] for index in sorted(trials)]
    iterations = sum(int(row["iterations"]) for row in first_rows)
    calls = sum(int(row["pkgen_calls"]) for row in first_rows)
    successes = sum(int(row["successes"]) for row in first_rows)
    duplicate_failures = sum(
        int(row["duplicate_failures"]) for row in first_rows
    )
    pivot_failures = sum(int(row["pivot_failures"]) for row in first_rows)
    keypair_ms = sum(float(row["keypair_total_ms"]) for row in first_rows)
    pkgen_ms = sum(float(row["pkgen_total_ms"]) for row in first_rows)
    success_pkgen_ms = sum(
        float(row["success_pkgen_ms"]) for row in first_rows
    )
    failure_pkgen_ms = sum(
        float(row["failure_pkgen_ms"]) for row in first_rows
    )

    success_phase_ms = defaultdict(float)
    all_phase_ms = defaultdict(float)
    per_trial_success_share = defaultdict(list)
    for row in rows:
        phase = row["phase"]
        success_phase_ms[phase] += float(row["success_phase_ms"])
        all_phase_ms[phase] += float(row["all_phase_ms"])
        per_trial_success_share[phase].append(float(row["success_share_pct"]))

    success_rank = sorted(
        success_phase_ms, key=lambda phase: success_phase_ms[phase], reverse=True
    )
    all_rank = sorted(
        all_phase_ms, key=lambda phase: all_phase_ms[phase], reverse=True
    )

    per_trial_keypair = [
        float(row["keypair_total_ms"]) / int(row["iterations"])
        for row in first_rows
    ]
    per_trial_success_pkgen = [
        float(row["success_pkgen_ms"]) / int(row["successes"])
        for row in first_rows
    ]

    print(f"files: {', '.join(paths)}")
    print(f"trials: {len(trials)}, successful keypairs: {iterations}")
    print(
        "pk_gen calls: "
        f"{calls} = success {successes} + pivot failure {pivot_failures} "
        f"+ duplicate failure {duplicate_failures}"
    )
    print(f"calls per successful keypair: {calls / successes:.3f}")
    print(f"failed-call fraction: {(calls - successes) / calls * 100:.2f}%")
    print(
        "keypair time: "
        f"aggregate {keypair_ms / iterations:.3f} ms/op, "
        f"trial median {statistics.median(per_trial_keypair):.3f} ms/op"
    )
    print(
        "successful pk_gen time: "
        f"aggregate {success_pkgen_ms / successes:.3f} ms/call, "
        f"trial median {statistics.median(per_trial_success_pkgen):.3f} ms/call"
    )
    print(
        f"all pk_gen attempts: {pkgen_ms / iterations:.3f} ms/keypair "
        f"({pkgen_ms / keypair_ms * 100:.2f}% of keypair time)"
    )
    print(
        f"failed pk_gen attempts: {failure_pkgen_ms / iterations:.3f} ms/keypair, "
        f"{failure_pkgen_ms / (calls - successes):.3f} ms/failed call"
    )

    print("\nsuccessful pk_gen phase ranking")
    for rank, phase in enumerate(success_rank, 1):
        share = success_phase_ms[phase] / success_pkgen_ms * 100
        trial_median = statistics.median(per_trial_success_share[phase])
        print(
            f"{rank:2d}. {phase:24s} "
            f"{success_phase_ms[phase] / successes:7.3f} ms/call "
            f"{share:6.2f}% (trial-share median {trial_median:6.2f}%)"
        )

    print("\nall attempts phase ranking (includes retries)")
    for rank, phase in enumerate(all_rank, 1):
        share = all_phase_ms[phase] / pkgen_ms * 100
        print(
            f"{rank:2d}. {phase:24s} "
            f"{all_phase_ms[phase] / iterations:7.3f} ms/keypair "
            f"{share:6.2f}%"
        )

    measured_success = sum(success_phase_ms.values())
    measured_all = sum(all_phase_ms.values())
    print(
        f"\nsuccess timing residual: "
        f"{(success_pkgen_ms - measured_success) / successes:.4f} ms/call"
    )
    print(
        f"all-attempt timing residual: "
        f"{(pkgen_ms - measured_all) / iterations:.4f} ms/keypair"
    )
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
