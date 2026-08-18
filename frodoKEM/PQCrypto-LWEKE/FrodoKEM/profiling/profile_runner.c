#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "profile.h"
#include "../src/api_frodo640.h"

static int run_correctness_check(void)
{
    unsigned char pk[CRYPTO_PUBLICKEYBYTES];
    unsigned char sk[CRYPTO_SECRETKEYBYTES];
    unsigned char ct[CRYPTO_CIPHERTEXTBYTES];
    unsigned char sender_secret[CRYPTO_BYTES];
    unsigned char receiver_secret[CRYPTO_BYTES];

    if (crypto_kem_keypair_Frodo640(pk, sk) != 0 ||
        crypto_kem_enc_Frodo640(ct, sender_secret, pk) != 0 ||
        crypto_kem_dec_Frodo640(receiver_secret, ct, sk) != 0) {
        return 0;
    }
    return memcmp(sender_secret, receiver_secret, CRYPTO_BYTES) == 0;
}

int main(int argc, char **argv)
{
    const unsigned int iterations = argc > 1 ? (unsigned int)strtoul(argv[1], NULL, 10) : 30;
    const unsigned int trials = argc > 2 ? (unsigned int)strtoul(argv[2], NULL, 10) : 5;
    const char *implementation = argc > 3 ? argv[3] : "unknown";
    const char *output_path = argc > 4 ? argv[4] : "profile-results.csv";
    unsigned char pk[CRYPTO_PUBLICKEYBYTES];
    unsigned char sk[CRYPTO_SECRETKEYBYTES];
    unsigned char ct[CRYPTO_CIPHERTEXTBYTES];
    unsigned char sender_secret[CRYPTO_BYTES];
    unsigned char receiver_secret[CRYPTO_BYTES];

    if (iterations == 0 || trials == 0) {
        fprintf(stderr, "iterations and trials must be positive\n");
        return 2;
    }
    if (!run_correctness_check()) {
        fprintf(stderr, "correctness check failed before profiling\n");
        return 3;
    }

    for (unsigned int i = 0; i < 3; i++) {
        crypto_kem_keypair_Frodo640(pk, sk);
        crypto_kem_enc_Frodo640(ct, sender_secret, pk);
        crypto_kem_dec_Frodo640(receiver_secret, ct, sk);
    }

    FILE *output = fopen(output_path, "w");
    if (output == NULL) {
        perror("fopen");
        return 4;
    }
    fprintf(output, "implementation,trial,stage,region,calls,total_ns,stage_total_ns\n");

    for (unsigned int trial = 0; trial < trials; trial++) {
        frodo_profile_reset();

        for (unsigned int i = 0; i < iterations; i++) {
            if (crypto_kem_keypair_Frodo640(pk, sk) != 0) {
                fclose(output);
                return 5;
            }
        }
        for (unsigned int i = 0; i < iterations; i++) {
            if (crypto_kem_enc_Frodo640(ct, sender_secret, pk) != 0) {
                fclose(output);
                return 6;
            }
        }
        for (unsigned int i = 0; i < iterations; i++) {
            if (crypto_kem_dec_Frodo640(receiver_secret, ct, sk) != 0) {
                fclose(output);
                return 7;
            }
        }

        if (memcmp(sender_secret, receiver_secret, CRYPTO_BYTES) != 0) {
            fprintf(stderr, "correctness check failed in trial %u\n", trial);
            fclose(output);
            return 8;
        }
        frodo_profile_write_csv(output, implementation, trial);
    }

    fclose(output);
    printf("profiled %s: %u iterations x %u trials -> %s\n",
           implementation, iterations, trials, output_path);
    return 0;
}
