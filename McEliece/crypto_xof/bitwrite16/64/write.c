// 20250428 djb: more cryptoint usage
// 20240504 djb

#include "crypto_int64.h"
#include "crypto_uint64.h"
#include "crypto_uint16.h"
#include "crypto_xof.h"

#define equal_mask crypto_uint64_equal_mask

static void atmost8192(
  unsigned char *h,long long hlen,
  const unsigned char *m,long long mlen
)
{
  long long i;
  long long words = hlen>>3;
  crypto_uint64 hlast = 0;

  for (i = 0;i < 8*words;++i) h[i] = 0;

  while (mlen >= 2) {
    crypto_uint16 pos = crypto_uint16_load(m);
    crypto_uint64 word64 = crypto_uint64_shlmod(1,pos);
    for (i = 0;i < words;++i) {
      crypto_uint64 hi = crypto_uint64_load(h+8*i);
      hi |= word64 & equal_mask(i,pos>>6);
      crypto_uint64_store(h+8*i,hi);
    }
    hlast |= word64 & equal_mask(words,pos>>6);

    m += 2;
    mlen -= 2;
  }

  for (i = 8*words;i < hlen;++i) {
    h[i] = hlast;
    hlast >>= 8;
  }
}

void crypto_xof(
  unsigned char *h,long long hlen,
  const unsigned char *m,long long mlen
)
{
  while (hlen > 8192) {
    atmost8192(h,8192,m,mlen);
    h += 8192;
    hlen -= 8192;
  }
  if (hlen > 0)
    atmost8192(h,hlen,m,mlen);
}
