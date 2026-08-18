# Copyright lowRISC contributors (OpenTitan project).
# Licensed under the Apache License, Version 2.0, see LICENSE for details.
# SPDX-License-Identifier: Apache-2.0

import random
from typing import List

from sim.decode import decode_words
from sim.flags import FlagReg
from sim.insn import (BNELIMMASK4, BNPIVOTMASK4, BNXORCOND,
                      BNXORCONDN)
from sim.state import OTBNState


MASK64 = (1 << 64) - 1


def _pack64(words: List[int]) -> int:
    assert len(words) == 4
    return sum((word & MASK64) << (64 * lane)
               for lane, word in enumerate(words))


def _write_wdr(state: OTBNState, reg: int, value: int) -> None:
    state.wdrs.get_reg(reg).write_unsigned(value)
    state.wdrs.commit()


def _write_flags(state: OTBNState, value: int) -> None:
    state.csrs.flags.write_unsigned(value)
    state.csrs.flags.commit()


def _execute_xorcond(insn_cls: type, state: OTBNState, wrd: int,
                     wrs1: int, wrs2: int, flag_group: int,
                     flag: int) -> int:
    operands = {
        'wrd': wrd,
        'wrs1': wrs1,
        'wrs2': wrs2,
        'flag_group': flag_group,
        'flag': flag,
    }
    insn_cls(0, operands).execute(state)
    state.wdrs.commit()
    return state.wdrs.get_reg(wrd).read_unsigned()


def _pivot_word(row: List[int], word_idx: int) -> int:
    chunk = word_idx // 4
    lane = word_idx % 4
    return (row[chunk] >> (64 * lane)) & MASK64


def test_mceliece_keygen_decode() -> None:
    decoded = decode_words(
        0,
        [
            (True, 0x3010215B),
            (True, 0xE01021DB),
            (True, 0x621022DB),
            (True, 0xC400A2DB),
        ],
    )

    xorcond, xorcondn, pivotmask4, elimmask4 = decoded
    assert isinstance(xorcond, BNXORCOND)
    assert isinstance(xorcondn, BNXORCONDN)
    assert isinstance(pivotmask4, BNPIVOTMASK4)
    assert isinstance(elimmask4, BNELIMMASK4)

    assert (xorcond.wrd, xorcond.wrs1, xorcond.wrs2,
            xorcond.flag_group, xorcond.flag) == (2, 0, 1, 0, 3)
    assert (xorcondn.wrd, xorcondn.wrs1, xorcondn.wrs2,
            xorcondn.flag_group, xorcondn.flag) == (3, 0, 1, 1, 2)
    assert (pivotmask4.wrs1, pivotmask4.wrs2, pivotmask4.current_lane,
            pivotmask4.bit_idx, pivotmask4.flag_group) == (0, 1, 2, 37, 0)
    assert (elimmask4.wrs, elimmask4.bit_idx,
            elimmask4.flag_group) == (1, 37, 1)


def test_xorcond_randomized() -> None:
    rng = random.Random(0x584F52434F4E44)

    for _ in range(200):
        lhs = rng.getrandbits(256)
        rhs = rng.getrandbits(256)
        flags = rng.getrandbits(8)

        for flag_group in range(2):
            for flag in range(4):
                flag_is_set = bool((flags >> (4 * flag_group + flag)) & 1)
                for insn_cls, invert in ((BNXORCOND, False),
                                         (BNXORCONDN, True)):
                    state = OTBNState()
                    _write_wdr(state, 0, lhs)
                    _write_wdr(state, 1, rhs)
                    _write_flags(state, flags)

                    result = _execute_xorcond(
                        insn_cls, state, 2, 0, 1, flag_group, flag)
                    should_xor = flag_is_set != invert
                    assert result == (lhs ^ rhs if should_xor else lhs)
                    assert state.csrs.flags.read_unsigned() == flags


def test_pivotmask4_randomized() -> None:
    rng = random.Random(0x5049564F5434)

    for _ in range(400):
        current_words = [rng.getrandbits(64) for _ in range(4)]
        candidate_words = [rng.getrandbits(64) for _ in range(4)]
        current_lane = rng.randrange(4)
        bit_idx = rng.randrange(64)
        flag_group = rng.randrange(2)
        old_flags = rng.getrandbits(8)

        state = OTBNState()
        _write_wdr(state, 0, _pack64(current_words))
        _write_wdr(state, 1, _pack64(candidate_words))
        _write_flags(state, old_flags)

        operands = {
            'wrs1': 0,
            'wrs2': 1,
            'current_lane': current_lane,
            'bit_idx': bit_idx,
            'flag_group': flag_group,
        }
        BNPIVOTMASK4(0, operands).execute(state)
        state.csrs.flags.commit()

        found = bool((current_words[current_lane] >> bit_idx) & 1)
        expected_group = 0
        for lane, candidate_word in enumerate(candidate_words):
            expected_group |= int(not found) << lane
            found |= bool((candidate_word >> bit_idx) & 1)

        group_shift = 4 * flag_group
        expected_flags = ((old_flags & ~(0xF << group_shift)) |
                          (expected_group << group_shift))
        assert state.csrs.flags.read_unsigned() == expected_flags


