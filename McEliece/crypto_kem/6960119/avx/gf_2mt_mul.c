// 20240809 djb: split out of gf.c

// linker define GF_mul
// linker use gf_mul

#include "gf.h"
#include "params.h"

/* input: in0, in1 in GF((2^m)^t) */
/* output: out = in0*in1 */
void GF_mul(gf *out, const gf *in0, const gf *in1)
{
	int i, j;

	gf prod[ SYS_T*2-1 ];

	for (i = 0; i < SYS_T*2-1; i++)
		prod[i] = 0;

	for (i = 0; i < SYS_T; i++)
		for (j = 0; j < SYS_T; j++)
			prod[i+j] ^= gf_mul(in0[i], in1[j]);

	//

	for (i = (SYS_T-1)*2; i >= SYS_T; i--)
	{
		prod[i - SYS_T +  8] ^= prod[i];
		prod[i - SYS_T +  0] ^= prod[i];
	}

	for (i = 0; i < SYS_T; i++)
		out[i] = prod[i];
}

