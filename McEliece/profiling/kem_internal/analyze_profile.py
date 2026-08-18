#!/usr/bin/env python3

import csv
import statistics
import sys
from collections import defaultdict


def main() -> int:
    paths = sys.argv[1:] if len(sys.argv) > 1 else ["kem_internal_profile.csv"]
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
        key = (int(row["_file_index"]), int(row["trial"]), row["stage"])
        trials[key].append(row)

    print(f"files: {', '.join(paths)}")
    for stage in ("encapsulation", "decapsulation"):
        stage_trials = [value for key, value in trials.items() if key[2] == stage]
        first_rows = [trial_rows[0] for trial_rows in stage_trials]
        calls = sum(int(row["stage_calls"]) for row in first_rows)
        total_ns = sum(int(row["stage_total_ns"]) for row in first_rows)
        per_trial_ms = [
            int(row["stage_total_ns"]) / int(row["stage_calls"]) / 1e6
            for row in first_rows
        ]
        region_ns = defaultdict(int)
        region_calls = defaultdict(int)
        trial_shares = defaultdict(list)
        for trial_rows in stage_trials:
            for row in trial_rows:
                region = row["region"]
                region_ns[region] += int(row["region_total_ns"])
                region_calls[region] += int(row["region_calls"])
                trial_shares[region].append(float(row["stage_share_pct"]))

        print(f"\n{stage}")
        print(f"calls: {calls}")
        print(
            f"aggregate: {total_ns / calls / 1e6:.6f} ms/op, "
            f"trial median: {statistics.median(per_trial_ms):.6f} ms/op"
        )
        ranked = sorted(region_ns, key=region_ns.get, reverse=True)
        for rank, region in enumerate(ranked, 1):
            share = region_ns[region] / total_ns * 100
            calls_per_stage = region_calls[region] / calls
            print(
                f"{rank:2d}. {region:30s} "
                f"{region_ns[region] / calls / 1e6:9.6f} ms/op "
                f"{share:6.2f}% "
                f"calls/op {calls_per_stage:5.3f} "
                f"(trial median {statistics.median(trial_shares[region]):6.2f}%)"
            )
        measured_ns = sum(region_ns.values())
        print(f"residual: {(total_ns - measured_ns) / calls / 1e6:.6f} ms/op")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
