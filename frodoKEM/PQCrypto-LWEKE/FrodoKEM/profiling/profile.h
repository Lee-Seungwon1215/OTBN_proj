#ifndef FRODO_PROFILE_H
#define FRODO_PROFILE_H

#include <stddef.h>
#include <stdio.h>

typedef enum {
    FRODO_PROFILE_KEYGEN = 0,
    FRODO_PROFILE_ENCAP,
    FRODO_PROFILE_DECAP,
    FRODO_PROFILE_STAGE_COUNT
} frodo_profile_stage_t;

typedef enum {
    FRODO_REGION_RANDOM = 0,
    FRODO_REGION_SEED_A_XOF,
    FRODO_REGION_SAMPLE_XOF,
    FRODO_REGION_PUBLIC_KEY_HASH,
    FRODO_REGION_DERIVE_XOF,
    FRODO_REGION_SHARED_SECRET_XOF,
    FRODO_REGION_A_GENERATION,
    FRODO_REGION_A_ENDIAN,
    FRODO_REGION_LARGE_MATRIX_MAC,
    FRODO_REGION_SMALL_MATRIX_MAC,
    FRODO_REGION_NOISE_SAMPLING,
    FRODO_REGION_PACK,
    FRODO_REGION_UNPACK,
    FRODO_REGION_SMALL_ARITHMETIC,
    FRODO_REGION_VERIFY_SELECT,
    FRODO_REGION_SECRET_CLEAR,
    FRODO_REGION_COUNT
} frodo_profile_region_t;

#if defined(FRODO_PROFILE)
void frodo_profile_reset(void);
void frodo_profile_stage_begin(frodo_profile_stage_t stage);
void frodo_profile_stage_end(frodo_profile_stage_t stage);
void frodo_profile_region_begin(frodo_profile_region_t region);
void frodo_profile_region_end(frodo_profile_region_t region);
void frodo_profile_write_csv(FILE *stream, const char *implementation, unsigned int trial);

#define FRODO_PROFILE_STAGE_BEGIN(stage) frodo_profile_stage_begin((stage))
#define FRODO_PROFILE_STAGE_END(stage) frodo_profile_stage_end((stage))
#define FRODO_PROFILE_REGION_BEGIN(region) frodo_profile_region_begin((region))
#define FRODO_PROFILE_REGION_END(region) frodo_profile_region_end((region))
#else
#define FRODO_PROFILE_STAGE_BEGIN(stage) ((void)0)
#define FRODO_PROFILE_STAGE_END(stage) ((void)0)
#define FRODO_PROFILE_REGION_BEGIN(region) ((void)0)
#define FRODO_PROFILE_REGION_END(region) ((void)0)
#endif

#endif
