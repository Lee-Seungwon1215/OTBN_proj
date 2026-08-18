/*
  This file is for functions for field arithmetic
*/
// 20240810 djb: even more cryptoint usage
// 20240809 djb: restructuring
// 20240805 djb: more cryptoint usage
// 20221231 djb: const for GF_mul
// 20221230 djb: add linker line

// linker define gf_iszero gf_inv
// linker use gf_mul

#include "gf.h"

#include "crypto_int32.h"

/* check if a == 0 */
gf gf_iszero(gf a)
{
	return crypto_int32_zero_mask(a) & GFMASK;
}

/* input: field element in */
/* return: in^2 */
static gf gf_sq(gf in)
{
	const uint32_t B[] = {0x55555555, 0x33333333, 0x0F0F0F0F, 0x00FF00FF};

	uint32_t x = in;
	uint32_t t;

	x = (x | crypto_int32_shlmod(x,8)) & B[3];
	x = (x | crypto_int32_shlmod(x,4)) & B[2];
	x = (x | crypto_int32_shlmod(x,2)) & B[1];
	x = (x | crypto_int32_shlmod(x,1)) & B[0];

	t = x & 0x7FC000;
	x ^= t >> 9;
	x ^= t >> 12;

	t = x & 0x3000;
	x ^= t >> 9;
	x ^= t >> 12;

	return x & GFMASK;
}

gf gf_inv(gf in)
{
	gf tmp_11;
	gf tmp_1111;

	gf out = in;

	out = gf_sq(out);
	tmp_11 = gf_mul(out, in); // 11

	out = gf_sq(tmp_11);
	out = gf_sq(out);
	tmp_1111 = gf_mul(out, tmp_11); // 1111

	out = gf_sq(tmp_1111);
	out = gf_sq(out);
	out = gf_sq(out);
	out = gf_sq(out);
	out = gf_mul(out, tmp_1111); // 11111111

	out = gf_sq(out);
	out = gf_sq(out);
	out = gf_mul(out, tmp_11); // 1111111111

	out = gf_sq(out);
	out = gf_mul(out, in); // 11111111111

	return gf_sq(out); // 111111111110
}