def test_elimmask4_randomized() -> None:
    rng = random.Random(0x454C494D34)

    for _ in range(400):
        target_words = [rng.getrandbits(64) for _ in range(4)]
        bit_idx = rng.randrange(64)
        flag_group = rng.randrange(2)
        old_flags = rng.getrandbits(8)

        state = OTBNState()
        _write_wdr(state, 0, _pack64(target_words))
        _write_flags(state, old_flags)

        operands = {
            'wrs': 0,
            'bit_idx': bit_idx,
            'flag_group': flag_group,
        }
        BNELIMMASK4(0, operands).execute(state)
        state.csrs.flags.commit()

        expected_group = sum(
            ((word >> bit_idx) & 1) << lane
            for lane, word in enumerate(target_words))
        group_shift = 4 * flag_group
        expected_flags = ((old_flags & ~(0xF << group_shift)) |
                          (expected_group << group_shift))
        assert state.csrs.flags.read_unsigned() == expected_flags


def test_parallel_prefix_pivot_schedule() -> None:
    """Check batched prefix search against the original sequential loop."""
    rng = random.Random(0x4D43454C5049564F54)

    for _ in range(200):
        current = [rng.getrandbits(256) for _ in range(6)]
        candidates = [[rng.getrandbits(256) for _ in range(6)]
                      for _ in range(12)]
        word_idx = rng.randrange(12)
        bit_idx = rng.randrange(64)
        pivot_chunk = word_idx // 4
        current_lane = word_idx % 4

        expected = list(current)
        for candidate in candidates:
            pivot = (_pivot_word(expected, word_idx) >> bit_idx) & 1
            if not pivot:
                expected = [lhs ^ rhs
                            for lhs, rhs in zip(expected, candidate)]

        state = OTBNState()
        for chunk, value in enumerate(current):
            _write_wdr(state, chunk, value)

        for batch_base in range(0, len(candidates), 4):
            batch = candidates[batch_base:batch_base + 4]
            packed_pivots = _pack64(
                [_pivot_word(row, word_idx) for row in batch])
            _write_wdr(state, 30, packed_pivots)

            pivot_operands = {
                'wrs1': pivot_chunk,
                'wrs2': 30,
                'current_lane': current_lane,
                'bit_idx': bit_idx,
                'flag_group': 0,
            }
            BNPIVOTMASK4(0, pivot_operands).execute(state)
            state.csrs.flags.commit()

            for chunk in range(6):
                for lane, candidate in enumerate(batch):
                    _write_wdr(state, 8 + lane, candidate[chunk])
                for lane in range(4):
                    _execute_xorcond(
                        BNXORCOND, state, chunk, chunk, 8 + lane, 0, lane)

        assert [state.wdrs.get_reg(chunk).read_unsigned()
                for chunk in range(6)] == expected


def test_four_row_forward_elimination_schedule() -> None:
    """Check one four-row batch against four independent scalar updates."""
    rng = random.Random(0x4D43454C454C494D)

    for _ in range(200):
        pivot_row = [rng.getrandbits(256) for _ in range(6)]
        targets = [[rng.getrandbits(256) for _ in range(6)]
                   for _ in range(4)]
        word_idx = rng.randrange(12)
        bit_idx = rng.randrange(64)

        expected = [list(target) for target in targets]
        for lane, target in enumerate(targets):
            predicate = (_pivot_word(target, word_idx) >> bit_idx) & 1
            if predicate:
                expected[lane] = [lhs ^ rhs
                                  for lhs, rhs in zip(target, pivot_row)]

        state = OTBNState()
        for chunk, value in enumerate(pivot_row):
            _write_wdr(state, chunk, value)

        packed_pivots = _pack64(
            [_pivot_word(target, word_idx) for target in targets])
        _write_wdr(state, 30, packed_pivots)
        BNELIMMASK4(0, {
            'wrs': 30,
            'bit_idx': bit_idx,
            'flag_group': 1,
        }).execute(state)
        state.csrs.flags.commit()

        actual = [[0] * 6 for _ in range(4)]
        for chunk in range(6):
            for lane, target in enumerate(targets):
                _write_wdr(state, 8 + lane, target[chunk])
            for lane in range(4):
                actual[lane][chunk] = _execute_xorcond(
                    BNXORCOND, state, 8 + lane, 8 + lane,
                    chunk, 1, lane)

        assert actual == expected


def test_single_wdr_forward_streaming_schedule() -> None:
    """Check the low-register-pressure w6 overwrite schedule."""
    rng = random.Random(0x53545245414D36)

    for _ in range(200):
        pivot_row = [rng.getrandbits(256) for _ in range(6)]
        target = [rng.getrandbits(256) for _ in range(6)]
        word_idx = rng.randrange(12)
        bit_idx = rng.randrange(64)
        pivot_bit = (_pivot_word(target, word_idx) >> bit_idx) & 1
        expected = ([lhs ^ rhs for lhs, rhs in zip(target, pivot_row)]
                    if pivot_bit else target)

        state = OTBNState()
        for chunk, value in enumerate(pivot_row):
            _write_wdr(state, chunk, value)

        # BN.AND would set Z to one when the target pivot bit is zero.
        _write_flags(state, int(not pivot_bit) << 3)
        actual = []
        for chunk, value in enumerate(target):
            _write_wdr(state, 6, value)
            actual.append(_execute_xorcond(
                BNXORCONDN, state, 6, 6, chunk, 0, 3))

        assert actual == expected
