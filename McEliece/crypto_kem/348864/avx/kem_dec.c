// 20260619 djb: more cryptoint usage
// 20240805 djb: more cryptoint usage
// 20221230 djb: add linker lines
// 20221230 djb: split out of operations.c

// linker define operation_dec
// linker use decrypt

#include "operations.h"

#include "hash.h"
#include "decrypt.h"
#include "params.h"
#include "util.h"

#include <stdint.h>
#include <string.h>
#include "crypto_uint8.h"

#ifdef MCELIECE_KEM_PROFILE
#include <kem_profile.h>
#define KEM_STAGE_BEGIN(stage) \
	mceliece348864_kem_profile_stage_begin((stage))
#define KEM_STAGE_END(stage) \
	mceliece348864_kem_profile_stage_end((stage))
#define KEM_REGION_BEGIN(region) \
	mceliece348864_kem_profile_region_begin((region))
#define KEM_REGION_END(region) \
	mceliece348864_kem_profile_region_end((region))
#else
#define KEM_STAGE_BEGIN(stage) do { } while (0)
#define KEM_STAGE_END(stage) do { } while (0)
#define KEM_REGION_BEGIN(region) do { } while (0)
#define KEM_REGION_END(region) do { } while (0)
#endif

int operation_dec(
       unsigned char *key,
       const unsigned char *c,
       const unsigned char *sk
)
{
	int i;

	unsigned char fail = 0;

	unsigned char m;

	unsigned char e[ SYS_N/8 ];
	unsigned char preimage[ 1 + SYS_N/8 + SYND_BYTES ];
	unsigned char *x = preimage;
	const unsigned char *s = sk + 40 + IRR_BYTES + COND_BYTES;

	//
	KEM_STAGE_BEGIN(MCELIECE_KEM_DECAP);

	fail = decrypt(e, sk + 40, c);

	KEM_REGION_BEGIN(MCELIECE_DECAP_PREIMAGE_SELECT);
	m = crypto_uint8_zero_mask(fail);

	*x++ = crypto_uint8_bottombit_01(m);
	for (i = 0; i < SYS_N/8; i++) 
		*x++ = (~m & s[i]) | (m & e[i]);

	for (i = 0; i < SYND_BYTES; i++) 
		*x++ = c[i];
	KEM_REGION_END(MCELIECE_DECAP_PREIMAGE_SELECT);

	KEM_REGION_BEGIN(MCELIECE_DECAP_SHAKE256);
	crypto_hash_32b(key, preimage, sizeof(preimage)); 
	KEM_REGION_END(MCELIECE_DECAP_SHAKE256);

	KEM_STAGE_END(MCELIECE_KEM_DECAP);

	return 0;
}
