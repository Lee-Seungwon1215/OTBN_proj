/*
  This file is for functions for field arithmetic
*/
// 20240809 djb: merge this file across sizes
// 20240809 djb: whittle down to declarations of gf_{iszero,mul,mul2,inv} and GF_mul
// 20221231 djb: const for GF_mul

#ifndef GF_H
#define GF_H
#define gf_inv CRYPTO_NAMESPACE(gf_inv)
#define gf_iszero CRYPTO_NAMESPACE(gf_iszero)
#define gf_mul2 CRYPTO_NAMESPACE(gf_mul2)
#define gf_mul CRYPTO_NAMESPACE(gf_mul)
#define GF_mul CRYPTO_NAMESPACE(GF_mul)

#include "gf_params.h"

#include <stdint.h>

typedef uint16_t gf;

gf gf_iszero(gf);
gf gf_mul(gf, gf);
uint64_t gf_mul2(gf, gf, gf);
gf gf_inv(gf);

void GF_mul(gf *, const gf *, const gf *);

#endif

