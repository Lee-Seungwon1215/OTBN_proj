/*
  This file is for public-key generation
*/
// 20240805 djb: more use of cryptoint
// 20240715 djb: more use of crypto_*_mask
// 20240508 djb: switch to crypto_sort_int64
// 20221231 djb: more 0 initialization to clarify data flow; tnx thom wiggers
// 20221230 djb: add linker lines

// linker define pk_gen
// linker use fft vec_inv vec_mul

#include "pk_gen.h"

#include "controlbits.h"
#include "crypto_sort_int64.h"
#include "params.h"
#include "benes.h"
#include "util.h"
#include "fft.h"
#include "vec.h"
#include "crypto_declassify.h"
#include "crypto_uint64.h"
#include "crypto_int64.h"

static crypto_uint64 uint64_is_equal_declassify(uint64_t t,uint64_t u)
{
  crypto_uint64 mask = crypto_uint64_equal_mask(t,u);
  crypto_declassify(&mask,sizeof mask);
  return mask;
}

static crypto_uint64 uint64_is_zero_declassify(uint64_t t)
{
  crypto_uint64 mask = crypto_uint64_zero_mask(t);
  crypto_declassify(&mask,sizeof mask);
  return mask;
}

#include <stdint.h>

#ifdef MCELIECE_PKGEN_PROFILE
#include <pk_gen_profile.h>

#include <string.h>
#include <time.h>

const char *const
mceliece348864_vec_pkgen_phase_names[MCELIECE_PKGEN_PHASE_COUNT] = {
	"inverse_eval",
	"permutation_sort",
	"left_matrix_build",
	"ops_init",
	"pivot_search",
	"forward_elimination",
	"backward_elimination",
	"right_matrix_build",
	"apply_linear_map",
	"serialize"
};

static struct mceliece_pkgen_profile pkgen_profile;

static uint64_t pkgen_profile_now_ns(void)
{
	struct timespec ts;

	clock_gettime(CLOCK_MONOTONIC, &ts);
	return (uint64_t) ts.tv_sec * 1000000000ULL + (uint64_t) ts.tv_nsec;
}

void mceliece348864_vec_pkgen_profile_reset(void)
{
	memset(&pkgen_profile, 0, sizeof pkgen_profile);
}

void mceliece348864_vec_pkgen_profile_snapshot(
	struct mceliece_pkgen_profile *out)
{
	*out = pkgen_profile;
}

static void pkgen_profile_finish(
	const uint64_t phases[MCELIECE_PKGEN_PHASE_COUNT],
	uint64_t total_ns,
	int result)
{
	int phase;

	pkgen_profile.calls++;
	pkgen_profile.total_ns += total_ns;

	if (result == 0) {
		pkgen_profile.successes++;
		pkgen_profile.success_total_ns += total_ns;
	} else {
		pkgen_profile.failure_total_ns += total_ns;
		if (result == -1)
			pkgen_profile.duplicate_failures++;
		else
			pkgen_profile.pivot_failures++;
	}

	for (phase = 0; phase < MCELIECE_PKGEN_PHASE_COUNT; phase++) {
		pkgen_profile.phase_ns[phase] += phases[phase];
		if (result == 0)
			pkgen_profile.success_phase_ns[phase] += phases[phase];
		else
			pkgen_profile.failure_phase_ns[phase] += phases[phase];
	}
}
#endif

static void de_bitslicing(uint64_t * out, const vec in[][GFBITS])
{
	int i, j, r;

	for (i = 0; i < (1 << GFBITS); i++)
		out[i] = 0 ;

	for (i = 0; i < 64; i++)
	for (j = GFBITS-1; j >= 0; j--)
	for (r = 0; r < 64; r++) 
	{ 
		out[i*64 + r] <<= 1; 
		out[i*64 + r] |= crypto_int64_bitmod_01(in[i][j], r); 
	}
}

static void to_bitslicing_2x(vec out0[][GFBITS], vec out1[][GFBITS], const uint64_t * in)
{
	int i, j, r;

	for (i = 0; i < 64; i++)
	{
		for (j = 0;j < GFBITS;++j) out0[i][j] = out1[i][j] = 0;

		for (j = GFBITS-1; j >= 0; j--)
		for (r = 63; r >= 0; r--)
		{
			out1[i][j] <<= 1;
			out1[i][j] |= crypto_int64_bitmod_01(in[i*64 + r], j + GFBITS);
		}
        
		for (j = GFBITS-1; j >= 0; j--)
		for (r = 63; r >= 0; r--)
		{
			out0[i][GFBITS-1-j] <<= 1;
			out0[i][GFBITS-1-j] |= crypto_int64_bitmod_01(in[i*64 + r], j);
		}
	}
}

