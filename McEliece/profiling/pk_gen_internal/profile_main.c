#include "mceliece.h"
#include "pk_gen_profile.h"

#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

static uint64_t now_ns(void)
{
  struct timespec ts;

  clock_gettime(CLOCK_MONOTONIC, &ts);
  return (uint64_t) ts.tv_sec * 1000000000ULL + (uint64_t) ts.tv_nsec;
}

static int parse_positive(const char *text, const char *name)
{
  char *end;
  long value;

  errno = 0;
  value = strtol(text, &end, 10);
  if (errno != 0 || *text == '\0' || *end != '\0' || value <= 0 ||
      value > 1000000) {
    fprintf(stderr, "invalid %s: %s\n", name, text);
    exit(2);
  }
  return (int) value;
}

static int kem_roundtrip(
    unsigned char *pk,
    unsigned char *sk,
    unsigned char *ct,
    unsigned char *shared_enc,
    unsigned char *shared_dec,
    uint64_t *keypair_ns)
{
  uint64_t start = now_ns();
  int result;

  mceliece348864_keypair(pk, sk);
  *keypair_ns = now_ns() - start;

  result = mceliece348864_enc(ct, shared_enc, pk);
  if (result != 0)
    return -1;

  result = mceliece348864_dec(shared_dec, ct, sk);
  if (result != 0)
    return -2;

  if (memcmp(shared_enc, shared_dec, mceliece348864_BYTES) != 0)
    return -3;

  return 0;
}

int main(int argc, char **argv)
{
  int trials = 7;
  int iterations = 10;
  int warmups = 2;
  const char *csv_path = "pk_gen_profile.csv";
  unsigned char *pk;
  unsigned char *sk;
  unsigned char *ct;
  unsigned char *shared_enc;
  unsigned char *shared_dec;
  FILE *csv;
  int trial;
  int iteration;
  int phase;
  uint64_t keypair_ns;
  uint64_t keypair_total_ns;
  struct mceliece_pkgen_profile profile;

  if (argc > 1)
    trials = parse_positive(argv[1], "trials");
  if (argc > 2)
    iterations = parse_positive(argv[2], "iterations");
  if (argc > 3)
    warmups = parse_positive(argv[3], "warmups");
  if (argc > 4)
    csv_path = argv[4];
  if (argc > 5) {
    fprintf(stderr,
        "usage: %s [trials] [iterations] [warmups] [csv-path]\n", argv[0]);
    return 2;
  }

  pk = malloc(mceliece348864_PUBLICKEYBYTES);
  sk = malloc(mceliece348864_SECRETKEYBYTES);
  ct = malloc(mceliece348864_CIPHERTEXTBYTES);
  shared_enc = malloc(mceliece348864_BYTES);
  shared_dec = malloc(mceliece348864_BYTES);
  if (pk == NULL || sk == NULL || ct == NULL || shared_enc == NULL ||
      shared_dec == NULL) {
    fprintf(stderr, "allocation failed\n");
    return 2;
  }

  for (iteration = 0; iteration < warmups; iteration++) {
    if (kem_roundtrip(pk, sk, ct, shared_enc, shared_dec, &keypair_ns) != 0) {
      fprintf(stderr, "warmup KEM round-trip failed\n");
      return 1;
    }
  }

  csv = fopen(csv_path, "w");
  if (csv == NULL) {
    perror(csv_path);
    return 2;
  }

  fprintf(csv,
      "trial,iterations,pkgen_calls,successes,duplicate_failures,"
      "pivot_failures,keypair_total_ms,pkgen_total_ms,success_pkgen_ms,"
      "failure_pkgen_ms,phase,success_phase_ms,success_share_pct,"
      "all_phase_ms,all_share_pct\n");

  printf("Classic McEliece 348864 vec pk_gen internal profile\n");
  printf("trials=%d iterations/trial=%d warmups=%d\n\n",
      trials, iterations, warmups);

  for (trial = 1; trial <= trials; trial++) {
    mceliece348864_vec_pkgen_profile_reset();
    keypair_total_ns = 0;

    for (iteration = 0; iteration < iterations; iteration++) {
      if (kem_roundtrip(pk, sk, ct, shared_enc, shared_dec, &keypair_ns) != 0) {
        fprintf(stderr, "trial %d iteration %d KEM round-trip failed\n",
            trial, iteration + 1);
        return 1;
      }
      keypair_total_ns += keypair_ns;
    }

    mceliece348864_vec_pkgen_profile_snapshot(&profile);
    if (profile.calls == 0 || profile.successes != (uint64_t) iterations) {
      fprintf(stderr,
          "profiler was not reached or success count is wrong: calls=%" PRIu64
          " successes=%" PRIu64 "\n",
          profile.calls, profile.successes);
      return 1;
    }

    printf("trial %d: keypair %.3f ms/op, pk_gen %.3f ms/success, "
           "calls=%" PRIu64 " (pivot retry=%" PRIu64
           ", duplicate retry=%" PRIu64 ")\n",
        trial,
        (double) keypair_total_ns / 1000000.0 / iterations,
        (double) profile.success_total_ns / 1000000.0 / profile.successes,
        profile.calls, profile.pivot_failures, profile.duplicate_failures);

    for (phase = 0; phase < MCELIECE_PKGEN_PHASE_COUNT; phase++) {
      double success_share = profile.success_total_ns == 0 ? 0.0 :
          100.0 * (double) profile.success_phase_ns[phase] /
              (double) profile.success_total_ns;
      double all_share = profile.total_ns == 0 ? 0.0 :
          100.0 * (double) profile.phase_ns[phase] /
              (double) profile.total_ns;

      fprintf(csv,
          "%d,%d,%" PRIu64 ",%" PRIu64 ",%" PRIu64 ",%" PRIu64
          ",%.6f,%.6f,%.6f,%.6f,%s,%.6f,%.6f,%.6f,%.6f\n",
          trial, iterations, profile.calls, profile.successes,
          profile.duplicate_failures, profile.pivot_failures,
          (double) keypair_total_ns / 1000000.0,
          (double) profile.total_ns / 1000000.0,
          (double) profile.success_total_ns / 1000000.0,
          (double) profile.failure_total_ns / 1000000.0,
          mceliece348864_vec_pkgen_phase_names[phase],
          (double) profile.success_phase_ns[phase] / 1000000.0,
          success_share,
          (double) profile.phase_ns[phase] / 1000000.0,
          all_share);
    }
  }

  if (fclose(csv) != 0) {
    perror(csv_path);
    return 2;
  }

  printf("\ncorrectness: all %d KEM enc/dec round-trips passed\n",
      warmups + trials * iterations);
  printf("csv: %s\n", csv_path);

  free(shared_dec);
  free(shared_enc);
  free(ct);
  free(sk);
  free(pk);
  return 0;
}
