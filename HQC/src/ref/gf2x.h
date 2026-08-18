/**
 * @file gf2x.h
 * @brief Header file for gf2x.c
 */

#ifndef HQC_GF2X_H
#define HQC_GF2X_H

#include <stdint.h>

#ifdef HQC_GF2X_PROFILE
/**
 * @brief Exclusive timing and operation counts for the reference vect_mul implementation.
 *
 * Timings are accumulated across calls and are not thread-safe. The timed stages do not
 * overlap. residual time is intentionally not stored: callers can compute it as
 * vect_mul_ns minus the sum of the four stage timings.
 */
typedef struct {
    uint64_t vect_mul_calls;
    uint64_t karatsuba_calls;
    uint64_t karatsuba_internal_calls;
    uint64_t schoolbook_calls;
    uint64_t schoolbook_inner_iterations;
    uint64_t karatsuba_prepare_word_iterations;
    uint64_t karatsuba_assemble_word_iterations;
    uint64_t reduction_word_iterations;
    uint64_t vect_mul_ns;
    uint64_t schoolbook_ns;
    uint64_t karatsuba_prepare_ns;
    uint64_t karatsuba_assemble_ns;
    uint64_t reduction_ns;
} hqc_gf2x_profile_t;

void hqc_gf2x_profile_reset(void);
void hqc_gf2x_profile_get(hqc_gf2x_profile_t *profile);
#endif

void vect_mul(uint64_t *o, const uint64_t *v1, const uint64_t *v2);

#endif  // HQC_GF2X_H
