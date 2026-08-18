/*
  This file is for implementing the Gao-Mateer FFT, see 
  http://www.math.clemson.edu/~sgao/papers/GM10.pdf

  For the implementation strategy, see
  https://eprint.iacr.org/2017/793.pdf
*/
// 20240805 djb: more use of cryptoint
// 20240508 djb: include vec{128,256}_gf.h
// 20221230 djb: split these arrays into separate .c files
// 20221230 djb: rename consts array as fft_consts
// 20221230 djb: rename s array as fft_scalars_2x
// 20221230 djb: add linker lines

// linker define fft
// linker use vec128_mul_asm
// linker use vec256_maa_asm
// linker use transpose_64x256_sp_asm
// linker use fft_scalars_2x fft_consts fft_powers

#include "fft.h"
#include "fft_scalars_2x.h"
#include "fft_consts.h"
#include "fft_powers.h"

#include "transpose.h"
#include "vec128_gf.h"
#include "vec256_gf.h"

#include <stdint.h>
#include "crypto_int64.h"

/* input: in, polynomial in bitsliced form */
/* output: in, result of applying the radix conversions on in */
static void radix_conversions(vec128 *in)
{
	int i, j, k;
	vec128 t;
	uint64_t v0, v1;

	const vec128 mask[5][2] = 
	{
		{vec128_set2x(0x8888888888888888, 0x8888888888888888),
		 vec128_set2x(0x4444444444444444, 0x4444444444444444)},
		{vec128_set2x(0xC0C0C0C0C0C0C0C0, 0xC0C0C0C0C0C0C0C0),
		 vec128_set2x(0x3030303030303030, 0x3030303030303030)},
		{vec128_set2x(0xF000F000F000F000, 0xF000F000F000F000),
		 vec128_set2x(0x0F000F000F000F00, 0x0F000F000F000F00)},
		{vec128_set2x(0xFF000000FF000000, 0xFF000000FF000000),
		 vec128_set2x(0x00FF000000FF0000, 0x00FF000000FF0000)},
		{vec128_set2x(0xFFFF000000000000, 0xFFFF000000000000),
		 vec128_set2x(0x0000FFFF00000000, 0x0000FFFF00000000)}
	};

	//

	for (j = 0; j <= 5; j++)
	{
		for (i = 0; i < GFBITS; i++)
		{
			v1 = vec128_extract(in[i], 1); 
			v1 ^= v1 >> 32;
			v0 = vec128_extract(in[i], 0); 
			v0 ^= v1 << 32;
			in[i] = vec128_set2x(v0, v1);
		}

		for (i = 0; i < GFBITS; i++)
		for (k = 4; k >= j; k--)
		{
			t = vec128_and(in[i], mask[k][0]);
			t = vec128_srl_2x(t, 1 << k);
			in[i] = vec128_xor(in[i], t);

			t = vec128_and(in[i], mask[k][1]);
			t = vec128_srl_2x(t, 1 << k);
			in[i] = vec128_xor(in[i], t);
		}

		if (j < 5)
			vec128_mul(in, in, fft_scalars_2x[j]); // scaling
	}
}

