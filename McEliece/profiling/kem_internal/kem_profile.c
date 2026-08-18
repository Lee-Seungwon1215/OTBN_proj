#include "kem_profile.h"

#include <string.h>
#include <time.h>

const char *const
mceliece348864_kem_stage_names[MCELIECE_KEM_STAGE_COUNT] = {
  "encapsulation",
  "decapsulation"
};

const char *const
mceliece348864_kem_region_names[MCELIECE_KEM_REGION_COUNT] = {
  "error_rng_filter",
  "error_sort_collision_check",
  "error_vector_materialize",
  "syndrome_public_key_scan",
  "preimage_copy",
  "shake256_shared_secret",
  "preprocess",
  "benes_inverse",
  "scaling_fft",
  "scaling_batch_inverse",
  "scaling_apply",
  "syndrome_fft_tr",
  "berlekamp_massey",
  "locator_fft",
  "root_extract",
  "scaling_inverse_apply",
  "reencrypt_fft_tr",
  "syndrome_compare",
  "benes_forward",
  "postprocess",
  "weight_check",
  "preimage_select",
  "shake256_shared_secret"
};

static struct mceliece_kem_profile profile;
static uint64_t stage_start[MCELIECE_KEM_STAGE_COUNT];
static uint64_t region_start[MCELIECE_KEM_REGION_COUNT];

static uint64_t now_ns(void)
{
  struct timespec ts;

  clock_gettime(CLOCK_MONOTONIC, &ts);
  return (uint64_t) ts.tv_sec * 1000000000ULL + (uint64_t) ts.tv_nsec;
}

void mceliece348864_kem_profile_reset(void)
{
  memset(&profile, 0, sizeof profile);
  memset(stage_start, 0, sizeof stage_start);
  memset(region_start, 0, sizeof region_start);
}

void mceliece348864_kem_profile_stage_begin(
    enum mceliece_kem_profile_stage stage)
{
  stage_start[stage] = now_ns();
}

void mceliece348864_kem_profile_stage_end(
    enum mceliece_kem_profile_stage stage)
{
  profile.stage_ns[stage] += now_ns() - stage_start[stage];
  profile.stage_calls[stage]++;
}

void mceliece348864_kem_profile_region_begin(
    enum mceliece_kem_profile_region region)
{
  region_start[region] = now_ns();
}

void mceliece348864_kem_profile_region_end(
    enum mceliece_kem_profile_region region)
{
  profile.region_ns[region] += now_ns() - region_start[region];
  profile.region_calls[region]++;
}

void mceliece348864_kem_profile_snapshot(struct mceliece_kem_profile *out)
{
  *out = profile;
}
