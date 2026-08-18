#include "profile.h"

#if defined(FRODO_PROFILE)

#include <stdint.h>
#include <string.h>
#if defined(__APPLE__)
#include <mach/mach_time.h>
#else
#include <time.h>
#endif

typedef struct {
    uint64_t stage_ticks[FRODO_PROFILE_STAGE_COUNT];
    uint64_t stage_calls[FRODO_PROFILE_STAGE_COUNT];
    uint64_t region_ticks[FRODO_PROFILE_STAGE_COUNT][FRODO_REGION_COUNT];
    uint64_t region_calls[FRODO_PROFILE_STAGE_COUNT][FRODO_REGION_COUNT];
} frodo_profile_data_t;

static frodo_profile_data_t profile_data;
static int current_stage = -1;
static uint64_t stage_start;
static uint64_t region_start[FRODO_REGION_COUNT];

static const char *stage_names[FRODO_PROFILE_STAGE_COUNT] = {
    "keygen", "encaps", "decaps"
};

static const char *region_names[FRODO_REGION_COUNT] = {
    "system_random",
    "seed_a_xof",
    "sample_xof",
    "public_key_hash",
    "derive_xof",
    "shared_secret_xof",
    "a_generation",
    "a_endian",
    "large_matrix_mac",
    "small_matrix_mac",
    "noise_sampling",
    "pack",
    "unpack",
    "small_arithmetic",
    "verify_select",
    "secret_clear"
};

static uint64_t profile_now(void)
{
#if defined(__APPLE__)
    return mach_continuous_time();
#else
    struct timespec now;
    clock_gettime(CLOCK_MONOTONIC_RAW, &now);
    return (uint64_t)now.tv_sec * 1000000000ULL + (uint64_t)now.tv_nsec;
#endif
}

static double ticks_to_ns(uint64_t ticks)
{
#if defined(__APPLE__)
    static mach_timebase_info_data_t timebase;
    if (timebase.denom == 0) {
        mach_timebase_info(&timebase);
    }
    return (double)ticks * (double)timebase.numer / (double)timebase.denom;
#else
    return (double)ticks;
#endif
}

void frodo_profile_reset(void)
{
    memset(&profile_data, 0, sizeof(profile_data));
    memset(region_start, 0, sizeof(region_start));
    current_stage = -1;
    stage_start = 0;
}

void frodo_profile_stage_begin(frodo_profile_stage_t stage)
{
    current_stage = (int)stage;
    stage_start = profile_now();
}

void frodo_profile_stage_end(frodo_profile_stage_t stage)
{
    uint64_t end = profile_now();
    if (current_stage == (int)stage) {
        profile_data.stage_ticks[stage] += end - stage_start;
        profile_data.stage_calls[stage]++;
    }
    current_stage = -1;
}

void frodo_profile_region_begin(frodo_profile_region_t region)
{
    if (current_stage >= 0) {
        region_start[region] = profile_now();
    }
}

void frodo_profile_region_end(frodo_profile_region_t region)
{
    uint64_t end = profile_now();
    if (current_stage >= 0 && region_start[region] != 0) {
        profile_data.region_ticks[current_stage][region] += end - region_start[region];
        profile_data.region_calls[current_stage][region]++;
        region_start[region] = 0;
    }
}

void frodo_profile_write_csv(FILE *stream, const char *implementation, unsigned int trial)
{
    for (int stage = 0; stage < FRODO_PROFILE_STAGE_COUNT; stage++) {
        double stage_ns = ticks_to_ns(profile_data.stage_ticks[stage]);
        fprintf(stream, "%s,%u,%s,total,%llu,%.3f,%.3f\n",
                implementation,
                trial,
                stage_names[stage],
                (unsigned long long)profile_data.stage_calls[stage],
                stage_ns,
                stage_ns);

        for (int region = 0; region < FRODO_REGION_COUNT; region++) {
            double region_ns = ticks_to_ns(profile_data.region_ticks[stage][region]);
            fprintf(stream, "%s,%u,%s,%s,%llu,%.3f,%.3f\n",
                    implementation,
                    trial,
                    stage_names[stage],
                    region_names[region],
                    (unsigned long long)profile_data.region_calls[stage][region],
                    region_ns,
                    stage_ns);
        }
    }
}

#endif
