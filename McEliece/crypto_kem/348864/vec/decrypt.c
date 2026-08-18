/*
  This file is for Niederreiter decryption
*/
// 20240805 djb: more cryptoint usage
// 20240503 djb: remove #ifdef KAT ... #endif
// 20221230 djb: add linker lines

// linker define decrypt
// linker use benes bm fft fft_tr
// linker use vec_mul vec_sq vec_inv

#include "decrypt.h"

#include "params.h"
#include "fft_tr.h"
#include "benes.h"
#include "util.h"
#include "fft.h"
#include "vec.h"
#include "bm.h"

#include "crypto_int16.h"
#include "crypto_int8.h"
#include "crypto_int64.h"

#ifdef MCELIECE_KEM_PROFILE
#include <kem_profile.h>
#define KEM_REGION_BEGIN(region) \
	mceliece348864_kem_profile_region_begin((region))
#define KEM_REGION_END(region) \
	mceliece348864_kem_profile_region_end((region))
#else
#define KEM_REGION_BEGIN(region) do { } while (0)
#define KEM_REGION_END(region) do { } while (0)
#endif

static void scaling(vec out[][GFBITS], vec inv[][GFBITS], const unsigned char *sk, vec *recv)
{
	int i, j;
	
	vec irr_int[ GFBITS ];
	vec eval[64][ GFBITS ];
	vec tmp[ GFBITS ];

	//
	KEM_REGION_BEGIN(MCELIECE_DECAP_SCALING_FFT);

	irr_load(irr_int, sk);

	fft(eval, irr_int);
	KEM_REGION_END(MCELIECE_DECAP_SCALING_FFT);

	KEM_REGION_BEGIN(MCELIECE_DECAP_SCALING_BATCH_INVERSE);
	for (i = 0; i < 64; i++)
		vec_sq(eval[i], eval[i]);

	vec_copy(inv[0], eval[0]);

	for (i = 1; i < 64; i++)
		vec_mul(inv[i], inv[i-1], eval[i]);

	vec_inv(tmp, inv[63]);

	for (i = 62; i >= 0; i--)
	{
		vec_mul(inv[i+1], tmp, inv[i]);
		vec_mul(tmp, tmp, eval[i+1]);
	}

	vec_copy(inv[0], tmp);
	KEM_REGION_END(MCELIECE_DECAP_SCALING_BATCH_INVERSE);
		
	//
	KEM_REGION_BEGIN(MCELIECE_DECAP_SCALING_APPLY);

	for (i = 0; i < 64; i++)
	for (j = 0; j < GFBITS; j++)
		out[i][j] = inv[i][j] & recv[i];
	KEM_REGION_END(MCELIECE_DECAP_SCALING_APPLY);
}

static void preprocess(vec *recv, const unsigned char *s)
{
	int i;
	unsigned char r[ 512 ];

	for (i = 0; i < SYND_BYTES; i++)    
		r[i] = s[i];

	for (i = SYND_BYTES; i < 512; i++) 
		r[i] = 0;

	for (i = 0; i < 64; i++)
		recv[i] = load8(r + i*8);
}

static void postprocess(unsigned char * e, vec * err)
{
	int i;
	unsigned char error8[ (1 << GFBITS)/8 ];

	for (i = 0; i < 64; i++)
		store8(error8 + i*8, err[i]);

	for (i = 0; i < SYS_N/8; i++)
		e[i] = error8[i];
}

static void scaling_inv(vec out[][GFBITS], vec inv[][GFBITS], vec *recv)
{
	int i, j;

	for (i = 0; i < 64; i++)
	for (j = 0; j < GFBITS; j++)
		out[i][j] = inv[i][j] & recv[i];
}

static int weight_check(unsigned char * e, vec * error)
{
	int i;
	uint16_t w0 = 0;
	uint16_t w1 = 0;
	uint16_t check;

	for (i = 0; i < (1 << GFBITS); i++)
		w0 += crypto_int64_bitmod_01(error[i/64], i);

	for (i = 0; i < SYS_N; i++)
		w1 += crypto_int8_bitmod_01(e[i/8], i);

	check = (w0 ^ SYS_T) | (w1 ^ SYS_T);
	return -crypto_int16_zero_mask(check);
}

