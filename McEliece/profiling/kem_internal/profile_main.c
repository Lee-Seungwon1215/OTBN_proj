#include "kem_profile.h"
#include "mceliece.h"

#include <errno.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int parse_positive(const char *text, const char *name)
{
  char *end;
  long value;

  errno = 0;
  value = strtol(text, &end, 10);
  if (errno != 0 || *text == '\0' || *end != '\0' || value <= 0 ||
      value > 10000000) {
    fprintf(stderr, "invalid %s: %s\n", name, text);
    exit(2);
  }
  return (int) value;
}

static enum mceliece_kem_profile_stage region_stage(int region)
{
  return region <= MCELIECE_ENCAP_SHAKE256 ?
      MCELIECE_KEM_ENCAP : MCELIECE_KEM_DECAP;
}

static int roundtrip(
    unsigned char *ct,
    unsigned char *shared_enc,
    unsigned char *shared_dec,
    const unsigned char *pk,
    const unsigned char *sk)
{
  if (mceliece348864_enc(ct, shared_enc, pk) != 0)
    return -1;
  if (mceliece348864_dec(shared_dec, ct, sk) != 0)
    return -2;
  if (memcmp(shared_enc, shared_dec, mceliece348864_BYTES) != 0)
    return -3;
  return 0;
}

int main(int argc, char **argv)
{
  int trials = 9;
  int iterations = 1000;
  int warmups = 100;
  const char *csv_path = "kem_internal_profile.csv";
  unsigned char *pk;
  unsigned char *sk;
  unsigned char *ct;
  unsigned char *shared_enc;
  unsigned char *shared_dec;
  struct mceliece_kem_profile profile;
  FILE *csv;
  int trial;
  int iteration;
  int region;
  int stage;

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

  mceliece348864_keypair(pk, sk);

  for (iteration = 0; iteration < warmups; iteration++) {
    if (roundtrip(ct, shared_enc, shared_dec, pk, sk) != 0) {
      fprintf(stderr, "warmup round-trip failed\n");
      return 1;
    }
  }

  csv = fopen(csv_path, "w");
  if (csv == NULL) {
    perror(csv_path);
    return 2;
  }
  fprintf(csv,
      "trial,iterations,stage,stage_calls,stage_total_ns,region,"
      "region_calls,region_total_ns,stage_share_pct\n");

  printf("Classic McEliece 348864 vec encaps/decaps internal profile\n");
  printf("trials=%d iterations/trial=%d warmups=%d\n\n",
      trials, iterations, warmups);

  for (trial = 1; trial <= trials; trial++) {
    mceliece348864_kem_profile_reset();

    for (iteration = 0; iteration < iterations; iteration++) {
      if (roundtrip(ct, shared_enc, shared_dec, pk, sk) != 0) {
        fprintf(stderr, "trial %d iteration %d round-trip failed\n",
            trial, iteration + 1);
        return 1;
      }
    }

    mceliece348864_kem_profile_snapshot(&profile);
    for (stage = 0; stage < MCELIECE_KEM_STAGE_COUNT; stage++) {
      if (profile.stage_calls[stage] != (uint64_t) iterations) {
        fprintf(stderr,
            "wrong %s count: got %" PRIu64 ", expected %d\n",
            mceliece348864_kem_stage_names[stage],
            profile.stage_calls[stage], iterations);
        return 1;
      }
      printf("trial %d %s: %.6f ms/op\n",
          trial, mceliece348864_kem_stage_names[stage],
          (double) profile.stage_ns[stage] / 1000000.0 /
              profile.stage_calls[stage]);
    }

    for (region = 0; region < MCELIECE_KEM_REGION_COUNT; region++) {
      double share;

      stage = region_stage(region);
      share = profile.stage_ns[stage] == 0 ? 0.0 :
          100.0 * (double) profile.region_ns[region] /
              (double) profile.stage_ns[stage];
      fprintf(csv,
          "%d,%d,%s,%" PRIu64 ",%" PRIu64 ",%s,%" PRIu64
          ",%" PRIu64 ",%.6f\n",
          trial, iterations, mceliece348864_kem_stage_names[stage],
          profile.stage_calls[stage], profile.stage_ns[stage],
          mceliece348864_kem_region_names[region],
          profile.region_calls[region], profile.region_ns[region], share);
    }
  }

  if (fclose(csv) != 0) {
    perror(csv_path);
    return 2;
  }

  printf("\ncorrectness: all %d KEM round-trips passed\n",
      warmups + trials * iterations);
  printf("csv: %s\n", csv_path);

  free(shared_dec);
  free(shared_enc);
  free(ct);
  free(sk);
  free(pk);
  return 0;
}
