// 20230102 djb: rename encrypt() as pke_encrypt()
// 20221230 djb: add linker lines
// 20221230 djb: split out of operations.c

// linker define operation_enc
// linker use pke_encrypt

#include "operations.h"

#include "hash.h"
#include "encrypt.h"
#include "params.h"
#include "util.h"

#include <stdint.h>
#include <string.h>

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

int operation_enc(
       unsigned char *c,
       unsigned char *key,
       const unsigned char *pk
)
{
	unsigned char e[ SYS_N/8 ];
	unsigned char one_ec[ 1 + SYS_N/8 + SYND_BYTES ] = {1};

	//
	KEM_STAGE_BEGIN(MCELIECE_KEM_ENCAP);

	pke_encrypt(c, pk, e);

	KEM_REGION_BEGIN(MCELIECE_ENCAP_PREIMAGE_COPY);
	memcpy(one_ec + 1, e, SYS_N/8);
	memcpy(one_ec + 1 + SYS_N/8, c, SYND_BYTES);
	KEM_REGION_END(MCELIECE_ENCAP_PREIMAGE_COPY);

	KEM_REGION_BEGIN(MCELIECE_ENCAP_SHAKE256);
	crypto_hash_32b(key, one_ec, sizeof(one_ec));
	KEM_REGION_END(MCELIECE_ENCAP_SHAKE256);

	KEM_STAGE_END(MCELIECE_KEM_ENCAP);

	return 0;
}
