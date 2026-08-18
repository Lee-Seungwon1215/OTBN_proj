/* Copyright lowRISC contributors (OpenTitan project). */
/* Licensed under the Apache License, Version 2.0, see LICENSE for details. */
/* SPDX-License-Identifier: Apache-2.0 */

/* Exercise both halves of BN.CLMULVL4 for every broadcast lane. */
.section .text.start
  addi x2, x0, 0
  la x3, operand_a
  bn.lid x2, 0(x3)

  addi x2, x0, 1
  la x3, operand_b
  bn.lid x2, 0(x3)

  bn.clmulvl4.lo w2, w0, w1, 0
  bn.clmulvl4.hi w3, w0, w1, 0
  bn.clmulvl4.lo w4, w0, w1, 1
  bn.clmulvl4.hi w5, w0, w1, 1
  bn.clmulvl4.lo w6, w0, w1, 2
  bn.clmulvl4.hi w7, w0, w1, 2
  bn.clmulvl4.lo w8, w0, w1, 3
  bn.clmulvl4.hi w9, w0, w1, 3

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
