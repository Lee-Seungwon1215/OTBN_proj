/* Copyright lowRISC contributors (OpenTitan project). */
/* Licensed under the Apache License, Version 2.0, see LICENSE for details. */
/* SPDX-License-Identifier: Apache-2.0 */

/**
 * Standalone runner for the Classic McEliece KeyGen row-operation kernels.
 *
 * Tests or a host fill the exported DMEM buffers before starting OTBN. The
 * program executes one four-candidate pivot batch and one four-target forward
 * elimination batch, then stops. Each row is 192 bytes (six WDRs).
 */
.section .text.start
main:
  la    x10, pivot_current
  la    x11, pivot_candidates
  la    x12, pivot_bits
  jal   x1, mceliece_keygen_pivot_batch4

  la    x10, elim_pivot
  la    x11, elim_targets
  la    x12, elim_bits
  jal   x1, mceliece_keygen_elim_batch4

  ecall

.section .bss
.balign 32
.globl pivot_current
pivot_current:
  .zero 192

.balign 32
.globl pivot_candidates
pivot_candidates:
  .zero 768

.balign 32
.globl pivot_bits
pivot_bits:
  .zero 64

.balign 32
.globl elim_pivot
elim_pivot:
  .zero 192

.balign 32
.globl elim_targets
elim_targets:
  .zero 768

.balign 32
.globl elim_bits
elim_bits:
  .zero 32
