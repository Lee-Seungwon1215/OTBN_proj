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

int operation_dec(
       unsigned char *key,
       const unsigned char *c,
       const unsigned char *sk
)
{
	int i;

	unsigned char fail = 0;

	unsigned char m;

	unsigned char conf[32];
	unsigned char two_e[ 1 + SYS_N/8 ] = {2};
	unsigned char *e = two_e + 1;
	unsigned char preimage[ 1 + SYS_N/8 + (SYND_BYTES + 32) ];
	unsigned char *x = preimage;
	const unsigned char *s = sk + 40 + IRR_BYTES + COND_BYTES;

	//

	fail = decrypt(e, sk + 40, c);

	crypto_hash_32b(conf, two_e, sizeof(two_e)); 

	for (i = 0; i < 32; i++) 
		fail |= conf[i] ^ c[SYND_BYTES + i];

	m = crypto_uint8_zero_mask(fail);

	*x++ = crypto_uint8_bottombit_01(m);
	for (i = 0; i < SYS_N/8; i++) 
		*x++ = (~m & s[i]) | (m & e[i]);

	for (i = 0; i < SYND_BYTES + 32; i++) 
		*x++ = c[i];

	crypto_hash_32b(key, preimage, sizeof(preimage)); 

	return 0;
}

