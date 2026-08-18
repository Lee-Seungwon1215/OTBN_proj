# Copyright lowRISC contributors (OpenTitan project).
# Licensed under the Apache License, Version 2.0, see LICENSE for details.
# SPDX-License-Identifier: Apache-2.0

import os
import random
import struct
from typing import List

import py

import testutil


MASK256 = (1 << 256) - 1
ROW_WDRS = 6

CRYPTO_DIR = os.path.normpath(os.path.join(
    testutil.OTBN_DIR, '..', '..', '..', 'sw', 'otbn', 'crypto'))
KERNEL_PATH = os.path.join(CRYPTO_DIR, 'mceliece_keygen_row_ops.s')
RUNNER_PATH = os.path.join(CRYPTO_DIR, 'run_mceliece_keygen_row_ops.s')


def _pack_wdrs(values: List[int]) -> bytes:
    return b''.join(value.to_bytes(32, 'little') for value in values)


def _pack_lanes(values: List[int]) -> bytes:
    assert len(values) == 4
    return struct.pack('<QQQQ', *values)


def _read_wdrs(sim, symbol: str, count: int) -> List[int]:
    address = sim.symbols[symbol]
    result = []
    for offset in range(count):
        value, valid = sim.state.dmem.load_u256(address + 32 * offset)
        assert valid
        result.append(value)
    return result


def _row_word(row: List[int], word_idx: int) -> int:
    chunk = word_idx // 4
    lane = word_idx % 4
    return (row[chunk] >> (64 * lane)) & ((1 << 64) - 1)


def test_mceliece_keygen_row_ops_assembly(tmpdir: py.path.local) -> None:
    """Assemble and execute both optimized four-row kernels end to end."""
    with open(RUNNER_PATH, encoding='utf-8') as runner_file:
        runner = runner_file.read()
    with open(KERNEL_PATH, encoding='utf-8') as kernel_file:
        kernel = kernel_file.read()

    sim = testutil.prepare_sim_for_asm_str(
        kernel + '\n' + runner, tmpdir, False)

    rng = random.Random(0x4D43454C4F54424E)
    pivot_current = [rng.getrandbits(256) for _ in range(ROW_WDRS)]
    pivot_candidates = [
        [rng.getrandbits(256) for _ in range(ROW_WDRS)]
        for _ in range(4)
    ]
    elim_pivot = [rng.getrandbits(256) for _ in range(ROW_WDRS)]
    elim_targets = [
        [rng.getrandbits(256) for _ in range(ROW_WDRS)]
        for _ in range(4)
    ]

    # Use an arbitrary mat word and bit. The caller normalizes these pivot
    # bits into bit 0 of the staging lanes consumed by the assembly kernel.
    word_idx = 5
    bit_idx = 37
    current_bit = (_row_word(pivot_current, word_idx) >> bit_idx) & 1
    candidate_bits = [
        (_row_word(candidate, word_idx) >> bit_idx) & 1
        for candidate in pivot_candidates
    ]
    target_bits = [
        (_row_word(target, word_idx) >> bit_idx) & 1
        for target in elim_targets
    ]

    sim.load_dmem_vars({
        'pivot_current': _pack_wdrs(pivot_current),
        'pivot_candidates': _pack_wdrs([
            value for row in pivot_candidates for value in row
        ]),
        'pivot_bits': (_pack_lanes([current_bit, 0, 0, 0]) +
                       _pack_lanes(candidate_bits)),
        'elim_pivot': _pack_wdrs(elim_pivot),
        'elim_targets': _pack_wdrs([
            value for row in elim_targets for value in row
        ]),
        'elim_bits': _pack_lanes(target_bits),
    })

    expected_current = list(pivot_current)
    found = bool(current_bit)
    for candidate, candidate_bit in zip(pivot_candidates, candidate_bits):
        if not found:
            expected_current = [
                (lhs ^ rhs) & MASK256
                for lhs, rhs in zip(expected_current, candidate)
            ]
        found |= bool(candidate_bit)

    expected_targets = []
    for target, predicate in zip(elim_targets, target_bits):
        expected_targets.append([
            ((value ^ pivot) if predicate else value) & MASK256
            for value, pivot in zip(target, elim_pivot)
        ])

    sim.run(verbose=False, dump_file=None)

    assert sim.state.ext_regs.read('ERR_BITS', False) == 0
    assert _read_wdrs(sim, 'pivot_current', ROW_WDRS) == expected_current
    assert _read_wdrs(sim, 'elim_targets', 4 * ROW_WDRS) == [
        value for row in expected_targets for value in row
    ]
