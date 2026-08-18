# OTBN PQC custom-instruction prototype

This repository packages the OpenTitan files needed to reproduce the
experimental `BN.CLMULVL4.LO/HI` instruction for HQC carry-less schoolbook
multiplication.

The full OpenTitan source is intentionally not vendored. The bootstrap script
checks out the exact upstream revision and copies the reviewed overlay into it.

## Current scope

- OpenTitan base commit: `b9d39c6c9c3e10e7363613a3054132f154e21037`
- ISA and encoding definitions for `BN.CLMULVL4.LO/HI`
- Python OTBNSim semantics
- decoder and randomized tests
- direct instruction and 256×256 schoolbook assembly tests
- `clmul256.s` example microkernel
- Ubuntu execution and RTL follow-up prompt

The instruction is implemented in the Python ISS only. RTL support has not yet
been added, so current hardware simulation will report an illegal instruction
until the decoder and datapath are extended.

## Ubuntu quick start

Clone this branch until its pull request is merged:

```bash
git clone -b agent/clmulvl4-prototype --single-branch \
  https://github.com/Lee-Seungwon1215/OTBN_proj.git
cd OTBN_proj
./scripts/bootstrap_opentitan.sh
```

This creates `./opentitan` at the pinned upstream commit and installs the
overlay. Then follow [`SCHOOL_UBUNTU_OTBN_CLMUL_PROMPT.md`](SCHOOL_UBUNTU_OTBN_CLMUL_PROMPT.md)
for dependencies, ELF tests, RTL implementation, and Verilator verification.

## Focused ISS tests

After installing the OpenTitan Python requirements and RISC-V GNU toolchain:

```bash
cd opentitan/hw/ip/otbn/dv/otbnsim
python3 -m pytest -vv test/clmulvl4_test.py
python3 -m pytest -vv test/simple_test.py -k 'bn_clmulvl4'
```

Expected 256×256 carry-less product:

```text
w10 = 0x3f5e8362c726fb193df83175bcf93074fc9a30576503a9ce0123456789abcdef
w11 = 0x7fffffffffffffffc0e13cdd789944a5ff1ec3228766bb5b7ead20f3da098457
```

## Repository layout

```text
overlay/opentitan/                    Modified OpenTitan files
scripts/bootstrap_opentitan.sh        Pinned checkout and overlay installer
SCHOOL_UBUNTU_OTBN_CLMUL_PROMPT.md    Full Ubuntu/RTL continuation prompt
```
