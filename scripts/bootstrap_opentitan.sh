#!/usr/bin/env bash

set -euo pipefail

project_root=$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)
opentitan_dir="$project_root/opentitan"
overlay_dir="$project_root/overlay/opentitan"
upstream_url="https://github.com/lowRISC/opentitan.git"
upstream_commit="b9d39c6c9c3e10e7363613a3054132f154e21037"

if [[ -e "$opentitan_dir" ]]; then
  echo "error: $opentitan_dir already exists; refusing to overwrite it" >&2
  exit 1
fi

if [[ ! -d "$overlay_dir" ]]; then
  echo "error: overlay directory is missing: $overlay_dir" >&2
  exit 1
fi

echo "Cloning OpenTitan..."
git clone --filter=blob:none --no-checkout "$upstream_url" "$opentitan_dir"

echo "Checking out pinned commit $upstream_commit..."
git -C "$opentitan_dir" checkout --detach "$upstream_commit"

echo "Installing BN.CLMULVL4 overlay..."
cp -a "$overlay_dir/." "$opentitan_dir/"

echo "Checking the resulting worktree..."
git -C "$opentitan_dir" diff --check

echo
echo "OpenTitan is ready at: $opentitan_dir"
echo "Pinned base: $upstream_commit"
echo "Modified files:"
git -C "$opentitan_dir" status --short
echo
echo "Next: follow SCHOOL_UBUNTU_OTBN_CLMUL_PROMPT.md from this repository."