/* input: in, result of applying the radix conversions to the input polynomial */
/* output: out, evaluation results (by applying the FFT butterflies) */
static void butterflies(vec256 out[][ GFBITS ], vec128 *in)
{
	int i, j, k, s, b;

	vec128 tmp[ GFBITS ];
	vec256 tmp0[ GFBITS ];
	vec256 tmp1[ GFBITS ];
	vec128 t[ GFBITS ];

	union {
		vec128 v[8][  GFBITS+1    ];
		vec256 V[8][ (GFBITS+1)/2 ];
	} pre;

	union {
		vec128 v[64][ 2 ];
		vec256 V[64];
	} buf;

	uint64_t v0, v1;

	uint64_t consts_ptr = 2;

	const unsigned char reversal[64] = 
	{ 
	  0, 32, 16, 48,  8, 40, 24, 56, 
	  4, 36, 20, 52, 12, 44, 28, 60, 
	  2, 34, 18, 50, 10, 42, 26, 58, 
	  6, 38, 22, 54, 14, 46, 30, 62, 
	  1, 33, 17, 49,  9, 41, 25, 57, 
	  5, 37, 21, 53, 13, 45, 29, 61, 
	  3, 35, 19, 51, 11, 43, 27, 59, 
	  7, 39, 23, 55, 15, 47, 31, 63
	};

	const uint16_t beta[8] = {2522, 7827, 7801, 8035, 6897, 8167, 3476, 0};

	// boradcast

	for (j = 0; j < GFBITS; j++)
		t[j] = vec128_unpack_high(in[j], in[j]);

	for (i = 0; i < 8; i+=2)
	{
		for (j = 0; j < GFBITS; j++)
		{
			v0 = crypto_int64_bitmod_mask(beta[i+0], j);
			v1 = crypto_int64_bitmod_mask(beta[i+1], j);

			tmp[j] = vec128_set2x(v0, v1);
		}

		vec128_mul(tmp, t, tmp);

		for (j = 0; j < GFBITS; j++)
		{
			pre.v[i+0][j] = vec128_unpack_low(tmp[j], tmp[j]);
			pre.v[i+1][j] = vec128_unpack_high(tmp[j], tmp[j]);
		}
	}

	for (i = 0; i < GFBITS; i+=2)
	{
		if (i != GFBITS-1)
		buf.v[0][1] = vec128_unpack_low(in[i+1], in[i+1] ^ pre.v[6][i+1]);
		buf.v[0][0] = vec128_unpack_low(in[i+0], in[i+0] ^ pre.v[6][i+0]);

#define XOR vec256_xor

		buf.V[1] = XOR(buf.V[0], pre.V[0][i/2]);    buf.V[16] = XOR(buf.V[0], pre.V[4][i/2]);
		buf.V[3] = XOR(buf.V[1], pre.V[1][i/2]);    buf.V[48] = XOR(buf.V[16], pre.V[5][i/2]);
                                           	buf.V[49] = XOR(buf.V[48], pre.V[0][i/2]);
		buf.V[2] = XOR(buf.V[0], pre.V[1][i/2]);    buf.V[51] = XOR(buf.V[49], pre.V[1][i/2]);
		buf.V[6] = XOR(buf.V[2], pre.V[2][i/2]);    buf.V[50] = XOR(buf.V[51], pre.V[0][i/2]);
		buf.V[7] = XOR(buf.V[6], pre.V[0][i/2]);    buf.V[54] = XOR(buf.V[50], pre.V[2][i/2]);
		buf.V[5] = XOR(buf.V[7], pre.V[1][i/2]);    buf.V[55] = XOR(buf.V[54], pre.V[0][i/2]);
                                            buf.V[53] = XOR(buf.V[55], pre.V[1][i/2]);
		buf.V[4] = XOR(buf.V[0], pre.V[2][i/2]);    buf.V[52] = XOR(buf.V[53], pre.V[0][i/2]);
		buf.V[12] = XOR(buf.V[4], pre.V[3][i/2]);   buf.V[60] = XOR(buf.V[52], pre.V[3][i/2]);
		buf.V[13] = XOR(buf.V[12], pre.V[0][i/2]);  buf.V[61] = XOR(buf.V[60], pre.V[0][i/2]);
		buf.V[15] = XOR(buf.V[13], pre.V[1][i/2]);  buf.V[63] = XOR(buf.V[61], pre.V[1][i/2]);
		buf.V[14] = XOR(buf.V[15], pre.V[0][i/2]);  buf.V[62] = XOR(buf.V[63], pre.V[0][i/2]);
		buf.V[10] = XOR(buf.V[14], pre.V[2][i/2]);  buf.V[58] = XOR(buf.V[62], pre.V[2][i/2]);
		buf.V[11] = XOR(buf.V[10], pre.V[0][i/2]);  buf.V[59] = XOR(buf.V[58], pre.V[0][i/2]);
		buf.V[9] = XOR(buf.V[11], pre.V[1][i/2]);   buf.V[57] = XOR(buf.V[59], pre.V[1][i/2]);
                                            buf.V[56] = XOR(buf.V[57], pre.V[0][i/2]);
		buf.V[8] = XOR(buf.V[0], pre.V[3][i/2]);    buf.V[40] = XOR(buf.V[56], pre.V[4][i/2]);
		buf.V[24] = XOR(buf.V[8], pre.V[4][i/2]);   buf.V[41] = XOR(buf.V[40], pre.V[0][i/2]);
		buf.V[25] = XOR(buf.V[24], pre.V[0][i/2]);  buf.V[43] = XOR(buf.V[41], pre.V[1][i/2]);
		buf.V[27] = XOR(buf.V[25], pre.V[1][i/2]);  buf.V[42] = XOR(buf.V[43], pre.V[0][i/2]);
		buf.V[26] = XOR(buf.V[27], pre.V[0][i/2]);  buf.V[46] = XOR(buf.V[42], pre.V[2][i/2]);
		buf.V[30] = XOR(buf.V[26], pre.V[2][i/2]);  buf.V[47] = XOR(buf.V[46], pre.V[0][i/2]);
		buf.V[31] = XOR(buf.V[30], pre.V[0][i/2]);  buf.V[45] = XOR(buf.V[47], pre.V[1][i/2]);
		buf.V[29] = XOR(buf.V[31], pre.V[1][i/2]);  buf.V[44] = XOR(buf.V[45], pre.V[0][i/2]);
		buf.V[28] = XOR(buf.V[29], pre.V[0][i/2]);  buf.V[36] = XOR(buf.V[44], pre.V[3][i/2]);
		buf.V[20] = XOR(buf.V[28], pre.V[3][i/2]);  buf.V[37] = XOR(buf.V[36], pre.V[0][i/2]);
		buf.V[21] = XOR(buf.V[20], pre.V[0][i/2]);  buf.V[39] = XOR(buf.V[37], pre.V[1][i/2]);
		buf.V[23] = XOR(buf.V[21], pre.V[1][i/2]);  buf.V[38] = XOR(buf.V[39], pre.V[0][i/2]);
		buf.V[22] = XOR(buf.V[23], pre.V[0][i/2]);  buf.V[34] = XOR(buf.V[38], pre.V[2][i/2]);
		buf.V[18] = XOR(buf.V[22], pre.V[2][i/2]);  buf.V[35] = XOR(buf.V[34], pre.V[0][i/2]);
		buf.V[19] = XOR(buf.V[18], pre.V[0][i/2]);  buf.V[33] = XOR(buf.V[35], pre.V[1][i/2]);
		buf.V[17] = XOR(buf.V[19], pre.V[1][i/2]);  buf.V[32] = XOR(buf.V[33], pre.V[0][i/2]);

#undef XOR

		// transpose

		transpose_64x256_sp(buf.V);
	
		for (j = 0; j < 32; j++)
		{
			if (i != GFBITS-1)
			out[j][i+1] = vec256_unpack_high(buf.V[ reversal[2*j+0] ], buf.V[ reversal[2*j+1] ]);
			out[j][i+0] = vec256_unpack_low (buf.V[ reversal[2*j+0] ], buf.V[ reversal[2*j+1] ]);
		}
	}

	// butterflies

	for (k = 0; k < 32; k+=2)
	{
		for (b = 0; b < GFBITS; b++) tmp0[b] = vec256_unpack_low (out[k][b], out[k+1][b]);
		for (b = 0; b < GFBITS; b++) tmp1[b] = vec256_unpack_high (out[k][b], out[k+1][b]); 

		vec256_maa_asm(tmp0, tmp1, fft_consts[1]);

		for (b = 0; b < GFBITS; b++) out[k][b] = vec256_unpack_low (tmp0[b], tmp1[b]);
		for (b = 0; b < GFBITS; b++) out[k+1][b] = vec256_unpack_high (tmp0[b], tmp1[b]);
	}

	for (i = 0; i <= 4; i++)
	{
		s = 1 << i;

		for (j = 0; j < 32; j += 2*s)
		for (k = j; k < j+s; k++)
		{
			vec256_maa_asm(out[k], out[k+s], fft_consts[ consts_ptr + (k-j) ]);
		}

		consts_ptr += (1 << i);
	}

	// adding the part contributed by x^128

	for (i = 0; i <     32; i++)
	for (b = 0; b < GFBITS; b++) 
		out[i][b] = vec256_xor(out[i][b], fft_powers[i][b]);
}

/* input: in, polynomial in bitsliced form */
/* output: out, bitsliced results of evaluating in all the field elements */
void fft(vec256 out[][GFBITS], vec128 *in)
{
	radix_conversions(in);
	butterflies(out, in);
}

