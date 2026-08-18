/* Copyright lowRISC contributors (OpenTitan project). */
/* Licensed under the Apache License, Version 2.0, see LICENSE for details. */
/* SPDX-License-Identifier: Apache-2.0 */

/*
 * Experimental 256x256-bit carry-less schoolbook multiplication.
 *
 * BN.CLMULVL4.LO/HI are simulator-only custom instructions until their RTL
 * implementation is added. The two inputs are loaded into w0 and w1. The
 * 512-bit GF(2) polynomial product is returned in w11:w10.
 */
.section .text.start
  addi x2, x0, 0
  la x3, operand_a
  bn.lid x2, 0(x3)

  addi x2, x0, 1
  la x3, operand_b
  bn.lid x2, 0(x3)

  bn.xor w11, w11, w11

  /* b[0] */
  bn.clmulvl4.lo w10, w0, w1, 0
  bn.clmulvl4.hi w3, w0, w1, 0
  bn.xor w10, w10, w3 << 64
  bn.xor w11, w11, w3 >> 192

  /* b[1] */
  bn.clmulvl4.lo w2, w0, w1, 1
  bn.clmulvl4.hi w3, w0, w1, 1
  bn.xor w10, w10, w2 << 64
  bn.xor w11, w11, w2 >> 192
  bn.xor w10, w10, w3 << 128
  bn.xor w11, w11, w3 >> 128

  /* b[2] */
  bn.clmulvl4.lo w2, w0, w1, 2
  bn.clmulvl4.hi w3, w0, w1, 2
  bn.xor w10, w10, w2 << 128
  bn.xor w11, w11, w2 >> 128
  bn.xor w10, w10, w3 << 192
  bn.xor w11, w11, w3 >> 64

  /* b[3] */
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

/*
 * Expected result:
 * w11 = 7fffffffffffffffc0e13cdd789944a5ff1ec3228766bb5b7ead20f3da098457
 * w10 = 3f5e8362c726fb193df83175bcf93074fc9a30576503a9ce0123456789abcdef
 */
