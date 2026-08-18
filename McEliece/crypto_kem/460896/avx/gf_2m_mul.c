// 20240809 djb: split out of gf.c

// linker define gf_mul

#include "gf.h"
#include "crypto_int32.h"

/* field multiplication: returns in0 * in1 */
gf gf_mul(gf in0, gf in1)
{
	int i;

	uint32_t tmp;
	uint32_t t0;
	uint32_t t1;
	uint32_t t;

	t0 = in0;
	t1 = in1;

	tmp = t0 & crypto_int32_bottombit_mask(t1);

	for (i = 1; i < GFBITS; i++) {
		t0 <<= 1;
		t1 >>= 1;
		tmp ^= t0 & crypto_int32_bottombit_mask(t1);
	}

	//

	t = tmp & 0x1FF0000;
	tmp ^= (t >> 9) ^ (t >> 10) ^ (t >> 12) ^ (t >> 13);

	t = tmp & 0x000E000;
	tmp ^= (t >> 9) ^ (t >> 10) ^ (t >> 12) ^ (t >> 13);

	return tmp & GFMASK;
}

