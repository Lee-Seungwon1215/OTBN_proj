/* Copyright lowRISC contributors (OpenTitan project). */
/* Licensed under the Apache License, Version 2.0, see LICENSE for details. */
/* SPDX-License-Identifier: Apache-2.0 */

/* Public interface. */
.section .text
.globl mceliece_keygen_pivot_batch4
.globl mceliece_keygen_elim_batch4

/**
 * Classic McEliece 348864 KeyGen row-operation kernels.
 *
 * A logical row consists of mat[0..11] followed by ops[0..11]. Four adjacent
 * 64-bit words are packed little-endian into one WDR, so one row occupies six
 * WDRs (192 bytes).
 *
 * The caller stages pivot bits separately. Bit 0 of pivot_bits[0] contains
 * the current-row pivot. Bit 0 in lanes 0..3 of pivot_bits[1] contains the
 * four candidate pivots. This makes the kernel independent of the current
 * row index while the first ISA prototype keeps bit_idx/current_lane as
 * immediates.
 */

/**
 * Process four sequential pivot candidates with prefix predicates.
 *
 * @param[in,out] x10: current_row, six packed WDRs
 * @param[in]     x11: candidates, four consecutive six-WDR rows
 * @param[in]     x12: pivot_bits, two WDRs as described above
 *
 * Current row stays resident in w0..w5. Candidate fragments stream through
 * w8..w11. The function is constant-time for a four-row batch.
 *
 * Clobbered registers: x2, x13..x16, w0..w5, w8..w11, w29, w30
 * Clobbered flag groups: FG0
 */
mceliece_keygen_pivot_batch4:
  /* Keep all six current-row fragments resident. */
  li        x2, 0
  bn.lid    x2++, 0(x10)
  bn.lid    x2++, 32(x10)
  bn.lid    x2++, 64(x10)
  bn.lid    x2++, 96(x10)
  bn.lid    x2++, 128(x10)
  bn.lid    x2, 160(x10)

  /* Generate C/M/L/Z prefix predicates for candidates 0/1/2/3. */
  li        x2, 29
  bn.lid    x2, 0(x12)
  li        x2, 30
  bn.lid    x2, 32(x12)
  bn.pivotmask4 w29, w30, 0, 0, FG0

  /* Point at the same fragment in each of the four candidate rows. */
  addi      x13, x11, 0
  addi      x14, x11, 192
  addi      x15, x11, 384
  addi      x16, x11, 576

  /* Chunk 0. */
  li          x2, 8
  bn.lid      x2, 0(x13++)
  li          x2, 9
  bn.lid      x2, 0(x14++)
  li          x2, 10
  bn.lid      x2, 0(x15++)
  li          x2, 11
  bn.lid      x2, 0(x16++)
  bn.xorcond  w0, w0, w8, FG0.C
  bn.xorcond  w0, w0, w9, FG0.M
  bn.xorcond  w0, w0, w10, FG0.L
  bn.xorcond  w0, w0, w11, FG0.Z
  li          x2, 0
  bn.sid      x2, 0(x10)

  /* Chunk 1. */
  li          x2, 8
  bn.lid      x2, 0(x13++)
  li          x2, 9
  bn.lid      x2, 0(x14++)
  li          x2, 10
  bn.lid      x2, 0(x15++)
  li          x2, 11
  bn.lid      x2, 0(x16++)
  bn.xorcond  w1, w1, w8, FG0.C
  bn.xorcond  w1, w1, w9, FG0.M
  bn.xorcond  w1, w1, w10, FG0.L
  bn.xorcond  w1, w1, w11, FG0.Z
  li          x2, 1
  bn.sid      x2, 32(x10)

  /* Chunk 2. */
  li          x2, 8
  bn.lid      x2, 0(x13++)
  li          x2, 9
  bn.lid      x2, 0(x14++)
  li          x2, 10
  bn.lid      x2, 0(x15++)
  li          x2, 11
  bn.lid      x2, 0(x16++)
  bn.xorcond  w2, w2, w8, FG0.C
  bn.xorcond  w2, w2, w9, FG0.M
  bn.xorcond  w2, w2, w10, FG0.L
  bn.xorcond  w2, w2, w11, FG0.Z
  li          x2, 2
  bn.sid      x2, 64(x10)

  /* Chunk 3. */
  li          x2, 8
  bn.lid      x2, 0(x13++)
  li          x2, 9
  bn.lid      x2, 0(x14++)
  li          x2, 10
  bn.lid      x2, 0(x15++)
  li          x2, 11
  bn.lid      x2, 0(x16++)
  bn.xorcond  w3, w3, w8, FG0.C
  bn.xorcond  w3, w3, w9, FG0.M
  bn.xorcond  w3, w3, w10, FG0.L
  bn.xorcond  w3, w3, w11, FG0.Z
  li          x2, 3
  bn.sid      x2, 96(x10)

  /* Chunk 4. */
  li          x2, 8
  bn.lid      x2, 0(x13++)
  li          x2, 9
  bn.lid      x2, 0(x14++)
  li          x2, 10
  bn.lid      x2, 0(x15++)
  li          x2, 11
  bn.lid      x2, 0(x16++)
  bn.xorcond  w4, w4, w8, FG0.C
  bn.xorcond  w4, w4, w9, FG0.M
  bn.xorcond  w4, w4, w10, FG0.L
  bn.xorcond  w4, w4, w11, FG0.Z
  li          x2, 4
  bn.sid      x2, 128(x10)

  /* Chunk 5. */
  li          x2, 8
  bn.lid      x2, 0(x13++)
  li          x2, 9
  bn.lid      x2, 0(x14++)
  li          x2, 10
  bn.lid      x2, 0(x15++)
  li          x2, 11
  bn.lid      x2, 0(x16++)
  bn.xorcond  w5, w5, w8, FG0.C
  bn.xorcond  w5, w5, w9, FG0.M
  bn.xorcond  w5, w5, w10, FG0.L
  bn.xorcond  w5, w5, w11, FG0.Z
  li          x2, 5
  bn.sid      x2, 160(x10)

  ret

