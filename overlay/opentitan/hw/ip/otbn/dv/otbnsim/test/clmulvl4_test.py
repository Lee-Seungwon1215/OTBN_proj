# Copyright lowRISC contributors (OpenTitan project).
# Licensed under the Apache License, Version 2.0, see LICENSE for details.
# SPDX-License-Identifier: Apache-2.0

import random
from typing import List

from sim.decode import decode_words
from sim.insn import BNCLMULVL4HI, BNCLMULVL4LO
from sim.state import OTBNState


MASK64 = (1 << 64) - 1
MASK256 = (1 << 256) - 1


def _clmul64_reference(a: int, b: int) -> int:
    result = 0
    for bit in range(64):
        if (b >> bit) & 1:
            result ^= a << bit
    return result


def _pack(words: List[int]) -> int:
    return sum(word << (64 * idx) for idx, word in enumerate(words))


def _execute(insn_cls: type, state: OTBNState, lane: int) -> int:
    operands = {'wrd': 2, 'wrs1': 0, 'wrs2': 1, 'lane': lane}
    insn_cls(0, operands).execute(state)
    result = state.wdrs.get_reg(2).read_next()
    state.wdrs.abort()
    assert result is not None
    return result


def test_clmulvl4_decode() -> None:
    raw_lo = [0x0010115B, 0x1010115B, 0x2010115B, 0x3010115B]
    raw_hi = [0x401011DB, 0x501011DB, 0x601011DB, 0x701011DB]

    for lane in range(4):
        lo, hi = decode_words(0, [(True, raw_lo[lane]), (True, raw_hi[lane])])
        assert isinstance(lo, BNCLMULVL4LO)
        assert isinstance(hi, BNCLMULVL4HI)
        assert (lo.wrd, lo.wrs1, lo.wrs2, lo.lane) == (2, 0, 1, lane)
        assert (hi.wrd, hi.wrs1, hi.wrs2, hi.lane) == (3, 0, 1, lane)


def test_clmulvl4_randomized() -> None:
    rng = random.Random(0x434C4D554C)

    for _ in range(200):
        vec_a = [rng.getrandbits(64) for _ in range(4)]
        vec_b = [rng.getrandbits(64) for _ in range(4)]

        state = OTBNState()
        state.wdrs.get_reg(0).write_unsigned(_pack(vec_a))
        state.wdrs.get_reg(1).write_unsigned(_pack(vec_b))
        state.wdrs.commit()

        for lane in range(4):
            products = [_clmul64_reference(a, vec_b[lane]) for a in vec_a]
            expected_lo = _pack([product & MASK64 for product in products])
            expected_hi = _pack([product >> 64 for product in products])

            assert _execute(BNCLMULVL4LO, state, lane) == expected_lo
            assert _execute(BNCLMULVL4HI, state, lane) == expected_hi


def test_clmulvl4_schoolbook_schedule() -> None:
    rng = random.Random(0x485143)

    for _ in range(200):
        vec_a = [rng.getrandbits(64) for _ in range(4)]
        vec_b = [rng.getrandbits(64) for _ in range(4)]

        state = OTBNState()
        state.wdrs.get_reg(0).write_unsigned(_pack(vec_a))
        state.wdrs.get_reg(1).write_unsigned(_pack(vec_b))
        state.wdrs.commit()

        result = 0
        for lane in range(4):
            lo = _execute(BNCLMULVL4LO, state, lane)
            hi = _execute(BNCLMULVL4HI, state, lane)
            result ^= lo << (64 * lane)
            result ^= hi << (64 * (lane + 1))

        expected = 0
        for a_idx, a in enumerate(vec_a):
            for b_idx, b in enumerate(vec_b):
                expected ^= _clmul64_reference(a, b) << (64 * (a_idx + b_idx))

        assert result & MASK256 == expected & MASK256
        assert result >> 256 == expected >> 256