static uint16_t synd_cmp(vec s0[][ GFBITS ] , vec s1[][ GFBITS ])
{
	int i, j;
	vec diff = 0;

	for (i = 0; i < 2; i++)
	for (j = 0; j < GFBITS; j++)
		diff |= (s0[i][j] ^ s1[i][j]);
	
	return vec_testz(diff);	
}

/* Niederreiter decryption with the Berlekamp decoder */
/* intput: sk, secret key */
/*         s, ciphertext (syndrome) */
/* output: e, error vector */
/* return: 0 for success; 1 for failure */
int decrypt(unsigned char *e, const unsigned char *sk, const unsigned char *s)
{
	int i; 

	uint16_t check_synd;
	uint16_t check_weight;

	vec inv[ 64 ][ GFBITS ];
	vec scaled[ 64 ][ GFBITS ];
	vec eval[ 64 ][ GFBITS ];

	vec error[ 64 ];

	vec s_priv[ 2 ][ GFBITS ];
	vec s_priv_cmp[ 2 ][ GFBITS ];
	vec locator[ GFBITS ];

	vec recv[ 64 ];
	vec allone;

	// Berlekamp decoder

	KEM_REGION_BEGIN(MCELIECE_DECAP_PREPROCESS);
	preprocess(recv, s);
	KEM_REGION_END(MCELIECE_DECAP_PREPROCESS);

	KEM_REGION_BEGIN(MCELIECE_DECAP_BENES_INVERSE);
	benes(recv, sk + IRR_BYTES, 1);
	KEM_REGION_END(MCELIECE_DECAP_BENES_INVERSE);

	scaling(scaled, inv, sk, recv);

	KEM_REGION_BEGIN(MCELIECE_DECAP_SYNDROME_FFT_TR);
	fft_tr(s_priv, scaled);
	KEM_REGION_END(MCELIECE_DECAP_SYNDROME_FFT_TR);

	KEM_REGION_BEGIN(MCELIECE_DECAP_BERLEKAMP_MASSEY);
	bm(locator, s_priv);
	KEM_REGION_END(MCELIECE_DECAP_BERLEKAMP_MASSEY);

	KEM_REGION_BEGIN(MCELIECE_DECAP_LOCATOR_FFT);
	fft(eval, locator);
	KEM_REGION_END(MCELIECE_DECAP_LOCATOR_FFT);

	// reencryption and weight check

	allone = vec_setbits(1);

	KEM_REGION_BEGIN(MCELIECE_DECAP_ROOT_EXTRACT);
	for (i = 0; i < 64; i++)
	{
		error[i] = vec_or_reduce(eval[i]);
		error[i] ^= allone;
	}
	KEM_REGION_END(MCELIECE_DECAP_ROOT_EXTRACT);

	KEM_REGION_BEGIN(MCELIECE_DECAP_SCALING_INVERSE_APPLY);
	scaling_inv(scaled, inv, error);
	KEM_REGION_END(MCELIECE_DECAP_SCALING_INVERSE_APPLY);

	KEM_REGION_BEGIN(MCELIECE_DECAP_REENCRYPT_FFT_TR);
	fft_tr(s_priv_cmp, scaled);
	KEM_REGION_END(MCELIECE_DECAP_REENCRYPT_FFT_TR);

	KEM_REGION_BEGIN(MCELIECE_DECAP_SYNDROME_COMPARE);
	check_synd = synd_cmp(s_priv, s_priv_cmp);
	KEM_REGION_END(MCELIECE_DECAP_SYNDROME_COMPARE);

	//

	KEM_REGION_BEGIN(MCELIECE_DECAP_BENES_FORWARD);
	benes(error, sk + IRR_BYTES, 0);
	KEM_REGION_END(MCELIECE_DECAP_BENES_FORWARD);

	KEM_REGION_BEGIN(MCELIECE_DECAP_POSTPROCESS);
	postprocess(e, error);
	KEM_REGION_END(MCELIECE_DECAP_POSTPROCESS);

	KEM_REGION_BEGIN(MCELIECE_DECAP_WEIGHT_CHECK);
	check_weight = weight_check(e, error);
	KEM_REGION_END(MCELIECE_DECAP_WEIGHT_CHECK);

	return 1 - (check_synd & check_weight);
}
