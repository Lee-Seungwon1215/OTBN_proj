/*
  this file is for functions for field arithmetic
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
#include "crypto_int64.h"

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

	t = x & 0xFF80000;
	x ^= (t >> 9) ^ (t >> 10) ^ (t >> 12) ^ (t >> 13);

	t = x & 0x007E000;
	x ^= (t >> 9) ^ (t >> 10) ^ (t >> 12) ^ (t >> 13);

	return x & GFMASK;
}

/* 2 field squarings */
static gf gf_sq2(gf in)
{
	int i;

	const uint64_t B[] = {0x1111111111111111,
	                      0x0303030303030303,
	                      0x000F000F000F000F,
	                      0x000000FF000000FF};

	const uint64_t M[] = {0x0001FF0000000000,
	                      0x000000FF80000000,
	                      0x000000007FC00000,
	                      0x00000000003FE000};

	uint64_t x = in;
	uint64_t t;

	x = (x | crypto_int64_shlmod(x,24)) & B[3];
	x = (x | crypto_int64_shlmod(x,12)) & B[2];
	x = (x | crypto_int64_shlmod(x,6)) & B[1];
	x = (x | crypto_int64_shlmod(x,3)) & B[0];

	for (i = 0; i < 4; i++)
	{
		t = x & M[i];
		x ^= (t >> 9) ^ (t >> 10) ^ (t >> 12) ^ (t >> 13);
	}

	return x & GFMASK;
}

/* square and multiply */
static gf gf_sqmul(gf in, gf m)
{
	return gf_mul(gf_sq(in), m);
}

/* square twice and multiply */
static gf gf_sq2mul(gf in, gf m)
{
	return gf_mul(gf_sq2(in), m);
}

/* return 1/den */
gf gf_inv(gf den)
{
	gf tmp_11;
	gf tmp_1111;
	gf out;

	tmp_11 = gf_sqmul(den, den); // ^11
	tmp_1111 = gf_sq2mul(tmp_11, tmp_11); // ^1111
	out = gf_sq2(tmp_1111);
	out = gf_sq2mul(out, tmp_1111); // ^11111111
	out = gf_sq2(out);
	out = gf_sq2mul(out, tmp_1111); // ^111111111111

	return gf_sq(out); // ^1111111111110 = ^-1
}

