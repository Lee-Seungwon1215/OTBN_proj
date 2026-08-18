#ifndef MCELIECE_PK_GEN_PROFILE_H
#define MCELIECE_PK_GEN_PROFILE_H

#include <stdint.h>

enum mceliece_pkgen_phase {
  MCELIECE_PKGEN_INVERSE_EVAL = 0,
  MCELIECE_PKGEN_PERMUTATION_SORT,
  MCELIECE_PKGEN_LEFT_MATRIX_BUILD,
  MCELIECE_PKGEN_OPS_INIT,
  MCELIECE_PKGEN_PIVOT_SEARCH,
  MCELIECE_PKGEN_FORWARD_ELIMINATION,
  MCELIECE_PKGEN_BACKWARD_ELIMINATION,
  MCELIECE_PKGEN_RIGHT_MATRIX_BUILD,
  MCELIECE_PKGEN_APPLY_LINEAR_MAP,
  MCELIECE_PKGEN_SERIALIZE,
  MCELIECE_PKGEN_PHASE_COUNT
};

struct mceliece_pkgen_profile {
  uint64_t calls;
  uint64_t successes;
  uint64_t duplicate_failures;
  uint64_t pivot_failures;

  uint64_t total_ns;
  uint64_t success_total_ns;
  uint64_t failure_total_ns;

  uint64_t phase_ns[MCELIECE_PKGEN_PHASE_COUNT];
  uint64_t success_phase_ns[MCELIECE_PKGEN_PHASE_COUNT];
  uint64_t failure_phase_ns[MCELIECE_PKGEN_PHASE_COUNT];
};

extern const char *const
mceliece348864_vec_pkgen_phase_names[MCELIECE_PKGEN_PHASE_COUNT];

void mceliece348864_vec_pkgen_profile_reset(void);
void mceliece348864_vec_pkgen_profile_snapshot(
    struct mceliece_pkgen_profile *out);

#endif
