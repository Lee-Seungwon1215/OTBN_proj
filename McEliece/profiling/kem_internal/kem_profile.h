#ifndef MCELIECE_KEM_INTERNAL_PROFILE_H
#define MCELIECE_KEM_INTERNAL_PROFILE_H

#include <stdint.h>

enum mceliece_kem_profile_stage {
  MCELIECE_KEM_ENCAP = 0,
  MCELIECE_KEM_DECAP,
  MCELIECE_KEM_STAGE_COUNT
};

enum mceliece_kem_profile_region {
  MCELIECE_ENCAP_ERROR_RNG_FILTER = 0,
  MCELIECE_ENCAP_ERROR_SORT_CHECK,
  MCELIECE_ENCAP_ERROR_MATERIALIZE,
  MCELIECE_ENCAP_SYNDROME,
  MCELIECE_ENCAP_PREIMAGE_COPY,
  MCELIECE_ENCAP_SHAKE256,
  MCELIECE_DECAP_PREPROCESS,
  MCELIECE_DECAP_BENES_INVERSE,
  MCELIECE_DECAP_SCALING_FFT,
  MCELIECE_DECAP_SCALING_BATCH_INVERSE,
  MCELIECE_DECAP_SCALING_APPLY,
  MCELIECE_DECAP_SYNDROME_FFT_TR,
  MCELIECE_DECAP_BERLEKAMP_MASSEY,
  MCELIECE_DECAP_LOCATOR_FFT,
  MCELIECE_DECAP_ROOT_EXTRACT,
  MCELIECE_DECAP_SCALING_INVERSE_APPLY,
  MCELIECE_DECAP_REENCRYPT_FFT_TR,
  MCELIECE_DECAP_SYNDROME_COMPARE,
  MCELIECE_DECAP_BENES_FORWARD,
  MCELIECE_DECAP_POSTPROCESS,
  MCELIECE_DECAP_WEIGHT_CHECK,
  MCELIECE_DECAP_PREIMAGE_SELECT,
  MCELIECE_DECAP_SHAKE256,
  MCELIECE_KEM_REGION_COUNT
};

struct mceliece_kem_profile {
  uint64_t stage_calls[MCELIECE_KEM_STAGE_COUNT];
  uint64_t stage_ns[MCELIECE_KEM_STAGE_COUNT];
  uint64_t region_calls[MCELIECE_KEM_REGION_COUNT];
  uint64_t region_ns[MCELIECE_KEM_REGION_COUNT];
};

extern const char *const
mceliece348864_kem_stage_names[MCELIECE_KEM_STAGE_COUNT];
extern const char *const
mceliece348864_kem_region_names[MCELIECE_KEM_REGION_COUNT];

void mceliece348864_kem_profile_reset(void);
void mceliece348864_kem_profile_stage_begin(
    enum mceliece_kem_profile_stage stage);
void mceliece348864_kem_profile_stage_end(
    enum mceliece_kem_profile_stage stage);
void mceliece348864_kem_profile_region_begin(
    enum mceliece_kem_profile_region region);
void mceliece348864_kem_profile_region_end(
    enum mceliece_kem_profile_region region);
void mceliece348864_kem_profile_snapshot(struct mceliece_kem_profile *out);

#endif