/**
 * Eliminate one pivot from four independent target rows.
 *
 * @param[in]     x10: pivot_row, six packed WDRs
 * @param[in,out] x11: targets, four consecutive six-WDR rows
 * @param[in]     x12: target_bits, one WDR; bit 0 in lanes 0..3 contains the
 *                     target-row pivot predicates
 *
 * Pivot row stays resident in w0..w5. Target fragments stream through
 * w8..w11. The function is constant-time for a four-row batch.
 *
 * Clobbered registers: x2, x13..x16, w0..w5, w8..w11, w30
 * Clobbered flag groups: FG1
 */
mceliece_keygen_elim_batch4:
  /* Keep all six pivot-row fragments resident. */
  li        x2, 0
  bn.lid    x2++, 0(x10)
  bn.lid    x2++, 32(x10)
  bn.lid    x2++, 64(x10)
  bn.lid    x2++, 96(x10)
  bn.lid    x2++, 128(x10)
  bn.lid    x2, 160(x10)

  /* Generate four independent C/M/L/Z elimination predicates. */
  li        x2, 30
  bn.lid    x2, 0(x12)
  bn.elimmask4 w30, 0, FG1

  /* Point at the same fragment in each of the four target rows. */
  addi      x13, x11, 0
  addi      x14, x11, 192
  addi      x15, x11, 384
  addi      x16, x11, 576

  /* Chunk 0. */
  li          x2, 8
  bn.lid      x2, 0(x13)
  li          x2, 9
  bn.lid      x2, 0(x14)
  li          x2, 10
  bn.lid      x2, 0(x15)
  li          x2, 11
  bn.lid      x2, 0(x16)
  bn.xorcond  w8, w8, w0, FG1.C
  bn.xorcond  w9, w9, w0, FG1.M
  bn.xorcond  w10, w10, w0, FG1.L
  bn.xorcond  w11, w11, w0, FG1.Z
  li          x2, 8
  bn.sid      x2, 0(x13++)
  li          x2, 9
  bn.sid      x2, 0(x14++)
  li          x2, 10
  bn.sid      x2, 0(x15++)
  li          x2, 11
  bn.sid      x2, 0(x16++)

  /* Chunk 1. */
  li          x2, 8
  bn.lid      x2, 0(x13)
  li          x2, 9
  bn.lid      x2, 0(x14)
  li          x2, 10
  bn.lid      x2, 0(x15)
  li          x2, 11
  bn.lid      x2, 0(x16)
  bn.xorcond  w8, w8, w1, FG1.C
  bn.xorcond  w9, w9, w1, FG1.M
  bn.xorcond  w10, w10, w1, FG1.L
  bn.xorcond  w11, w11, w1, FG1.Z
  li          x2, 8
  bn.sid      x2, 0(x13++)
  li          x2, 9
  bn.sid      x2, 0(x14++)
  li          x2, 10
  bn.sid      x2, 0(x15++)
  li          x2, 11
  bn.sid      x2, 0(x16++)

  /* Chunk 2. */
  li          x2, 8
  bn.lid      x2, 0(x13)
  li          x2, 9
  bn.lid      x2, 0(x14)
  li          x2, 10
  bn.lid      x2, 0(x15)
  li          x2, 11
  bn.lid      x2, 0(x16)
  bn.xorcond  w8, w8, w2, FG1.C
  bn.xorcond  w9, w9, w2, FG1.M
  bn.xorcond  w10, w10, w2, FG1.L
  bn.xorcond  w11, w11, w2, FG1.Z
  li          x2, 8
  bn.sid      x2, 0(x13++)
  li          x2, 9
  bn.sid      x2, 0(x14++)
  li          x2, 10
  bn.sid      x2, 0(x15++)
  li          x2, 11
  bn.sid      x2, 0(x16++)

  /* Chunk 3. */
  li          x2, 8
  bn.lid      x2, 0(x13)
  li          x2, 9
  bn.lid      x2, 0(x14)
  li          x2, 10
  bn.lid      x2, 0(x15)
  li          x2, 11
  bn.lid      x2, 0(x16)
  bn.xorcond  w8, w8, w3, FG1.C
  bn.xorcond  w9, w9, w3, FG1.M
  bn.xorcond  w10, w10, w3, FG1.L
  bn.xorcond  w11, w11, w3, FG1.Z
  li          x2, 8
  bn.sid      x2, 0(x13++)
  li          x2, 9
  bn.sid      x2, 0(x14++)
  li          x2, 10
  bn.sid      x2, 0(x15++)
  li          x2, 11
  bn.sid      x2, 0(x16++)

  /* Chunk 4. */
  li          x2, 8
  bn.lid      x2, 0(x13)
  li          x2, 9
  bn.lid      x2, 0(x14)
  li          x2, 10
  bn.lid      x2, 0(x15)
  li          x2, 11
  bn.lid      x2, 0(x16)
  bn.xorcond  w8, w8, w4, FG1.C
  bn.xorcond  w9, w9, w4, FG1.M
  bn.xorcond  w10, w10, w4, FG1.L
  bn.xorcond  w11, w11, w4, FG1.Z
  li          x2, 8
  bn.sid      x2, 0(x13++)
  li          x2, 9
  bn.sid      x2, 0(x14++)
  li          x2, 10
  bn.sid      x2, 0(x15++)
  li          x2, 11
  bn.sid      x2, 0(x16++)

  /* Chunk 5. */
  li          x2, 8
  bn.lid      x2, 0(x13)
  li          x2, 9
  bn.lid      x2, 0(x14)
  li          x2, 10
  bn.lid      x2, 0(x15)
  li          x2, 11
  bn.lid      x2, 0(x16)
  bn.xorcond  w8, w8, w5, FG1.C
  bn.xorcond  w9, w9, w5, FG1.M
  bn.xorcond  w10, w10, w5, FG1.L
  bn.xorcond  w11, w11, w5, FG1.Z
  li          x2, 8
  bn.sid      x2, 0(x13++)
  li          x2, 9
  bn.sid      x2, 0(x14++)
  li          x2, 10
  bn.sid      x2, 0(x15++)
  li          x2, 11
  bn.sid      x2, 0(x16++)

  ret
