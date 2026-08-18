/* Copyright lowRISC contributors (OpenTitan project). */
/* Licensed under the Apache License, Version 2.0, see LICENSE for details. */
/* SPDX-License-Identifier: Apache-2.0 */

/*
 * Multiply two four-limb GF(2) polynomials.
 *
 * Input limbs are packed little-endian in w0 and w1. The 512-bit result is
 * returned in w11:w10. For each broadcast limb of w1, BN.CLMULVL4 produces
 * four partial products; existing BN.XOR shifts assemble their diagonals.
 */
.section .text.start
  addi x2, x0, 0
  la x3, operand_a
  bn.lid x2, 0(x3)

  addi x2, x0, 1
  la x3, operand_b
  bn.lid x2, 0(x3)

  bn.xor w11, w11, w11

  /* Contributions from b[0]. */
  bn.clmulvl4.lo w10, w0, w1, 0
  bn.clmulvl4.hi w3, w0, w1, 0
  bn.xor w10, w10, w3 << 64
  bn.xor w11, w11, w3 >> 192

  /* Contributions from b[1], shifted by one 64-bit result limb. */
  bn.clmulvl4.lo w2, w0, w1, 1
  bn.clmulvl4.hi w3, w0, w1, 1
  bn.xor w10, w10, w2 << 64
  bn.xor w11, w11, w2 >> 192
  bn.xor w10, w10, w3 << 128
  bn.xor w11, w11, w3 >> 128

  /* Contributions from b[2], shifted by two 64-bit result limbs. */
  bn.clmulvl4.lo w2, w0, w1, 2
  bn.clmulvl4.hi w3, w0, w1, 2
  bn.xor w10, w10, w2 << 128
  bn.xor w11, w11, w2 >> 128
  bn.xor w10, w10, w3 << 192
  bn.xor w11, w11, w3 >> 64

  /* Contributions from b[3], shifted by three 64-bit result limbs. */
  bn.clmulvl4.lo w2, w0, w1, 3
  bn.clmulvl4.hi w3, w0, w1, 3
  bn.xor w10, w10, w2 << 192
  bn.xor w11, w11, w2 >> 64
  bn.xor w11, w11, w3

  ecall

.section .data
.balign 32
operand_a:
  .quad 0x0123456789abcdef
  .quad 0xfedcba9876543210
  .quad 0x8000000000000001
  .quad 0xffffffffffffffff

.balign 32
operand_b:
  .quad 0x0000000000000001
  .quad 0x0000000000000002
  .quad 0x0123456789abcdef
  .quad 0x8000000000000000