int pk_gen(unsigned char * pk, const unsigned char * irr, uint32_t * perm, int16_t * pi)
{
	const int nblocks_H = (SYS_N + 63) / 64;
	const int nblocks_I = (PK_NROWS + 63) / 64;
	const int block_idx = nblocks_I;

	int i, j, k;
	int row, c;
	
	uint64_t mat[ PK_NROWS ][ nblocks_H ];
	uint64_t ops[ PK_NROWS ][ nblocks_I ];

	uint64_t mask;	

	uint64_t irr_int[ GFBITS ];

	vec consts[64][ GFBITS ];
	vec eval[ 64 ][ GFBITS ];
	vec prod[ 64 ][ GFBITS ];
	vec tmp[ GFBITS ];

	uint64_t list[1 << GFBITS];
	uint64_t one_row[ 64 ];

#ifdef MCELIECE_PKGEN_PROFILE
	uint64_t profile_phases[MCELIECE_PKGEN_PHASE_COUNT] = {0};
	uint64_t profile_total_start = pkgen_profile_now_ns();
	uint64_t profile_phase_start;
#define PROFILE_START() do { profile_phase_start = pkgen_profile_now_ns(); } while (0)
#define PROFILE_STOP(phase) do { \
	profile_phases[(phase)] += pkgen_profile_now_ns() - profile_phase_start; \
} while (0)
#define PROFILE_FINISH(result) do { \
	pkgen_profile_finish(profile_phases, \
		pkgen_profile_now_ns() - profile_total_start, (result)); \
} while (0)
#else
#define PROFILE_START() do { } while (0)
#define PROFILE_STOP(phase) do { } while (0)
#define PROFILE_FINISH(result) do { } while (0)
#endif

	// compute the inverses 

	PROFILE_START();

	irr_load(irr_int, irr);

	fft(eval, irr_int);

	vec_copy(prod[0], eval[0]);

	for (i = 1; i < 64; i++)
		vec_mul(prod[i], prod[i-1], eval[i]);

	vec_inv(tmp, prod[63]);

	for (i = 62; i >= 0; i--)
	{
		vec_mul(prod[i+1], prod[i], tmp);
		vec_mul(tmp, tmp, eval[i+1]);
	}

	vec_copy(prod[0], tmp);
	PROFILE_STOP(MCELIECE_PKGEN_INVERSE_EVAL);

	// fill matrix 

	PROFILE_START();

	de_bitslicing(list, prod);

	for (i = 0; i < (1 << GFBITS); i++)
	{	
		list[i] <<= GFBITS;
		list[i] |= i;	
		list[i] |= ((uint64_t) perm[i]) << 31;
	}

	crypto_sort_int64(list, 1 << GFBITS);

	for (i = 1; i < (1 << GFBITS); i++)
		if (uint64_is_equal_declassify(list[i-1] >> 31,list[i] >> 31))
		{
			PROFILE_STOP(MCELIECE_PKGEN_PERMUTATION_SORT);
			PROFILE_FINISH(-1);
			return -1;
		}

	to_bitslicing_2x(consts, prod, list);

	for (i = 0; i < (1 << GFBITS); i++)
		pi[i] = list[i] & GFMASK;
	PROFILE_STOP(MCELIECE_PKGEN_PERMUTATION_SORT);

	PROFILE_START();

	for (j = 0; j < nblocks_I; j++)
	for (k = 0; k < GFBITS; k++)
		mat[ k ][ j ] = prod[ j ][ k ];

	for (i = 1; i < SYS_T; i++)
	for (j = 0; j < nblocks_I; j++)
	{
		vec_mul(prod[j], prod[j], consts[j]);

		for (k = 0; k < GFBITS; k++)
			mat[ i*GFBITS + k ][ j ] = prod[ j ][ k ];
	}
	PROFILE_STOP(MCELIECE_PKGEN_LEFT_MATRIX_BUILD);

	// gaussian elimination to obtain an upper triangular matrix 
	// and keep track of the operations in ops

	PROFILE_START();

	for (i = 0; i < PK_NROWS; i++)
	for (j = 0; j < nblocks_I; j++)
		ops[ i ][ j ] = 0;

	for (i = 0; i < PK_NROWS; i++)
	{
		ops[ i ][ i / 64 ] = 1;
		ops[ i ][ i / 64 ] <<= (i % 64);
	}
	PROFILE_STOP(MCELIECE_PKGEN_OPS_INIT);

	for (row = 0; row < PK_NROWS; row++)
	{
		i = row >> 6;
		j = row & 63;

		PROFILE_START();

		for (k = row + 1; k < PK_NROWS; k++)
		{
			mask = ~crypto_uint64_bitmod_mask(mat[ row ][ i ], j);

			for (c = 0; c < nblocks_I; c++)
			{
				mat[ row ][ c ] ^= mat[ k ][ c ] & mask;
				ops[ row ][ c ] ^= ops[ k ][ c ] & mask;
			}
		}

		mask = crypto_uint64_bitmod_mask(mat[ row ][ i ], j);
		PROFILE_STOP(MCELIECE_PKGEN_PIVOT_SEARCH);
                if ( uint64_is_zero_declassify(mask) ) // return if not systematic
		{
			PROFILE_FINISH(-2);
			return -1;
		}

		PROFILE_START();
		for (k = row+1; k < PK_NROWS; k++)
		{
			mask = crypto_uint64_bitmod_mask(mat[ k ][ i ], j);

			for (c = 0; c < nblocks_I; c++)
			{
				mat[ k ][ c ] ^= mat[ row ][ c ] & mask;
				ops[ k ][ c ] ^= ops[ row ][ c ] & mask;
			}
		}
		PROFILE_STOP(MCELIECE_PKGEN_FORWARD_ELIMINATION);
	}

	// computing the lineaer map required to obatin the systematic form

	PROFILE_START();

	for (row = PK_NROWS-1; row >= 0; row--)
	for (k = 0; k < row; k++)
	{
		mask = crypto_uint64_bitmod_mask(mat[ k ][ row/64 ], row);

		for (c = 0; c < nblocks_I; c++)
			ops[ k ][ c ] ^= ops[ row ][ c ] & mask;
	}
	PROFILE_STOP(MCELIECE_PKGEN_BACKWARD_ELIMINATION);

	// apply the linear map to the non-systematic part

	PROFILE_START();

	for (j = nblocks_I; j < nblocks_H; j++)
	for (k = 0; k < GFBITS; k++)
		mat[ k ][ j ] = prod[ j ][ k ];

	for (i = 1; i < SYS_T; i++)
	for (j = nblocks_I; j < nblocks_H; j++)
	{
		vec_mul(prod[j], prod[j], consts[j]);

		for (k = 0; k < GFBITS; k++)
			mat[ i*GFBITS + k ][ j ] = prod[ j ][ k ];
	}
	PROFILE_STOP(MCELIECE_PKGEN_RIGHT_MATRIX_BUILD);

	for (row = 0; row < PK_NROWS; row++)
	{
		i = row >> 6;
		j = row & 63;

		PROFILE_START();
		for (k = 0; k < nblocks_H; k++)
			one_row[ k ] = 0;

		for (c = 0; c < PK_NROWS; c++)
		{
			mask = crypto_uint64_bitmod_mask(ops[ row ][ c >> 6 ], c);

			for (k = block_idx; k < nblocks_H; k++){
				one_row[ k ] ^= mat[ c ][ k ] & mask;
			}
		}
		PROFILE_STOP(MCELIECE_PKGEN_APPLY_LINEAR_MAP);

		PROFILE_START();
		for (k = block_idx; k < nblocks_H - 1; k++)
		{
			store8(pk, one_row[k]);
			pk += 8;
		}

                store_i(pk, one_row[k], PK_ROW_BYTES % 8);

		pk += PK_ROW_BYTES % 8;
		PROFILE_STOP(MCELIECE_PKGEN_SERIALIZE);
	}

	//

	PROFILE_FINISH(0);

#undef PROFILE_START
#undef PROFILE_STOP
#undef PROFILE_FINISH
	return 0;
}
