// 20240809 djb: split out of gf.h

// linker define gf_mul2

#include "gf.h"
#include "crypto_int64.h"

/* 2 field multiplications */
uint64_t gf_mul2(gf a, gf b0, gf b1)
{
	int i;

	uint64_t tmp=0;
	uint64_t t0;
	uint64_t t1;
	uint64_t t;

	t0 = a;
	t1 = b1;
	t1 = (t1 << 32) | b0;

	for (i = 0; i < GFBITS; i++)
	{
		tmp ^= t1 & crypto_int64_bottombit_mask(t0);
		t1 <<= 1;
		t0 >>= 1;
	}

	//

	t = tmp & 0x01FF000001FF0000;
	tmp ^= (t >> 9) ^ (t >> 10) ^ (t >> 12) ^ (t >> 13);

	t = tmp & 0x0000E0000000E000;
	tmp ^= (t >> 9) ^ (t >> 10) ^ (t >> 12) ^ (t >> 13);

	return tmp & 0x00001FFF00001FFF;
}

