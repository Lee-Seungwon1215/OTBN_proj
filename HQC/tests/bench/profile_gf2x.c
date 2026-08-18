#define _POSIX_C_SOURCE 200809L

#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifdef __APPLE__
#include <mach/mach_time.h>
#else
#include <time.h>
#endif

#include "api.h"
#include "gf2x.h"
#include "parameters.h"
#include "symmetric.h"

#define DEFAULT_ITERATIONS 30U
#define DEFAULT_WARMUP     3U

static uint64_t time_ns(void) {
#ifdef __APPLE__
    static mach_timebase_info_data_t timebase;
    if (timebase.denom == 0) {
        mach_timebase_info(&timebase);
    }
    uint64_t ticks = mach_absolute_time();
    return (ticks / timebase.denom) * timebase.numer + ((ticks % timebase.denom) * timebase.numer) / timebase.denom;
#else
    struct timespec now;
    clock_gettime(CLOCK_MONOTONIC, &now);
    return (uint64_t)now.tv_sec * 1000000000ULL + (uint64_t)now.tv_nsec;
#endif
}

static uint64_t parse_count(const char* text, const char* name) {
    char* end = NULL;
    errno = 0;
    unsigned long long value = strtoull(text, &end, 10);
    if (errno != 0 || end == text || *end != '\0' || value == 0) {
        fprintf(stderr, "invalid %s: %s\n", name, text);
        exit(EXIT_FAILURE);
    }
    return (uint64_t)value;
}

static double percentage(uint64_t part, uint64_t total) {
    return total == 0 ? 0.0 : 100.0 * (double)part / (double)total;
}

static uint64_t residual_ns(const hqc_gf2x_profile_t* profile) {
    uint64_t attributed =
        profile->schoolbook_ns + profile->karatsuba_prepare_ns + profile->karatsuba_assemble_ns + profile->reduction_ns;
    return profile->vect_mul_ns > attributed ? profile->vect_mul_ns - attributed : 0;
}

static void print_header(void) {
    puts(
        "operation,iterations,kem_total_ns,vect_mul_calls,vect_mul_ns,vect_mul_pct_kem,"
        "schoolbook_ns,schoolbook_pct_vect_mul,karatsuba_prepare_ns,karatsuba_prepare_pct_vect_mul,"
        "karatsuba_assemble_ns,karatsuba_assemble_pct_vect_mul,reduction_ns,reduction_pct_vect_mul,"
        "residual_ns,residual_pct_vect_mul,karatsuba_calls,karatsuba_internal_calls,schoolbook_calls,"
        "schoolbook_inner_iterations,karatsuba_prepare_word_iterations,karatsuba_assemble_word_iterations,"
        "reduction_word_iterations");
}

static void print_result(const char* operation, uint64_t iterations, uint64_t kem_total_ns,
                         const hqc_gf2x_profile_t* profile) {
    uint64_t residual = residual_ns(profile);
    printf("%s,%" PRIu64 ",%" PRIu64 ",%" PRIu64 ",%" PRIu64
           ",%.6f,"
           "%" PRIu64 ",%.6f,%" PRIu64 ",%.6f,%" PRIu64
           ",%.6f,"
           "%" PRIu64 ",%.6f,%" PRIu64 ",%.6f,%" PRIu64 ",%" PRIu64 ",%" PRIu64 ",%" PRIu64 ",%" PRIu64 ",%" PRIu64
           ",%" PRIu64 "\n",
           operation, iterations, kem_total_ns, profile->vect_mul_calls, profile->vect_mul_ns,
           percentage(profile->vect_mul_ns, kem_total_ns), profile->schoolbook_ns,
           percentage(profile->schoolbook_ns, profile->vect_mul_ns), profile->karatsuba_prepare_ns,
           percentage(profile->karatsuba_prepare_ns, profile->vect_mul_ns), profile->karatsuba_assemble_ns,
           percentage(profile->karatsuba_assemble_ns, profile->vect_mul_ns), profile->reduction_ns,
           percentage(profile->reduction_ns, profile->vect_mul_ns), residual,
           percentage(residual, profile->vect_mul_ns), profile->karatsuba_calls, profile->karatsuba_internal_calls,
           profile->schoolbook_calls, profile->schoolbook_inner_iterations, profile->karatsuba_prepare_word_iterations,
           profile->karatsuba_assemble_word_iterations, profile->reduction_word_iterations);
}

int main(int argc, char** argv) {
    uint64_t iterations = argc > 1 ? parse_count(argv[1], "iterations") : DEFAULT_ITERATIONS;
    uint64_t warmup = argc > 2 ? parse_count(argv[2], "warmup") : DEFAULT_WARMUP;
    if (argc > 3) {
        fprintf(stderr, "usage: %s [iterations] [warmup]\n", argv[0]);
        return EXIT_FAILURE;
    }

    uint8_t pk[PUBLIC_KEY_BYTES] = {0};
    uint8_t sk[SECRET_KEY_BYTES] = {0};
    uint8_t ct[CIPHERTEXT_BYTES] = {0};
    uint8_t ss_enc[SHARED_SECRET_BYTES] = {0};
    uint8_t ss_dec[SHARED_SECRET_BYTES] = {0};
    uint8_t seed[48] = {0};
    for (size_t i = 0; i < sizeof(seed); i++) {
        seed[i] = (uint8_t)i;
    }
    prng_init(seed, NULL, sizeof(seed), 0);

    for (uint64_t i = 0; i < warmup; i++) {
        crypto_kem_keypair(pk, sk);
        crypto_kem_enc(ct, ss_enc, pk);
        crypto_kem_dec(ss_dec, ct, sk);
        if (memcmp(ss_enc, ss_dec, SHARED_SECRET_BYTES) != 0) {
            fputs("HQC warmup correctness check failed\n", stderr);
            return EXIT_FAILURE;
        }
    }

    print_header();

    hqc_gf2x_profile_t profile;
    hqc_gf2x_profile_reset();
    uint64_t start_ns = time_ns();
    for (uint64_t i = 0; i < iterations; i++) {
        crypto_kem_keypair(pk, sk);
    }
    uint64_t elapsed_ns = time_ns() - start_ns;
    hqc_gf2x_profile_get(&profile);
    print_result("keygen", iterations, elapsed_ns, &profile);

    hqc_gf2x_profile_reset();
    start_ns = time_ns();
    for (uint64_t i = 0; i < iterations; i++) {
        crypto_kem_enc(ct, ss_enc, pk);
    }
    elapsed_ns = time_ns() - start_ns;
    hqc_gf2x_profile_get(&profile);
    print_result("encaps", iterations, elapsed_ns, &profile);

    hqc_gf2x_profile_reset();
    start_ns = time_ns();
    for (uint64_t i = 0; i < iterations; i++) {
        crypto_kem_dec(ss_dec, ct, sk);
    }
    elapsed_ns = time_ns() - start_ns;
    hqc_gf2x_profile_get(&profile);
    print_result("decaps", iterations, elapsed_ns, &profile);

    if (memcmp(ss_enc, ss_dec, SHARED_SECRET_BYTES) != 0) {
        fputs("HQC correctness check failed after profiling\n", stderr);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
