/* WARNING: auto-generated (by autogen/test); do not edit */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <time.h>
#include <assert.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/resource.h>
#include "crypto_uint8.h"
#include "crypto_uint32.h"
#include "crypto_uint64.h"
#include "crypto_declassify.h"
#include <mceliece.h> /* -lmceliece */
#include <randombytes.h>

static const char *targeto = 0;
static const char *targetp = 0;
static const char *targeti = 0;
static const char *targetn = 0;
static const char *targetoffset = 0;

static int ok = 1;

#define fail ((ok = 0),printf)

/* ----- valgrind support */

static int valgrind = 0;
static unsigned char valgrind_undefined_byte = 0;
static char *volatile valgrind_pointer = 0;

static char *valgrind_malloc_1(void)
{
  char *x = (char *) malloc(1);
  if (!x) abort();
  *(char **volatile) &valgrind_pointer = x;
  return valgrind_pointer;
}

static void valgrind_init(void)
{
  char *e = getenv("valgrind_multiplier");
  char *x;
  if (!e) return;
  x = valgrind_malloc_1();
  valgrind_undefined_byte = x[0]+1;
  valgrind_undefined_byte *= atoi(e);
  valgrind_undefined_byte ^= x[0]+1;
  free(x);
  valgrind = 1;
}

static void secret(void *xvoid,long long xlen)
{
  unsigned char *x = (unsigned char *) xvoid;
  while (xlen > 0) {
    *x ^= valgrind_undefined_byte;
    ++x;
    --xlen;
  }
}

static void declassify(void *x,long long xlen)
{
  crypto_declassify(x,xlen);
}

/* ----- rng and hash, from supercop/try-anything.c */

typedef crypto_uint8 u8;
typedef crypto_uint32 u32;
typedef crypto_uint64 u64;

#define FOR(i,n) for (i = 0;i < n;++i)

static u32 L32(u32 x,int c) { return (x << c) | ((x&0xffffffff) >> (32 - c)); }

static u32 ld32(const u8 *x)
{
  u32 u = x[3];
  u = (u<<8)|x[2];
  u = (u<<8)|x[1];
  return (u<<8)|x[0];
}

static void st32(u8 *x,u32 u)
{
  int i;
  FOR(i,4) { x[i] = u; u >>= 8; }
}

static const u8 sigma[17] = "expand 32-byte k";

static void core_salsa(u8 *out,const u8 *in,const u8 *k)
{
  u32 w[16],x[16],y[16],t[4];
  int i,j,m;

  FOR(i,4) {
    x[5*i] = ld32(sigma+4*i);
    x[1+i] = ld32(k+4*i);
    x[6+i] = ld32(in+4*i);
    x[11+i] = ld32(k+16+4*i);
  }

  FOR(i,16) y[i] = x[i];

  FOR(i,20) {
    FOR(j,4) {
      FOR(m,4) t[m] = x[(5*j+4*m)%16];
      t[1] ^= L32(t[0]+t[3], 7);
      t[2] ^= L32(t[1]+t[0], 9);
      t[3] ^= L32(t[2]+t[1],13);
      t[0] ^= L32(t[3]+t[2],18);
      FOR(m,4) w[4*j+(j+m)%4] = t[m];
    }
    FOR(m,16) x[m] = w[m];
  }

  FOR(i,16) st32(out + 4 * i,x[i] + y[i]);
}

static void salsa20(u8 *c,u64 b,const u8 *n,const u8 *k)
{
  u8 z[16],x[64];
  u32 u,i;
  if (!b) return;
  FOR(i,16) z[i] = 0;
  FOR(i,8) z[i] = n[i];
  while (b >= 64) {
    core_salsa(x,z,k);
    FOR(i,64) c[i] = x[i];
    u = 1;
    for (i = 8;i < 16;++i) {
      u += (u32) z[i];
      z[i] = u;
      u >>= 8;
    }
    b -= 64;
    c += 64;
  }
  if (b) {
    core_salsa(x,z,k);
    FOR(i,b) c[i] = x[i];
  }
}

static void increment(u8 *n)
{
  if (!++n[0])
    if (!++n[1])
      if (!++n[2])
        if (!++n[3])
          if (!++n[4])
            if (!++n[5])
              if (!++n[6])
                if (!++n[7])
                  ;
}

static unsigned char testvector_n[8];

static void testvector_clear(void)
{
  memset(testvector_n,0,sizeof testvector_n);
}

static void testvector(unsigned char *x,unsigned long long xlen)
{
  const static unsigned char testvector_k[33] = "generate inputs for test vectors";
  salsa20(x,xlen,testvector_n,testvector_k);
  increment(testvector_n);
}

static unsigned long long myrandom(void)
{
  unsigned char x[8];
  unsigned long long result;
  testvector(x,8);
  result = x[7];
  result = (result<<8)|x[6];
  result = (result<<8)|x[5];
  result = (result<<8)|x[4];
  result = (result<<8)|x[3];
  result = (result<<8)|x[2];
  result = (result<<8)|x[1];
  result = (result<<8)|x[0];
  return result;
}

static unsigned char canary_n[8];

static void canary(unsigned char *x,unsigned long long xlen)
{
  const static unsigned char canary_k[33] = "generate pad to catch overwrites";
  salsa20(x,xlen,canary_n,canary_k);
  increment(canary_n);
}

static void double_canary(unsigned char *x2,unsigned char *x,unsigned long long xlen)
{
  if (valgrind) return;
  canary(x - 16,16);
  canary(x + xlen,16);
  memcpy(x2 - 16,x - 16,16);
  memcpy(x2 + xlen,x + xlen,16);
}

static void input_prepare(unsigned char *x2,unsigned char *x,unsigned long long xlen)
{
  testvector(x,xlen);
  if (valgrind) {
    memcpy(x2,x,xlen);
    return;
  }
  canary(x - 16,16);
  canary(x + xlen,16);
  memcpy(x2 - 16,x - 16,xlen + 32);
}

static void input_compare(const unsigned char *x2,const unsigned char *x,unsigned long long xlen,const char *fun)
{
  if (valgrind) return;
  if (memcmp(x2 - 16,x - 16,xlen + 32)) {
    fail("failure: %s overwrites input\n",fun);
  }
}

static void output_prepare(unsigned char *x2,unsigned char *x,unsigned long long xlen)
{
  if (valgrind) {
    memcpy(x2,x,xlen);
    return;
  }
  canary(x - 16,xlen + 32);
  memcpy(x2 - 16,x - 16,xlen + 32);
}

static void output_compare(const unsigned char *x2,const unsigned char *x,unsigned long long xlen,const char *fun)
{
  if (valgrind) return;
  if (memcmp(x2 - 16,x - 16,16)) {
    fail("failure: %s writes before output\n",fun);
  }
  if (memcmp(x2 + xlen,x + xlen,16)) {
    fail("failure: %s writes after output\n",fun);
  }
}

/* ----- knownrandombytes */

static const int knownrandombytes_is_only_for_testing_not_for_cryptographic_use = 1;
#define knownrandombytes randombytes

#define QUARTERROUND(a,b,c,d) \
  a += b; d = L32(d^a,16); \
  c += d; b = L32(b^c,12); \
  a += b; d = L32(d^a, 8); \
  c += d; b = L32(b^c, 7);

static void core_chacha(u8 *out,const u8 *in,const u8 *k)
{
  u32 x[16],y[16];
  int i,j;
  FOR(i,4) {
    x[i] = ld32(sigma+4*i);
    x[12+i] = ld32(in+4*i);
  }
  FOR(i,8) x[4+i] = ld32(k+4*i);
  FOR(i,16) y[i] = x[i];
  FOR(i,10) {
    FOR(j,4) { QUARTERROUND(x[j],x[j+4],x[j+8],x[j+12]) }
    FOR(j,4) { QUARTERROUND(x[j],x[((j+1)&3)+4],x[((j+2)&3)+8],x[((j+3)&3)+12]) }
  }
  FOR(i,16) st32(out+4*i,x[i]+y[i]);
}

static void chacha20(u8 *c,u64 b,const u8 *n,const u8 *k)
{
  u8 z[16],x[64];
  u32 u,i;
  if (!b) return;
  FOR(i,16) z[i] = 0;
  FOR(i,8) z[i+8] = n[i];
  while (b >= 64) {
    core_chacha(x,z,k);
    FOR(i,64) c[i] = x[i];
    u = 1;
    FOR(i,8) {
      u += (u32) z[i];
      z[i] = u;
      u >>= 8;
    }
    b -= 64;
    c += 64;
  }
  if (b) {
    core_chacha(x,z,k);
    FOR(i,b) c[i] = x[i];
  }
}

#define crypto_rng_OUTPUTBYTES 736

static int crypto_rng(
        unsigned char *r, /* random output */
        unsigned char *n, /* new key */
  const unsigned char *g  /* old key */
)
{
  static const unsigned char nonce[8] = {0};
  unsigned char x[32+crypto_rng_OUTPUTBYTES];
  chacha20(x,sizeof x,nonce,g);
  memcpy(n,x,32);
  memcpy(r,x+32,crypto_rng_OUTPUTBYTES);
  return 0;
}

static unsigned char knownrandombytes_g[32];
static unsigned char knownrandombytes_r[crypto_rng_OUTPUTBYTES];
static unsigned long long knownrandombytes_pos = crypto_rng_OUTPUTBYTES;

static void knownrandombytes_clear(void)
{
  memset(knownrandombytes_g,0,sizeof knownrandombytes_g);
  memset(knownrandombytes_r,0,sizeof knownrandombytes_r);
  knownrandombytes_pos = crypto_rng_OUTPUTBYTES;
}

void knownrandombytes_main(void *xvoid,long long xlen)
{
  unsigned char *x = (unsigned char *) xvoid;
  assert(knownrandombytes_is_only_for_testing_not_for_cryptographic_use);

  while (xlen > 0) {
    if (knownrandombytes_pos == crypto_rng_OUTPUTBYTES) {
      crypto_rng(knownrandombytes_r,knownrandombytes_g,knownrandombytes_g);
      knownrandombytes_pos = 0;
    }
    *x++ = knownrandombytes_r[knownrandombytes_pos];
    xlen -= 1;
    knownrandombytes_r[knownrandombytes_pos++] = 0;
  }
}

void knownrandombytes(void *xvoid,long long xlen)
{
  knownrandombytes_main(xvoid,xlen);
  secret(xvoid,xlen);
}

/* ----- checksums */

static unsigned char checksum_state[64];
static char checksum_hex[65];

static void checksum_expected(const char *expected)
{
  long long i;
  for (i = 0;i < 32;++i) {
    checksum_hex[2 * i] = "0123456789abcdef"[15 & (checksum_state[i] >> 4)];
    checksum_hex[2 * i + 1] = "0123456789abcdef"[15 & checksum_state[i]];
  }
  checksum_hex[2 * i] = 0;

  if (strcmp(checksum_hex,expected))
    fail("failure: checksum mismatch: %s expected %s\n",checksum_hex,expected);
}

static void checksum_clear(void)
{
  memset(checksum_state,0,sizeof checksum_state);
  knownrandombytes_clear();
  testvector_clear();
  /* not necessary to clear canary */
}

static void checksum(const unsigned char *x,unsigned long long xlen)
{
  u8 block[16];
  int i;
  while (xlen >= 16) {
    core_salsa(checksum_state,x,checksum_state);
    x += 16;
    xlen -= 16;
  }
  FOR(i,16) block[i] = 0;
  FOR(i,xlen) block[i] = x[i];
  block[xlen] = 1;
  checksum_state[0] ^= 1;
  core_salsa(checksum_state,block,checksum_state);
}

#include "limits.inc"

static void *callocplus(long long len)
{
  if (valgrind) {
    unsigned char *x = (unsigned char *) malloc(len);
    if (!x) abort();
    return x;
  } else {
    unsigned char *x = (unsigned char *) calloc(1,len + 256);
    long long i;
    if (!x) abort();
    for (i = 0;i < len + 256;++i) x[i] = random();
    return x;
  }
}

static void *aligned(void *x,long long len)
{
  if (valgrind)
    return x;
  else {
    long long i;
    unsigned char *y = (unsigned char *) x;
    y += 64;
    y += 63 & (-(unsigned long) y);
    for (i = 0;i < len;++i) y[i] = 0;
    return y;
  }
}

/* ----- catching SIGILL, SIGBUS, SIGSEGV, etc. */

static void forked(void (*test)(long long),long long impl)
{
  if (valgrind) {
    test(impl);
    return;
  }
  fflush(stdout);
  pid_t child = fork();
  int childstatus = -1;
  if (child == -1) {
    fprintf(stderr,"fatal: fork failed: %s",strerror(errno));
    exit(111);
  }
  if (child == 0) {
    ok = 1;
    limits();
    test(impl);
    if (!ok) exit(100);
    exit(0);
  }
  if (waitpid(child,&childstatus,0) != child) {
    fprintf(stderr,"fatal: wait failed: %s",strerror(errno));
    exit(111);
  }
  if (childstatus)
    fail("failure: process failed, status %d\n",childstatus);
  fflush(stdout);
}

/* ----- endianness */

/* on big-endian machines, flip into little-endian */
/* other types of endianness are not supported */
static void endianness(unsigned char *e,unsigned long long words,unsigned long long bytesperword)
{
  long long i = 1;

  if (1 == *(unsigned char *) &i) return;

  while (words > 0) {
    for (i = 0;2 * i < bytesperword;++i) {
      long long j = bytesperword - 1 - i;
      unsigned char ei = e[i];
      e[i] = e[j];
      e[j] = ei;
    }
    e += bytesperword;
    words -= 1;
  }
}

/* ----- xof, derived from supercop/crypto_xof/try.c */
static void (*crypto_xof)(unsigned char *,long long,const unsigned char *,long long);
static const char *xof_shake256_checksums[] = {
  "a3c4908bf4412d650a1f0a69587778b72aeea66db5a9991a4f0cf2d782ca65b9",
  "cfec0f87445678928e802011140a1df31a1692ec574364da56ddaaf3d4a7d69e",
} ;

static void *storage_xof_shake256_h;
static unsigned char *test_xof_shake256_h;
static void *storage_xof_shake256_m;
static unsigned char *test_xof_shake256_m;
static void *storage_xof_shake256_h2;
static unsigned char *test_xof_shake256_h2;
static void *storage_xof_shake256_m2;
static unsigned char *test_xof_shake256_m2;

static void test_xof_shake256_impl(long long impl)
{
  unsigned char *h = test_xof_shake256_h;
  unsigned char *m = test_xof_shake256_m;
  unsigned char *h2 = test_xof_shake256_h2;
  unsigned char *m2 = test_xof_shake256_m2;
  long long hlen;
  long long mlen;

  if (targeti && strcmp(targeti,".") && strcmp(targeti,mceliece_dispatch_xof_shake256_implementation(impl))) return;
  if (targetn && atol(targetn) != impl) return;
  if (impl >= 0) {
    crypto_xof = mceliece_dispatch_xof_shake256(impl);
    printf("xof_shake256 %lld implementation %s compiler %s\n",impl,mceliece_dispatch_xof_shake256_implementation(impl),mceliece_dispatch_xof_shake256_compiler(impl));
  } else {
    crypto_xof = mceliece_xof_shake256;
    printf("xof_shake256 selected implementation %s compiler %s\n",mceliece_xof_shake256_implementation(),mceliece_xof_shake256_compiler());
  }
  for (long long checksumbig = 0;checksumbig < 2;++checksumbig) {
    long long loops = checksumbig ? 512 : 64;
    long long maxtest = checksumbig ? 16384 : 128;

    checksum_clear();

    for (long long loop = 0;loop < loops;++loop) {
      mlen = myrandom() % (maxtest + 1);
      hlen = myrandom() % (maxtest + 1);

      output_prepare(h2,h,hlen);
      input_prepare(m2,m,mlen);
      secret(m,mlen);
      crypto_xof(h,hlen,m,mlen);
      declassify(m,mlen);
      declassify(h,hlen);
      checksum(h,hlen);
      output_compare(h2,h,hlen,"crypto_xof");
      input_compare(m2,m,mlen,"crypto_xof");

      double_canary(h2,h,hlen);
      double_canary(m2,m,mlen);
      secret(m2,mlen);
      crypto_xof(h2,hlen,m2,mlen);
      declassify(m2,mlen);
      declassify(h2,hlen);
      if (memcmp(h2,h,hlen) != 0) fail("failure: crypto_xof is nondeterministic\n");

      double_canary(h2,h,hlen);
      double_canary(m2,m,mlen);
      secret(m2,mlen);
      crypto_xof(m2,hlen,m2,mlen);
      declassify(m2,hlen);
      if (memcmp(m2,h,hlen) != 0) fail("failure: crypto_xof does not handle m=h overlap\n");
      memcpy(m2,m,mlen);
    }
    checksum_expected(xof_shake256_checksums[checksumbig]);
  }
}

static void test_xof_shake256(void)
{
  if (targeto && strcmp(targeto,"xof")) return;
  if (targetp && strcmp(targetp,"shake256")) return;
  storage_xof_shake256_h = callocplus(16384);
  test_xof_shake256_h = (unsigned char *) aligned(storage_xof_shake256_h,16384);
  storage_xof_shake256_m = callocplus(16384);
  test_xof_shake256_m = (unsigned char *) aligned(storage_xof_shake256_m,16384);
  storage_xof_shake256_h2 = callocplus(16384);
  test_xof_shake256_h2 = (unsigned char *) aligned(storage_xof_shake256_h2,16384);
  storage_xof_shake256_m2 = callocplus(16384);
  test_xof_shake256_m2 = (unsigned char *) aligned(storage_xof_shake256_m2,16384);

  for (long long offset = 0;offset < 2;++offset) {
    if (targetoffset && atol(targetoffset) != offset) continue;
    if (offset && valgrind) break;
    printf("xof_shake256 offset %lld\n",offset);
    for (long long impl = -1;impl < mceliece_numimpl_xof_shake256();++impl)
      forked(test_xof_shake256_impl,impl);
    ++test_xof_shake256_h;
    ++test_xof_shake256_m;
    ++test_xof_shake256_h2;
    ++test_xof_shake256_m2;
  }
  free(storage_xof_shake256_m2);
  free(storage_xof_shake256_h2);
  free(storage_xof_shake256_m);
  free(storage_xof_shake256_h);
}
static const char *xof_bitwrite16_checksums[] = {
  "2a0c679fd13fe74f21610d5377326b5089346cb6b24dbd4524f1dbd357d57180",
  "375a8005efef8dda9b2277c93b8ef7e099acfd82df96f458f01d51b702846dd3",
} ;

static void *storage_xof_bitwrite16_h;
static unsigned char *test_xof_bitwrite16_h;
static void *storage_xof_bitwrite16_m;
static unsigned char *test_xof_bitwrite16_m;
static void *storage_xof_bitwrite16_h2;
static unsigned char *test_xof_bitwrite16_h2;
static void *storage_xof_bitwrite16_m2;
static unsigned char *test_xof_bitwrite16_m2;

static void test_xof_bitwrite16_impl(long long impl)
{
  unsigned char *h = test_xof_bitwrite16_h;
  unsigned char *m = test_xof_bitwrite16_m;
  unsigned char *h2 = test_xof_bitwrite16_h2;
  unsigned char *m2 = test_xof_bitwrite16_m2;
  long long hlen;
  long long mlen;

  if (targeti && strcmp(targeti,".") && strcmp(targeti,mceliece_dispatch_xof_bitwrite16_implementation(impl))) return;
  if (targetn && atol(targetn) != impl) return;
  if (impl >= 0) {
    crypto_xof = mceliece_dispatch_xof_bitwrite16(impl);
    printf("xof_bitwrite16 %lld implementation %s compiler %s\n",impl,mceliece_dispatch_xof_bitwrite16_implementation(impl),mceliece_dispatch_xof_bitwrite16_compiler(impl));
  } else {
    crypto_xof = mceliece_xof_bitwrite16;
    printf("xof_bitwrite16 selected implementation %s compiler %s\n",mceliece_xof_bitwrite16_implementation(),mceliece_xof_bitwrite16_compiler());
  }
  for (long long checksumbig = 0;checksumbig < 2;++checksumbig) {
    long long loops = checksumbig ? 512 : 64;
    long long maxtest = checksumbig ? 16384 : 128;

    checksum_clear();

    for (long long loop = 0;loop < loops;++loop) {
      mlen = myrandom() % (maxtest + 1);
      hlen = myrandom() % (maxtest + 1);

      output_prepare(h2,h,hlen);
      input_prepare(m2,m,mlen);
      secret(m,mlen);
      crypto_xof(h,hlen,m,mlen);
      declassify(m,mlen);
      declassify(h,hlen);
      checksum(h,hlen);
      output_compare(h2,h,hlen,"crypto_xof");
      input_compare(m2,m,mlen,"crypto_xof");

      double_canary(h2,h,hlen);
      double_canary(m2,m,mlen);
      secret(m2,mlen);
      crypto_xof(h2,hlen,m2,mlen);
      declassify(m2,mlen);
      declassify(h2,hlen);
      if (memcmp(h2,h,hlen) != 0) fail("failure: crypto_xof is nondeterministic\n");
    }
    checksum_expected(xof_bitwrite16_checksums[checksumbig]);
  }
}

static void test_xof_bitwrite16(void)
{
  if (targeto && strcmp(targeto,"xof")) return;
  if (targetp && strcmp(targetp,"bitwrite16")) return;
  storage_xof_bitwrite16_h = callocplus(16384);
  test_xof_bitwrite16_h = (unsigned char *) aligned(storage_xof_bitwrite16_h,16384);
  storage_xof_bitwrite16_m = callocplus(16384);
  test_xof_bitwrite16_m = (unsigned char *) aligned(storage_xof_bitwrite16_m,16384);
  storage_xof_bitwrite16_h2 = callocplus(16384);
  test_xof_bitwrite16_h2 = (unsigned char *) aligned(storage_xof_bitwrite16_h2,16384);
  storage_xof_bitwrite16_m2 = callocplus(16384);
  test_xof_bitwrite16_m2 = (unsigned char *) aligned(storage_xof_bitwrite16_m2,16384);

  for (long long offset = 0;offset < 2;++offset) {
    if (targetoffset && atol(targetoffset) != offset) continue;
    if (offset && valgrind) break;
    printf("xof_bitwrite16 offset %lld\n",offset);
    for (long long impl = -1;impl < mceliece_numimpl_xof_bitwrite16();++impl)
      forked(test_xof_bitwrite16_impl,impl);
    ++test_xof_bitwrite16_h;
    ++test_xof_bitwrite16_m;
    ++test_xof_bitwrite16_h2;
    ++test_xof_bitwrite16_m2;
  }
  free(storage_xof_bitwrite16_m2);
  free(storage_xof_bitwrite16_h2);
  free(storage_xof_bitwrite16_m);
  free(storage_xof_bitwrite16_h);
}

/* ----- sort, derived from supercop/crypto_sort/try.c */
static void (*crypto_sort)(void *,long long);
static const char *sort_int16_checksums[] = {
  "c336250bfe2501656d9ec94ce340ebeb7d3001436df73d161d4683ae4e9b9999",
  "2d0c1a7bea57b0255f5bc367be6003fb8d6ecb750ee9d81fe8820d9c0de30bdb",
} ;

#define crypto_sort_BYTES mceliece_sort_int16_BYTES

static void *storage_sort_int16_x;
static unsigned char *test_sort_int16_x;
static void *storage_sort_int16_x2;
static unsigned char *test_sort_int16_x2;

static void test_sort_int16_impl(long long impl)
{
  unsigned char *x = test_sort_int16_x;
  unsigned char *x2 = test_sort_int16_x2;
  long long xlen;
  long long xwords;

  if (targeti && strcmp(targeti,".") && strcmp(targeti,mceliece_dispatch_sort_int16_implementation(impl))) return;
  if (targetn && atol(targetn) != impl) return;
  if (impl >= 0) {
    crypto_sort = mceliece_dispatch_sort_int16(impl);
    printf("sort_int16 %lld implementation %s compiler %s\n",impl,mceliece_dispatch_sort_int16_implementation(impl),mceliece_dispatch_sort_int16_compiler(impl));
  } else {
    crypto_sort = mceliece_sort_int16;
    printf("sort_int16 selected implementation %s compiler %s\n",mceliece_sort_int16_implementation(),mceliece_sort_int16_compiler());
  }
  for (long long checksumbig = 0;checksumbig < 2;++checksumbig) {
    long long loops = checksumbig ? 4096 : 1024;
    long long maxtest = checksumbig ? 4096 : 128;

    checksum_clear();

    for (long long loop = 0;loop < loops;++loop) {
      xwords = myrandom() % (maxtest + 1);
      xlen = mceliece_sort_int16_BYTES*xwords;

      input_prepare(x2,x,xlen);
      endianness(x,xwords,mceliece_sort_int16_BYTES);
      secret(x,xlen);
      crypto_sort(x,xwords);
      declassify(x,xlen);
      endianness(x,xwords,mceliece_sort_int16_BYTES);
      checksum(x,xlen);
      output_compare(x2,x,xlen,"crypto_sort");

      double_canary(x2,x,xlen);
      endianness(x2,xwords,mceliece_sort_int16_BYTES);
      secret(x2,xlen);
      crypto_sort(x2,xwords);
      declassify(x2,xlen);
      endianness(x2,xwords,mceliece_sort_int16_BYTES);
      if (memcmp(x2,x,xlen) != 0) fail("failure: crypto_sort is nondeterministic\n");
    }
    checksum_expected(sort_int16_checksums[checksumbig]);
  }
}

static void test_sort_int16(void)
{
  if (targeto && strcmp(targeto,"sort")) return;
  if (targetp && strcmp(targetp,"int16")) return;
  storage_sort_int16_x = callocplus(mceliece_sort_int16_BYTES*4096);
  test_sort_int16_x = (unsigned char *) aligned(storage_sort_int16_x,mceliece_sort_int16_BYTES*4096);
  storage_sort_int16_x2 = callocplus(mceliece_sort_int16_BYTES*4096);
  test_sort_int16_x2 = (unsigned char *) aligned(storage_sort_int16_x2,mceliece_sort_int16_BYTES*4096);

  for (long long offset = 0;offset < 1;++offset) {
    if (targetoffset && atol(targetoffset) != offset) continue;
    if (offset && valgrind) break;
    printf("sort_int16 offset %lld\n",offset);
    for (long long impl = -1;impl < mceliece_numimpl_sort_int16();++impl)
      forked(test_sort_int16_impl,impl);
    ++test_sort_int16_x;
    ++test_sort_int16_x2;
  }
  free(storage_sort_int16_x2);
  free(storage_sort_int16_x);
}
#undef crypto_sort_BYTES

static const char *sort_int32_checksums[] = {
  "3458da92fdba9924c019db57dd7079f7613df0e243f3b312d10d94781af8c29a",
  "7265f7d8ed54b4a3bd12db9648e246615363373e7044c8d1b7c789ebfc177629",
} ;

#define crypto_sort_BYTES mceliece_sort_int32_BYTES

static void *storage_sort_int32_x;
static unsigned char *test_sort_int32_x;
static void *storage_sort_int32_x2;
static unsigned char *test_sort_int32_x2;

static void test_sort_int32_impl(long long impl)
{
  unsigned char *x = test_sort_int32_x;
  unsigned char *x2 = test_sort_int32_x2;
  long long xlen;
  long long xwords;

  if (targeti && strcmp(targeti,".") && strcmp(targeti,mceliece_dispatch_sort_int32_implementation(impl))) return;
  if (targetn && atol(targetn) != impl) return;
  if (impl >= 0) {
    crypto_sort = mceliece_dispatch_sort_int32(impl);
    printf("sort_int32 %lld implementation %s compiler %s\n",impl,mceliece_dispatch_sort_int32_implementation(impl),mceliece_dispatch_sort_int32_compiler(impl));
  } else {
    crypto_sort = mceliece_sort_int32;
    printf("sort_int32 selected implementation %s compiler %s\n",mceliece_sort_int32_implementation(),mceliece_sort_int32_compiler());
  }
  for (long long checksumbig = 0;checksumbig < 2;++checksumbig) {
    long long loops = checksumbig ? 4096 : 1024;
    long long maxtest = checksumbig ? 4096 : 128;

    checksum_clear();

    for (long long loop = 0;loop < loops;++loop) {
      xwords = myrandom() % (maxtest + 1);
      xlen = mceliece_sort_int32_BYTES*xwords;

      input_prepare(x2,x,xlen);
      endianness(x,xwords,mceliece_sort_int32_BYTES);
      secret(x,xlen);
      crypto_sort(x,xwords);
      declassify(x,xlen);
      endianness(x,xwords,mceliece_sort_int32_BYTES);
      checksum(x,xlen);
      output_compare(x2,x,xlen,"crypto_sort");

      double_canary(x2,x,xlen);
      endianness(x2,xwords,mceliece_sort_int32_BYTES);
      secret(x2,xlen);
      crypto_sort(x2,xwords);
      declassify(x2,xlen);
      endianness(x2,xwords,mceliece_sort_int32_BYTES);
      if (memcmp(x2,x,xlen) != 0) fail("failure: crypto_sort is nondeterministic\n");
    }
    checksum_expected(sort_int32_checksums[checksumbig]);
  }
}

static void test_sort_int32(void)
{
  if (targeto && strcmp(targeto,"sort")) return;
  if (targetp && strcmp(targetp,"int32")) return;
  storage_sort_int32_x = callocplus(mceliece_sort_int32_BYTES*4096);
  test_sort_int32_x = (unsigned char *) aligned(storage_sort_int32_x,mceliece_sort_int32_BYTES*4096);
  storage_sort_int32_x2 = callocplus(mceliece_sort_int32_BYTES*4096);
  test_sort_int32_x2 = (unsigned char *) aligned(storage_sort_int32_x2,mceliece_sort_int32_BYTES*4096);

  for (long long offset = 0;offset < 1;++offset) {
    if (targetoffset && atol(targetoffset) != offset) continue;
    if (offset && valgrind) break;
    printf("sort_int32 offset %lld\n",offset);
    for (long long impl = -1;impl < mceliece_numimpl_sort_int32();++impl)
      forked(test_sort_int32_impl,impl);
    ++test_sort_int32_x;
    ++test_sort_int32_x2;
  }
  free(storage_sort_int32_x2);
  free(storage_sort_int32_x);
}
#undef crypto_sort_BYTES

static const char *sort_int64_checksums[] = {
  "5c055d5c5a05b83d1b01d9cad686c795c3424feb62506188c95630211690fa67",
  "517b3da4601c76eab1e2efba97b81ba49742c2011746be3241475caab159bdbb",
} ;

#define crypto_sort_BYTES mceliece_sort_int64_BYTES

static void *storage_sort_int64_x;
static unsigned char *test_sort_int64_x;
static void *storage_sort_int64_x2;
static unsigned char *test_sort_int64_x2;

static void test_sort_int64_impl(long long impl)
{
  unsigned char *x = test_sort_int64_x;
  unsigned char *x2 = test_sort_int64_x2;
  long long xlen;
  long long xwords;

  if (targeti && strcmp(targeti,".") && strcmp(targeti,mceliece_dispatch_sort_int64_implementation(impl))) return;
  if (targetn && atol(targetn) != impl) return;
  if (impl >= 0) {
    crypto_sort = mceliece_dispatch_sort_int64(impl);
    printf("sort_int64 %lld implementation %s compiler %s\n",impl,mceliece_dispatch_sort_int64_implementation(impl),mceliece_dispatch_sort_int64_compiler(impl));
  } else {
    crypto_sort = mceliece_sort_int64;
    printf("sort_int64 selected implementation %s compiler %s\n",mceliece_sort_int64_implementation(),mceliece_sort_int64_compiler());
  }
  for (long long checksumbig = 0;checksumbig < 2;++checksumbig) {
    long long loops = checksumbig ? 4096 : 1024;
    long long maxtest = checksumbig ? 4096 : 128;

    checksum_clear();

    for (long long loop = 0;loop < loops;++loop) {
      xwords = myrandom() % (maxtest + 1);
      xlen = mceliece_sort_int64_BYTES*xwords;

      input_prepare(x2,x,xlen);
      endianness(x,xwords,mceliece_sort_int64_BYTES);
      secret(x,xlen);
      crypto_sort(x,xwords);
      declassify(x,xlen);
      endianness(x,xwords,mceliece_sort_int64_BYTES);
      checksum(x,xlen);
      output_compare(x2,x,xlen,"crypto_sort");

      double_canary(x2,x,xlen);
      endianness(x2,xwords,mceliece_sort_int64_BYTES);
      secret(x2,xlen);
      crypto_sort(x2,xwords);
      declassify(x2,xlen);
      endianness(x2,xwords,mceliece_sort_int64_BYTES);
      if (memcmp(x2,x,xlen) != 0) fail("failure: crypto_sort is nondeterministic\n");
    }
    checksum_expected(sort_int64_checksums[checksumbig]);
  }
}

static void test_sort_int64(void)
{
  if (targeto && strcmp(targeto,"sort")) return;
  if (targetp && strcmp(targetp,"int64")) return;
  storage_sort_int64_x = callocplus(mceliece_sort_int64_BYTES*4096);
  test_sort_int64_x = (unsigned char *) aligned(storage_sort_int64_x,mceliece_sort_int64_BYTES*4096);
  storage_sort_int64_x2 = callocplus(mceliece_sort_int64_BYTES*4096);
  test_sort_int64_x2 = (unsigned char *) aligned(storage_sort_int64_x2,mceliece_sort_int64_BYTES*4096);

  for (long long offset = 0;offset < 1;++offset) {
    if (targetoffset && atol(targetoffset) != offset) continue;
    if (offset && valgrind) break;
    printf("sort_int64 offset %lld\n",offset);
    for (long long impl = -1;impl < mceliece_numimpl_sort_int64();++impl)
      forked(test_sort_int64_impl,impl);
    ++test_sort_int64_x;
    ++test_sort_int64_x2;
  }
  free(storage_sort_int64_x2);
  free(storage_sort_int64_x);
}
#undef crypto_sort_BYTES


/* ----- kem, derived from supercop/crypto_kem/try.c */
static void (*crypto_kem_keypair)(unsigned char *,unsigned char *);
static int (*crypto_kem_enc)(unsigned char *,unsigned char *,const unsigned char *);
static int (*crypto_kem_dec)(unsigned char *,const unsigned char *,const unsigned char *);
static const char *kem_6960119_checksums[] = {
  "008c0538526a1c037e64f0543628b312a71e879c1f882f65493fd0d3a225d5d8",
  "15c6727d4f4867487a54bbb208c06c1142a56a7937d7b598c05f63801cbdd277",
} ;

#define crypto_kem_PUBLICKEYBYTES mceliece_kem_6960119_PUBLICKEYBYTES
#define crypto_kem_SECRETKEYBYTES mceliece_kem_6960119_SECRETKEYBYTES
#define crypto_kem_CIPHERTEXTBYTES mceliece_kem_6960119_CIPHERTEXTBYTES
#define crypto_kem_BYTES mceliece_kem_6960119_BYTES

static void *storage_kem_6960119_p;
static unsigned char *test_kem_6960119_p;
static void *storage_kem_6960119_s;
static unsigned char *test_kem_6960119_s;
static void *storage_kem_6960119_k;
static unsigned char *test_kem_6960119_k;
static void *storage_kem_6960119_c;
static unsigned char *test_kem_6960119_c;
static void *storage_kem_6960119_t;
static unsigned char *test_kem_6960119_t;
static void *storage_kem_6960119_p2;
static unsigned char *test_kem_6960119_p2;
static void *storage_kem_6960119_s2;
static unsigned char *test_kem_6960119_s2;
static void *storage_kem_6960119_k2;
static unsigned char *test_kem_6960119_k2;
static void *storage_kem_6960119_c2;
static unsigned char *test_kem_6960119_c2;
static void *storage_kem_6960119_t2;
static unsigned char *test_kem_6960119_t2;

static void test_kem_6960119_impl(long long impl)
{
  unsigned char *p = test_kem_6960119_p;
  unsigned char *s = test_kem_6960119_s;
  unsigned char *k = test_kem_6960119_k;
  unsigned char *c = test_kem_6960119_c;
  unsigned char *t = test_kem_6960119_t;
  unsigned char *p2 = test_kem_6960119_p2;
  unsigned char *s2 = test_kem_6960119_s2;
  unsigned char *k2 = test_kem_6960119_k2;
  unsigned char *c2 = test_kem_6960119_c2;
  unsigned char *t2 = test_kem_6960119_t2;
  long long plen = crypto_kem_PUBLICKEYBYTES;
  long long slen = crypto_kem_SECRETKEYBYTES;
  long long klen = crypto_kem_BYTES;
  long long clen = crypto_kem_CIPHERTEXTBYTES;
  long long tlen = crypto_kem_BYTES;

  if (targeti && strcmp(targeti,".") && strcmp(targeti,mceliece_dispatch_kem_6960119_implementation(impl))) return;
  if (targetn && atol(targetn) != impl) return;
  if (impl >= 0) {
    crypto_kem_keypair = mceliece_dispatch_kem_6960119_keypair(impl);
    crypto_kem_enc = mceliece_dispatch_kem_6960119_enc(impl);
    crypto_kem_dec = mceliece_dispatch_kem_6960119_dec(impl);
    printf("kem_6960119 %lld implementation %s compiler %s\n",impl,mceliece_dispatch_kem_6960119_implementation(impl),mceliece_dispatch_kem_6960119_compiler(impl));
  } else {
    crypto_kem_keypair = mceliece_kem_6960119_keypair;
    crypto_kem_enc = mceliece_kem_6960119_enc;
    crypto_kem_dec = mceliece_kem_6960119_dec;
    printf("kem_6960119 selected implementation %s compiler %s\n",mceliece_kem_6960119_implementation(),mceliece_kem_6960119_compiler());
  }
  for (long long checksumbig = 0;checksumbig < 2;++checksumbig) {
    long long loops = checksumbig ? 64 : 8;

    checksum_clear();

    for (long long loop = 0;loop < loops;++loop) {
      int result;

      output_prepare(p2,p,plen);
      output_prepare(s2,s,slen);
      crypto_kem_keypair(p,s);
      declassify(p,plen);
      declassify(s,slen);
      checksum(p,plen);
      checksum(s,slen);
      output_compare(p2,p,plen,"crypto_kem_keypair");
      output_compare(s2,s,slen,"crypto_kem_keypair");
      output_prepare(c2,c,clen);
      output_prepare(k2,k,klen);
      memcpy(p2,p,plen);
      double_canary(p2,p,plen);
      secret(p,plen);
      result = crypto_kem_enc(c,k,p);
      declassify(&result,sizeof result);
      if (result != 0) fail("failure: crypto_kem_enc returns nonzero\n");
      declassify(p,plen);
      declassify(c,clen);
      declassify(k,klen);
      checksum(c,clen);
      checksum(k,klen);
      output_compare(c2,c,clen,"crypto_kem_enc");
      output_compare(k2,k,klen,"crypto_kem_enc");
      input_compare(p2,p,plen,"crypto_kem_enc");
      output_prepare(t2,t,tlen);
      memcpy(c2,c,clen);
      double_canary(c2,c,clen);
      memcpy(s2,s,slen);
      double_canary(s2,s,slen);
      secret(c,clen);
      secret(s,slen);
      result = crypto_kem_dec(t,c,s);
      declassify(&result,sizeof result);
      if (result != 0) fail("failure: crypto_kem_dec returns nonzero\n");
      declassify(c,clen);
      declassify(s,slen);
      declassify(t,tlen);
      if (memcmp(t,k,klen) != 0) fail("failure: crypto_kem_dec does not match k\n");
      checksum(t,tlen);
      output_compare(t2,t,tlen,"crypto_kem_dec");
      input_compare(c2,c,clen,"crypto_kem_dec");
      input_compare(s2,s,slen,"crypto_kem_dec");

      double_canary(t2,t,tlen);
      double_canary(c2,c,clen);
      double_canary(s2,s,slen);
      secret(c2,clen);
      secret(s2,slen);
      result = crypto_kem_dec(t2,c2,s2);
      declassify(&result,sizeof result);
      if (result != 0) fail("failure: crypto_kem_dec returns nonzero\n");
      declassify(c2,clen);
      declassify(s2,slen);
      declassify(t2,tlen);
      if (memcmp(t2,t,tlen) != 0) fail("failure: crypto_kem_dec is nondeterministic\n");

      double_canary(t2,t,tlen);
      double_canary(c2,c,clen);
      double_canary(s2,s,slen);
      secret(c2,clen);
      secret(s,slen);
      result = crypto_kem_dec(c2,c2,s);
      declassify(&result,sizeof result);
      if (result != 0) fail("failure: crypto_kem_dec with c=t overlap returns nonzero\n");
      declassify(c2,tlen);
      declassify(s,slen);
      if (memcmp(c2,t,tlen) != 0) fail("failure: crypto_kem_dec does not handle c=t overlap\n");
      memcpy(c2,c,clen);
      secret(c,clen);
      secret(s2,slen);
      result = crypto_kem_dec(s2,c,s2);
      declassify(&result,sizeof result);
      if (result != 0) fail("failure: crypto_kem_dec with s=t overlap returns nonzero\n");
      declassify(s2,tlen);
      declassify(c,clen);
      if (memcmp(s2,t,tlen) != 0) fail("failure: crypto_kem_dec does not handle s=t overlap\n");
      memcpy(s2,s,slen);

      c[myrandom() % clen] += 1 + (myrandom() % 255);
      if (crypto_kem_dec(t,c,s) == 0)
        checksum(t,tlen);
      else
        checksum(c,clen);
      c[myrandom() % clen] += 1 + (myrandom() % 255);
      if (crypto_kem_dec(t,c,s) == 0)
        checksum(t,tlen);
      else
        checksum(c,clen);
      c[myrandom() % clen] += 1 + (myrandom() % 255);
      if (crypto_kem_dec(t,c,s) == 0)
        checksum(t,tlen);
      else
        checksum(c,clen);
    }
    checksum_expected(kem_6960119_checksums[checksumbig]);
  }
}

static void test_kem_6960119(void)
{
  if (targeto && strcmp(targeto,"kem")) return;
  if (targetp && strcmp(targetp,"6960119")) return;
  storage_kem_6960119_p = callocplus(crypto_kem_PUBLICKEYBYTES);
  test_kem_6960119_p = (unsigned char *) aligned(storage_kem_6960119_p,crypto_kem_PUBLICKEYBYTES);
  storage_kem_6960119_s = callocplus(crypto_kem_SECRETKEYBYTES);
  test_kem_6960119_s = (unsigned char *) aligned(storage_kem_6960119_s,crypto_kem_SECRETKEYBYTES);
  storage_kem_6960119_k = callocplus(crypto_kem_BYTES);
  test_kem_6960119_k = (unsigned char *) aligned(storage_kem_6960119_k,crypto_kem_BYTES);
  storage_kem_6960119_c = callocplus(crypto_kem_CIPHERTEXTBYTES);
  test_kem_6960119_c = (unsigned char *) aligned(storage_kem_6960119_c,crypto_kem_CIPHERTEXTBYTES);
  storage_kem_6960119_t = callocplus(crypto_kem_BYTES);
  test_kem_6960119_t = (unsigned char *) aligned(storage_kem_6960119_t,crypto_kem_BYTES);
  storage_kem_6960119_p2 = callocplus(crypto_kem_PUBLICKEYBYTES);
  test_kem_6960119_p2 = (unsigned char *) aligned(storage_kem_6960119_p2,crypto_kem_PUBLICKEYBYTES);
  storage_kem_6960119_s2 = callocplus(crypto_kem_SECRETKEYBYTES);
  test_kem_6960119_s2 = (unsigned char *) aligned(storage_kem_6960119_s2,crypto_kem_SECRETKEYBYTES);
  storage_kem_6960119_k2 = callocplus(crypto_kem_BYTES);
  test_kem_6960119_k2 = (unsigned char *) aligned(storage_kem_6960119_k2,crypto_kem_BYTES);
  storage_kem_6960119_c2 = callocplus(crypto_kem_CIPHERTEXTBYTES);
  test_kem_6960119_c2 = (unsigned char *) aligned(storage_kem_6960119_c2,crypto_kem_CIPHERTEXTBYTES);
  storage_kem_6960119_t2 = callocplus(crypto_kem_BYTES);
  test_kem_6960119_t2 = (unsigned char *) aligned(storage_kem_6960119_t2,crypto_kem_BYTES);

  for (long long offset = 0;offset < 2;++offset) {
    if (targetoffset && atol(targetoffset) != offset) continue;
    if (offset && valgrind) break;
    printf("kem_6960119 offset %lld\n",offset);
    for (long long impl = -1;impl < mceliece_numimpl_kem_6960119();++impl)
      forked(test_kem_6960119_impl,impl);
    ++test_kem_6960119_p;
    ++test_kem_6960119_s;
    ++test_kem_6960119_k;
    ++test_kem_6960119_c;
    ++test_kem_6960119_t;
    ++test_kem_6960119_p2;
    ++test_kem_6960119_s2;
    ++test_kem_6960119_k2;
    ++test_kem_6960119_c2;
    ++test_kem_6960119_t2;
  }
  free(storage_kem_6960119_t2);
  free(storage_kem_6960119_c2);
  free(storage_kem_6960119_k2);
  free(storage_kem_6960119_s2);
  free(storage_kem_6960119_p2);
  free(storage_kem_6960119_t);
  free(storage_kem_6960119_c);
  free(storage_kem_6960119_k);
  free(storage_kem_6960119_s);
  free(storage_kem_6960119_p);
}
#undef crypto_kem_PUBLICKEYBYTES
#undef crypto_kem_SECRETKEYBYTES
#undef crypto_kem_CIPHERTEXTBYTES
#undef crypto_kem_BYTES

static const char *kem_6960119f_checksums[] = {
  "8d0f85c0ffa074aff7cf1c5d2f8a048174de4ee62a74556e04e8da326e8b640d",
  "d62841358b16796439c261003bae87733ef9889374061bce0a261f80b072861f",
} ;

#define crypto_kem_PUBLICKEYBYTES mceliece_kem_6960119f_PUBLICKEYBYTES
#define crypto_kem_SECRETKEYBYTES mceliece_kem_6960119f_SECRETKEYBYTES
#define crypto_kem_CIPHERTEXTBYTES mceliece_kem_6960119f_CIPHERTEXTBYTES
#define crypto_kem_BYTES mceliece_kem_6960119f_BYTES

static void *storage_kem_6960119f_p;
static unsigned char *test_kem_6960119f_p;
static void *storage_kem_6960119f_s;
static unsigned char *test_kem_6960119f_s;
static void *storage_kem_6960119f_k;
static unsigned char *test_kem_6960119f_k;
static void *storage_kem_6960119f_c;
static unsigned char *test_kem_6960119f_c;
static void *storage_kem_6960119f_t;
static unsigned char *test_kem_6960119f_t;
static void *storage_kem_6960119f_p2;
static unsigned char *test_kem_6960119f_p2;
static void *storage_kem_6960119f_s2;
static unsigned char *test_kem_6960119f_s2;
static void *storage_kem_6960119f_k2;
static unsigned char *test_kem_6960119f_k2;
static void *storage_kem_6960119f_c2;
static unsigned char *test_kem_6960119f_c2;
static void *storage_kem_6960119f_t2;
static unsigned char *test_kem_6960119f_t2;

static void test_kem_6960119f_impl(long long impl)
{
  unsigned char *p = test_kem_6960119f_p;
  unsigned char *s = test_kem_6960119f_s;
  unsigned char *k = test_kem_6960119f_k;
  unsigned char *c = test_kem_6960119f_c;
  unsigned char *t = test_kem_6960119f_t;
  unsigned char *p2 = test_kem_6960119f_p2;
  unsigned char *s2 = test_kem_6960119f_s2;
  unsigned char *k2 = test_kem_6960119f_k2;
  unsigned char *c2 = test_kem_6960119f_c2;
  unsigned char *t2 = test_kem_6960119f_t2;
  long long plen = crypto_kem_PUBLICKEYBYTES;
  long long slen = crypto_kem_SECRETKEYBYTES;
  long long klen = crypto_kem_BYTES;
  long long clen = crypto_kem_CIPHERTEXTBYTES;
  long long tlen = crypto_kem_BYTES;

  if (targeti && strcmp(targeti,".") && strcmp(targeti,mceliece_dispatch_kem_6960119f_implementation(impl))) return;
  if (targetn && atol(targetn) != impl) return;
  if (impl >= 0) {
    crypto_kem_keypair = mceliece_dispatch_kem_6960119f_keypair(impl);
    crypto_kem_enc = mceliece_dispatch_kem_6960119f_enc(impl);
    crypto_kem_dec = mceliece_dispatch_kem_6960119f_dec(impl);
    printf("kem_6960119f %lld implementation %s compiler %s\n",impl,mceliece_dispatch_kem_6960119f_implementation(impl),mceliece_dispatch_kem_6960119f_compiler(impl));
  } else {
    crypto_kem_keypair = mceliece_kem_6960119f_keypair;
    crypto_kem_enc = mceliece_kem_6960119f_enc;
    crypto_kem_dec = mceliece_kem_6960119f_dec;
    printf("kem_6960119f selected implementation %s compiler %s\n",mceliece_kem_6960119f_implementation(),mceliece_kem_6960119f_compiler());
  }
  for (long long checksumbig = 0;checksumbig < 2;++checksumbig) {
    long long loops = checksumbig ? 64 : 8;

    checksum_clear();

    for (long long loop = 0;loop < loops;++loop) {
      int result;

      output_prepare(p2,p,plen);
      output_prepare(s2,s,slen);
      crypto_kem_keypair(p,s);
      declassify(p,plen);
      declassify(s,slen);
      checksum(p,plen);
      checksum(s,slen);
      output_compare(p2,p,plen,"crypto_kem_keypair");
      output_compare(s2,s,slen,"crypto_kem_keypair");
      output_prepare(c2,c,clen);
      output_prepare(k2,k,klen);
      memcpy(p2,p,plen);
      double_canary(p2,p,plen);
      secret(p,plen);
      result = crypto_kem_enc(c,k,p);
      declassify(&result,sizeof result);
      if (result != 0) fail("failure: crypto_kem_enc returns nonzero\n");
      declassify(p,plen);
      declassify(c,clen);
      declassify(k,klen);
      checksum(c,clen);
      checksum(k,klen);
      output_compare(c2,c,clen,"crypto_kem_enc");
      output_compare(k2,k,klen,"crypto_kem_enc");
      input_compare(p2,p,plen,"crypto_kem_enc");
      output_prepare(t2,t,tlen);
      memcpy(c2,c,clen);
      double_canary(c2,c,clen);
      memcpy(s2,s,slen);
      double_canary(s2,s,slen);
      secret(c,clen);
      secret(s,slen);
      result = crypto_kem_dec(t,c,s);
      declassify(&result,sizeof result);
      if (result != 0) fail("failure: crypto_kem_dec returns nonzero\n");
      declassify(c,clen);
      declassify(s,slen);
      declassify(t,tlen);
      if (memcmp(t,k,klen) != 0) fail("failure: crypto_kem_dec does not match k\n");
      checksum(t,tlen);
      output_compare(t2,t,tlen,"crypto_kem_dec");
      input_compare(c2,c,clen,"crypto_kem_dec");
      input_compare(s2,s,slen,"crypto_kem_dec");

      double_canary(t2,t,tlen);
      double_canary(c2,c,clen);
      double_canary(s2,s,slen);
      secret(c2,clen);
      secret(s2,slen);
      result = crypto_kem_dec(t2,c2,s2);
      declassify(&result,sizeof result);
      if (result != 0) fail("failure: crypto_kem_dec returns nonzero\n");
      declassify(c2,clen);
      declassify(s2,slen);
      declassify(t2,tlen);
      if (memcmp(t2,t,tlen) != 0) fail("failure: crypto_kem_dec is nondeterministic\n");

      double_canary(t2,t,tlen);
      double_canary(c2,c,clen);
      double_canary(s2,s,slen);
      secret(c2,clen);
      secret(s,slen);
      result = crypto_kem_dec(c2,c2,s);
      declassify(&result,sizeof result);
      if (result != 0) fail("failure: crypto_kem_dec with c=t overlap returns nonzero\n");
      declassify(c2,tlen);
      declassify(s,slen);
      if (memcmp(c2,t,tlen) != 0) fail("failure: crypto_kem_dec does not handle c=t overlap\n");
      memcpy(c2,c,clen);
      secret(c,clen);
      secret(s2,slen);
      result = crypto_kem_dec(s2,c,s2);
      declassify(&result,sizeof result);
      if (result != 0) fail("failure: crypto_kem_dec with s=t overlap returns nonzero\n");
      declassify(s2,tlen);
      declassify(c,clen);
      if (memcmp(s2,t,tlen) != 0) fail("failure: crypto_kem_dec does not handle s=t overlap\n");
      memcpy(s2,s,slen);

      c[myrandom() % clen] += 1 + (myrandom() % 255);
      if (crypto_kem_dec(t,c,s) == 0)
        checksum(t,tlen);
      else
        checksum(c,clen);
      c[myrandom() % clen] += 1 + (myrandom() % 255);
      if (crypto_kem_dec(t,c,s) == 0)
        checksum(t,tlen);
      else
        checksum(c,clen);
      c[myrandom() % clen] += 1 + (myrandom() % 255);
      if (crypto_kem_dec(t,c,s) == 0)
        checksum(t,tlen);
      else
        checksum(c,clen);
    }
    checksum_expected(kem_6960119f_checksums[checksumbig]);
  }
}

static void test_kem_6960119f(void)
{
  if (targeto && strcmp(targeto,"kem")) return;
  if (targetp && strcmp(targetp,"6960119f")) return;
  storage_kem_6960119f_p = callocplus(crypto_kem_PUBLICKEYBYTES);
  test_kem_6960119f_p = (unsigned char *) aligned(storage_kem_6960119f_p,crypto_kem_PUBLICKEYBYTES);
  storage_kem_6960119f_s = callocplus(crypto_kem_SECRETKEYBYTES);
  test_kem_6960119f_s = (unsigned char *) aligned(storage_kem_6960119f_s,crypto_kem_SECRETKEYBYTES);
  storage_kem_6960119f_k = callocplus(crypto_kem_BYTES);
  test_kem_6960119f_k = (unsigned char *) aligned(storage_kem_6960119f_k,crypto_kem_BYTES);
  storage_kem_6960119f_c = callocplus(crypto_kem_CIPHERTEXTBYTES);
  test_kem_6960119f_c = (unsigned char *) aligned(storage_kem_6960119f_c,crypto_kem_CIPHERTEXTBYTES);
  storage_kem_6960119f_t = callocplus(crypto_kem_BYTES);
  test_kem_6960119f_t = (unsigned char *) aligned(storage_kem_6960119f_t,crypto_kem_BYTES);
  storage_kem_6960119f_p2 = callocplus(crypto_kem_PUBLICKEYBYTES);
  test_kem_6960119f_p2 = (unsigned char *) aligned(storage_kem_6960119f_p2,crypto_kem_PUBLICKEYBYTES);
  storage_kem_6960119f_s2 = callocplus(crypto_kem_SECRETKEYBYTES);
  test_kem_6960119f_s2 = (unsigned char *) aligned(storage_kem_6960119f_s2,crypto_kem_SECRETKEYBYTES);
  storage_kem_6960119f_k2 = callocplus(crypto_kem_BYTES);
  test_kem_6960119f_k2 = (unsigned char *) aligned(storage_kem_6960119f_k2,crypto_kem_BYTES);
  storage_kem_6960119f_c2 = callocplus(crypto_kem_CIPHERTEXTBYTES);
  test_kem_6960119f_c2 = (unsigned char *) aligned(storage_kem_6960119f_c2,crypto_kem_CIPHERTEXTBYTES);
  storage_kem_6960119f_t2 = callocplus(crypto_kem_BYTES);
  test_kem_6960119f_t2 = (unsigned char *) aligned(storage_kem_6960119f_t2,crypto_kem_BYTES);

  for (long long offset = 0;offset < 2;++offset) {
    if (targetoffset && atol(targetoffset) != offset) continue;
    if (offset && valgrind) break;
    printf("kem_6960119f offset %lld\n",offset);
    for (long long impl = -1;impl < mceliece_numimpl_kem_6960119f();++impl)
      forked(test_kem_6960119f_impl,impl);
    ++test_kem_6960119f_p;
    ++test_kem_6960119f_s;
    ++test_kem_6960119f_k;
    ++test_kem_6960119f_c;
    ++test_kem_6960119f_t;
    ++test_kem_6960119f_p2;
    ++test_kem_6960119f_s2;
    ++test_kem_6960119f_k2;
    ++test_kem_6960119f_c2;
    ++test_kem_6960119f_t2;
  }
  free(storage_kem_6960119f_t2);
  free(storage_kem_6960119f_c2);
  free(storage_kem_6960119f_k2);
  free(storage_kem_6960119f_s2);
  free(storage_kem_6960119f_p2);
  free(storage_kem_6960119f_t);
  free(storage_kem_6960119f_c);
  free(storage_kem_6960119f_k);
  free(storage_kem_6960119f_s);
  free(storage_kem_6960119f_p);
}
#undef crypto_kem_PUBLICKEYBYTES
#undef crypto_kem_SECRETKEYBYTES
#undef crypto_kem_CIPHERTEXTBYTES
#undef crypto_kem_BYTES

static const char *kem_6960119pc_checksums[] = {
  "f164d7a16ea6175870f34056b211d4d45a2bc95085759e2f688721f3fbf326c8",
  "7f2438a79d20ae3b056f2d13bca43ea7c1ba2a2e0535cc35f7016188910a4720",
} ;

#define crypto_kem_PUBLICKEYBYTES mceliece_kem_6960119pc_PUBLICKEYBYTES
#define crypto_kem_SECRETKEYBYTES mceliece_kem_6960119pc_SECRETKEYBYTES
#define crypto_kem_CIPHERTEXTBYTES mceliece_kem_6960119pc_CIPHERTEXTBYTES
#define crypto_kem_BYTES mceliece_kem_6960119pc_BYTES

static void *storage_kem_6960119pc_p;
static unsigned char *test_kem_6960119pc_p;
static void *storage_kem_6960119pc_s;
static unsigned char *test_kem_6960119pc_s;
static void *storage_kem_6960119pc_k;
static unsigned char *test_kem_6960119pc_k;
static void *storage_kem_6960119pc_c;
static unsigned char *test_kem_6960119pc_c;
static void *storage_kem_6960119pc_t;
static unsigned char *test_kem_6960119pc_t;
static void *storage_kem_6960119pc_p2;
static unsigned char *test_kem_6960119pc_p2;
static void *storage_kem_6960119pc_s2;
static unsigned char *test_kem_6960119pc_s2;
static void *storage_kem_6960119pc_k2;
static unsigned char *test_kem_6960119pc_k2;
static void *storage_kem_6960119pc_c2;
static unsigned char *test_kem_6960119pc_c2;
static void *storage_kem_6960119pc_t2;
static unsigned char *test_kem_6960119pc_t2;

static void test_kem_6960119pc_impl(long long impl)
{
  unsigned char *p = test_kem_6960119pc_p;
  unsigned char *s = test_kem_6960119pc_s;
  unsigned char *k = test_kem_6960119pc_k;
  unsigned char *c = test_kem_6960119pc_c;
  unsigned char *t = test_kem_6960119pc_t;
  unsigned char *p2 = test_kem_6960119pc_p2;
  unsigned char *s2 = test_kem_6960119pc_s2;
  unsigned char *k2 = test_kem_6960119pc_k2;
  unsigned char *c2 = test_kem_6960119pc_c2;
  unsigned char *t2 = test_kem_6960119pc_t2;
  long long plen = crypto_kem_PUBLICKEYBYTES;
  long long slen = crypto_kem_SECRETKEYBYTES;
  long long klen = crypto_kem_BYTES;
  long long clen = crypto_kem_CIPHERTEXTBYTES;
  long long tlen = crypto_kem_BYTES;

  if (targeti && strcmp(targeti,".") && strcmp(targeti,mceliece_dispatch_kem_6960119pc_implementation(impl))) return;
  if (targetn && atol(targetn) != impl) return;
  if (impl >= 0) {
    crypto_kem_keypair = mceliece_dispatch_kem_6960119pc_keypair(impl);
    crypto_kem_enc = mceliece_dispatch_kem_6960119pc_enc(impl);
    crypto_kem_dec = mceliece_dispatch_kem_6960119pc_dec(impl);
    printf("kem_6960119pc %lld implementation %s compiler %s\n",impl,mceliece_dispatch_kem_6960119pc_implementation(impl),mceliece_dispatch_kem_6960119pc_compiler(impl));
  } else {
    crypto_kem_keypair = mceliece_kem_6960119pc_keypair;
    crypto_kem_enc = mceliece_kem_6960119pc_enc;
    crypto_kem_dec = mceliece_kem_6960119pc_dec;
    printf("kem_6960119pc selected implementation %s compiler %s\n",mceliece_kem_6960119pc_implementation(),mceliece_kem_6960119pc_compiler());
  }
  for (long long checksumbig = 0;checksumbig < 2;++checksumbig) {
    long long loops = checksumbig ? 64 : 8;

    checksum_clear();

    for (long long loop = 0;loop < loops;++loop) {
      int result;

      output_prepare(p2,p,plen);
      output_prepare(s2,s,slen);
      crypto_kem_keypair(p,s);
      declassify(p,plen);
      declassify(s,slen);
      checksum(p,plen);
      checksum(s,slen);
      output_compare(p2,p,plen,"crypto_kem_keypair");
      output_compare(s2,s,slen,"crypto_kem_keypair");
      output_prepare(c2,c,clen);
      output_prepare(k2,k,klen);
      memcpy(p2,p,plen);
      double_canary(p2,p,plen);
      secret(p,plen);
      result = crypto_kem_enc(c,k,p);
      declassify(&result,sizeof result);
      if (result != 0) fail("failure: crypto_kem_enc returns nonzero\n");
      declassify(p,plen);
      declassify(c,clen);
      declassify(k,klen);
      checksum(c,clen);
      checksum(k,klen);
      output_compare(c2,c,clen,"crypto_kem_enc");
      output_compare(k2,k,klen,"crypto_kem_enc");
      input_compare(p2,p,plen,"crypto_kem_enc");
      output_prepare(t2,t,tlen);
      memcpy(c2,c,clen);
      double_canary(c2,c,clen);
      memcpy(s2,s,slen);
      double_canary(s2,s,slen);
      secret(c,clen);
      secret(s,slen);
      result = crypto_kem_dec(t,c,s);
      declassify(&result,sizeof result);
      if (result != 0) fail("failure: crypto_kem_dec returns nonzero\n");
      declassify(c,clen);
      declassify(s,slen);
      declassify(t,tlen);
      if (memcmp(t,k,klen) != 0) fail("failure: crypto_kem_dec does not match k\n");
      checksum(t,tlen);
      output_compare(t2,t,tlen,"crypto_kem_dec");
      input_compare(c2,c,clen,"crypto_kem_dec");
      input_compare(s2,s,slen,"crypto_kem_dec");

      double_canary(t2,t,tlen);
      double_canary(c2,c,clen);
      double_canary(s2,s,slen);
      secret(c2,clen);
      secret(s2,slen);
      result = crypto_kem_dec(t2,c2,s2);
      declassify(&result,sizeof result);
      if (result != 0) fail("failure: crypto_kem_dec returns nonzero\n");
      declassify(c2,clen);
      declassify(s2,slen);
      declassify(t2,tlen);
      if (memcmp(t2,t,tlen) != 0) fail("failure: crypto_kem_dec is nondeterministic\n");

      double_canary(t2,t,tlen);
      double_canary(c2,c,clen);
      double_canary(s2,s,slen);
      secret(c2,clen);
      secret(s,slen);
      result = crypto_kem_dec(c2,c2,s);
      declassify(&result,sizeof result);
      if (result != 0) fail("failure: crypto_kem_dec with c=t overlap returns nonzero\n");
      declassify(c2,tlen);
      declassify(s,slen);
      if (memcmp(c2,t,tlen) != 0) fail("failure: crypto_kem_dec does not handle c=t overlap\n");
      memcpy(c2,c,clen);
      secret(c,clen);
      secret(s2,slen);
      result = crypto_kem_dec(s2,c,s2);
      declassify(&result,sizeof result);
      if (result != 0) fail("failure: crypto_kem_dec with s=t overlap returns nonzero\n");
      declassify(s2,tlen);
      declassify(c,clen);
      if (memcmp(s2,t,tlen) != 0) fail("failure: crypto_kem_dec does not handle s=t overlap\n");
      memcpy(s2,s,slen);

      c[myrandom() % clen] += 1 + (myrandom() % 255);
      if (crypto_kem_dec(t,c,s) == 0)
        checksum(t,tlen);
      else
        checksum(c,clen);
      c[myrandom() % clen] += 1 + (myrandom() % 255);
      if (crypto_kem_dec(t,c,s) == 0)
        checksum(t,tlen);
      else
        checksum(c,clen);
      c[myrandom() % clen] += 1 + (myrandom() % 255);
      if (crypto_kem_dec(t,c,s) == 0)
        checksum(t,tlen);
      else
        checksum(c,clen);
    }
    checksum_expected(kem_6960119pc_checksums[checksumbig]);
  }
}

static void test_kem_6960119pc(void)
{
  if (targeto && strcmp(targeto,"kem")) return;
  if (targetp && strcmp(targetp,"6960119pc")) return;
  storage_kem_6960119pc_p = callocplus(crypto_kem_PUBLICKEYBYTES);
  test_kem_6960119pc_p = (unsigned char *) aligned(storage_kem_6960119pc_p,crypto_kem_PUBLICKEYBYTES);
  storage_kem_6960119pc_s = callocplus(crypto_kem_SECRETKEYBYTES);
  test_kem_6960119pc_s = (unsigned char *) aligned(storage_kem_6960119pc_s,crypto_kem_SECRETKEYBYTES);
  storage_kem_6960119pc_k = callocplus(crypto_kem_BYTES);
  test_kem_6960119pc_k = (unsigned char *) aligned(storage_kem_6960119pc_k,crypto_kem_BYTES);
  storage_kem_6960119pc_c = callocplus(crypto_kem_CIPHERTEXTBYTES);
  test_kem_6960119pc_c = (unsigned char *) aligned(storage_kem_6960119pc_c,crypto_kem_CIPHERTEXTBYTES);
  storage_kem_6960119pc_t = callocplus(crypto_kem_BYTES);
  test_kem_6960119pc_t = (unsigned char *) aligned(storage_kem_6960119pc_t,crypto_kem_BYTES);
  storage_kem_6960119pc_p2 = callocplus(crypto_kem_PUBLICKEYBYTES);
  test_kem_6960119pc_p2 = (unsigned char *) aligned(storage_kem_6960119pc_p2,crypto_kem_PUBLICKEYBYTES);
  storage_kem_6960119pc_s2 = callocplus(crypto_kem_SECRETKEYBYTES);
  test_kem_6960119pc_s2 = (unsigned char *) aligned(storage_kem_6960119pc_s2,crypto_kem_SECRETKEYBYTES);
  storage_kem_6960119pc_k2 = callocplus(crypto_kem_BYTES);
  test_kem_6960119pc_k2 = (unsigned char *) aligned(storage_kem_6960119pc_k2,crypto_kem_BYTES);
  storage_kem_6960119pc_c2 = callocplus(crypto_kem_CIPHERTEXTBYTES);
  test_kem_6960119pc_c2 = (unsigned char *) aligned(storage_kem_6960119pc_c2,crypto_kem_CIPHERTEXTBYTES);
  storage_kem_6960119pc_t2 = callocplus(crypto_kem_BYTES);
  test_kem_6960119pc_t2 = (unsigned char *) aligned(storage_kem_6960119pc_t2,crypto_kem_BYTES);

  for (long long offset = 0;offset < 2;++offset) {
    if (targetoffset && atol(targetoffset) != offset) continue;
    if (offset && valgrind) break;
    printf("kem_6960119pc offset %lld\n",offset);
    for (long long impl = -1;impl < mceliece_numimpl_kem_6960119pc();++impl)
      forked(test_kem_6960119pc_impl,impl);
    ++test_kem_6960119pc_p;
    ++test_kem_6960119pc_s;
    ++test_kem_6960119pc_k;
    ++test_kem_6960119pc_c;
    ++test_kem_6960119pc_t;
    ++test_kem_6960119pc_p2;
    ++test_kem_6960119pc_s2;
    ++test_kem_6960119pc_k2;
    ++test_kem_6960119pc_c2;
    ++test_kem_6960119pc_t2;
  }
  free(storage_kem_6960119pc_t2);
  free(storage_kem_6960119pc_c2);
  free(storage_kem_6960119pc_k2);
  free(storage_kem_6960119pc_s2);
  free(storage_kem_6960119pc_p2);
  free(storage_kem_6960119pc_t);
  free(storage_kem_6960119pc_c);
  free(storage_kem_6960119pc_k);
  free(storage_kem_6960119pc_s);
  free(storage_kem_6960119pc_p);
}
#undef crypto_kem_PUBLICKEYBYTES
#undef crypto_kem_SECRETKEYBYTES
#undef crypto_kem_CIPHERTEXTBYTES
#undef crypto_kem_BYTES

static const char *kem_6960119pcf_checksums[] = {
  "873616887e3e83679d5a708b3fbd8eb2301d18ea21f0f7c238db87178596267a",
  "d709f666d84fe4450ec59759ef20982df8d614afe788db2b7d0f91b0c0e02254",
} ;

#define crypto_kem_PUBLICKEYBYTES mceliece_kem_6960119pcf_PUBLICKEYBYTES
#define crypto_kem_SECRETKEYBYTES mceliece_kem_6960119pcf_SECRETKEYBYTES
#define crypto_kem_CIPHERTEXTBYTES mceliece_kem_6960119pcf_CIPHERTEXTBYTES
#define crypto_kem_BYTES mceliece_kem_6960119pcf_BYTES

static void *storage_kem_6960119pcf_p;
static unsigned char *test_kem_6960119pcf_p;
static void *storage_kem_6960119pcf_s;
static unsigned char *test_kem_6960119pcf_s;
static void *storage_kem_6960119pcf_k;
static unsigned char *test_kem_6960119pcf_k;
static void *storage_kem_6960119pcf_c;
static unsigned char *test_kem_6960119pcf_c;
static void *storage_kem_6960119pcf_t;
static unsigned char *test_kem_6960119pcf_t;
static void *storage_kem_6960119pcf_p2;
static unsigned char *test_kem_6960119pcf_p2;
static void *storage_kem_6960119pcf_s2;
static unsigned char *test_kem_6960119pcf_s2;
static void *storage_kem_6960119pcf_k2;
static unsigned char *test_kem_6960119pcf_k2;
static void *storage_kem_6960119pcf_c2;
static unsigned char *test_kem_6960119pcf_c2;
static void *storage_kem_6960119pcf_t2;
static unsigned char *test_kem_6960119pcf_t2;

static void test_kem_6960119pcf_impl(long long impl)
{
  unsigned char *p = test_kem_6960119pcf_p;
  unsigned char *s = test_kem_6960119pcf_s;
  unsigned char *k = test_kem_6960119pcf_k;
  unsigned char *c = test_kem_6960119pcf_c;
  unsigned char *t = test_kem_6960119pcf_t;
  unsigned char *p2 = test_kem_6960119pcf_p2;
  unsigned char *s2 = test_kem_6960119pcf_s2;
  unsigned char *k2 = test_kem_6960119pcf_k2;
  unsigned char *c2 = test_kem_6960119pcf_c2;
  unsigned char *t2 = test_kem_6960119pcf_t2;
  long long plen = crypto_kem_PUBLICKEYBYTES;
  long long slen = crypto_kem_SECRETKEYBYTES;
  long long klen = crypto_kem_BYTES;
  long long clen = crypto_kem_CIPHERTEXTBYTES;
  long long tlen = crypto_kem_BYTES;

  if (targeti && strcmp(targeti,".") && strcmp(targeti,mceliece_dispatch_kem_6960119pcf_implementation(impl))) return;
  if (targetn && atol(targetn) != impl) return;
  if (impl >= 0) {
    crypto_kem_keypair = mceliece_dispatch_kem_6960119pcf_keypair(impl);
    crypto_kem_enc = mceliece_dispatch_kem_6960119pcf_enc(impl);
    crypto_kem_dec = mceliece_dispatch_kem_6960119pcf_dec(impl);
    printf("kem_6960119pcf %lld implementation %s compiler %s\n",impl,mceliece_dispatch_kem_6960119pcf_implementation(impl),mceliece_dispatch_kem_6960119pcf_compiler(impl));
  } else {
    crypto_kem_keypair = mceliece_kem_6960119pcf_keypair;
    crypto_kem_enc = mceliece_kem_6960119pcf_enc;
    crypto_kem_dec = mceliece_kem_6960119pcf_dec;
    printf("kem_6960119pcf selected implementation %s compiler %s\n",mceliece_kem_6960119pcf_implementation(),mceliece_kem_6960119pcf_compiler());
  }
  for (long long checksumbig = 0;checksumbig < 2;++checksumbig) {
    long long loops = checksumbig ? 64 : 8;

    checksum_clear();

    for (long long loop = 0;loop < loops;++loop) {
      int result;

      output_prepare(p2,p,plen);
      output_prepare(s2,s,slen);
      crypto_kem_keypair(p,s);
      declassify(p,plen);
      declassify(s,slen);
      checksum(p,plen);
      checksum(s,slen);
      output_compare(p2,p,plen,"crypto_kem_keypair");
      output_compare(s2,s,slen,"crypto_kem_keypair");
      output_prepare(c2,c,clen);
      output_prepare(k2,k,klen);
      memcpy(p2,p,plen);
      double_canary(p2,p,plen);
      secret(p,plen);
      result = crypto_kem_enc(c,k,p);
      declassify(&result,sizeof result);
      if (result != 0) fail("failure: crypto_kem_enc returns nonzero\n");
      declassify(p,plen);
      declassify(c,clen);
      declassify(k,klen);
      checksum(c,clen);
      checksum(k,klen);
      output_compare(c2,c,clen,"crypto_kem_enc");
      output_compare(k2,k,klen,"crypto_kem_enc");
      input_compare(p2,p,plen,"crypto_kem_enc");
      output_prepare(t2,t,tlen);
      memcpy(c2,c,clen);
      double_canary(c2,c,clen);
      memcpy(s2,s,slen);
      double_canary(s2,s,slen);
      secret(c,clen);
      secret(s,slen);
      result = crypto_kem_dec(t,c,s);
      declassify(&result,sizeof result);
      if (result != 0) fail("failure: crypto_kem_dec returns nonzero\n");
      declassify(c,clen);
      declassify(s,slen);
      declassify(t,tlen);
      if (memcmp(t,k,klen) != 0) fail("failure: crypto_kem_dec does not match k\n");
      checksum(t,tlen);
      output_compare(t2,t,tlen,"crypto_kem_dec");
      input_compare(c2,c,clen,"crypto_kem_dec");
      input_compare(s2,s,slen,"crypto_kem_dec");

      double_canary(t2,t,tlen);
      double_canary(c2,c,clen);
      double_canary(s2,s,slen);
      secret(c2,clen);
      secret(s2,slen);
      result = crypto_kem_dec(t2,c2,s2);
      declassify(&result,sizeof result);
      if (result != 0) fail("failure: crypto_kem_dec returns nonzero\n");
      declassify(c2,clen);
      declassify(s2,slen);
      declassify(t2,tlen);
      if (memcmp(t2,t,tlen) != 0) fail("failure: crypto_kem_dec is nondeterministic\n");

      double_canary(t2,t,tlen);
      double_canary(c2,c,clen);
      double_canary(s2,s,slen);
      secret(c2,clen);
      secret(s,slen);
      result = crypto_kem_dec(c2,c2,s);
      declassify(&result,sizeof result);
      if (result != 0) fail("failure: crypto_kem_dec with c=t overlap returns nonzero\n");
      declassify(c2,tlen);
      declassify(s,slen);
      if (memcmp(c2,t,tlen) != 0) fail("failure: crypto_kem_dec does not handle c=t overlap\n");
      memcpy(c2,c,clen);
      secret(c,clen);
      secret(s2,slen);
      result = crypto_kem_dec(s2,c,s2);
      declassify(&result,sizeof result);
      if (result != 0) fail("failure: crypto_kem_dec with s=t overlap returns nonzero\n");
      declassify(s2,tlen);
      declassify(c,clen);
      if (memcmp(s2,t,tlen) != 0) fail("failure: crypto_kem_dec does not handle s=t overlap\n");
      memcpy(s2,s,slen);

      c[myrandom() % clen] += 1 + (myrandom() % 255);
      if (crypto_kem_dec(t,c,s) == 0)
        checksum(t,tlen);
      else
        checksum(c,clen);
      c[myrandom() % clen] += 1 + (myrandom() % 255);
      if (crypto_kem_dec(t,c,s) == 0)
        checksum(t,tlen);
      else
        checksum(c,clen);
      c[myrandom() % clen] += 1 + (myrandom() % 255);
      if (crypto_kem_dec(t,c,s) == 0)
        checksum(t,tlen);
      else
        checksum(c,clen);
    }
    checksum_expected(kem_6960119pcf_checksums[checksumbig]);
  }
}

static void test_kem_6960119pcf(void)
{
  if (targeto && strcmp(targeto,"kem")) return;
  if (targetp && strcmp(targetp,"6960119pcf")) return;
  storage_kem_6960119pcf_p = callocplus(crypto_kem_PUBLICKEYBYTES);
  test_kem_6960119pcf_p = (unsigned char *) aligned(storage_kem_6960119pcf_p,crypto_kem_PUBLICKEYBYTES);
  storage_kem_6960119pcf_s = callocplus(crypto_kem_SECRETKEYBYTES);
  test_kem_6960119pcf_s = (unsigned char *) aligned(storage_kem_6960119pcf_s,crypto_kem_SECRETKEYBYTES);
  storage_kem_6960119pcf_k = callocplus(crypto_kem_BYTES);
  test_kem_6960119pcf_k = (unsigned char *) aligned(storage_kem_6960119pcf_k,crypto_kem_BYTES);
  storage_kem_6960119pcf_c = callocplus(crypto_kem_CIPHERTEXTBYTES);
  test_kem_6960119pcf_c = (unsigned char *) aligned(storage_kem_6960119pcf_c,crypto_kem_CIPHERTEXTBYTES);
  storage_kem_6960119pcf_t = callocplus(crypto_kem_BYTES);
  test_kem_6960119pcf_t = (unsigned char *) aligned(storage_kem_6960119pcf_t,crypto_kem_BYTES);
  storage_kem_6960119pcf_p2 = callocplus(crypto_kem_PUBLICKEYBYTES);
  test_kem_6960119pcf_p2 = (unsigned char *) aligned(storage_kem_6960119pcf_p2,crypto_kem_PUBLICKEYBYTES);
  storage_kem_6960119pcf_s2 = callocplus(crypto_kem_SECRETKEYBYTES);
  test_kem_6960119pcf_s2 = (unsigned char *) aligned(storage_kem_6960119pcf_s2,crypto_kem_SECRETKEYBYTES);
  storage_kem_6960119pcf_k2 = callocplus(crypto_kem_BYTES);
  test_kem_6960119pcf_k2 = (unsigned char *) aligned(storage_kem_6960119pcf_k2,crypto_kem_BYTES);
  storage_kem_6960119pcf_c2 = callocplus(crypto_kem_CIPHERTEXTBYTES);
  test_kem_6960119pcf_c2 = (unsigned char *) aligned(storage_kem_6960119pcf_c2,crypto_kem_CIPHERTEXTBYTES);
  storage_kem_6960119pcf_t2 = callocplus(crypto_kem_BYTES);
  test_kem_6960119pcf_t2 = (unsigned char *) aligned(storage_kem_6960119pcf_t2,crypto_kem_BYTES);

  for (long long offset = 0;offset < 2;++offset) {
    if (targetoffset && atol(targetoffset) != offset) continue;
    if (offset && valgrind) break;
    printf("kem_6960119pcf offset %lld\n",offset);
    for (long long impl = -1;impl < mceliece_numimpl_kem_6960119pcf();++impl)
      forked(test_kem_6960119pcf_impl,impl);
    ++test_kem_6960119pcf_p;
    ++test_kem_6960119pcf_s;
    ++test_kem_6960119pcf_k;
    ++test_kem_6960119pcf_c;
    ++test_kem_6960119pcf_t;
    ++test_kem_6960119pcf_p2;
    ++test_kem_6960119pcf_s2;
    ++test_kem_6960119pcf_k2;
    ++test_kem_6960119pcf_c2;
    ++test_kem_6960119pcf_t2;
  }
  free(storage_kem_6960119pcf_t2);
  free(storage_kem_6960119pcf_c2);
  free(storage_kem_6960119pcf_k2);
  free(storage_kem_6960119pcf_s2);
  free(storage_kem_6960119pcf_p2);
  free(storage_kem_6960119pcf_t);
  free(storage_kem_6960119pcf_c);
  free(storage_kem_6960119pcf_k);
  free(storage_kem_6960119pcf_s);
  free(storage_kem_6960119pcf_p);
}
#undef crypto_kem_PUBLICKEYBYTES
#undef crypto_kem_SECRETKEYBYTES
#undef crypto_kem_CIPHERTEXTBYTES
#undef crypto_kem_BYTES

static const char *kem_6688128_checksums[] = {
  "a3446acecf9aff0e757dfafc5402e365eb3ba485dd1f7b052f3ca6eabfdcb6c4",
  "b2ee78aaa23c0612155239b1d92e9e1af589cb810bdb9d8c44eb85dbfd2e46d4",
} ;

#define crypto_kem_PUBLICKEYBYTES mceliece_kem_6688128_PUBLICKEYBYTES
#define crypto_kem_SECRETKEYBYTES mceliece_kem_6688128_SECRETKEYBYTES
#define crypto_kem_CIPHERTEXTBYTES mceliece_kem_6688128_CIPHERTEXTBYTES
#define crypto_kem_BYTES mceliece_kem_6688128_BYTES

static void *storage_kem_6688128_p;
static unsigned char *test_kem_6688128_p;
static void *storage_kem_6688128_s;
static unsigned char *test_kem_6688128_s;
static void *storage_kem_6688128_k;
static unsigned char *test_kem_6688128_k;
static void *storage_kem_6688128_c;
static unsigned char *test_kem_6688128_c;
static void *storage_kem_6688128_t;
static unsigned char *test_kem_6688128_t;
static void *storage_kem_6688128_p2;
static unsigned char *test_kem_6688128_p2;
static void *storage_kem_6688128_s2;
static unsigned char *test_kem_6688128_s2;
static void *storage_kem_6688128_k2;
static unsigned char *test_kem_6688128_k2;
static void *storage_kem_6688128_c2;
static unsigned char *test_kem_6688128_c2;
static void *storage_kem_6688128_t2;
static unsigned char *test_kem_6688128_t2;

static void test_kem_6688128_impl(long long impl)
{
  unsigned char *p = test_kem_6688128_p;
  unsigned char *s = test_kem_6688128_s;
  unsigned char *k = test_kem_6688128_k;
  unsigned char *c = test_kem_6688128_c;
  unsigned char *t = test_kem_6688128_t;
  unsigned char *p2 = test_kem_6688128_p2;
  unsigned char *s2 = test_kem_6688128_s2;
  unsigned char *k2 = test_kem_6688128_k2;
  unsigned char *c2 = test_kem_6688128_c2;
  unsigned char *t2 = test_kem_6688128_t2;
  long long plen = crypto_kem_PUBLICKEYBYTES;
  long long slen = crypto_kem_SECRETKEYBYTES;
  long long klen = crypto_kem_BYTES;
  long long clen = crypto_kem_CIPHERTEXTBYTES;
  long long tlen = crypto_kem_BYTES;

  if (targeti && strcmp(targeti,".") && strcmp(targeti,mceliece_dispatch_kem_6688128_implementation(impl))) return;
  if (targetn && atol(targetn) != impl) return;
  if (impl >= 0) {
    crypto_kem_keypair = mceliece_dispatch_kem_6688128_keypair(impl);
    crypto_kem_enc = mceliece_dispatch_kem_6688128_enc(impl);
    crypto_kem_dec = mceliece_dispatch_kem_6688128_dec(impl);
    printf("kem_6688128 %lld implementation %s compiler %s\n",impl,mceliece_dispatch_kem_6688128_implementation(impl),mceliece_dispatch_kem_6688128_compiler(impl));
  } else {
    crypto_kem_keypair = mceliece_kem_6688128_keypair;
    crypto_kem_enc = mceliece_kem_6688128_enc;
    crypto_kem_dec = mceliece_kem_6688128_dec;
    printf("kem_6688128 selected implementation %s compiler %s\n",mceliece_kem_6688128_implementation(),mceliece_kem_6688128_compiler());
  }
  for (long long checksumbig = 0;checksumbig < 2;++checksumbig) {
    long long loops = checksumbig ? 64 : 8;

    checksum_clear();

    for (long long loop = 0;loop < loops;++loop) {
      int result;

      output_prepare(p2,p,plen);
      output_prepare(s2,s,slen);
      crypto_kem_keypair(p,s);
      declassify(p,plen);
      declassify(s,slen);
      checksum(p,plen);
      checksum(s,slen);
      output_compare(p2,p,plen,"crypto_kem_keypair");
      output_compare(s2,s,slen,"crypto_kem_keypair");
      output_prepare(c2,c,clen);
      output_prepare(k2,k,klen);
      memcpy(p2,p,plen);
      double_canary(p2,p,plen);
      secret(p,plen);
      result = crypto_kem_enc(c,k,p);
      declassify(&result,sizeof result);
      if (result != 0) fail("failure: crypto_kem_enc returns nonzero\n");
      declassify(p,plen);
      declassify(c,clen);
      declassify(k,klen);
      checksum(c,clen);
      checksum(k,klen);
      output_compare(c2,c,clen,"crypto_kem_enc");
      output_compare(k2,k,klen,"crypto_kem_enc");
      input_compare(p2,p,plen,"crypto_kem_enc");
      output_prepare(t2,t,tlen);
      memcpy(c2,c,clen);
      double_canary(c2,c,clen);
      memcpy(s2,s,slen);
      double_canary(s2,s,slen);
      secret(c,clen);
      secret(s,slen);
      result = crypto_kem_dec(t,c,s);
      declassify(&result,sizeof result);
      if (result != 0) fail("failure: crypto_kem_dec returns nonzero\n");
      declassify(c,clen);
      declassify(s,slen);
      declassify(t,tlen);
      if (memcmp(t,k,klen) != 0) fail("failure: crypto_kem_dec does not match k\n");
      checksum(t,tlen);
      output_compare(t2,t,tlen,"crypto_kem_dec");
      input_compare(c2,c,clen,"crypto_kem_dec");
      input_compare(s2,s,slen,"crypto_kem_dec");

      double_canary(t2,t,tlen);
      double_canary(c2,c,clen);
      double_canary(s2,s,slen);
      secret(c2,clen);
      secret(s2,slen);
      result = crypto_kem_dec(t2,c2,s2);
      declassify(&result,sizeof result);
      if (result != 0) fail("failure: crypto_kem_dec returns nonzero\n");
      declassify(c2,clen);
      declassify(s2,slen);
      declassify(t2,tlen);
      if (memcmp(t2,t,tlen) != 0) fail("failure: crypto_kem_dec is nondeterministic\n");

      double_canary(t2,t,tlen);
      double_canary(c2,c,clen);
      double_canary(s2,s,slen);
      secret(c2,clen);
      secret(s,slen);
      result = crypto_kem_dec(c2,c2,s);
      declassify(&result,sizeof result);
      if (result != 0) fail("failure: crypto_kem_dec with c=t overlap returns nonzero\n");
      declassify(c2,tlen);
      declassify(s,slen);
      if (memcmp(c2,t,tlen) != 0) fail("failure: crypto_kem_dec does not handle c=t overlap\n");
      memcpy(c2,c,clen);
      secret(c,clen);
      secret(s2,slen);
      result = crypto_kem_dec(s2,c,s2);
      declassify(&result,sizeof result);
      if (result != 0) fail("failure: crypto_kem_dec with s=t overlap returns nonzero\n");
      declassify(s2,tlen);
      declassify(c,clen);
      if (memcmp(s2,t,tlen) != 0) fail("failure: crypto_kem_dec does not handle s=t overlap\n");
      memcpy(s2,s,slen);

      c[myrandom() % clen] += 1 + (myrandom() % 255);
      if (crypto_kem_dec(t,c,s) == 0)
        checksum(t,tlen);
      else
        checksum(c,clen);
      c[myrandom() % clen] += 1 + (myrandom() % 255);
      if (crypto_kem_dec(t,c,s) == 0)
        checksum(t,tlen);
      else
        checksum(c,clen);
      c[myrandom() % clen] += 1 + (myrandom() % 255);
      if (crypto_kem_dec(t,c,s) == 0)
        checksum(t,tlen);
      else
        checksum(c,clen);
    }
    checksum_expected(kem_6688128_checksums[checksumbig]);
  }
}

static void test_kem_6688128(void)
{
  if (targeto && strcmp(targeto,"kem")) return;
  if (targetp && strcmp(targetp,"6688128")) return;
  storage_kem_6688128_p = callocplus(crypto_kem_PUBLICKEYBYTES);
  test_kem_6688128_p = (unsigned char *) aligned(storage_kem_6688128_p,crypto_kem_PUBLICKEYBYTES);
  storage_kem_6688128_s = callocplus(crypto_kem_SECRETKEYBYTES);
  test_kem_6688128_s = (unsigned char *) aligned(storage_kem_6688128_s,crypto_kem_SECRETKEYBYTES);
  storage_kem_6688128_k = callocplus(crypto_kem_BYTES);
  test_kem_6688128_k = (unsigned char *) aligned(storage_kem_6688128_k,crypto_kem_BYTES);
  storage_kem_6688128_c = callocplus(crypto_kem_CIPHERTEXTBYTES);
  test_kem_6688128_c = (unsigned char *) aligned(storage_kem_6688128_c,crypto_kem_CIPHERTEXTBYTES);
  storage_kem_6688128_t = callocplus(crypto_kem_BYTES);
  test_kem_6688128_t = (unsigned char *) aligned(storage_kem_6688128_t,crypto_kem_BYTES);
  storage_kem_6688128_p2 = callocplus(crypto_kem_PUBLICKEYBYTES);
  test_kem_6688128_p2 = (unsigned char *) aligned(storage_kem_6688128_p2,crypto_kem_PUBLICKEYBYTES);
  storage_kem_6688128_s2 = callocplus(crypto_kem_SECRETKEYBYTES);
  test_kem_6688128_s2 = (unsigned char *) aligned(storage_kem_6688128_s2,crypto_kem_SECRETKEYBYTES);
  storage_kem_6688128_k2 = callocplus(crypto_kem_BYTES);
  test_kem_6688128_k2 = (unsigned char *) aligned(storage_kem_6688128_k2,crypto_kem_BYTES);
  storage_kem_6688128_c2 = callocplus(crypto_kem_CIPHERTEXTBYTES);
  test_kem_6688128_c2 = (unsigned char *) aligned(storage_kem_6688128_c2,crypto_kem_CIPHERTEXTBYTES);
  storage_kem_6688128_t2 = callocplus(crypto_kem_BYTES);
  test_kem_6688128_t2 = (unsigned char *) aligned(storage_kem_6688128_t2,crypto_kem_BYTES);

  for (long long offset = 0;offset < 2;++offset) {
    if (targetoffset && atol(targetoffset) != offset) continue;
    if (offset && valgrind) break;
    printf("kem_6688128 offset %lld\n",offset);
    for (long long impl = -1;impl < mceliece_numimpl_kem_6688128();++impl)
      forked(test_kem_6688128_impl,impl);
    ++test_kem_6688128_p;
    ++test_kem_6688128_s;
    ++test_kem_6688128_k;
    ++test_kem_6688128_c;
    ++test_kem_6688128_t;
    ++test_kem_6688128_p2;
    ++test_kem_6688128_s2;
    ++test_kem_6688128_k2;
    ++test_kem_6688128_c2;
    ++test_kem_6688128_t2;
  }
  free(storage_kem_6688128_t2);
  free(storage_kem_6688128_c2);
  free(storage_kem_6688128_k2);
  free(storage_kem_6688128_s2);
  free(storage_kem_6688128_p2);
  free(storage_kem_6688128_t);
  free(storage_kem_6688128_c);
  free(storage_kem_6688128_k);
  free(storage_kem_6688128_s);
  free(storage_kem_6688128_p);
}
#undef crypto_kem_PUBLICKEYBYTES
#undef crypto_kem_SECRETKEYBYTES
#undef crypto_kem_CIPHERTEXTBYTES
#undef crypto_kem_BYTES

static const char *kem_6688128f_checksums[] = {
  "daec95f7a2db91986d2d1ca7312d66314149b066db0f467935ecf027aa1f4403",
  "a371ae9485120c1ea108b85723470e5b317ca4428fa01a27b3b5f33f5d924d32",
} ;

#define crypto_kem_PUBLICKEYBYTES mceliece_kem_6688128f_PUBLICKEYBYTES
#define crypto_kem_SECRETKEYBYTES mceliece_kem_6688128f_SECRETKEYBYTES
#define crypto_kem_CIPHERTEXTBYTES mceliece_kem_6688128f_CIPHERTEXTBYTES
#define crypto_kem_BYTES mceliece_kem_6688128f_BYTES

static void *storage_kem_6688128f_p;
static unsigned char *test_kem_6688128f_p;
static void *storage_kem_6688128f_s;
static unsigned char *test_kem_6688128f_s;
static void *storage_kem_6688128f_k;
static unsigned char *test_kem_6688128f_k;
static void *storage_kem_6688128f_c;
static unsigned char *test_kem_6688128f_c;
static void *storage_kem_6688128f_t;
static unsigned char *test_kem_6688128f_t;
static void *storage_kem_6688128f_p2;
static unsigned char *test_kem_6688128f_p2;
static void *storage_kem_6688128f_s2;
static unsigned char *test_kem_6688128f_s2;
static void *storage_kem_6688128f_k2;
static unsigned char *test_kem_6688128f_k2;
static void *storage_kem_6688128f_c2;
static unsigned char *test_kem_6688128f_c2;
static void *storage_kem_6688128f_t2;
static unsigned char *test_kem_6688128f_t2;

static void test_kem_6688128f_impl(long long impl)
{
  unsigned char *p = test_kem_6688128f_p;
  unsigned char *s = test_kem_6688128f_s;
  unsigned char *k = test_kem_6688128f_k;
  unsigned char *c = test_kem_6688128f_c;
  unsigned char *t = test_kem_6688128f_t;
  unsigned char *p2 = test_kem_6688128f_p2;
  unsigned char *s2 = test_kem_6688128f_s2;
  unsigned char *k2 = test_kem_6688128f_k2;
  unsigned char *c2 = test_kem_6688128f_c2;
  unsigned char *t2 = test_kem_6688128f_t2;
  long long plen = crypto_kem_PUBLICKEYBYTES;
  long long slen = crypto_kem_SECRETKEYBYTES;
  long long klen = crypto_kem_BYTES;
  long long clen = crypto_kem_CIPHERTEXTBYTES;
  long long tlen = crypto_kem_BYTES;

  if (targeti && strcmp(targeti,".") && strcmp(targeti,mceliece_dispatch_kem_6688128f_implementation(impl))) return;
  if (targetn && atol(targetn) != impl) return;
  if (impl >= 0) {
    crypto_kem_keypair = mceliece_dispatch_kem_6688128f_keypair(impl);
    crypto_kem_enc = mceliece_dispatch_kem_6688128f_enc(impl);
    crypto_kem_dec = mceliece_dispatch_kem_6688128f_dec(impl);
    printf("kem_6688128f %lld implementation %s compiler %s\n",impl,mceliece_dispatch_kem_6688128f_implementation(impl),mceliece_dispatch_kem_6688128f_compiler(impl));
  } else {
    crypto_kem_keypair = mceliece_kem_6688128f_keypair;
    crypto_kem_enc = mceliece_kem_6688128f_enc;
    crypto_kem_dec = mceliece_kem_6688128f_dec;
    printf("kem_6688128f selected implementation %s compiler %s\n",mceliece_kem_6688128f_implementation(),mceliece_kem_6688128f_compiler());
  }
  for (long long checksumbig = 0;checksumbig < 2;++checksumbig) {
    long long loops = checksumbig ? 64 : 8;

    checksum_clear();

    for (long long loop = 0;loop < loops;++loop) {
      int result;

      output_prepare(p2,p,plen);
      output_prepare(s2,s,slen);
      crypto_kem_keypair(p,s);
      declassify(p,plen);
      declassify(s,slen);
      checksum(p,plen);
      checksum(s,slen);
      output_compare(p2,p,plen,"crypto_kem_keypair");
      output_compare(s2,s,slen,"crypto_kem_keypair");
      output_prepare(c2,c,clen);
      output_prepare(k2,k,klen);
      memcpy(p2,p,plen);
      double_canary(p2,p,plen);
      secret(p,plen);
      result = crypto_kem_enc(c,k,p);
      declassify(&result,sizeof result);
      if (result != 0) fail("failure: crypto_kem_enc returns nonzero\n");
      declassify(p,plen);
      declassify(c,clen);
      declassify(k,klen);
      checksum(c,clen);
      checksum(k,klen);
      output_compare(c2,c,clen,"crypto_kem_enc");
      output_compare(k2,k,klen,"crypto_kem_enc");
      input_compare(p2,p,plen,"crypto_kem_enc");
      output_prepare(t2,t,tlen);
      memcpy(c2,c,clen);
      double_canary(c2,c,clen);
      memcpy(s2,s,slen);
      double_canary(s2,s,slen);
      secret(c,clen);
      secret(s,slen);
      result = crypto_kem_dec(t,c,s);
      declassify(&result,sizeof result);
      if (result != 0) fail("failure: crypto_kem_dec returns nonzero\n");
      declassify(c,clen);
      declassify(s,slen);
      declassify(t,tlen);
      if (memcmp(t,k,klen) != 0) fail("failure: crypto_kem_dec does not match k\n");
      checksum(t,tlen);
      output_compare(t2,t,tlen,"crypto_kem_dec");
      input_compare(c2,c,clen,"crypto_kem_dec");
      input_compare(s2,s,slen,"crypto_kem_dec");

      double_canary(t2,t,tlen);
      double_canary(c2,c,clen);
      double_canary(s2,s,slen);
      secret(c2,clen);
      secret(s2,slen);
      result = crypto_kem_dec(t2,c2,s2);
      declassify(&result,sizeof result);
      if (result != 0) fail("failure: crypto_kem_dec returns nonzero\n");
      declassify(c2,clen);
      declassify(s2,slen);
      declassify(t2,tlen);
      if (memcmp(t2,t,tlen) != 0) fail("failure: crypto_kem_dec is nondeterministic\n");

      double_canary(t2,t,tlen);
      double_canary(c2,c,clen);
      double_canary(s2,s,slen);
      secret(c2,clen);
      secret(s,slen);
      result = crypto_kem_dec(c2,c2,s);
      declassify(&result,sizeof result);
      if (result != 0) fail("failure: crypto_kem_dec with c=t overlap returns nonzero\n");
      declassify(c2,tlen);
      declassify(s,slen);
      if (memcmp(c2,t,tlen) != 0) fail("failure: crypto_kem_dec does not handle c=t overlap\n");
      memcpy(c2,c,clen);
      secret(c,clen);
      secret(s2,slen);
      result = crypto_kem_dec(s2,c,s2);
      declassify(&result,sizeof result);
      if (result != 0) fail("failure: crypto_kem_dec with s=t overlap returns nonzero\n");
      declassify(s2,tlen);
      declassify(c,clen);
      if (memcmp(s2,t,tlen) != 0) fail("failure: crypto_kem_dec does not handle s=t overlap\n");
      memcpy(s2,s,slen);

      c[myrandom() % clen] += 1 + (myrandom() % 255);
      if (crypto_kem_dec(t,c,s) == 0)
        checksum(t,tlen);
      else
        checksum(c,clen);
      c[myrandom() % clen] += 1 + (myrandom() % 255);
      if (crypto_kem_dec(t,c,s) == 0)
        checksum(t,tlen);
      else
        checksum(c,clen);
      c[myrandom() % clen] += 1 + (myrandom() % 255);
      if (crypto_kem_dec(t,c,s) == 0)
        checksum(t,tlen);
      else
        checksum(c,clen);
    }
    checksum_expected(kem_6688128f_checksums[checksumbig]);
  }
}

static void test_kem_6688128f(void)
{
  if (targeto && strcmp(targeto,"kem")) return;
  if (targetp && strcmp(targetp,"6688128f")) return;
  storage_kem_6688128f_p = callocplus(crypto_kem_PUBLICKEYBYTES);
  test_kem_6688128f_p = (unsigned char *) aligned(storage_kem_6688128f_p,crypto_kem_PUBLICKEYBYTES);
  storage_kem_6688128f_s = callocplus(crypto_kem_SECRETKEYBYTES);
  test_kem_6688128f_s = (unsigned char *) aligned(storage_kem_6688128f_s,crypto_kem_SECRETKEYBYTES);
  storage_kem_6688128f_k = callocplus(crypto_kem_BYTES);
  test_kem_6688128f_k = (unsigned char *) aligned(storage_kem_6688128f_k,crypto_kem_BYTES);
  storage_kem_6688128f_c = callocplus(crypto_kem_CIPHERTEXTBYTES);
  test_kem_6688128f_c = (unsigned char *) aligned(storage_kem_6688128f_c,crypto_kem_CIPHERTEXTBYTES);
  storage_kem_6688128f_t = callocplus(crypto_kem_BYTES);
  test_kem_6688128f_t = (unsigned char *) aligned(storage_kem_6688128f_t,crypto_kem_BYTES);
  storage_kem_6688128f_p2 = callocplus(crypto_kem_PUBLICKEYBYTES);
  test_kem_6688128f_p2 = (unsigned char *) aligned(storage_kem_6688128f_p2,crypto_kem_PUBLICKEYBYTES);
  storage_kem_6688128f_s2 = callocplus(crypto_kem_SECRETKEYBYTES);
  test_kem_6688128f_s2 = (unsigned char *) aligned(storage_kem_6688128f_s2,crypto_kem_SECRETKEYBYTES);
  storage_kem_6688128f_k2 = callocplus(crypto_kem_BYTES);
  test_kem_6688128f_k2 = (unsigned char *) aligned(storage_kem_6688128f_k2,crypto_kem_BYTES);
  storage_kem_6688128f_c2 = callocplus(crypto_kem_CIPHERTEXTBYTES);
  test_kem_6688128f_c2 = (unsigned char *) aligned(storage_kem_6688128f_c2,crypto_kem_CIPHERTEXTBYTES);
  storage_kem_6688128f_t2 = callocplus(crypto_kem_BYTES);
  test_kem_6688128f_t2 = (unsigned char *) aligned(storage_kem_6688128f_t2,crypto_kem_BYTES);

  for (long long offset = 0;offset < 2;++offset) {
    if (targetoffset && atol(targetoffset) != offset) continue;
    if (offset && valgrind) break;
    printf("kem_6688128f offset %lld\n",offset);
    for (long long impl = -1;impl < mceliece_numimpl_kem_6688128f();++impl)
      forked(test_kem_6688128f_impl,impl);
    ++test_kem_6688128f_p;
    ++test_kem_6688128f_s;
    ++test_kem_6688128f_k;
    ++test_kem_6688128f_c;
    ++test_kem_6688128f_t;
    ++test_kem_6688128f_p2;
    ++test_kem_6688128f_s2;
    ++test_kem_6688128f_k2;
    ++test_kem_6688128f_c2;
    ++test_kem_6688128f_t2;
  }
  free(storage_kem_6688128f_t2);
  free(storage_kem_6688128f_c2);
  free(storage_kem_6688128f_k2);
  free(storage_kem_6688128f_s2);
  free(storage_kem_6688128f_p2);
  free(storage_kem_6688128f_t);
  free(storage_kem_6688128f_c);
  free(storage_kem_6688128f_k);
  free(storage_kem_6688128f_s);
  free(storage_kem_6688128f_p);
}
#undef crypto_kem_PUBLICKEYBYTES
#undef crypto_kem_SECRETKEYBYTES
#undef crypto_kem_CIPHERTEXTBYTES
#undef crypto_kem_BYTES

static const char *kem_6688128pc_checksums[] = {
  "f6d44759e9e52330923b5dc2957cd080c10b31990a96e0540c52ba42017fa849",
  "53e96db3d38fe59717c537c269eddb0474e0548e964d2fbfbc1082ef03e68857",
} ;

#define crypto_kem_PUBLICKEYBYTES mceliece_kem_6688128pc_PUBLICKEYBYTES
#define crypto_kem_SECRETKEYBYTES mceliece_kem_6688128pc_SECRETKEYBYTES
#define crypto_kem_CIPHERTEXTBYTES mceliece_kem_6688128pc_CIPHERTEXTBYTES
#define crypto_kem_BYTES mceliece_kem_6688128pc_BYTES

static void *storage_kem_6688128pc_p;
static unsigned char *test_kem_6688128pc_p;
static void *storage_kem_6688128pc_s;
static unsigned char *test_kem_6688128pc_s;
static void *storage_kem_6688128pc_k;
static unsigned char *test_kem_6688128pc_k;
static void *storage_kem_6688128pc_c;
static unsigned char *test_kem_6688128pc_c;
static void *storage_kem_6688128pc_t;
static unsigned char *test_kem_6688128pc_t;
static void *storage_kem_6688128pc_p2;
static unsigned char *test_kem_6688128pc_p2;
static void *storage_kem_6688128pc_s2;
static unsigned char *test_kem_6688128pc_s2;
static void *storage_kem_6688128pc_k2;
static unsigned char *test_kem_6688128pc_k2;
static void *storage_kem_6688128pc_c2;
static unsigned char *test_kem_6688128pc_c2;
static void *storage_kem_6688128pc_t2;
static unsigned char *test_kem_6688128pc_t2;

static void test_kem_6688128pc_impl(long long impl)
{
  unsigned char *p = test_kem_6688128pc_p;
  unsigned char *s = test_kem_6688128pc_s;
  unsigned char *k = test_kem_6688128pc_k;
  unsigned char *c = test_kem_6688128pc_c;
  unsigned char *t = test_kem_6688128pc_t;
  unsigned char *p2 = test_kem_6688128pc_p2;
  unsigned char *s2 = test_kem_6688128pc_s2;
  unsigned char *k2 = test_kem_6688128pc_k2;
  unsigned char *c2 = test_kem_6688128pc_c2;
  unsigned char *t2 = test_kem_6688128pc_t2;
  long long plen = crypto_kem_PUBLICKEYBYTES;
  long long slen = crypto_kem_SECRETKEYBYTES;
  long long klen = crypto_kem_BYTES;
  long long clen = crypto_kem_CIPHERTEXTBYTES;
  long long tlen = crypto_kem_BYTES;

  if (targeti && strcmp(targeti,".") && strcmp(targeti,mceliece_dispatch_kem_6688128pc_implementation(impl))) return;
  if (targetn && atol(targetn) != impl) return;
  if (impl >= 0) {
    crypto_kem_keypair = mceliece_dispatch_kem_6688128pc_keypair(impl);
    crypto_kem_enc = mceliece_dispatch_kem_6688128pc_enc(impl);
    crypto_kem_dec = mceliece_dispatch_kem_6688128pc_dec(impl);
    printf("kem_6688128pc %lld implementation %s compiler %s\n",impl,mceliece_dispatch_kem_6688128pc_implementation(impl),mceliece_dispatch_kem_6688128pc_compiler(impl));
  } else {
    crypto_kem_keypair = mceliece_kem_6688128pc_keypair;
    crypto_kem_enc = mceliece_kem_6688128pc_enc;
    crypto_kem_dec = mceliece_kem_6688128pc_dec;
    printf("kem_6688128pc selected implementation %s compiler %s\n",mceliece_kem_6688128pc_implementation(),mceliece_kem_6688128pc_compiler());
  }
  for (long long checksumbig = 0;checksumbig < 2;++checksumbig) {
    long long loops = checksumbig ? 64 : 8;

    checksum_clear();

    for (long long loop = 0;loop < loops;++loop) {
      int result;

      output_prepare(p2,p,plen);
      output_prepare(s2,s,slen);
      crypto_kem_keypair(p,s);
      declassify(p,plen);
      declassify(s,slen);
      checksum(p,plen);
      checksum(s,slen);
      output_compare(p2,p,plen,"crypto_kem_keypair");
      output_compare(s2,s,slen,"crypto_kem_keypair");
      output_prepare(c2,c,clen);
      output_prepare(k2,k,klen);
      memcpy(p2,p,plen);
      double_canary(p2,p,plen);
      secret(p,plen);
      result = crypto_kem_enc(c,k,p);
      declassify(&result,sizeof result);
      if (result != 0) fail("failure: crypto_kem_enc returns nonzero\n");
      declassify(p,plen);
      declassify(c,clen);
      declassify(k,klen);
      checksum(c,clen);
      checksum(k,klen);
      output_compare(c2,c,clen,"crypto_kem_enc");
      output_compare(k2,k,klen,"crypto_kem_enc");
      input_compare(p2,p,plen,"crypto_kem_enc");
      output_prepare(t2,t,tlen);
      memcpy(c2,c,clen);
      double_canary(c2,c,clen);
      memcpy(s2,s,slen);
      double_canary(s2,s,slen);
      secret(c,clen);
      secret(s,slen);
      result = crypto_kem_dec(t,c,s);
      declassify(&result,sizeof result);
      if (result != 0) fail("failure: crypto_kem_dec returns nonzero\n");
      declassify(c,clen);
      declassify(s,slen);
      declassify(t,tlen);
      if (memcmp(t,k,klen) != 0) fail("failure: crypto_kem_dec does not match k\n");
      checksum(t,tlen);
      output_compare(t2,t,tlen,"crypto_kem_dec");
      input_compare(c2,c,clen,"crypto_kem_dec");
      input_compare(s2,s,slen,"crypto_kem_dec");

      double_canary(t2,t,tlen);
      double_canary(c2,c,clen);
      double_canary(s2,s,slen);
      secret(c2,clen);
      secret(s2,slen);
      result = crypto_kem_dec(t2,c2,s2);
      declassify(&result,sizeof result);
      if (result != 0) fail("failure: crypto_kem_dec returns nonzero\n");
      declassify(c2,clen);
      declassify(s2,slen);
      declassify(t2,tlen);
      if (memcmp(t2,t,tlen) != 0) fail("failure: crypto_kem_dec is nondeterministic\n");

      double_canary(t2,t,tlen);
      double_canary(c2,c,clen);
      double_canary(s2,s,slen);
      secret(c2,clen);
      secret(s,slen);
      result = crypto_kem_dec(c2,c2,s);
      declassify(&result,sizeof result);
      if (result != 0) fail("failure: crypto_kem_dec with c=t overlap returns nonzero\n");
      declassify(c2,tlen);
      declassify(s,slen);
      if (memcmp(c2,t,tlen) != 0) fail("failure: crypto_kem_dec does not handle c=t overlap\n");
      memcpy(c2,c,clen);
      secret(c,clen);
      secret(s2,slen);
      result = crypto_kem_dec(s2,c,s2);
      declassify(&result,sizeof result);
      if (result != 0) fail("failure: crypto_kem_dec with s=t overlap returns nonzero\n");
      declassify(s2,tlen);
      declassify(c,clen);
      if (memcmp(s2,t,tlen) != 0) fail("failure: crypto_kem_dec does not handle s=t overlap\n");
      memcpy(s2,s,slen);

      c[myrandom() % clen] += 1 + (myrandom() % 255);
      if (crypto_kem_dec(t,c,s) == 0)
        checksum(t,tlen);
      else
        checksum(c,clen);
      c[myrandom() % clen] += 1 + (myrandom() % 255);
      if (crypto_kem_dec(t,c,s) == 0)
        checksum(t,tlen);
      else
        checksum(c,clen);
      c[myrandom() % clen] += 1 + (myrandom() % 255);
      if (crypto_kem_dec(t,c,s) == 0)
        checksum(t,tlen);
      else
        checksum(c,clen);
    }
    checksum_expected(kem_6688128pc_checksums[checksumbig]);
  }
}

static void test_kem_6688128pc(void)
{
  if (targeto && strcmp(targeto,"kem")) return;
  if (targetp && strcmp(targetp,"6688128pc")) return;
  storage_kem_6688128pc_p = callocplus(crypto_kem_PUBLICKEYBYTES);
  test_kem_6688128pc_p = (unsigned char *) aligned(storage_kem_6688128pc_p,crypto_kem_PUBLICKEYBYTES);
  storage_kem_6688128pc_s = callocplus(crypto_kem_SECRETKEYBYTES);
  test_kem_6688128pc_s = (unsigned char *) aligned(storage_kem_6688128pc_s,crypto_kem_SECRETKEYBYTES);
  storage_kem_6688128pc_k = callocplus(crypto_kem_BYTES);
  test_kem_6688128pc_k = (unsigned char *) aligned(storage_kem_6688128pc_k,crypto_kem_BYTES);
  storage_kem_6688128pc_c = callocplus(crypto_kem_CIPHERTEXTBYTES);
  test_kem_6688128pc_c = (unsigned char *) aligned(storage_kem_6688128pc_c,crypto_kem_CIPHERTEXTBYTES);
  storage_kem_6688128pc_t = callocplus(crypto_kem_BYTES);
  test_kem_6688128pc_t = (unsigned char *) aligned(storage_kem_6688128pc_t,crypto_kem_BYTES);
  storage_kem_6688128pc_p2 = callocplus(crypto_kem_PUBLICKEYBYTES);
  test_kem_6688128pc_p2 = (unsigned char *) aligned(storage_kem_6688128pc_p2,crypto_kem_PUBLICKEYBYTES);
  storage_kem_6688128pc_s2 = callocplus(crypto_kem_SECRETKEYBYTES);
  test_kem_6688128pc_s2 = (unsigned char *) aligned(storage_kem_6688128pc_s2,crypto_kem_SECRETKEYBYTES);
  storage_kem_6688128pc_k2 = callocplus(crypto_kem_BYTES);
  test_kem_6688128pc_k2 = (unsigned char *) aligned(storage_kem_6688128pc_k2,crypto_kem_BYTES);
  storage_kem_6688128pc_c2 = callocplus(crypto_kem_CIPHERTEXTBYTES);
  test_kem_6688128pc_c2 = (unsigned char *) aligned(storage_kem_6688128pc_c2,crypto_kem_CIPHERTEXTBYTES);
  storage_kem_6688128pc_t2 = callocplus(crypto_kem_BYTES);
  test_kem_6688128pc_t2 = (unsigned char *) aligned(storage_kem_6688128pc_t2,crypto_kem_BYTES);

  for (long long offset = 0;offset < 2;++offset) {
    if (targetoffset && atol(targetoffset) != offset) continue;
    if (offset && valgrind) break;
    printf("kem_6688128pc offset %lld\n",offset);
    for (long long impl = -1;impl < mceliece_numimpl_kem_6688128pc();++impl)
      forked(test_kem_6688128pc_impl,impl);
    ++test_kem_6688128pc_p;
    ++test_kem_6688128pc_s;
    ++test_kem_6688128pc_k;
    ++test_kem_6688128pc_c;
    ++test_kem_6688128pc_t;
    ++test_kem_6688128pc_p2;
    ++test_kem_6688128pc_s2;
    ++test_kem_6688128pc_k2;
    ++test_kem_6688128pc_c2;
    ++test_kem_6688128pc_t2;
  }
  free(storage_kem_6688128pc_t2);
  free(storage_kem_6688128pc_c2);
  free(storage_kem_6688128pc_k2);
  free(storage_kem_6688128pc_s2);
  free(storage_kem_6688128pc_p2);
  free(storage_kem_6688128pc_t);
  free(storage_kem_6688128pc_c);
  free(storage_kem_6688128pc_k);
  free(storage_kem_6688128pc_s);
  free(storage_kem_6688128pc_p);
}
#undef crypto_kem_PUBLICKEYBYTES
#undef crypto_kem_SECRETKEYBYTES
#undef crypto_kem_CIPHERTEXTBYTES
#undef crypto_kem_BYTES

static const char *kem_6688128pcf_checksums[] = {
  "80e0655938457c4dcd6aa6323d60f2495efda8a2d4a13b1958e8ca8fd2e848b6",
  "a4451d736f136a43032cd4d1047b4b7494ee6d0c91d75deff011e596bdb1b3ec",
} ;

#define crypto_kem_PUBLICKEYBYTES mceliece_kem_6688128pcf_PUBLICKEYBYTES
#define crypto_kem_SECRETKEYBYTES mceliece_kem_6688128pcf_SECRETKEYBYTES
#define crypto_kem_CIPHERTEXTBYTES mceliece_kem_6688128pcf_CIPHERTEXTBYTES
#define crypto_kem_BYTES mceliece_kem_6688128pcf_BYTES

static void *storage_kem_6688128pcf_p;
static unsigned char *test_kem_6688128pcf_p;
static void *storage_kem_6688128pcf_s;
static unsigned char *test_kem_6688128pcf_s;
static void *storage_kem_6688128pcf_k;
static unsigned char *test_kem_6688128pcf_k;
static void *storage_kem_6688128pcf_c;
static unsigned char *test_kem_6688128pcf_c;
static void *storage_kem_6688128pcf_t;
static unsigned char *test_kem_6688128pcf_t;
static void *storage_kem_6688128pcf_p2;
static unsigned char *test_kem_6688128pcf_p2;
static void *storage_kem_6688128pcf_s2;
static unsigned char *test_kem_6688128pcf_s2;
static void *storage_kem_6688128pcf_k2;
static unsigned char *test_kem_6688128pcf_k2;
static void *storage_kem_6688128pcf_c2;
static unsigned char *test_kem_6688128pcf_c2;
static void *storage_kem_6688128pcf_t2;
static unsigned char *test_kem_6688128pcf_t2;

static void test_kem_6688128pcf_impl(long long impl)
{
  unsigned char *p = test_kem_6688128pcf_p;
  unsigned char *s = test_kem_6688128pcf_s;
  unsigned char *k = test_kem_6688128pcf_k;
  unsigned char *c = test_kem_6688128pcf_c;
  unsigned char *t = test_kem_6688128pcf_t;
  unsigned char *p2 = test_kem_6688128pcf_p2;
  unsigned char *s2 = test_kem_6688128pcf_s2;
  unsigned char *k2 = test_kem_6688128pcf_k2;
  unsigned char *c2 = test_kem_6688128pcf_c2;
  unsigned char *t2 = test_kem_6688128pcf_t2;
  long long plen = crypto_kem_PUBLICKEYBYTES;
  long long slen = crypto_kem_SECRETKEYBYTES;
  long long klen = crypto_kem_BYTES;
  long long clen = crypto_kem_CIPHERTEXTBYTES;
  long long tlen = crypto_kem_BYTES;

  if (targeti && strcmp(targeti,".") && strcmp(targeti,mceliece_dispatch_kem_6688128pcf_implementation(impl))) return;
  if (targetn && atol(targetn) != impl) return;
  if (impl >= 0) {
    crypto_kem_keypair = mceliece_dispatch_kem_6688128pcf_keypair(impl);
    crypto_kem_enc = mceliece_dispatch_kem_6688128pcf_enc(impl);
    crypto_kem_dec = mceliece_dispatch_kem_6688128pcf_dec(impl);
    printf("kem_6688128pcf %lld implementation %s compiler %s\n",impl,mceliece_dispatch_kem_6688128pcf_implementation(impl),mceliece_dispatch_kem_6688128pcf_compiler(impl));
  } else {
    crypto_kem_keypair = mceliece_kem_6688128pcf_keypair;
    crypto_kem_enc = mceliece_kem_6688128pcf_enc;
    crypto_kem_dec = mceliece_kem_6688128pcf_dec;
    printf("kem_6688128pcf selected implementation %s compiler %s\n",mceliece_kem_6688128pcf_implementation(),mceliece_kem_6688128pcf_compiler());
  }
  for (long long checksumbig = 0;checksumbig < 2;++checksumbig) {
    long long loops = checksumbig ? 64 : 8;

    checksum_clear();

    for (long long loop = 0;loop < loops;++loop) {
      int result;

      output_prepare(p2,p,plen);
      output_prepare(s2,s,slen);
      crypto_kem_keypair(p,s);
      declassify(p,plen);
      declassify(s,slen);
      checksum(p,plen);
      checksum(s,slen);
      output_compare(p2,p,plen,"crypto_kem_keypair");
      output_compare(s2,s,slen,"crypto_kem_keypair");
      output_prepare(c2,c,clen);
      output_prepare(k2,k,klen);
      memcpy(p2,p,plen);
      double_canary(p2,p,plen);
      secret(p,plen);
      result = crypto_kem_enc(c,k,p);
      declassify(&result,sizeof result);
      if (result != 0) fail("failure: crypto_kem_enc returns nonzero\n");
      declassify(p,plen);
      declassify(c,clen);
      declassify(k,klen);
      checksum(c,clen);
      checksum(k,klen);
      output_compare(c2,c,clen,"crypto_kem_enc");
      output_compare(k2,k,klen,"crypto_kem_enc");
      input_compare(p2,p,plen,"crypto_kem_enc");
      output_prepare(t2,t,tlen);
      memcpy(c2,c,clen);
      double_canary(c2,c,clen);
      memcpy(s2,s,slen);
      double_canary(s2,s,slen);
      secret(c,clen);
      secret(s,slen);
      result = crypto_kem_dec(t,c,s);
      declassify(&result,sizeof result);
      if (result != 0) fail("failure: crypto_kem_dec returns nonzero\n");
      declassify(c,clen);
      declassify(s,slen);
      declassify(t,tlen);
      if (memcmp(t,k,klen) != 0) fail("failure: crypto_kem_dec does not match k\n");
      checksum(t,tlen);
      output_compare(t2,t,tlen,"crypto_kem_dec");
      input_compare(c2,c,clen,"crypto_kem_dec");
      input_compare(s2,s,slen,"crypto_kem_dec");

      double_canary(t2,t,tlen);
      double_canary(c2,c,clen);
      double_canary(s2,s,slen);
      secret(c2,clen);
      secret(s2,slen);
      result = crypto_kem_dec(t2,c2,s2);
      declassify(&result,sizeof result);
      if (result != 0) fail("failure: crypto_kem_dec returns nonzero\n");
      declassify(c2,clen);
      declassify(s2,slen);
      declassify(t2,tlen);
      if (memcmp(t2,t,tlen) != 0) fail("failure: crypto_kem_dec is nondeterministic\n");

      double_canary(t2,t,tlen);
      double_canary(c2,c,clen);
      double_canary(s2,s,slen);
      secret(c2,clen);
      secret(s,slen);
      result = crypto_kem_dec(c2,c2,s);
      declassify(&result,sizeof result);
      if (result != 0) fail("failure: crypto_kem_dec with c=t overlap returns nonzero\n");
      declassify(c2,tlen);
      declassify(s,slen);
      if (memcmp(c2,t,tlen) != 0) fail("failure: crypto_kem_dec does not handle c=t overlap\n");
      memcpy(c2,c,clen);
      secret(c,clen);
      secret(s2,slen);
      result = crypto_kem_dec(s2,c,s2);
      declassify(&result,sizeof result);
      if (result != 0) fail("failure: crypto_kem_dec with s=t overlap returns nonzero\n");
      declassify(s2,tlen);
      declassify(c,clen);
      if (memcmp(s2,t,tlen) != 0) fail("failure: crypto_kem_dec does not handle s=t overlap\n");
      memcpy(s2,s,slen);

      c[myrandom() % clen] += 1 + (myrandom() % 255);
      if (crypto_kem_dec(t,c,s) == 0)
        checksum(t,tlen);
      else
        checksum(c,clen);
      c[myrandom() % clen] += 1 + (myrandom() % 255);
      if (crypto_kem_dec(t,c,s) == 0)
        checksum(t,tlen);
      else
        checksum(c,clen);
      c[myrandom() % clen] += 1 + (myrandom() % 255);
      if (crypto_kem_dec(t,c,s) == 0)
        checksum(t,tlen);
      else
        checksum(c,clen);
    }
    checksum_expected(kem_6688128pcf_checksums[checksumbig]);
  }
}

static void test_kem_6688128pcf(void)
{
  if (targeto && strcmp(targeto,"kem")) return;
  if (targetp && strcmp(targetp,"6688128pcf")) return;
  storage_kem_6688128pcf_p = callocplus(crypto_kem_PUBLICKEYBYTES);
  test_kem_6688128pcf_p = (unsigned char *) aligned(storage_kem_6688128pcf_p,crypto_kem_PUBLICKEYBYTES);
  storage_kem_6688128pcf_s = callocplus(crypto_kem_SECRETKEYBYTES);
  test_kem_6688128pcf_s = (unsigned char *) aligned(storage_kem_6688128pcf_s,crypto_kem_SECRETKEYBYTES);
  storage_kem_6688128pcf_k = callocplus(crypto_kem_BYTES);
  test_kem_6688128pcf_k = (unsigned char *) aligned(storage_kem_6688128pcf_k,crypto_kem_BYTES);
  storage_kem_6688128pcf_c = callocplus(crypto_kem_CIPHERTEXTBYTES);
  test_kem_6688128pcf_c = (unsigned char *) aligned(storage_kem_6688128pcf_c,crypto_kem_CIPHERTEXTBYTES);
  storage_kem_6688128pcf_t = callocplus(crypto_kem_BYTES);
  test_kem_6688128pcf_t = (unsigned char *) aligned(storage_kem_6688128pcf_t,crypto_kem_BYTES);
  storage_kem_6688128pcf_p2 = callocplus(crypto_kem_PUBLICKEYBYTES);
  test_kem_6688128pcf_p2 = (unsigned char *) aligned(storage_kem_6688128pcf_p2,crypto_kem_PUBLICKEYBYTES);
  storage_kem_6688128pcf_s2 = callocplus(crypto_kem_SECRETKEYBYTES);
  test_kem_6688128pcf_s2 = (unsigned char *) aligned(storage_kem_6688128pcf_s2,crypto_kem_SECRETKEYBYTES);
  storage_kem_6688128pcf_k2 = callocplus(crypto_kem_BYTES);
  test_kem_6688128pcf_k2 = (unsigned char *) aligned(storage_kem_6688128pcf_k2,crypto_kem_BYTES);
  storage_kem_6688128pcf_c2 = callocplus(crypto_kem_CIPHERTEXTBYTES);
  test_kem_6688128pcf_c2 = (unsigned char *) aligned(storage_kem_6688128pcf_c2,crypto_kem_CIPHERTEXTBYTES);
  storage_kem_6688128pcf_t2 = callocplus(crypto_kem_BYTES);
  test_kem_6688128pcf_t2 = (unsigned char *) aligned(storage_kem_6688128pcf_t2,crypto_kem_BYTES);

  for (long long offset = 0;offset < 2;++offset) {
    if (targetoffset && atol(targetoffset) != offset) continue;
    if (offset && valgrind) break;
    printf("kem_6688128pcf offset %lld\n",offset);
    for (long long impl = -1;impl < mceliece_numimpl_kem_6688128pcf();++impl)
      forked(test_kem_6688128pcf_impl,impl);
    ++test_kem_6688128pcf_p;
    ++test_kem_6688128pcf_s;
    ++test_kem_6688128pcf_k;
    ++test_kem_6688128pcf_c;
    ++test_kem_6688128pcf_t;
    ++test_kem_6688128pcf_p2;
    ++test_kem_6688128pcf_s2;
    ++test_kem_6688128pcf_k2;
    ++test_kem_6688128pcf_c2;
    ++test_kem_6688128pcf_t2;
  }
  free(storage_kem_6688128pcf_t2);
  free(storage_kem_6688128pcf_c2);
  free(storage_kem_6688128pcf_k2);
  free(storage_kem_6688128pcf_s2);
  free(storage_kem_6688128pcf_p2);
  free(storage_kem_6688128pcf_t);
  free(storage_kem_6688128pcf_c);
  free(storage_kem_6688128pcf_k);
  free(storage_kem_6688128pcf_s);
  free(storage_kem_6688128pcf_p);
}
#undef crypto_kem_PUBLICKEYBYTES
#undef crypto_kem_SECRETKEYBYTES
#undef crypto_kem_CIPHERTEXTBYTES
#undef crypto_kem_BYTES

static const char *kem_8192128_checksums[] = {
  "debad73db5027e8239b7e97d04c5a98b7521caba8ea4e58581c90efb50dd4b9e",
  "5e64e0aeb5ab566a1efbb2b1127dcbf909ee1b395945f066cd5f097a85f2e135",
} ;

#define crypto_kem_PUBLICKEYBYTES mceliece_kem_8192128_PUBLICKEYBYTES
#define crypto_kem_SECRETKEYBYTES mceliece_kem_8192128_SECRETKEYBYTES
#define crypto_kem_CIPHERTEXTBYTES mceliece_kem_8192128_CIPHERTEXTBYTES
#define crypto_kem_BYTES mceliece_kem_8192128_BYTES

static void *storage_kem_8192128_p;
static unsigned char *test_kem_8192128_p;
static void *storage_kem_8192128_s;
static unsigned char *test_kem_8192128_s;
static void *storage_kem_8192128_k;
static unsigned char *test_kem_8192128_k;
static void *storage_kem_8192128_c;
static unsigned char *test_kem_8192128_c;
static void *storage_kem_8192128_t;
static unsigned char *test_kem_8192128_t;
static void *storage_kem_8192128_p2;
static unsigned char *test_kem_8192128_p2;
static void *storage_kem_8192128_s2;
static unsigned char *test_kem_8192128_s2;
static void *storage_kem_8192128_k2;
static unsigned char *test_kem_8192128_k2;
static void *storage_kem_8192128_c2;
static unsigned char *test_kem_8192128_c2;
static void *storage_kem_8192128_t2;
static unsigned char *test_kem_8192128_t2;

static void test_kem_8192128_impl(long long impl)
{
  unsigned char *p = test_kem_8192128_p;
  unsigned char *s = test_kem_8192128_s;
  unsigned char *k = test_kem_8192128_k;
  unsigned char *c = test_kem_8192128_c;
  unsigned char *t = test_kem_8192128_t;
  unsigned char *p2 = test_kem_8192128_p2;
  unsigned char *s2 = test_kem_8192128_s2;
  unsigned char *k2 = test_kem_8192128_k2;
  unsigned char *c2 = test_kem_8192128_c2;
  unsigned char *t2 = test_kem_8192128_t2;
  long long plen = crypto_kem_PUBLICKEYBYTES;
  long long slen = crypto_kem_SECRETKEYBYTES;
  long long klen = crypto_kem_BYTES;
  long long clen = crypto_kem_CIPHERTEXTBYTES;
  long long tlen = crypto_kem_BYTES;

  if (targeti && strcmp(targeti,".") && strcmp(targeti,mceliece_dispatch_kem_8192128_implementation(impl))) return;
  if (targetn && atol(targetn) != impl) return;
  if (impl >= 0) {
    crypto_kem_keypair = mceliece_dispatch_kem_8192128_keypair(impl);
    crypto_kem_enc = mceliece_dispatch_kem_8192128_enc(impl);
    crypto_kem_dec = mceliece_dispatch_kem_8192128_dec(impl);
    printf("kem_8192128 %lld implementation %s compiler %s\n",impl,mceliece_dispatch_kem_8192128_implementation(impl),mceliece_dispatch_kem_8192128_compiler(impl));
  } else {
    crypto_kem_keypair = mceliece_kem_8192128_keypair;
    crypto_kem_enc = mceliece_kem_8192128_enc;
    crypto_kem_dec = mceliece_kem_8192128_dec;
    printf("kem_8192128 selected implementation %s compiler %s\n",mceliece_kem_8192128_implementation(),mceliece_kem_8192128_compiler());
  }
  for (long long checksumbig = 0;checksumbig < 2;++checksumbig) {
    long long loops = checksumbig ? 64 : 8;

    checksum_clear();

    for (long long loop = 0;loop < loops;++loop) {
      int result;

      output_prepare(p2,p,plen);
      output_prepare(s2,s,slen);
      crypto_kem_keypair(p,s);
      declassify(p,plen);
      declassify(s,slen);
      checksum(p,plen);
      checksum(s,slen);
      output_compare(p2,p,plen,"crypto_kem_keypair");
      output_compare(s2,s,slen,"crypto_kem_keypair");
      output_prepare(c2,c,clen);
      output_prepare(k2,k,klen);
      memcpy(p2,p,plen);
      double_canary(p2,p,plen);
      secret(p,plen);
      result = crypto_kem_enc(c,k,p);
      declassify(&result,sizeof result);
      if (result != 0) fail("failure: crypto_kem_enc returns nonzero\n");
      declassify(p,plen);
      declassify(c,clen);
      declassify(k,klen);
      checksum(c,clen);
      checksum(k,klen);
      output_compare(c2,c,clen,"crypto_kem_enc");
      output_compare(k2,k,klen,"crypto_kem_enc");
      input_compare(p2,p,plen,"crypto_kem_enc");
      output_prepare(t2,t,tlen);
      memcpy(c2,c,clen);
      double_canary(c2,c,clen);
      memcpy(s2,s,slen);
      double_canary(s2,s,slen);
      secret(c,clen);
      secret(s,slen);
      result = crypto_kem_dec(t,c,s);
      declassify(&result,sizeof result);
      if (result != 0) fail("failure: crypto_kem_dec returns nonzero\n");
      declassify(c,clen);
      declassify(s,slen);
      declassify(t,tlen);
      if (memcmp(t,k,klen) != 0) fail("failure: crypto_kem_dec does not match k\n");
      checksum(t,tlen);
      output_compare(t2,t,tlen,"crypto_kem_dec");
      input_compare(c2,c,clen,"crypto_kem_dec");
      input_compare(s2,s,slen,"crypto_kem_dec");

      double_canary(t2,t,tlen);
      double_canary(c2,c,clen);
      double_canary(s2,s,slen);
      secret(c2,clen);
      secret(s2,slen);
      result = crypto_kem_dec(t2,c2,s2);
      declassify(&result,sizeof result);
      if (result != 0) fail("failure: crypto_kem_dec returns nonzero\n");
      declassify(c2,clen);
      declassify(s2,slen);
      declassify(t2,tlen);
      if (memcmp(t2,t,tlen) != 0) fail("failure: crypto_kem_dec is nondeterministic\n");

      double_canary(t2,t,tlen);
      double_canary(c2,c,clen);
      double_canary(s2,s,slen);
      secret(c2,clen);
      secret(s,slen);
      result = crypto_kem_dec(c2,c2,s);
      declassify(&result,sizeof result);
      if (result != 0) fail("failure: crypto_kem_dec with c=t overlap returns nonzero\n");
      declassify(c2,tlen);
      declassify(s,slen);
      if (memcmp(c2,t,tlen) != 0) fail("failure: crypto_kem_dec does not handle c=t overlap\n");
      memcpy(c2,c,clen);
      secret(c,clen);
      secret(s2,slen);
      result = crypto_kem_dec(s2,c,s2);
      declassify(&result,sizeof result);
      if (result != 0) fail("failure: crypto_kem_dec with s=t overlap returns nonzero\n");
      declassify(s2,tlen);
      declassify(c,clen);
      if (memcmp(s2,t,tlen) != 0) fail("failure: crypto_kem_dec does not handle s=t overlap\n");
      memcpy(s2,s,slen);

      c[myrandom() % clen] += 1 + (myrandom() % 255);
      if (crypto_kem_dec(t,c,s) == 0)
        checksum(t,tlen);
      else
        checksum(c,clen);
      c[myrandom() % clen] += 1 + (myrandom() % 255);
      if (crypto_kem_dec(t,c,s) == 0)
        checksum(t,tlen);
      else
        checksum(c,clen);
      c[myrandom() % clen] += 1 + (myrandom() % 255);
      if (crypto_kem_dec(t,c,s) == 0)
        checksum(t,tlen);
      else
        checksum(c,clen);
    }
    checksum_expected(kem_8192128_checksums[checksumbig]);
  }
}

static void test_kem_8192128(void)
{
  if (targeto && strcmp(targeto,"kem")) return;
  if (targetp && strcmp(targetp,"8192128")) return;
  storage_kem_8192128_p = callocplus(crypto_kem_PUBLICKEYBYTES);
  test_kem_8192128_p = (unsigned char *) aligned(storage_kem_8192128_p,crypto_kem_PUBLICKEYBYTES);
  storage_kem_8192128_s = callocplus(crypto_kem_SECRETKEYBYTES);
  test_kem_8192128_s = (unsigned char *) aligned(storage_kem_8192128_s,crypto_kem_SECRETKEYBYTES);
  storage_kem_8192128_k = callocplus(crypto_kem_BYTES);
  test_kem_8192128_k = (unsigned char *) aligned(storage_kem_8192128_k,crypto_kem_BYTES);
  storage_kem_8192128_c = callocplus(crypto_kem_CIPHERTEXTBYTES);
  test_kem_8192128_c = (unsigned char *) aligned(storage_kem_8192128_c,crypto_kem_CIPHERTEXTBYTES);
  storage_kem_8192128_t = callocplus(crypto_kem_BYTES);
  test_kem_8192128_t = (unsigned char *) aligned(storage_kem_8192128_t,crypto_kem_BYTES);
  storage_kem_8192128_p2 = callocplus(crypto_kem_PUBLICKEYBYTES);
  test_kem_8192128_p2 = (unsigned char *) aligned(storage_kem_8192128_p2,crypto_kem_PUBLICKEYBYTES);
  storage_kem_8192128_s2 = callocplus(crypto_kem_SECRETKEYBYTES);
  test_kem_8192128_s2 = (unsigned char *) aligned(storage_kem_8192128_s2,crypto_kem_SECRETKEYBYTES);
  storage_kem_8192128_k2 = callocplus(crypto_kem_BYTES);
  test_kem_8192128_k2 = (unsigned char *) aligned(storage_kem_8192128_k2,crypto_kem_BYTES);
  storage_kem_8192128_c2 = callocplus(crypto_kem_CIPHERTEXTBYTES);
  test_kem_8192128_c2 = (unsigned char *) aligned(storage_kem_8192128_c2,crypto_kem_CIPHERTEXTBYTES);
  storage_kem_8192128_t2 = callocplus(crypto_kem_BYTES);
  test_kem_8192128_t2 = (unsigned char *) aligned(storage_kem_8192128_t2,crypto_kem_BYTES);

  for (long long offset = 0;offset < 2;++offset) {
    if (targetoffset && atol(targetoffset) != offset) continue;
    if (offset && valgrind) break;
    printf("kem_8192128 offset %lld\n",offset);
    for (long long impl = -1;impl < mceliece_numimpl_kem_8192128();++impl)
      forked(test_kem_8192128_impl,impl);
    ++test_kem_8192128_p;
    ++test_kem_8192128_s;
    ++test_kem_8192128_k;
    ++test_kem_8192128_c;
    ++test_kem_8192128_t;
    ++test_kem_8192128_p2;
    ++test_kem_8192128_s2;
    ++test_kem_8192128_k2;
    ++test_kem_8192128_c2;
    ++test_kem_8192128_t2;
  }
  free(storage_kem_8192128_t2);
  free(storage_kem_8192128_c2);
  free(storage_kem_8192128_k2);
  free(storage_kem_8192128_s2);
  free(storage_kem_8192128_p2);
  free(storage_kem_8192128_t);
  free(storage_kem_8192128_c);
  free(storage_kem_8192128_k);
  free(storage_kem_8192128_s);
  free(storage_kem_8192128_p);
}
#undef crypto_kem_PUBLICKEYBYTES
#undef crypto_kem_SECRETKEYBYTES
#undef crypto_kem_CIPHERTEXTBYTES
#undef crypto_kem_BYTES

static const char *kem_8192128f_checksums[] = {
  "2d50dd3ea54c764b5f79505d181c08cefc2276a28c791681cce3a45888c687cc",
  "717835d0cdf7f4e9a36a53d93116028be3ba3eb7f57bf4913303f3c2e1830900",
} ;

#define crypto_kem_PUBLICKEYBYTES mceliece_kem_8192128f_PUBLICKEYBYTES
#define crypto_kem_SECRETKEYBYTES mceliece_kem_8192128f_SECRETKEYBYTES
#define crypto_kem_CIPHERTEXTBYTES mceliece_kem_8192128f_CIPHERTEXTBYTES
#define crypto_kem_BYTES mceliece_kem_8192128f_BYTES

static void *storage_kem_8192128f_p;
static unsigned char *test_kem_8192128f_p;
static void *storage_kem_8192128f_s;
static unsigned char *test_kem_8192128f_s;
static void *storage_kem_8192128f_k;
static unsigned char *test_kem_8192128f_k;
static void *storage_kem_8192128f_c;
static unsigned char *test_kem_8192128f_c;
static void *storage_kem_8192128f_t;
static unsigned char *test_kem_8192128f_t;
static void *storage_kem_8192128f_p2;
static unsigned char *test_kem_8192128f_p2;
static void *storage_kem_8192128f_s2;
static unsigned char *test_kem_8192128f_s2;
static void *storage_kem_8192128f_k2;
static unsigned char *test_kem_8192128f_k2;
static void *storage_kem_8192128f_c2;
static unsigned char *test_kem_8192128f_c2;
static void *storage_kem_8192128f_t2;
static unsigned char *test_kem_8192128f_t2;

static void test_kem_8192128f_impl(long long impl)
{
  unsigned char *p = test_kem_8192128f_p;
  unsigned char *s = test_kem_8192128f_s;
  unsigned char *k = test_kem_8192128f_k;
  unsigned char *c = test_kem_8192128f_c;
  unsigned char *t = test_kem_8192128f_t;
  unsigned char *p2 = test_kem_8192128f_p2;
  unsigned char *s2 = test_kem_8192128f_s2;
  unsigned char *k2 = test_kem_8192128f_k2;
  unsigned char *c2 = test_kem_8192128f_c2;
  unsigned char *t2 = test_kem_8192128f_t2;
  long long plen = crypto_kem_PUBLICKEYBYTES;
  long long slen = crypto_kem_SECRETKEYBYTES;
  long long klen = crypto_kem_BYTES;
  long long clen = crypto_kem_CIPHERTEXTBYTES;
  long long tlen = crypto_kem_BYTES;

  if (targeti && strcmp(targeti,".") && strcmp(targeti,mceliece_dispatch_kem_8192128f_implementation(impl))) return;
  if (targetn && atol(targetn) != impl) return;
  if (impl >= 0) {
    crypto_kem_keypair = mceliece_dispatch_kem_8192128f_keypair(impl);
    crypto_kem_enc = mceliece_dispatch_kem_8192128f_enc(impl);
    crypto_kem_dec = mceliece_dispatch_kem_8192128f_dec(impl);
    printf("kem_8192128f %lld implementation %s compiler %s\n",impl,mceliece_dispatch_kem_8192128f_implementation(impl),mceliece_dispatch_kem_8192128f_compiler(impl));
  } else {
    crypto_kem_keypair = mceliece_kem_8192128f_keypair;
    crypto_kem_enc = mceliece_kem_8192128f_enc;
    crypto_kem_dec = mceliece_kem_8192128f_dec;
    printf("kem_8192128f selected implementation %s compiler %s\n",mceliece_kem_8192128f_implementation(),mceliece_kem_8192128f_compiler());
  }
  for (long long checksumbig = 0;checksumbig < 2;++checksumbig) {
    long long loops = checksumbig ? 64 : 8;

    checksum_clear();

    for (long long loop = 0;loop < loops;++loop) {
      int result;

      output_prepare(p2,p,plen);
      output_prepare(s2,s,slen);
      crypto_kem_keypair(p,s);
      declassify(p,plen);
      declassify(s,slen);
      checksum(p,plen);
      checksum(s,slen);
      output_compare(p2,p,plen,"crypto_kem_keypair");
      output_compare(s2,s,slen,"crypto_kem_keypair");
      output_prepare(c2,c,clen);
      output_prepare(k2,k,klen);
      memcpy(p2,p,plen);
      double_canary(p2,p,plen);
      secret(p,plen);
      result = crypto_kem_enc(c,k,p);
      declassify(&result,sizeof result);
      if (result != 0) fail("failure: crypto_kem_enc returns nonzero\n");
      declassify(p,plen);
      declassify(c,clen);
      declassify(k,klen);
      checksum(c,clen);
      checksum(k,klen);
      output_compare(c2,c,clen,"crypto_kem_enc");
      output_compare(k2,k,klen,"crypto_kem_enc");
      input_compare(p2,p,plen,"crypto_kem_enc");
      output_prepare(t2,t,tlen);
      memcpy(c2,c,clen);
      double_canary(c2,c,clen);
      memcpy(s2,s,slen);
      double_canary(s2,s,slen);
      secret(c,clen);
      secret(s,slen);
      result = crypto_kem_dec(t,c,s);
      declassify(&result,sizeof result);
      if (result != 0) fail("failure: crypto_kem_dec returns nonzero\n");
      declassify(c,clen);
      declassify(s,slen);
      declassify(t,tlen);
      if (memcmp(t,k,klen) != 0) fail("failure: crypto_kem_dec does not match k\n");
      checksum(t,tlen);
      output_compare(t2,t,tlen,"crypto_kem_dec");
      input_compare(c2,c,clen,"crypto_kem_dec");
      input_compare(s2,s,slen,"crypto_kem_dec");

      double_canary(t2,t,tlen);
      double_canary(c2,c,clen);
      double_canary(s2,s,slen);
      secret(c2,clen);
      secret(s2,slen);
      result = crypto_kem_dec(t2,c2,s2);
      declassify(&result,sizeof result);
      if (result != 0) fail("failure: crypto_kem_dec returns nonzero\n");
      declassify(c2,clen);
      declassify(s2,slen);
      declassify(t2,tlen);
      if (memcmp(t2,t,tlen) != 0) fail("failure: crypto_kem_dec is nondeterministic\n");

      double_canary(t2,t,tlen);
      double_canary(c2,c,clen);
      double_canary(s2,s,slen);
      secret(c2,clen);
      secret(s,slen);
      result = crypto_kem_dec(c2,c2,s);
      declassify(&result,sizeof result);
      if (result != 0) fail("failure: crypto_kem_dec with c=t overlap returns nonzero\n");
      declassify(c2,tlen);
      declassify(s,slen);
      if (memcmp(c2,t,tlen) != 0) fail("failure: crypto_kem_dec does not handle c=t overlap\n");
      memcpy(c2,c,clen);
      secret(c,clen);
      secret(s2,slen);
      result = crypto_kem_dec(s2,c,s2);
      declassify(&result,sizeof result);
      if (result != 0) fail("failure: crypto_kem_dec with s=t overlap returns nonzero\n");
      declassify(s2,tlen);
      declassify(c,clen);
      if (memcmp(s2,t,tlen) != 0) fail("failure: crypto_kem_dec does not handle s=t overlap\n");
      memcpy(s2,s,slen);

      c[myrandom() % clen] += 1 + (myrandom() % 255);
      if (crypto_kem_dec(t,c,s) == 0)
        checksum(t,tlen);
      else
        checksum(c,clen);
      c[myrandom() % clen] += 1 + (myrandom() % 255);
      if (crypto_kem_dec(t,c,s) == 0)
        checksum(t,tlen);
      else
        checksum(c,clen);
      c[myrandom() % clen] += 1 + (myrandom() % 255);
      if (crypto_kem_dec(t,c,s) == 0)
        checksum(t,tlen);
      else
        checksum(c,clen);
    }
    checksum_expected(kem_8192128f_checksums[checksumbig]);
  }
}

static void test_kem_8192128f(void)
{
  if (targeto && strcmp(targeto,"kem")) return;
  if (targetp && strcmp(targetp,"8192128f")) return;
  storage_kem_8192128f_p = callocplus(crypto_kem_PUBLICKEYBYTES);
  test_kem_8192128f_p = (unsigned char *) aligned(storage_kem_8192128f_p,crypto_kem_PUBLICKEYBYTES);
  storage_kem_8192128f_s = callocplus(crypto_kem_SECRETKEYBYTES);
  test_kem_8192128f_s = (unsigned char *) aligned(storage_kem_8192128f_s,crypto_kem_SECRETKEYBYTES);
  storage_kem_8192128f_k = callocplus(crypto_kem_BYTES);
  test_kem_8192128f_k = (unsigned char *) aligned(storage_kem_8192128f_k,crypto_kem_BYTES);
  storage_kem_8192128f_c = callocplus(crypto_kem_CIPHERTEXTBYTES);
  test_kem_8192128f_c = (unsigned char *) aligned(storage_kem_8192128f_c,crypto_kem_CIPHERTEXTBYTES);
  storage_kem_8192128f_t = callocplus(crypto_kem_BYTES);
  test_kem_8192128f_t = (unsigned char *) aligned(storage_kem_8192128f_t,crypto_kem_BYTES);
  storage_kem_8192128f_p2 = callocplus(crypto_kem_PUBLICKEYBYTES);
  test_kem_8192128f_p2 = (unsigned char *) aligned(storage_kem_8192128f_p2,crypto_kem_PUBLICKEYBYTES);
  storage_kem_8192128f_s2 = callocplus(crypto_kem_SECRETKEYBYTES);
  test_kem_8192128f_s2 = (unsigned char *) aligned(storage_kem_8192128f_s2,crypto_kem_SECRETKEYBYTES);
  storage_kem_8192128f_k2 = callocplus(crypto_kem_BYTES);
  test_kem_8192128f_k2 = (unsigned char *) aligned(storage_kem_8192128f_k2,crypto_kem_BYTES);
  storage_kem_8192128f_c2 = callocplus(crypto_kem_CIPHERTEXTBYTES);
  test_kem_8192128f_c2 = (unsigned char *) aligned(storage_kem_8192128f_c2,crypto_kem_CIPHERTEXTBYTES);
  storage_kem_8192128f_t2 = callocplus(crypto_kem_BYTES);
  test_kem_8192128f_t2 = (unsigned char *) aligned(storage_kem_8192128f_t2,crypto_kem_BYTES);

  for (long long offset = 0;offset < 2;++offset) {
    if (targetoffset && atol(targetoffset) != offset) continue;
    if (offset && valgrind) break;
    printf("kem_8192128f offset %lld\n",offset);
    for (long long impl = -1;impl < mceliece_numimpl_kem_8192128f();++impl)
      forked(test_kem_8192128f_impl,impl);
    ++test_kem_8192128f_p;
    ++test_kem_8192128f_s;
    ++test_kem_8192128f_k;
    ++test_kem_8192128f_c;
    ++test_kem_8192128f_t;
    ++test_kem_8192128f_p2;
    ++test_kem_8192128f_s2;
    ++test_kem_8192128f_k2;
    ++test_kem_8192128f_c2;
    ++test_kem_8192128f_t2;
  }
  free(storage_kem_8192128f_t2);
  free(storage_kem_8192128f_c2);
  free(storage_kem_8192128f_k2);
  free(storage_kem_8192128f_s2);
  free(storage_kem_8192128f_p2);
  free(storage_kem_8192128f_t);
  free(storage_kem_8192128f_c);
  free(storage_kem_8192128f_k);
  free(storage_kem_8192128f_s);
  free(storage_kem_8192128f_p);
}
#undef crypto_kem_PUBLICKEYBYTES
#undef crypto_kem_SECRETKEYBYTES
#undef crypto_kem_CIPHERTEXTBYTES
#undef crypto_kem_BYTES

static const char *kem_8192128pc_checksums[] = {
  "a9d56a17b9b870e832cddde5c5787b55ada2189992d03eb75e23e710bcb98ccd",
  "ac060fe5c1bdb9bd96bfa21ad4875cacb61f8e4eed791511020db06c65909811",
} ;

#define crypto_kem_PUBLICKEYBYTES mceliece_kem_8192128pc_PUBLICKEYBYTES
#define crypto_kem_SECRETKEYBYTES mceliece_kem_8192128pc_SECRETKEYBYTES
#define crypto_kem_CIPHERTEXTBYTES mceliece_kem_8192128pc_CIPHERTEXTBYTES
#define crypto_kem_BYTES mceliece_kem_8192128pc_BYTES

static void *storage_kem_8192128pc_p;
static unsigned char *test_kem_8192128pc_p;
static void *storage_kem_8192128pc_s;
static unsigned char *test_kem_8192128pc_s;
static void *storage_kem_8192128pc_k;
static unsigned char *test_kem_8192128pc_k;
static void *storage_kem_8192128pc_c;
static unsigned char *test_kem_8192128pc_c;
static void *storage_kem_8192128pc_t;
static unsigned char *test_kem_8192128pc_t;
static void *storage_kem_8192128pc_p2;
static unsigned char *test_kem_8192128pc_p2;
static void *storage_kem_8192128pc_s2;
static unsigned char *test_kem_8192128pc_s2;
static void *storage_kem_8192128pc_k2;
static unsigned char *test_kem_8192128pc_k2;
static void *storage_kem_8192128pc_c2;
static unsigned char *test_kem_8192128pc_c2;
static void *storage_kem_8192128pc_t2;
static unsigned char *test_kem_8192128pc_t2;

static void test_kem_8192128pc_impl(long long impl)
{
  unsigned char *p = test_kem_8192128pc_p;
  unsigned char *s = test_kem_8192128pc_s;
  unsigned char *k = test_kem_8192128pc_k;
  unsigned char *c = test_kem_8192128pc_c;
  unsigned char *t = test_kem_8192128pc_t;
  unsigned char *p2 = test_kem_8192128pc_p2;
  unsigned char *s2 = test_kem_8192128pc_s2;
  unsigned char *k2 = test_kem_8192128pc_k2;
  unsigned char *c2 = test_kem_8192128pc_c2;
  unsigned char *t2 = test_kem_8192128pc_t2;
  long long plen = crypto_kem_PUBLICKEYBYTES;
  long long slen = crypto_kem_SECRETKEYBYTES;
  long long klen = crypto_kem_BYTES;
  long long clen = crypto_kem_CIPHERTEXTBYTES;
  long long tlen = crypto_kem_BYTES;

  if (targeti && strcmp(targeti,".") && strcmp(targeti,mceliece_dispatch_kem_8192128pc_implementation(impl))) return;
  if (targetn && atol(targetn) != impl) return;
  if (impl >= 0) {
    crypto_kem_keypair = mceliece_dispatch_kem_8192128pc_keypair(impl);
    crypto_kem_enc = mceliece_dispatch_kem_8192128pc_enc(impl);
    crypto_kem_dec = mceliece_dispatch_kem_8192128pc_dec(impl);
    printf("kem_8192128pc %lld implementation %s compiler %s\n",impl,mceliece_dispatch_kem_8192128pc_implementation(impl),mceliece_dispatch_kem_8192128pc_compiler(impl));
  } else {
    crypto_kem_keypair = mceliece_kem_8192128pc_keypair;
    crypto_kem_enc = mceliece_kem_8192128pc_enc;
    crypto_kem_dec = mceliece_kem_8192128pc_dec;
    printf("kem_8192128pc selected implementation %s compiler %s\n",mceliece_kem_8192128pc_implementation(),mceliece_kem_8192128pc_compiler());
  }
  for (long long checksumbig = 0;checksumbig < 2;++checksumbig) {
    long long loops = checksumbig ? 64 : 8;

    checksum_clear();

    for (long long loop = 0;loop < loops;++loop) {
      int result;

      output_prepare(p2,p,plen);
      output_prepare(s2,s,slen);
      crypto_kem_keypair(p,s);
      declassify(p,plen);
      declassify(s,slen);
      checksum(p,plen);
      checksum(s,slen);
      output_compare(p2,p,plen,"crypto_kem_keypair");
      output_compare(s2,s,slen,"crypto_kem_keypair");
      output_prepare(c2,c,clen);
      output_prepare(k2,k,klen);
      memcpy(p2,p,plen);
      double_canary(p2,p,plen);
      secret(p,plen);
      result = crypto_kem_enc(c,k,p);
      declassify(&result,sizeof result);
      if (result != 0) fail("failure: crypto_kem_enc returns nonzero\n");
      declassify(p,plen);
      declassify(c,clen);
      declassify(k,klen);
      checksum(c,clen);
      checksum(k,klen);
      output_compare(c2,c,clen,"crypto_kem_enc");
      output_compare(k2,k,klen,"crypto_kem_enc");
      input_compare(p2,p,plen,"crypto_kem_enc");
      output_prepare(t2,t,tlen);
      memcpy(c2,c,clen);
      double_canary(c2,c,clen);
      memcpy(s2,s,slen);
      double_canary(s2,s,slen);
      secret(c,clen);
      secret(s,slen);
      result = crypto_kem_dec(t,c,s);
      declassify(&result,sizeof result);
      if (result != 0) fail("failure: crypto_kem_dec returns nonzero\n");
      declassify(c,clen);
      declassify(s,slen);
      declassify(t,tlen);
      if (memcmp(t,k,klen) != 0) fail("failure: crypto_kem_dec does not match k\n");
      checksum(t,tlen);
      output_compare(t2,t,tlen,"crypto_kem_dec");
      input_compare(c2,c,clen,"crypto_kem_dec");
      input_compare(s2,s,slen,"crypto_kem_dec");

      double_canary(t2,t,tlen);
      double_canary(c2,c,clen);
      double_canary(s2,s,slen);
      secret(c2,clen);
      secret(s2,slen);
      result = crypto_kem_dec(t2,c2,s2);
      declassify(&result,sizeof result);
      if (result != 0) fail("failure: crypto_kem_dec returns nonzero\n");
      declassify(c2,clen);
      declassify(s2,slen);
      declassify(t2,tlen);
      if (memcmp(t2,t,tlen) != 0) fail("failure: crypto_kem_dec is nondeterministic\n");

      double_canary(t2,t,tlen);
      double_canary(c2,c,clen);
      double_canary(s2,s,slen);
      secret(c2,clen);
      secret(s,slen);
      result = crypto_kem_dec(c2,c2,s);
      declassify(&result,sizeof result);
      if (result != 0) fail("failure: crypto_kem_dec with c=t overlap returns nonzero\n");
      declassify(c2,tlen);
      declassify(s,slen);
      if (memcmp(c2,t,tlen) != 0) fail("failure: crypto_kem_dec does not handle c=t overlap\n");
      memcpy(c2,c,clen);
      secret(c,clen);
      secret(s2,slen);
      result = crypto_kem_dec(s2,c,s2);
      declassify(&result,sizeof result);
      if (result != 0) fail("failure: crypto_kem_dec with s=t overlap returns nonzero\n");
      declassify(s2,tlen);
      declassify(c,clen);
      if (memcmp(s2,t,tlen) != 0) fail("failure: crypto_kem_dec does not handle s=t overlap\n");
      memcpy(s2,s,slen);

      c[myrandom() % clen] += 1 + (myrandom() % 255);
      if (crypto_kem_dec(t,c,s) == 0)
        checksum(t,tlen);
      else
        checksum(c,clen);
      c[myrandom() % clen] += 1 + (myrandom() % 255);
      if (crypto_kem_dec(t,c,s) == 0)
        checksum(t,tlen);
      else
        checksum(c,clen);
      c[myrandom() % clen] += 1 + (myrandom() % 255);
      if (crypto_kem_dec(t,c,s) == 0)
        checksum(t,tlen);
      else
        checksum(c,clen);
    }
    checksum_expected(kem_8192128pc_checksums[checksumbig]);
  }
}

static void test_kem_8192128pc(void)
{
  if (targeto && strcmp(targeto,"kem")) return;
  if (targetp && strcmp(targetp,"8192128pc")) return;
  storage_kem_8192128pc_p = callocplus(crypto_kem_PUBLICKEYBYTES);
  test_kem_8192128pc_p = (unsigned char *) aligned(storage_kem_8192128pc_p,crypto_kem_PUBLICKEYBYTES);
  storage_kem_8192128pc_s = callocplus(crypto_kem_SECRETKEYBYTES);
  test_kem_8192128pc_s = (unsigned char *) aligned(storage_kem_8192128pc_s,crypto_kem_SECRETKEYBYTES);
  storage_kem_8192128pc_k = callocplus(crypto_kem_BYTES);
  test_kem_8192128pc_k = (unsigned char *) aligned(storage_kem_8192128pc_k,crypto_kem_BYTES);
  storage_kem_8192128pc_c = callocplus(crypto_kem_CIPHERTEXTBYTES);
  test_kem_8192128pc_c = (unsigned char *) aligned(storage_kem_8192128pc_c,crypto_kem_CIPHERTEXTBYTES);
  storage_kem_8192128pc_t = callocplus(crypto_kem_BYTES);
  test_kem_8192128pc_t = (unsigned char *) aligned(storage_kem_8192128pc_t,crypto_kem_BYTES);
  storage_kem_8192128pc_p2 = callocplus(crypto_kem_PUBLICKEYBYTES);
  test_kem_8192128pc_p2 = (unsigned char *) aligned(storage_kem_8192128pc_p2,crypto_kem_PUBLICKEYBYTES);
  storage_kem_8192128pc_s2 = callocplus(crypto_kem_SECRETKEYBYTES);
  test_kem_8192128pc_s2 = (unsigned char *) aligned(storage_kem_8192128pc_s2,crypto_kem_SECRETKEYBYTES);
  storage_kem_8192128pc_k2 = callocplus(crypto_kem_BYTES);
  test_kem_8192128pc_k2 = (unsigned char *) aligned(storage_kem_8192128pc_k2,crypto_kem_BYTES);
  storage_kem_8192128pc_c2 = callocplus(crypto_kem_CIPHERTEXTBYTES);
  test_kem_8192128pc_c2 = (unsigned char *) aligned(storage_kem_8192128pc_c2,crypto_kem_CIPHERTEXTBYTES);
  storage_kem_8192128pc_t2 = callocplus(crypto_kem_BYTES);
  test_kem_8192128pc_t2 = (unsigned char *) aligned(storage_kem_8192128pc_t2,crypto_kem_BYTES);

  for (long long offset = 0;offset < 2;++offset) {
    if (targetoffset && atol(targetoffset) != offset) continue;
    if (offset && valgrind) break;
    printf("kem_8192128pc offset %lld\n",offset);
    for (long long impl = -1;impl < mceliece_numimpl_kem_8192128pc();++impl)
      forked(test_kem_8192128pc_impl,impl);
    ++test_kem_8192128pc_p;
    ++test_kem_8192128pc_s;
    ++test_kem_8192128pc_k;
    ++test_kem_8192128pc_c;
    ++test_kem_8192128pc_t;
    ++test_kem_8192128pc_p2;
    ++test_kem_8192128pc_s2;
    ++test_kem_8192128pc_k2;
    ++test_kem_8192128pc_c2;
    ++test_kem_8192128pc_t2;
  }
  free(storage_kem_8192128pc_t2);
  free(storage_kem_8192128pc_c2);
  free(storage_kem_8192128pc_k2);
  free(storage_kem_8192128pc_s2);
  free(storage_kem_8192128pc_p2);
  free(storage_kem_8192128pc_t);
  free(storage_kem_8192128pc_c);
  free(storage_kem_8192128pc_k);
  free(storage_kem_8192128pc_s);
  free(storage_kem_8192128pc_p);
}
#undef crypto_kem_PUBLICKEYBYTES
#undef crypto_kem_SECRETKEYBYTES
#undef crypto_kem_CIPHERTEXTBYTES
#undef crypto_kem_BYTES

static const char *kem_8192128pcf_checksums[] = {
  "fdf47ca26ac3e1a3ae8c2859619cce789420a4af8533ded9e1104d232bd62f5e",
  "182ec5f02250b7764c121a1b481ec6003c0897f7d772ae7d0bba226660bb99e4",
} ;

#define crypto_kem_PUBLICKEYBYTES mceliece_kem_8192128pcf_PUBLICKEYBYTES
#define crypto_kem_SECRETKEYBYTES mceliece_kem_8192128pcf_SECRETKEYBYTES
#define crypto_kem_CIPHERTEXTBYTES mceliece_kem_8192128pcf_CIPHERTEXTBYTES
#define crypto_kem_BYTES mceliece_kem_8192128pcf_BYTES

static void *storage_kem_8192128pcf_p;
static unsigned char *test_kem_8192128pcf_p;
static void *storage_kem_8192128pcf_s;
static unsigned char *test_kem_8192128pcf_s;
static void *storage_kem_8192128pcf_k;
static unsigned char *test_kem_8192128pcf_k;
static void *storage_kem_8192128pcf_c;
static unsigned char *test_kem_8192128pcf_c;
static void *storage_kem_8192128pcf_t;
static unsigned char *test_kem_8192128pcf_t;
static void *storage_kem_8192128pcf_p2;
static unsigned char *test_kem_8192128pcf_p2;
static void *storage_kem_8192128pcf_s2;
static unsigned char *test_kem_8192128pcf_s2;
static void *storage_kem_8192128pcf_k2;
static unsigned char *test_kem_8192128pcf_k2;
static void *storage_kem_8192128pcf_c2;
static unsigned char *test_kem_8192128pcf_c2;
static void *storage_kem_8192128pcf_t2;
static unsigned char *test_kem_8192128pcf_t2;

static void test_kem_8192128pcf_impl(long long impl)
{
  unsigned char *p = test_kem_8192128pcf_p;
  unsigned char *s = test_kem_8192128pcf_s;
  unsigned char *k = test_kem_8192128pcf_k;
  unsigned char *c = test_kem_8192128pcf_c;
  unsigned char *t = test_kem_8192128pcf_t;
  unsigned char *p2 = test_kem_8192128pcf_p2;
  unsigned char *s2 = test_kem_8192128pcf_s2;
  unsigned char *k2 = test_kem_8192128pcf_k2;
  unsigned char *c2 = test_kem_8192128pcf_c2;
  unsigned char *t2 = test_kem_8192128pcf_t2;
  long long plen = crypto_kem_PUBLICKEYBYTES;
  long long slen = crypto_kem_SECRETKEYBYTES;
  long long klen = crypto_kem_BYTES;
  long long clen = crypto_kem_CIPHERTEXTBYTES;
  long long tlen = crypto_kem_BYTES;

  if (targeti && strcmp(targeti,".") && strcmp(targeti,mceliece_dispatch_kem_8192128pcf_implementation(impl))) return;
  if (targetn && atol(targetn) != impl) return;
  if (impl >= 0) {
    crypto_kem_keypair = mceliece_dispatch_kem_8192128pcf_keypair(impl);
    crypto_kem_enc = mceliece_dispatch_kem_8192128pcf_enc(impl);
    crypto_kem_dec = mceliece_dispatch_kem_8192128pcf_dec(impl);
    printf("kem_8192128pcf %lld implementation %s compiler %s\n",impl,mceliece_dispatch_kem_8192128pcf_implementation(impl),mceliece_dispatch_kem_8192128pcf_compiler(impl));
  } else {
    crypto_kem_keypair = mceliece_kem_8192128pcf_keypair;
    crypto_kem_enc = mceliece_kem_8192128pcf_enc;
    crypto_kem_dec = mceliece_kem_8192128pcf_dec;
    printf("kem_8192128pcf selected implementation %s compiler %s\n",mceliece_kem_8192128pcf_implementation(),mceliece_kem_8192128pcf_compiler());
  }
  for (long long checksumbig = 0;checksumbig < 2;++checksumbig) {
    long long loops = checksumbig ? 64 : 8;

    checksum_clear();

    for (long long loop = 0;loop < loops;++loop) {
      int result;

      output_prepare(p2,p,plen);
      output_prepare(s2,s,slen);
      crypto_kem_keypair(p,s);
      declassify(p,plen);
      declassify(s,slen);
      checksum(p,plen);
      checksum(s,slen);
      output_compare(p2,p,plen,"crypto_kem_keypair");
      output_compare(s2,s,slen,"crypto_kem_keypair");
      output_prepare(c2,c,clen);
      output_prepare(k2,k,klen);
      memcpy(p2,p,plen);
      double_canary(p2,p,plen);
      secret(p,plen);
      result = crypto_kem_enc(c,k,p);
      declassify(&result,sizeof result);
      if (result != 0) fail("failure: crypto_kem_enc returns nonzero\n");
      declassify(p,plen);
      declassify(c,clen);
      declassify(k,klen);
      checksum(c,clen);
      checksum(k,klen);
      output_compare(c2,c,clen,"crypto_kem_enc");
      output_compare(k2,k,klen,"crypto_kem_enc");
      input_compare(p2,p,plen,"crypto_kem_enc");
      output_prepare(t2,t,tlen);
      memcpy(c2,c,clen);
      double_canary(c2,c,clen);
      memcpy(s2,s,slen);
      double_canary(s2,s,slen);
      secret(c,clen);
      secret(s,slen);
      result = crypto_kem_dec(t,c,s);
      declassify(&result,sizeof result);
      if (result != 0) fail("failure: crypto_kem_dec returns nonzero\n");
      declassify(c,clen);
      declassify(s,slen);
      declassify(t,tlen);
      if (memcmp(t,k,klen) != 0) fail("failure: crypto_kem_dec does not match k\n");
      checksum(t,tlen);
      output_compare(t2,t,tlen,"crypto_kem_dec");
      input_compare(c2,c,clen,"crypto_kem_dec");
      input_compare(s2,s,slen,"crypto_kem_dec");

      double_canary(t2,t,tlen);
      double_canary(c2,c,clen);
      double_canary(s2,s,slen);
      secret(c2,clen);
      secret(s2,slen);
      result = crypto_kem_dec(t2,c2,s2);
      declassify(&result,sizeof result);
      if (result != 0) fail("failure: crypto_kem_dec returns nonzero\n");
      declassify(c2,clen);
      declassify(s2,slen);
      declassify(t2,tlen);
      if (memcmp(t2,t,tlen) != 0) fail("failure: crypto_kem_dec is nondeterministic\n");

      double_canary(t2,t,tlen);
      double_canary(c2,c,clen);
      double_canary(s2,s,slen);
      secret(c2,clen);
      secret(s,slen);
      result = crypto_kem_dec(c2,c2,s);
      declassify(&result,sizeof result);
      if (result != 0) fail("failure: crypto_kem_dec with c=t overlap returns nonzero\n");
      declassify(c2,tlen);
      declassify(s,slen);
      if (memcmp(c2,t,tlen) != 0) fail("failure: crypto_kem_dec does not handle c=t overlap\n");
      memcpy(c2,c,clen);
      secret(c,clen);
      secret(s2,slen);
      result = crypto_kem_dec(s2,c,s2);
      declassify(&result,sizeof result);
      if (result != 0) fail("failure: crypto_kem_dec with s=t overlap returns nonzero\n");
      declassify(s2,tlen);
      declassify(c,clen);
      if (memcmp(s2,t,tlen) != 0) fail("failure: crypto_kem_dec does not handle s=t overlap\n");
      memcpy(s2,s,slen);

      c[myrandom() % clen] += 1 + (myrandom() % 255);
      if (crypto_kem_dec(t,c,s) == 0)
        checksum(t,tlen);
      else
        checksum(c,clen);
      c[myrandom() % clen] += 1 + (myrandom() % 255);
      if (crypto_kem_dec(t,c,s) == 0)
        checksum(t,tlen);
      else
        checksum(c,clen);
      c[myrandom() % clen] += 1 + (myrandom() % 255);
      if (crypto_kem_dec(t,c,s) == 0)
        checksum(t,tlen);
      else
        checksum(c,clen);
    }
    checksum_expected(kem_8192128pcf_checksums[checksumbig]);
  }
}

static void test_kem_8192128pcf(void)
{
  if (targeto && strcmp(targeto,"kem")) return;
  if (targetp && strcmp(targetp,"8192128pcf")) return;
  storage_kem_8192128pcf_p = callocplus(crypto_kem_PUBLICKEYBYTES);
  test_kem_8192128pcf_p = (unsigned char *) aligned(storage_kem_8192128pcf_p,crypto_kem_PUBLICKEYBYTES);
  storage_kem_8192128pcf_s = callocplus(crypto_kem_SECRETKEYBYTES);
  test_kem_8192128pcf_s = (unsigned char *) aligned(storage_kem_8192128pcf_s,crypto_kem_SECRETKEYBYTES);
  storage_kem_8192128pcf_k = callocplus(crypto_kem_BYTES);
  test_kem_8192128pcf_k = (unsigned char *) aligned(storage_kem_8192128pcf_k,crypto_kem_BYTES);
  storage_kem_8192128pcf_c = callocplus(crypto_kem_CIPHERTEXTBYTES);
  test_kem_8192128pcf_c = (unsigned char *) aligned(storage_kem_8192128pcf_c,crypto_kem_CIPHERTEXTBYTES);
  storage_kem_8192128pcf_t = callocplus(crypto_kem_BYTES);
  test_kem_8192128pcf_t = (unsigned char *) aligned(storage_kem_8192128pcf_t,crypto_kem_BYTES);
  storage_kem_8192128pcf_p2 = callocplus(crypto_kem_PUBLICKEYBYTES);
  test_kem_8192128pcf_p2 = (unsigned char *) aligned(storage_kem_8192128pcf_p2,crypto_kem_PUBLICKEYBYTES);
  storage_kem_8192128pcf_s2 = callocplus(crypto_kem_SECRETKEYBYTES);
  test_kem_8192128pcf_s2 = (unsigned char *) aligned(storage_kem_8192128pcf_s2,crypto_kem_SECRETKEYBYTES);
  storage_kem_8192128pcf_k2 = callocplus(crypto_kem_BYTES);
  test_kem_8192128pcf_k2 = (unsigned char *) aligned(storage_kem_8192128pcf_k2,crypto_kem_BYTES);
  storage_kem_8192128pcf_c2 = callocplus(crypto_kem_CIPHERTEXTBYTES);
  test_kem_8192128pcf_c2 = (unsigned char *) aligned(storage_kem_8192128pcf_c2,crypto_kem_CIPHERTEXTBYTES);
  storage_kem_8192128pcf_t2 = callocplus(crypto_kem_BYTES);
  test_kem_8192128pcf_t2 = (unsigned char *) aligned(storage_kem_8192128pcf_t2,crypto_kem_BYTES);

  for (long long offset = 0;offset < 2;++offset) {
    if (targetoffset && atol(targetoffset) != offset) continue;
    if (offset && valgrind) break;
    printf("kem_8192128pcf offset %lld\n",offset);
    for (long long impl = -1;impl < mceliece_numimpl_kem_8192128pcf();++impl)
      forked(test_kem_8192128pcf_impl,impl);
    ++test_kem_8192128pcf_p;
    ++test_kem_8192128pcf_s;
    ++test_kem_8192128pcf_k;
    ++test_kem_8192128pcf_c;
    ++test_kem_8192128pcf_t;
    ++test_kem_8192128pcf_p2;
    ++test_kem_8192128pcf_s2;
    ++test_kem_8192128pcf_k2;
    ++test_kem_8192128pcf_c2;
    ++test_kem_8192128pcf_t2;
  }
  free(storage_kem_8192128pcf_t2);
  free(storage_kem_8192128pcf_c2);
  free(storage_kem_8192128pcf_k2);
  free(storage_kem_8192128pcf_s2);
  free(storage_kem_8192128pcf_p2);
  free(storage_kem_8192128pcf_t);
  free(storage_kem_8192128pcf_c);
  free(storage_kem_8192128pcf_k);
  free(storage_kem_8192128pcf_s);
  free(storage_kem_8192128pcf_p);
}
#undef crypto_kem_PUBLICKEYBYTES
#undef crypto_kem_SECRETKEYBYTES
#undef crypto_kem_CIPHERTEXTBYTES
#undef crypto_kem_BYTES

static const char *kem_460896_checksums[] = {
  "006c110df7fd3ff1852c9096a6514855ef3e715469ecc21d5b6ba14d31057417",
  "604d5d0be1ec220a2a914735fa5469622cd1f66737cf7e0709b7eaaa1e382f66",
} ;

#define crypto_kem_PUBLICKEYBYTES mceliece_kem_460896_PUBLICKEYBYTES
#define crypto_kem_SECRETKEYBYTES mceliece_kem_460896_SECRETKEYBYTES
#define crypto_kem_CIPHERTEXTBYTES mceliece_kem_460896_CIPHERTEXTBYTES
#define crypto_kem_BYTES mceliece_kem_460896_BYTES

static void *storage_kem_460896_p;
static unsigned char *test_kem_460896_p;
static void *storage_kem_460896_s;
static unsigned char *test_kem_460896_s;
static void *storage_kem_460896_k;
static unsigned char *test_kem_460896_k;
static void *storage_kem_460896_c;
static unsigned char *test_kem_460896_c;
static void *storage_kem_460896_t;
static unsigned char *test_kem_460896_t;
static void *storage_kem_460896_p2;
static unsigned char *test_kem_460896_p2;
static void *storage_kem_460896_s2;
static unsigned char *test_kem_460896_s2;
static void *storage_kem_460896_k2;
static unsigned char *test_kem_460896_k2;
static void *storage_kem_460896_c2;
static unsigned char *test_kem_460896_c2;
static void *storage_kem_460896_t2;
static unsigned char *test_kem_460896_t2;

static void test_kem_460896_impl(long long impl)
{
  unsigned char *p = test_kem_460896_p;
  unsigned char *s = test_kem_460896_s;
  unsigned char *k = test_kem_460896_k;
  unsigned char *c = test_kem_460896_c;
  unsigned char *t = test_kem_460896_t;
  unsigned char *p2 = test_kem_460896_p2;
  unsigned char *s2 = test_kem_460896_s2;
  unsigned char *k2 = test_kem_460896_k2;
  unsigned char *c2 = test_kem_460896_c2;
  unsigned char *t2 = test_kem_460896_t2;
  long long plen = crypto_kem_PUBLICKEYBYTES;
  long long slen = crypto_kem_SECRETKEYBYTES;
  long long klen = crypto_kem_BYTES;
  long long clen = crypto_kem_CIPHERTEXTBYTES;
  long long tlen = crypto_kem_BYTES;

  if (targeti && strcmp(targeti,".") && strcmp(targeti,mceliece_dispatch_kem_460896_implementation(impl))) return;
  if (targetn && atol(targetn) != impl) return;
  if (impl >= 0) {
    crypto_kem_keypair = mceliece_dispatch_kem_460896_keypair(impl);
    crypto_kem_enc = mceliece_dispatch_kem_460896_enc(impl);
    crypto_kem_dec = mceliece_dispatch_kem_460896_dec(impl);
    printf("kem_460896 %lld implementation %s compiler %s\n",impl,mceliece_dispatch_kem_460896_implementation(impl),mceliece_dispatch_kem_460896_compiler(impl));
  } else {
    crypto_kem_keypair = mceliece_kem_460896_keypair;
    crypto_kem_enc = mceliece_kem_460896_enc;
    crypto_kem_dec = mceliece_kem_460896_dec;
    printf("kem_460896 selected implementation %s compiler %s\n",mceliece_kem_460896_implementation(),mceliece_kem_460896_compiler());
  }
  for (long long checksumbig = 0;checksumbig < 2;++checksumbig) {
    long long loops = checksumbig ? 64 : 8;

    checksum_clear();

    for (long long loop = 0;loop < loops;++loop) {
      int result;

      output_prepare(p2,p,plen);
      output_prepare(s2,s,slen);
      crypto_kem_keypair(p,s);
      declassify(p,plen);
      declassify(s,slen);
      checksum(p,plen);
      checksum(s,slen);
      output_compare(p2,p,plen,"crypto_kem_keypair");
      output_compare(s2,s,slen,"crypto_kem_keypair");
      output_prepare(c2,c,clen);
      output_prepare(k2,k,klen);
      memcpy(p2,p,plen);
      double_canary(p2,p,plen);
      secret(p,plen);
      result = crypto_kem_enc(c,k,p);
      declassify(&result,sizeof result);
      if (result != 0) fail("failure: crypto_kem_enc returns nonzero\n");
      declassify(p,plen);
      declassify(c,clen);
      declassify(k,klen);
      checksum(c,clen);
      checksum(k,klen);
      output_compare(c2,c,clen,"crypto_kem_enc");
      output_compare(k2,k,klen,"crypto_kem_enc");
      input_compare(p2,p,plen,"crypto_kem_enc");
      output_prepare(t2,t,tlen);
      memcpy(c2,c,clen);
      double_canary(c2,c,clen);
      memcpy(s2,s,slen);
      double_canary(s2,s,slen);
      secret(c,clen);
      secret(s,slen);
      result = crypto_kem_dec(t,c,s);
      declassify(&result,sizeof result);
      if (result != 0) fail("failure: crypto_kem_dec returns nonzero\n");
      declassify(c,clen);
      declassify(s,slen);
      declassify(t,tlen);
      if (memcmp(t,k,klen) != 0) fail("failure: crypto_kem_dec does not match k\n");
      checksum(t,tlen);
      output_compare(t2,t,tlen,"crypto_kem_dec");
      input_compare(c2,c,clen,"crypto_kem_dec");
      input_compare(s2,s,slen,"crypto_kem_dec");

      double_canary(t2,t,tlen);
      double_canary(c2,c,clen);
      double_canary(s2,s,slen);
      secret(c2,clen);
      secret(s2,slen);
      result = crypto_kem_dec(t2,c2,s2);
      declassify(&result,sizeof result);
      if (result != 0) fail("failure: crypto_kem_dec returns nonzero\n");
      declassify(c2,clen);
      declassify(s2,slen);
      declassify(t2,tlen);
      if (memcmp(t2,t,tlen) != 0) fail("failure: crypto_kem_dec is nondeterministic\n");

      double_canary(t2,t,tlen);
      double_canary(c2,c,clen);
      double_canary(s2,s,slen);
      secret(c2,clen);
      secret(s,slen);
      result = crypto_kem_dec(c2,c2,s);
      declassify(&result,sizeof result);
      if (result != 0) fail("failure: crypto_kem_dec with c=t overlap returns nonzero\n");
      declassify(c2,tlen);
      declassify(s,slen);
      if (memcmp(c2,t,tlen) != 0) fail("failure: crypto_kem_dec does not handle c=t overlap\n");
      memcpy(c2,c,clen);
      secret(c,clen);
      secret(s2,slen);
      result = crypto_kem_dec(s2,c,s2);
      declassify(&result,sizeof result);
      if (result != 0) fail("failure: crypto_kem_dec with s=t overlap returns nonzero\n");
      declassify(s2,tlen);
      declassify(c,clen);
      if (memcmp(s2,t,tlen) != 0) fail("failure: crypto_kem_dec does not handle s=t overlap\n");
      memcpy(s2,s,slen);

      c[myrandom() % clen] += 1 + (myrandom() % 255);
      if (crypto_kem_dec(t,c,s) == 0)
        checksum(t,tlen);
      else
        checksum(c,clen);
      c[myrandom() % clen] += 1 + (myrandom() % 255);
      if (crypto_kem_dec(t,c,s) == 0)
        checksum(t,tlen);
      else
        checksum(c,clen);
      c[myrandom() % clen] += 1 + (myrandom() % 255);
      if (crypto_kem_dec(t,c,s) == 0)
        checksum(t,tlen);
      else
        checksum(c,clen);
    }
    checksum_expected(kem_460896_checksums[checksumbig]);
  }
}

static void test_kem_460896(void)
{
  if (targeto && strcmp(targeto,"kem")) return;
  if (targetp && strcmp(targetp,"460896")) return;
  storage_kem_460896_p = callocplus(crypto_kem_PUBLICKEYBYTES);
  test_kem_460896_p = (unsigned char *) aligned(storage_kem_460896_p,crypto_kem_PUBLICKEYBYTES);
  storage_kem_460896_s = callocplus(crypto_kem_SECRETKEYBYTES);
  test_kem_460896_s = (unsigned char *) aligned(storage_kem_460896_s,crypto_kem_SECRETKEYBYTES);
  storage_kem_460896_k = callocplus(crypto_kem_BYTES);
  test_kem_460896_k = (unsigned char *) aligned(storage_kem_460896_k,crypto_kem_BYTES);
  storage_kem_460896_c = callocplus(crypto_kem_CIPHERTEXTBYTES);
  test_kem_460896_c = (unsigned char *) aligned(storage_kem_460896_c,crypto_kem_CIPHERTEXTBYTES);
  storage_kem_460896_t = callocplus(crypto_kem_BYTES);
  test_kem_460896_t = (unsigned char *) aligned(storage_kem_460896_t,crypto_kem_BYTES);
  storage_kem_460896_p2 = callocplus(crypto_kem_PUBLICKEYBYTES);
  test_kem_460896_p2 = (unsigned char *) aligned(storage_kem_460896_p2,crypto_kem_PUBLICKEYBYTES);
  storage_kem_460896_s2 = callocplus(crypto_kem_SECRETKEYBYTES);
  test_kem_460896_s2 = (unsigned char *) aligned(storage_kem_460896_s2,crypto_kem_SECRETKEYBYTES);
  storage_kem_460896_k2 = callocplus(crypto_kem_BYTES);
  test_kem_460896_k2 = (unsigned char *) aligned(storage_kem_460896_k2,crypto_kem_BYTES);
  storage_kem_460896_c2 = callocplus(crypto_kem_CIPHERTEXTBYTES);
  test_kem_460896_c2 = (unsigned char *) aligned(storage_kem_460896_c2,crypto_kem_CIPHERTEXTBYTES);
  storage_kem_460896_t2 = callocplus(crypto_kem_BYTES);
  test_kem_460896_t2 = (unsigned char *) aligned(storage_kem_460896_t2,crypto_kem_BYTES);

  for (long long offset = 0;offset < 2;++offset) {
    if (targetoffset && atol(targetoffset) != offset) continue;
    if (offset && valgrind) break;
    printf("kem_460896 offset %lld\n",offset);
    for (long long impl = -1;impl < mceliece_numimpl_kem_460896();++impl)
      forked(test_kem_460896_impl,impl);
    ++test_kem_460896_p;
    ++test_kem_460896_s;
    ++test_kem_460896_k;
    ++test_kem_460896_c;
    ++test_kem_460896_t;
    ++test_kem_460896_p2;
    ++test_kem_460896_s2;
    ++test_kem_460896_k2;
    ++test_kem_460896_c2;
    ++test_kem_460896_t2;
  }
  free(storage_kem_460896_t2);
  free(storage_kem_460896_c2);
  free(storage_kem_460896_k2);
  free(storage_kem_460896_s2);
  free(storage_kem_460896_p2);
  free(storage_kem_460896_t);
  free(storage_kem_460896_c);
  free(storage_kem_460896_k);
  free(storage_kem_460896_s);
  free(storage_kem_460896_p);
}
#undef crypto_kem_PUBLICKEYBYTES
#undef crypto_kem_SECRETKEYBYTES
#undef crypto_kem_CIPHERTEXTBYTES
#undef crypto_kem_BYTES

static const char *kem_460896f_checksums[] = {
  "1418b90ac6aa9d36bd3c42c7e8c4ba299eafa45e93a903a383041629fb47f043",
  "863b850af9436f66906c5824c32165b512352f398f32b2933c424bac34dcdd23",
} ;

#define crypto_kem_PUBLICKEYBYTES mceliece_kem_460896f_PUBLICKEYBYTES
#define crypto_kem_SECRETKEYBYTES mceliece_kem_460896f_SECRETKEYBYTES
#define crypto_kem_CIPHERTEXTBYTES mceliece_kem_460896f_CIPHERTEXTBYTES
#define crypto_kem_BYTES mceliece_kem_460896f_BYTES

static void *storage_kem_460896f_p;
static unsigned char *test_kem_460896f_p;
static void *storage_kem_460896f_s;
static unsigned char *test_kem_460896f_s;
static void *storage_kem_460896f_k;
static unsigned char *test_kem_460896f_k;
static void *storage_kem_460896f_c;
static unsigned char *test_kem_460896f_c;
static void *storage_kem_460896f_t;
static unsigned char *test_kem_460896f_t;
static void *storage_kem_460896f_p2;
static unsigned char *test_kem_460896f_p2;
static void *storage_kem_460896f_s2;
static unsigned char *test_kem_460896f_s2;
static void *storage_kem_460896f_k2;
static unsigned char *test_kem_460896f_k2;
static void *storage_kem_460896f_c2;
static unsigned char *test_kem_460896f_c2;
static void *storage_kem_460896f_t2;
static unsigned char *test_kem_460896f_t2;

static void test_kem_460896f_impl(long long impl)
{
  unsigned char *p = test_kem_460896f_p;
  unsigned char *s = test_kem_460896f_s;
  unsigned char *k = test_kem_460896f_k;
  unsigned char *c = test_kem_460896f_c;
  unsigned char *t = test_kem_460896f_t;
  unsigned char *p2 = test_kem_460896f_p2;
  unsigned char *s2 = test_kem_460896f_s2;
  unsigned char *k2 = test_kem_460896f_k2;
  unsigned char *c2 = test_kem_460896f_c2;
  unsigned char *t2 = test_kem_460896f_t2;
  long long plen = crypto_kem_PUBLICKEYBYTES;
  long long slen = crypto_kem_SECRETKEYBYTES;
  long long klen = crypto_kem_BYTES;
  long long clen = crypto_kem_CIPHERTEXTBYTES;
  long long tlen = crypto_kem_BYTES;

  if (targeti && strcmp(targeti,".") && strcmp(targeti,mceliece_dispatch_kem_460896f_implementation(impl))) return;
  if (targetn && atol(targetn) != impl) return;
  if (impl >= 0) {
    crypto_kem_keypair = mceliece_dispatch_kem_460896f_keypair(impl);
    crypto_kem_enc = mceliece_dispatch_kem_460896f_enc(impl);
    crypto_kem_dec = mceliece_dispatch_kem_460896f_dec(impl);
    printf("kem_460896f %lld implementation %s compiler %s\n",impl,mceliece_dispatch_kem_460896f_implementation(impl),mceliece_dispatch_kem_460896f_compiler(impl));
  } else {
    crypto_kem_keypair = mceliece_kem_460896f_keypair;
    crypto_kem_enc = mceliece_kem_460896f_enc;
    crypto_kem_dec = mceliece_kem_460896f_dec;
    printf("kem_460896f selected implementation %s compiler %s\n",mceliece_kem_460896f_implementation(),mceliece_kem_460896f_compiler());
  }
  for (long long checksumbig = 0;checksumbig < 2;++checksumbig) {
    long long loops = checksumbig ? 64 : 8;

    checksum_clear();

    for (long long loop = 0;loop < loops;++loop) {
      int result;

      output_prepare(p2,p,plen);
      output_prepare(s2,s,slen);
      crypto_kem_keypair(p,s);
      declassify(p,plen);
      declassify(s,slen);
      checksum(p,plen);
      checksum(s,slen);
      output_compare(p2,p,plen,"crypto_kem_keypair");
      output_compare(s2,s,slen,"crypto_kem_keypair");
      output_prepare(c2,c,clen);
      output_prepare(k2,k,klen);
      memcpy(p2,p,plen);
      double_canary(p2,p,plen);
      secret(p,plen);
      result = crypto_kem_enc(c,k,p);
      declassify(&result,sizeof result);
      if (result != 0) fail("failure: crypto_kem_enc returns nonzero\n");
      declassify(p,plen);
      declassify(c,clen);
      declassify(k,klen);
      checksum(c,clen);
      checksum(k,klen);
      output_compare(c2,c,clen,"crypto_kem_enc");
      output_compare(k2,k,klen,"crypto_kem_enc");
      input_compare(p2,p,plen,"crypto_kem_enc");
      output_prepare(t2,t,tlen);
      memcpy(c2,c,clen);
      double_canary(c2,c,clen);
      memcpy(s2,s,slen);
      double_canary(s2,s,slen);
      secret(c,clen);
      secret(s,slen);
      result = crypto_kem_dec(t,c,s);
      declassify(&result,sizeof result);
      if (result != 0) fail("failure: crypto_kem_dec returns nonzero\n");
      declassify(c,clen);
      declassify(s,slen);
      declassify(t,tlen);
      if (memcmp(t,k,klen) != 0) fail("failure: crypto_kem_dec does not match k\n");
      checksum(t,tlen);
      output_compare(t2,t,tlen,"crypto_kem_dec");
      input_compare(c2,c,clen,"crypto_kem_dec");
      input_compare(s2,s,slen,"crypto_kem_dec");

      double_canary(t2,t,tlen);
      double_canary(c2,c,clen);
      double_canary(s2,s,slen);
      secret(c2,clen);
      secret(s2,slen);
      result = crypto_kem_dec(t2,c2,s2);
      declassify(&result,sizeof result);
      if (result != 0) fail("failure: crypto_kem_dec returns nonzero\n");
      declassify(c2,clen);
      declassify(s2,slen);
      declassify(t2,tlen);
      if (memcmp(t2,t,tlen) != 0) fail("failure: crypto_kem_dec is nondeterministic\n");

      double_canary(t2,t,tlen);
      double_canary(c2,c,clen);
      double_canary(s2,s,slen);
      secret(c2,clen);
      secret(s,slen);
      result = crypto_kem_dec(c2,c2,s);
      declassify(&result,sizeof result);
      if (result != 0) fail("failure: crypto_kem_dec with c=t overlap returns nonzero\n");
      declassify(c2,tlen);
      declassify(s,slen);
      if (memcmp(c2,t,tlen) != 0) fail("failure: crypto_kem_dec does not handle c=t overlap\n");
      memcpy(c2,c,clen);
      secret(c,clen);
      secret(s2,slen);
      result = crypto_kem_dec(s2,c,s2);
      declassify(&result,sizeof result);
      if (result != 0) fail("failure: crypto_kem_dec with s=t overlap returns nonzero\n");
      declassify(s2,tlen);
      declassify(c,clen);
      if (memcmp(s2,t,tlen) != 0) fail("failure: crypto_kem_dec does not handle s=t overlap\n");
      memcpy(s2,s,slen);

      c[myrandom() % clen] += 1 + (myrandom() % 255);
      if (crypto_kem_dec(t,c,s) == 0)
        checksum(t,tlen);
      else
        checksum(c,clen);
      c[myrandom() % clen] += 1 + (myrandom() % 255);
      if (crypto_kem_dec(t,c,s) == 0)
        checksum(t,tlen);
      else
        checksum(c,clen);
      c[myrandom() % clen] += 1 + (myrandom() % 255);
      if (crypto_kem_dec(t,c,s) == 0)
        checksum(t,tlen);
      else
        checksum(c,clen);
    }
    checksum_expected(kem_460896f_checksums[checksumbig]);
  }
}

static void test_kem_460896f(void)
{
  if (targeto && strcmp(targeto,"kem")) return;
  if (targetp && strcmp(targetp,"460896f")) return;
  storage_kem_460896f_p = callocplus(crypto_kem_PUBLICKEYBYTES);
  test_kem_460896f_p = (unsigned char *) aligned(storage_kem_460896f_p,crypto_kem_PUBLICKEYBYTES);
  storage_kem_460896f_s = callocplus(crypto_kem_SECRETKEYBYTES);
  test_kem_460896f_s = (unsigned char *) aligned(storage_kem_460896f_s,crypto_kem_SECRETKEYBYTES);
  storage_kem_460896f_k = callocplus(crypto_kem_BYTES);
  test_kem_460896f_k = (unsigned char *) aligned(storage_kem_460896f_k,crypto_kem_BYTES);
  storage_kem_460896f_c = callocplus(crypto_kem_CIPHERTEXTBYTES);
  test_kem_460896f_c = (unsigned char *) aligned(storage_kem_460896f_c,crypto_kem_CIPHERTEXTBYTES);
  storage_kem_460896f_t = callocplus(crypto_kem_BYTES);
  test_kem_460896f_t = (unsigned char *) aligned(storage_kem_460896f_t,crypto_kem_BYTES);
  storage_kem_460896f_p2 = callocplus(crypto_kem_PUBLICKEYBYTES);
  test_kem_460896f_p2 = (unsigned char *) aligned(storage_kem_460896f_p2,crypto_kem_PUBLICKEYBYTES);
  storage_kem_460896f_s2 = callocplus(crypto_kem_SECRETKEYBYTES);
  test_kem_460896f_s2 = (unsigned char *) aligned(storage_kem_460896f_s2,crypto_kem_SECRETKEYBYTES);
  storage_kem_460896f_k2 = callocplus(crypto_kem_BYTES);
  test_kem_460896f_k2 = (unsigned char *) aligned(storage_kem_460896f_k2,crypto_kem_BYTES);
  storage_kem_460896f_c2 = callocplus(crypto_kem_CIPHERTEXTBYTES);
  test_kem_460896f_c2 = (unsigned char *) aligned(storage_kem_460896f_c2,crypto_kem_CIPHERTEXTBYTES);
  storage_kem_460896f_t2 = callocplus(crypto_kem_BYTES);
  test_kem_460896f_t2 = (unsigned char *) aligned(storage_kem_460896f_t2,crypto_kem_BYTES);

  for (long long offset = 0;offset < 2;++offset) {
    if (targetoffset && atol(targetoffset) != offset) continue;
    if (offset && valgrind) break;
    printf("kem_460896f offset %lld\n",offset);
    for (long long impl = -1;impl < mceliece_numimpl_kem_460896f();++impl)
      forked(test_kem_460896f_impl,impl);
    ++test_kem_460896f_p;
    ++test_kem_460896f_s;
    ++test_kem_460896f_k;
    ++test_kem_460896f_c;
    ++test_kem_460896f_t;
    ++test_kem_460896f_p2;
    ++test_kem_460896f_s2;
    ++test_kem_460896f_k2;
    ++test_kem_460896f_c2;
    ++test_kem_460896f_t2;
  }
  free(storage_kem_460896f_t2);
  free(storage_kem_460896f_c2);
  free(storage_kem_460896f_k2);
  free(storage_kem_460896f_s2);
  free(storage_kem_460896f_p2);
  free(storage_kem_460896f_t);
  free(storage_kem_460896f_c);
  free(storage_kem_460896f_k);
  free(storage_kem_460896f_s);
  free(storage_kem_460896f_p);
}
#undef crypto_kem_PUBLICKEYBYTES
#undef crypto_kem_SECRETKEYBYTES
#undef crypto_kem_CIPHERTEXTBYTES
#undef crypto_kem_BYTES

static const char *kem_460896pc_checksums[] = {
  "e27bb3f53c37eaaef460488d21750a80baf3874b0b26b23e510325e45c31c560",
  "99fe694290b1e02673ad7f1b69ce51aa94406ba23cdf77e69012f0b2fbcebaba",
} ;

#define crypto_kem_PUBLICKEYBYTES mceliece_kem_460896pc_PUBLICKEYBYTES
#define crypto_kem_SECRETKEYBYTES mceliece_kem_460896pc_SECRETKEYBYTES
#define crypto_kem_CIPHERTEXTBYTES mceliece_kem_460896pc_CIPHERTEXTBYTES
#define crypto_kem_BYTES mceliece_kem_460896pc_BYTES

static void *storage_kem_460896pc_p;
static unsigned char *test_kem_460896pc_p;
static void *storage_kem_460896pc_s;
static unsigned char *test_kem_460896pc_s;
static void *storage_kem_460896pc_k;
static unsigned char *test_kem_460896pc_k;
static void *storage_kem_460896pc_c;
static unsigned char *test_kem_460896pc_c;
static void *storage_kem_460896pc_t;
static unsigned char *test_kem_460896pc_t;
static void *storage_kem_460896pc_p2;
static unsigned char *test_kem_460896pc_p2;
static void *storage_kem_460896pc_s2;
static unsigned char *test_kem_460896pc_s2;
static void *storage_kem_460896pc_k2;
static unsigned char *test_kem_460896pc_k2;
static void *storage_kem_460896pc_c2;
static unsigned char *test_kem_460896pc_c2;
static void *storage_kem_460896pc_t2;
static unsigned char *test_kem_460896pc_t2;

static void test_kem_460896pc_impl(long long impl)
{
  unsigned char *p = test_kem_460896pc_p;
  unsigned char *s = test_kem_460896pc_s;
  unsigned char *k = test_kem_460896pc_k;
  unsigned char *c = test_kem_460896pc_c;
  unsigned char *t = test_kem_460896pc_t;
  unsigned char *p2 = test_kem_460896pc_p2;
  unsigned char *s2 = test_kem_460896pc_s2;
  unsigned char *k2 = test_kem_460896pc_k2;
  unsigned char *c2 = test_kem_460896pc_c2;
  unsigned char *t2 = test_kem_460896pc_t2;
  long long plen = crypto_kem_PUBLICKEYBYTES;
  long long slen = crypto_kem_SECRETKEYBYTES;
  long long klen = crypto_kem_BYTES;
  long long clen = crypto_kem_CIPHERTEXTBYTES;
  long long tlen = crypto_kem_BYTES;

  if (targeti && strcmp(targeti,".") && strcmp(targeti,mceliece_dispatch_kem_460896pc_implementation(impl))) return;
  if (targetn && atol(targetn) != impl) return;
  if (impl >= 0) {
    crypto_kem_keypair = mceliece_dispatch_kem_460896pc_keypair(impl);
    crypto_kem_enc = mceliece_dispatch_kem_460896pc_enc(impl);
    crypto_kem_dec = mceliece_dispatch_kem_460896pc_dec(impl);
    printf("kem_460896pc %lld implementation %s compiler %s\n",impl,mceliece_dispatch_kem_460896pc_implementation(impl),mceliece_dispatch_kem_460896pc_compiler(impl));
  } else {
    crypto_kem_keypair = mceliece_kem_460896pc_keypair;
    crypto_kem_enc = mceliece_kem_460896pc_enc;
    crypto_kem_dec = mceliece_kem_460896pc_dec;
    printf("kem_460896pc selected implementation %s compiler %s\n",mceliece_kem_460896pc_implementation(),mceliece_kem_460896pc_compiler());
  }
  for (long long checksumbig = 0;checksumbig < 2;++checksumbig) {
    long long loops = checksumbig ? 64 : 8;

    checksum_clear();

    for (long long loop = 0;loop < loops;++loop) {
      int result;

      output_prepare(p2,p,plen);
      output_prepare(s2,s,slen);
      crypto_kem_keypair(p,s);
      declassify(p,plen);
      declassify(s,slen);
      checksum(p,plen);
      checksum(s,slen);
      output_compare(p2,p,plen,"crypto_kem_keypair");
      output_compare(s2,s,slen,"crypto_kem_keypair");
      output_prepare(c2,c,clen);
      output_prepare(k2,k,klen);
      memcpy(p2,p,plen);
      double_canary(p2,p,plen);
      secret(p,plen);
      result = crypto_kem_enc(c,k,p);
      declassify(&result,sizeof result);
      if (result != 0) fail("failure: crypto_kem_enc returns nonzero\n");
      declassify(p,plen);
      declassify(c,clen);
      declassify(k,klen);
      checksum(c,clen);
      checksum(k,klen);
      output_compare(c2,c,clen,"crypto_kem_enc");
      output_compare(k2,k,klen,"crypto_kem_enc");
      input_compare(p2,p,plen,"crypto_kem_enc");
      output_prepare(t2,t,tlen);
      memcpy(c2,c,clen);
      double_canary(c2,c,clen);
      memcpy(s2,s,slen);
      double_canary(s2,s,slen);
      secret(c,clen);
      secret(s,slen);
      result = crypto_kem_dec(t,c,s);
      declassify(&result,sizeof result);
      if (result != 0) fail("failure: crypto_kem_dec returns nonzero\n");
      declassify(c,clen);
      declassify(s,slen);
      declassify(t,tlen);
      if (memcmp(t,k,klen) != 0) fail("failure: crypto_kem_dec does not match k\n");
      checksum(t,tlen);
      output_compare(t2,t,tlen,"crypto_kem_dec");
      input_compare(c2,c,clen,"crypto_kem_dec");
      input_compare(s2,s,slen,"crypto_kem_dec");

      double_canary(t2,t,tlen);
      double_canary(c2,c,clen);
      double_canary(s2,s,slen);
      secret(c2,clen);
      secret(s2,slen);
      result = crypto_kem_dec(t2,c2,s2);
      declassify(&result,sizeof result);
      if (result != 0) fail("failure: crypto_kem_dec returns nonzero\n");
      declassify(c2,clen);
      declassify(s2,slen);
      declassify(t2,tlen);
      if (memcmp(t2,t,tlen) != 0) fail("failure: crypto_kem_dec is nondeterministic\n");

      double_canary(t2,t,tlen);
      double_canary(c2,c,clen);
      double_canary(s2,s,slen);
      secret(c2,clen);
      secret(s,slen);
      result = crypto_kem_dec(c2,c2,s);
      declassify(&result,sizeof result);
      if (result != 0) fail("failure: crypto_kem_dec with c=t overlap returns nonzero\n");
      declassify(c2,tlen);
      declassify(s,slen);
      if (memcmp(c2,t,tlen) != 0) fail("failure: crypto_kem_dec does not handle c=t overlap\n");
      memcpy(c2,c,clen);
      secret(c,clen);
      secret(s2,slen);
      result = crypto_kem_dec(s2,c,s2);
      declassify(&result,sizeof result);
      if (result != 0) fail("failure: crypto_kem_dec with s=t overlap returns nonzero\n");
      declassify(s2,tlen);
      declassify(c,clen);
      if (memcmp(s2,t,tlen) != 0) fail("failure: crypto_kem_dec does not handle s=t overlap\n");
      memcpy(s2,s,slen);

      c[myrandom() % clen] += 1 + (myrandom() % 255);
      if (crypto_kem_dec(t,c,s) == 0)
        checksum(t,tlen);
      else
        checksum(c,clen);
      c[myrandom() % clen] += 1 + (myrandom() % 255);
      if (crypto_kem_dec(t,c,s) == 0)
        checksum(t,tlen);
      else
        checksum(c,clen);
      c[myrandom() % clen] += 1 + (myrandom() % 255);
      if (crypto_kem_dec(t,c,s) == 0)
        checksum(t,tlen);
      else
        checksum(c,clen);
    }
    checksum_expected(kem_460896pc_checksums[checksumbig]);
  }
}

static void test_kem_460896pc(void)
{
  if (targeto && strcmp(targeto,"kem")) return;
  if (targetp && strcmp(targetp,"460896pc")) return;
  storage_kem_460896pc_p = callocplus(crypto_kem_PUBLICKEYBYTES);
  test_kem_460896pc_p = (unsigned char *) aligned(storage_kem_460896pc_p,crypto_kem_PUBLICKEYBYTES);
  storage_kem_460896pc_s = callocplus(crypto_kem_SECRETKEYBYTES);
  test_kem_460896pc_s = (unsigned char *) aligned(storage_kem_460896pc_s,crypto_kem_SECRETKEYBYTES);
  storage_kem_460896pc_k = callocplus(crypto_kem_BYTES);
  test_kem_460896pc_k = (unsigned char *) aligned(storage_kem_460896pc_k,crypto_kem_BYTES);
  storage_kem_460896pc_c = callocplus(crypto_kem_CIPHERTEXTBYTES);
  test_kem_460896pc_c = (unsigned char *) aligned(storage_kem_460896pc_c,crypto_kem_CIPHERTEXTBYTES);
  storage_kem_460896pc_t = callocplus(crypto_kem_BYTES);
  test_kem_460896pc_t = (unsigned char *) aligned(storage_kem_460896pc_t,crypto_kem_BYTES);
  storage_kem_460896pc_p2 = callocplus(crypto_kem_PUBLICKEYBYTES);
  test_kem_460896pc_p2 = (unsigned char *) aligned(storage_kem_460896pc_p2,crypto_kem_PUBLICKEYBYTES);
  storage_kem_460896pc_s2 = callocplus(crypto_kem_SECRETKEYBYTES);
  test_kem_460896pc_s2 = (unsigned char *) aligned(storage_kem_460896pc_s2,crypto_kem_SECRETKEYBYTES);
  storage_kem_460896pc_k2 = callocplus(crypto_kem_BYTES);
  test_kem_460896pc_k2 = (unsigned char *) aligned(storage_kem_460896pc_k2,crypto_kem_BYTES);
  storage_kem_460896pc_c2 = callocplus(crypto_kem_CIPHERTEXTBYTES);
  test_kem_460896pc_c2 = (unsigned char *) aligned(storage_kem_460896pc_c2,crypto_kem_CIPHERTEXTBYTES);
  storage_kem_460896pc_t2 = callocplus(crypto_kem_BYTES);
  test_kem_460896pc_t2 = (unsigned char *) aligned(storage_kem_460896pc_t2,crypto_kem_BYTES);

  for (long long offset = 0;offset < 2;++offset) {
    if (targetoffset && atol(targetoffset) != offset) continue;
    if (offset && valgrind) break;
    printf("kem_460896pc offset %lld\n",offset);
    for (long long impl = -1;impl < mceliece_numimpl_kem_460896pc();++impl)
      forked(test_kem_460896pc_impl,impl);
    ++test_kem_460896pc_p;
    ++test_kem_460896pc_s;
    ++test_kem_460896pc_k;
    ++test_kem_460896pc_c;
    ++test_kem_460896pc_t;
    ++test_kem_460896pc_p2;
    ++test_kem_460896pc_s2;
    ++test_kem_460896pc_k2;
    ++test_kem_460896pc_c2;
    ++test_kem_460896pc_t2;
  }
  free(storage_kem_460896pc_t2);
  free(storage_kem_460896pc_c2);
  free(storage_kem_460896pc_k2);
  free(storage_kem_460896pc_s2);
  free(storage_kem_460896pc_p2);
  free(storage_kem_460896pc_t);
  free(storage_kem_460896pc_c);
  free(storage_kem_460896pc_k);
  free(storage_kem_460896pc_s);
  free(storage_kem_460896pc_p);
}
#undef crypto_kem_PUBLICKEYBYTES
#undef crypto_kem_SECRETKEYBYTES
#undef crypto_kem_CIPHERTEXTBYTES
#undef crypto_kem_BYTES

static const char *kem_460896pcf_checksums[] = {
  "1980e3f38d8258eca9d8d4300ac8dd6a6cde2f2c10c5e7b589971972531c8505",
  "063a2ecf26e027499a9f6b4e8344800819c28bf094926af1e3ec45107175ce53",
} ;

#define crypto_kem_PUBLICKEYBYTES mceliece_kem_460896pcf_PUBLICKEYBYTES
#define crypto_kem_SECRETKEYBYTES mceliece_kem_460896pcf_SECRETKEYBYTES
#define crypto_kem_CIPHERTEXTBYTES mceliece_kem_460896pcf_CIPHERTEXTBYTES
#define crypto_kem_BYTES mceliece_kem_460896pcf_BYTES

static void *storage_kem_460896pcf_p;
static unsigned char *test_kem_460896pcf_p;
static void *storage_kem_460896pcf_s;
static unsigned char *test_kem_460896pcf_s;
static void *storage_kem_460896pcf_k;
static unsigned char *test_kem_460896pcf_k;
static void *storage_kem_460896pcf_c;
static unsigned char *test_kem_460896pcf_c;
static void *storage_kem_460896pcf_t;
static unsigned char *test_kem_460896pcf_t;
static void *storage_kem_460896pcf_p2;
static unsigned char *test_kem_460896pcf_p2;
static void *storage_kem_460896pcf_s2;
static unsigned char *test_kem_460896pcf_s2;
static void *storage_kem_460896pcf_k2;
static unsigned char *test_kem_460896pcf_k2;
static void *storage_kem_460896pcf_c2;
static unsigned char *test_kem_460896pcf_c2;
static void *storage_kem_460896pcf_t2;
static unsigned char *test_kem_460896pcf_t2;

static void test_kem_460896pcf_impl(long long impl)
{
  unsigned char *p = test_kem_460896pcf_p;
  unsigned char *s = test_kem_460896pcf_s;
  unsigned char *k = test_kem_460896pcf_k;
  unsigned char *c = test_kem_460896pcf_c;
  unsigned char *t = test_kem_460896pcf_t;
  unsigned char *p2 = test_kem_460896pcf_p2;
  unsigned char *s2 = test_kem_460896pcf_s2;
  unsigned char *k2 = test_kem_460896pcf_k2;
  unsigned char *c2 = test_kem_460896pcf_c2;
  unsigned char *t2 = test_kem_460896pcf_t2;
  long long plen = crypto_kem_PUBLICKEYBYTES;
  long long slen = crypto_kem_SECRETKEYBYTES;
  long long klen = crypto_kem_BYTES;
  long long clen = crypto_kem_CIPHERTEXTBYTES;
  long long tlen = crypto_kem_BYTES;

  if (targeti && strcmp(targeti,".") && strcmp(targeti,mceliece_dispatch_kem_460896pcf_implementation(impl))) return;
  if (targetn && atol(targetn) != impl) return;
  if (impl >= 0) {
    crypto_kem_keypair = mceliece_dispatch_kem_460896pcf_keypair(impl);
    crypto_kem_enc = mceliece_dispatch_kem_460896pcf_enc(impl);
    crypto_kem_dec = mceliece_dispatch_kem_460896pcf_dec(impl);
    printf("kem_460896pcf %lld implementation %s compiler %s\n",impl,mceliece_dispatch_kem_460896pcf_implementation(impl),mceliece_dispatch_kem_460896pcf_compiler(impl));
  } else {
    crypto_kem_keypair = mceliece_kem_460896pcf_keypair;
    crypto_kem_enc = mceliece_kem_460896pcf_enc;
    crypto_kem_dec = mceliece_kem_460896pcf_dec;
    printf("kem_460896pcf selected implementation %s compiler %s\n",mceliece_kem_460896pcf_implementation(),mceliece_kem_460896pcf_compiler());
  }
  for (long long checksumbig = 0;checksumbig < 2;++checksumbig) {
    long long loops = checksumbig ? 64 : 8;

    checksum_clear();

    for (long long loop = 0;loop < loops;++loop) {
      int result;

      output_prepare(p2,p,plen);
      output_prepare(s2,s,slen);
      crypto_kem_keypair(p,s);
      declassify(p,plen);
      declassify(s,slen);
      checksum(p,plen);
      checksum(s,slen);
      output_compare(p2,p,plen,"crypto_kem_keypair");
      output_compare(s2,s,slen,"crypto_kem_keypair");
      output_prepare(c2,c,clen);
      output_prepare(k2,k,klen);
      memcpy(p2,p,plen);
      double_canary(p2,p,plen);
      secret(p,plen);
      result = crypto_kem_enc(c,k,p);
      declassify(&result,sizeof result);
      if (result != 0) fail("failure: crypto_kem_enc returns nonzero\n");
      declassify(p,plen);
      declassify(c,clen);
      declassify(k,klen);
      checksum(c,clen);
      checksum(k,klen);
      output_compare(c2,c,clen,"crypto_kem_enc");
      output_compare(k2,k,klen,"crypto_kem_enc");
      input_compare(p2,p,plen,"crypto_kem_enc");
      output_prepare(t2,t,tlen);
      memcpy(c2,c,clen);
      double_canary(c2,c,clen);
      memcpy(s2,s,slen);
      double_canary(s2,s,slen);
      secret(c,clen);
      secret(s,slen);
      result = crypto_kem_dec(t,c,s);
      declassify(&result,sizeof result);
      if (result != 0) fail("failure: crypto_kem_dec returns nonzero\n");
      declassify(c,clen);
      declassify(s,slen);
      declassify(t,tlen);
      if (memcmp(t,k,klen) != 0) fail("failure: crypto_kem_dec does not match k\n");
      checksum(t,tlen);
      output_compare(t2,t,tlen,"crypto_kem_dec");
      input_compare(c2,c,clen,"crypto_kem_dec");
      input_compare(s2,s,slen,"crypto_kem_dec");

      double_canary(t2,t,tlen);
      double_canary(c2,c,clen);
      double_canary(s2,s,slen);
      secret(c2,clen);
      secret(s2,slen);
      result = crypto_kem_dec(t2,c2,s2);
      declassify(&result,sizeof result);
      if (result != 0) fail("failure: crypto_kem_dec returns nonzero\n");
      declassify(c2,clen);
      declassify(s2,slen);
      declassify(t2,tlen);
      if (memcmp(t2,t,tlen) != 0) fail("failure: crypto_kem_dec is nondeterministic\n");

      double_canary(t2,t,tlen);
      double_canary(c2,c,clen);
      double_canary(s2,s,slen);
      secret(c2,clen);
      secret(s,slen);
      result = crypto_kem_dec(c2,c2,s);
      declassify(&result,sizeof result);
      if (result != 0) fail("failure: crypto_kem_dec with c=t overlap returns nonzero\n");
      declassify(c2,tlen);
      declassify(s,slen);
      if (memcmp(c2,t,tlen) != 0) fail("failure: crypto_kem_dec does not handle c=t overlap\n");
      memcpy(c2,c,clen);
      secret(c,clen);
      secret(s2,slen);
      result = crypto_kem_dec(s2,c,s2);
      declassify(&result,sizeof result);
      if (result != 0) fail("failure: crypto_kem_dec with s=t overlap returns nonzero\n");
      declassify(s2,tlen);
      declassify(c,clen);
      if (memcmp(s2,t,tlen) != 0) fail("failure: crypto_kem_dec does not handle s=t overlap\n");
      memcpy(s2,s,slen);

      c[myrandom() % clen] += 1 + (myrandom() % 255);
      if (crypto_kem_dec(t,c,s) == 0)
        checksum(t,tlen);
      else
        checksum(c,clen);
      c[myrandom() % clen] += 1 + (myrandom() % 255);
      if (crypto_kem_dec(t,c,s) == 0)
        checksum(t,tlen);
      else
        checksum(c,clen);
      c[myrandom() % clen] += 1 + (myrandom() % 255);
      if (crypto_kem_dec(t,c,s) == 0)
        checksum(t,tlen);
      else
        checksum(c,clen);
    }
    checksum_expected(kem_460896pcf_checksums[checksumbig]);
  }
}

static void test_kem_460896pcf(void)
{
  if (targeto && strcmp(targeto,"kem")) return;
  if (targetp && strcmp(targetp,"460896pcf")) return;
  storage_kem_460896pcf_p = callocplus(crypto_kem_PUBLICKEYBYTES);
  test_kem_460896pcf_p = (unsigned char *) aligned(storage_kem_460896pcf_p,crypto_kem_PUBLICKEYBYTES);
  storage_kem_460896pcf_s = callocplus(crypto_kem_SECRETKEYBYTES);
  test_kem_460896pcf_s = (unsigned char *) aligned(storage_kem_460896pcf_s,crypto_kem_SECRETKEYBYTES);
  storage_kem_460896pcf_k = callocplus(crypto_kem_BYTES);
  test_kem_460896pcf_k = (unsigned char *) aligned(storage_kem_460896pcf_k,crypto_kem_BYTES);
  storage_kem_460896pcf_c = callocplus(crypto_kem_CIPHERTEXTBYTES);
  test_kem_460896pcf_c = (unsigned char *) aligned(storage_kem_460896pcf_c,crypto_kem_CIPHERTEXTBYTES);
  storage_kem_460896pcf_t = callocplus(crypto_kem_BYTES);
  test_kem_460896pcf_t = (unsigned char *) aligned(storage_kem_460896pcf_t,crypto_kem_BYTES);
  storage_kem_460896pcf_p2 = callocplus(crypto_kem_PUBLICKEYBYTES);
  test_kem_460896pcf_p2 = (unsigned char *) aligned(storage_kem_460896pcf_p2,crypto_kem_PUBLICKEYBYTES);
  storage_kem_460896pcf_s2 = callocplus(crypto_kem_SECRETKEYBYTES);
  test_kem_460896pcf_s2 = (unsigned char *) aligned(storage_kem_460896pcf_s2,crypto_kem_SECRETKEYBYTES);
  storage_kem_460896pcf_k2 = callocplus(crypto_kem_BYTES);
  test_kem_460896pcf_k2 = (unsigned char *) aligned(storage_kem_460896pcf_k2,crypto_kem_BYTES);
  storage_kem_460896pcf_c2 = callocplus(crypto_kem_CIPHERTEXTBYTES);
  test_kem_460896pcf_c2 = (unsigned char *) aligned(storage_kem_460896pcf_c2,crypto_kem_CIPHERTEXTBYTES);
  storage_kem_460896pcf_t2 = callocplus(crypto_kem_BYTES);
  test_kem_460896pcf_t2 = (unsigned char *) aligned(storage_kem_460896pcf_t2,crypto_kem_BYTES);

  for (long long offset = 0;offset < 2;++offset) {
    if (targetoffset && atol(targetoffset) != offset) continue;
    if (offset && valgrind) break;
    printf("kem_460896pcf offset %lld\n",offset);
    for (long long impl = -1;impl < mceliece_numimpl_kem_460896pcf();++impl)
      forked(test_kem_460896pcf_impl,impl);
    ++test_kem_460896pcf_p;
    ++test_kem_460896pcf_s;
    ++test_kem_460896pcf_k;
    ++test_kem_460896pcf_c;
    ++test_kem_460896pcf_t;
    ++test_kem_460896pcf_p2;
    ++test_kem_460896pcf_s2;
    ++test_kem_460896pcf_k2;
    ++test_kem_460896pcf_c2;
    ++test_kem_460896pcf_t2;
  }
  free(storage_kem_460896pcf_t2);
  free(storage_kem_460896pcf_c2);
  free(storage_kem_460896pcf_k2);
  free(storage_kem_460896pcf_s2);
  free(storage_kem_460896pcf_p2);
  free(storage_kem_460896pcf_t);
  free(storage_kem_460896pcf_c);
  free(storage_kem_460896pcf_k);
  free(storage_kem_460896pcf_s);
  free(storage_kem_460896pcf_p);
}
#undef crypto_kem_PUBLICKEYBYTES
#undef crypto_kem_SECRETKEYBYTES
#undef crypto_kem_CIPHERTEXTBYTES
#undef crypto_kem_BYTES

static const char *kem_348864_checksums[] = {
  "2f36e1825115c5accc9a6ea609dec708f83be85e7fe448637bd502de50a1dd91",
  "df7965299cab8d4669eb29ebe87a2f61a539aa016a8dcda268a8cd595bf6d8da",
} ;

#define crypto_kem_PUBLICKEYBYTES mceliece_kem_348864_PUBLICKEYBYTES
#define crypto_kem_SECRETKEYBYTES mceliece_kem_348864_SECRETKEYBYTES
#define crypto_kem_CIPHERTEXTBYTES mceliece_kem_348864_CIPHERTEXTBYTES
#define crypto_kem_BYTES mceliece_kem_348864_BYTES

static void *storage_kem_348864_p;
static unsigned char *test_kem_348864_p;
static void *storage_kem_348864_s;
static unsigned char *test_kem_348864_s;
static void *storage_kem_348864_k;
static unsigned char *test_kem_348864_k;
static void *storage_kem_348864_c;
static unsigned char *test_kem_348864_c;
static void *storage_kem_348864_t;
static unsigned char *test_kem_348864_t;
static void *storage_kem_348864_p2;
static unsigned char *test_kem_348864_p2;
static void *storage_kem_348864_s2;
static unsigned char *test_kem_348864_s2;
static void *storage_kem_348864_k2;
static unsigned char *test_kem_348864_k2;
static void *storage_kem_348864_c2;
static unsigned char *test_kem_348864_c2;
static void *storage_kem_348864_t2;
static unsigned char *test_kem_348864_t2;

static void test_kem_348864_impl(long long impl)
{
  unsigned char *p = test_kem_348864_p;
  unsigned char *s = test_kem_348864_s;
  unsigned char *k = test_kem_348864_k;
  unsigned char *c = test_kem_348864_c;
  unsigned char *t = test_kem_348864_t;
  unsigned char *p2 = test_kem_348864_p2;
  unsigned char *s2 = test_kem_348864_s2;
  unsigned char *k2 = test_kem_348864_k2;
  unsigned char *c2 = test_kem_348864_c2;
  unsigned char *t2 = test_kem_348864_t2;
  long long plen = crypto_kem_PUBLICKEYBYTES;
  long long slen = crypto_kem_SECRETKEYBYTES;
  long long klen = crypto_kem_BYTES;
  long long clen = crypto_kem_CIPHERTEXTBYTES;
  long long tlen = crypto_kem_BYTES;

  if (targeti && strcmp(targeti,".") && strcmp(targeti,mceliece_dispatch_kem_348864_implementation(impl))) return;
  if (targetn && atol(targetn) != impl) return;
  if (impl >= 0) {
    crypto_kem_keypair = mceliece_dispatch_kem_348864_keypair(impl);
    crypto_kem_enc = mceliece_dispatch_kem_348864_enc(impl);
    crypto_kem_dec = mceliece_dispatch_kem_348864_dec(impl);
    printf("kem_348864 %lld implementation %s compiler %s\n",impl,mceliece_dispatch_kem_348864_implementation(impl),mceliece_dispatch_kem_348864_compiler(impl));
  } else {
    crypto_kem_keypair = mceliece_kem_348864_keypair;
    crypto_kem_enc = mceliece_kem_348864_enc;
    crypto_kem_dec = mceliece_kem_348864_dec;
    printf("kem_348864 selected implementation %s compiler %s\n",mceliece_kem_348864_implementation(),mceliece_kem_348864_compiler());
  }
  for (long long checksumbig = 0;checksumbig < 2;++checksumbig) {
    long long loops = checksumbig ? 64 : 8;

    checksum_clear();

    for (long long loop = 0;loop < loops;++loop) {
      int result;

      output_prepare(p2,p,plen);
      output_prepare(s2,s,slen);
      crypto_kem_keypair(p,s);
      declassify(p,plen);
      declassify(s,slen);
      checksum(p,plen);
      checksum(s,slen);
      output_compare(p2,p,plen,"crypto_kem_keypair");
      output_compare(s2,s,slen,"crypto_kem_keypair");
      output_prepare(c2,c,clen);
      output_prepare(k2,k,klen);
      memcpy(p2,p,plen);
      double_canary(p2,p,plen);
      secret(p,plen);
      result = crypto_kem_enc(c,k,p);
      declassify(&result,sizeof result);
      if (result != 0) fail("failure: crypto_kem_enc returns nonzero\n");
      declassify(p,plen);
      declassify(c,clen);
      declassify(k,klen);
      checksum(c,clen);
      checksum(k,klen);
      output_compare(c2,c,clen,"crypto_kem_enc");
      output_compare(k2,k,klen,"crypto_kem_enc");
      input_compare(p2,p,plen,"crypto_kem_enc");
      output_prepare(t2,t,tlen);
      memcpy(c2,c,clen);
      double_canary(c2,c,clen);
      memcpy(s2,s,slen);
      double_canary(s2,s,slen);
      secret(c,clen);
      secret(s,slen);
      result = crypto_kem_dec(t,c,s);
      declassify(&result,sizeof result);
      if (result != 0) fail("failure: crypto_kem_dec returns nonzero\n");
      declassify(c,clen);
      declassify(s,slen);
      declassify(t,tlen);
      if (memcmp(t,k,klen) != 0) fail("failure: crypto_kem_dec does not match k\n");
      checksum(t,tlen);
      output_compare(t2,t,tlen,"crypto_kem_dec");
      input_compare(c2,c,clen,"crypto_kem_dec");
      input_compare(s2,s,slen,"crypto_kem_dec");

      double_canary(t2,t,tlen);
      double_canary(c2,c,clen);
      double_canary(s2,s,slen);
      secret(c2,clen);
      secret(s2,slen);
      result = crypto_kem_dec(t2,c2,s2);
      declassify(&result,sizeof result);
      if (result != 0) fail("failure: crypto_kem_dec returns nonzero\n");
      declassify(c2,clen);
      declassify(s2,slen);
      declassify(t2,tlen);
      if (memcmp(t2,t,tlen) != 0) fail("failure: crypto_kem_dec is nondeterministic\n");

      double_canary(t2,t,tlen);
      double_canary(c2,c,clen);
      double_canary(s2,s,slen);
      secret(c2,clen);
      secret(s,slen);
      result = crypto_kem_dec(c2,c2,s);
      declassify(&result,sizeof result);
      if (result != 0) fail("failure: crypto_kem_dec with c=t overlap returns nonzero\n");
      declassify(c2,tlen);
      declassify(s,slen);
      if (memcmp(c2,t,tlen) != 0) fail("failure: crypto_kem_dec does not handle c=t overlap\n");
      memcpy(c2,c,clen);
      secret(c,clen);
      secret(s2,slen);
      result = crypto_kem_dec(s2,c,s2);
      declassify(&result,sizeof result);
      if (result != 0) fail("failure: crypto_kem_dec with s=t overlap returns nonzero\n");
      declassify(s2,tlen);
      declassify(c,clen);
      if (memcmp(s2,t,tlen) != 0) fail("failure: crypto_kem_dec does not handle s=t overlap\n");
      memcpy(s2,s,slen);

      c[myrandom() % clen] += 1 + (myrandom() % 255);
      if (crypto_kem_dec(t,c,s) == 0)
        checksum(t,tlen);
      else
        checksum(c,clen);
      c[myrandom() % clen] += 1 + (myrandom() % 255);
      if (crypto_kem_dec(t,c,s) == 0)
        checksum(t,tlen);
      else
        checksum(c,clen);
      c[myrandom() % clen] += 1 + (myrandom() % 255);
      if (crypto_kem_dec(t,c,s) == 0)
        checksum(t,tlen);
      else
        checksum(c,clen);
    }
    checksum_expected(kem_348864_checksums[checksumbig]);
  }
}

static void test_kem_348864(void)
{
  if (targeto && strcmp(targeto,"kem")) return;
  if (targetp && strcmp(targetp,"348864")) return;
  storage_kem_348864_p = callocplus(crypto_kem_PUBLICKEYBYTES);
  test_kem_348864_p = (unsigned char *) aligned(storage_kem_348864_p,crypto_kem_PUBLICKEYBYTES);
  storage_kem_348864_s = callocplus(crypto_kem_SECRETKEYBYTES);
  test_kem_348864_s = (unsigned char *) aligned(storage_kem_348864_s,crypto_kem_SECRETKEYBYTES);
  storage_kem_348864_k = callocplus(crypto_kem_BYTES);
  test_kem_348864_k = (unsigned char *) aligned(storage_kem_348864_k,crypto_kem_BYTES);
  storage_kem_348864_c = callocplus(crypto_kem_CIPHERTEXTBYTES);
  test_kem_348864_c = (unsigned char *) aligned(storage_kem_348864_c,crypto_kem_CIPHERTEXTBYTES);
  storage_kem_348864_t = callocplus(crypto_kem_BYTES);
  test_kem_348864_t = (unsigned char *) aligned(storage_kem_348864_t,crypto_kem_BYTES);
  storage_kem_348864_p2 = callocplus(crypto_kem_PUBLICKEYBYTES);
  test_kem_348864_p2 = (unsigned char *) aligned(storage_kem_348864_p2,crypto_kem_PUBLICKEYBYTES);
  storage_kem_348864_s2 = callocplus(crypto_kem_SECRETKEYBYTES);
  test_kem_348864_s2 = (unsigned char *) aligned(storage_kem_348864_s2,crypto_kem_SECRETKEYBYTES);
  storage_kem_348864_k2 = callocplus(crypto_kem_BYTES);
  test_kem_348864_k2 = (unsigned char *) aligned(storage_kem_348864_k2,crypto_kem_BYTES);
  storage_kem_348864_c2 = callocplus(crypto_kem_CIPHERTEXTBYTES);
  test_kem_348864_c2 = (unsigned char *) aligned(storage_kem_348864_c2,crypto_kem_CIPHERTEXTBYTES);
  storage_kem_348864_t2 = callocplus(crypto_kem_BYTES);
  test_kem_348864_t2 = (unsigned char *) aligned(storage_kem_348864_t2,crypto_kem_BYTES);

  for (long long offset = 0;offset < 2;++offset) {
    if (targetoffset && atol(targetoffset) != offset) continue;
    if (offset && valgrind) break;
    printf("kem_348864 offset %lld\n",offset);
    for (long long impl = -1;impl < mceliece_numimpl_kem_348864();++impl)
      forked(test_kem_348864_impl,impl);
    ++test_kem_348864_p;
    ++test_kem_348864_s;
    ++test_kem_348864_k;
    ++test_kem_348864_c;
    ++test_kem_348864_t;
    ++test_kem_348864_p2;
    ++test_kem_348864_s2;
    ++test_kem_348864_k2;
    ++test_kem_348864_c2;
    ++test_kem_348864_t2;
  }
  free(storage_kem_348864_t2);
  free(storage_kem_348864_c2);
  free(storage_kem_348864_k2);
  free(storage_kem_348864_s2);
  free(storage_kem_348864_p2);
  free(storage_kem_348864_t);
  free(storage_kem_348864_c);
  free(storage_kem_348864_k);
  free(storage_kem_348864_s);
  free(storage_kem_348864_p);
}
#undef crypto_kem_PUBLICKEYBYTES
#undef crypto_kem_SECRETKEYBYTES
#undef crypto_kem_CIPHERTEXTBYTES
#undef crypto_kem_BYTES

static const char *kem_348864f_checksums[] = {
  "5ad76eff6b5ccaedc1615e9795880cfd79b44c4247db4b8a13684c507a5db437",
  "471a096310df17d7650c5d1a2e798909598b3b16652c70eb722be84673cf2f8f",
} ;

#define crypto_kem_PUBLICKEYBYTES mceliece_kem_348864f_PUBLICKEYBYTES
#define crypto_kem_SECRETKEYBYTES mceliece_kem_348864f_SECRETKEYBYTES
#define crypto_kem_CIPHERTEXTBYTES mceliece_kem_348864f_CIPHERTEXTBYTES
#define crypto_kem_BYTES mceliece_kem_348864f_BYTES

static void *storage_kem_348864f_p;
static unsigned char *test_kem_348864f_p;
static void *storage_kem_348864f_s;
static unsigned char *test_kem_348864f_s;
static void *storage_kem_348864f_k;
static unsigned char *test_kem_348864f_k;
static void *storage_kem_348864f_c;
static unsigned char *test_kem_348864f_c;
static void *storage_kem_348864f_t;
static unsigned char *test_kem_348864f_t;
static void *storage_kem_348864f_p2;
static unsigned char *test_kem_348864f_p2;
static void *storage_kem_348864f_s2;
static unsigned char *test_kem_348864f_s2;
static void *storage_kem_348864f_k2;
static unsigned char *test_kem_348864f_k2;
static void *storage_kem_348864f_c2;
static unsigned char *test_kem_348864f_c2;
static void *storage_kem_348864f_t2;
static unsigned char *test_kem_348864f_t2;

static void test_kem_348864f_impl(long long impl)
{
  unsigned char *p = test_kem_348864f_p;
  unsigned char *s = test_kem_348864f_s;
  unsigned char *k = test_kem_348864f_k;
  unsigned char *c = test_kem_348864f_c;
  unsigned char *t = test_kem_348864f_t;
  unsigned char *p2 = test_kem_348864f_p2;
  unsigned char *s2 = test_kem_348864f_s2;
  unsigned char *k2 = test_kem_348864f_k2;
  unsigned char *c2 = test_kem_348864f_c2;
  unsigned char *t2 = test_kem_348864f_t2;
  long long plen = crypto_kem_PUBLICKEYBYTES;
  long long slen = crypto_kem_SECRETKEYBYTES;
  long long klen = crypto_kem_BYTES;
  long long clen = crypto_kem_CIPHERTEXTBYTES;
  long long tlen = crypto_kem_BYTES;

  if (targeti && strcmp(targeti,".") && strcmp(targeti,mceliece_dispatch_kem_348864f_implementation(impl))) return;
  if (targetn && atol(targetn) != impl) return;
  if (impl >= 0) {
    crypto_kem_keypair = mceliece_dispatch_kem_348864f_keypair(impl);
    crypto_kem_enc = mceliece_dispatch_kem_348864f_enc(impl);
    crypto_kem_dec = mceliece_dispatch_kem_348864f_dec(impl);
    printf("kem_348864f %lld implementation %s compiler %s\n",impl,mceliece_dispatch_kem_348864f_implementation(impl),mceliece_dispatch_kem_348864f_compiler(impl));
  } else {
    crypto_kem_keypair = mceliece_kem_348864f_keypair;
    crypto_kem_enc = mceliece_kem_348864f_enc;
    crypto_kem_dec = mceliece_kem_348864f_dec;
    printf("kem_348864f selected implementation %s compiler %s\n",mceliece_kem_348864f_implementation(),mceliece_kem_348864f_compiler());
  }
  for (long long checksumbig = 0;checksumbig < 2;++checksumbig) {
    long long loops = checksumbig ? 64 : 8;

    checksum_clear();

    for (long long loop = 0;loop < loops;++loop) {
      int result;

      output_prepare(p2,p,plen);
      output_prepare(s2,s,slen);
      crypto_kem_keypair(p,s);
      declassify(p,plen);
      declassify(s,slen);
      checksum(p,plen);
      checksum(s,slen);
      output_compare(p2,p,plen,"crypto_kem_keypair");
      output_compare(s2,s,slen,"crypto_kem_keypair");
      output_prepare(c2,c,clen);
      output_prepare(k2,k,klen);
      memcpy(p2,p,plen);
      double_canary(p2,p,plen);
      secret(p,plen);
      result = crypto_kem_enc(c,k,p);
      declassify(&result,sizeof result);
      if (result != 0) fail("failure: crypto_kem_enc returns nonzero\n");
      declassify(p,plen);
      declassify(c,clen);
      declassify(k,klen);
      checksum(c,clen);
      checksum(k,klen);
      output_compare(c2,c,clen,"crypto_kem_enc");
      output_compare(k2,k,klen,"crypto_kem_enc");
      input_compare(p2,p,plen,"crypto_kem_enc");
      output_prepare(t2,t,tlen);
      memcpy(c2,c,clen);
      double_canary(c2,c,clen);
      memcpy(s2,s,slen);
      double_canary(s2,s,slen);
      secret(c,clen);
      secret(s,slen);
      result = crypto_kem_dec(t,c,s);
      declassify(&result,sizeof result);
      if (result != 0) fail("failure: crypto_kem_dec returns nonzero\n");
      declassify(c,clen);
      declassify(s,slen);
      declassify(t,tlen);
      if (memcmp(t,k,klen) != 0) fail("failure: crypto_kem_dec does not match k\n");
      checksum(t,tlen);
      output_compare(t2,t,tlen,"crypto_kem_dec");
      input_compare(c2,c,clen,"crypto_kem_dec");
      input_compare(s2,s,slen,"crypto_kem_dec");

      double_canary(t2,t,tlen);
      double_canary(c2,c,clen);
      double_canary(s2,s,slen);
      secret(c2,clen);
      secret(s2,slen);
      result = crypto_kem_dec(t2,c2,s2);
      declassify(&result,sizeof result);
      if (result != 0) fail("failure: crypto_kem_dec returns nonzero\n");
      declassify(c2,clen);
      declassify(s2,slen);
      declassify(t2,tlen);
      if (memcmp(t2,t,tlen) != 0) fail("failure: crypto_kem_dec is nondeterministic\n");

      double_canary(t2,t,tlen);
      double_canary(c2,c,clen);
      double_canary(s2,s,slen);
      secret(c2,clen);
      secret(s,slen);
      result = crypto_kem_dec(c2,c2,s);
      declassify(&result,sizeof result);
      if (result != 0) fail("failure: crypto_kem_dec with c=t overlap returns nonzero\n");
      declassify(c2,tlen);
      declassify(s,slen);
      if (memcmp(c2,t,tlen) != 0) fail("failure: crypto_kem_dec does not handle c=t overlap\n");
      memcpy(c2,c,clen);
      secret(c,clen);
      secret(s2,slen);
      result = crypto_kem_dec(s2,c,s2);
      declassify(&result,sizeof result);
      if (result != 0) fail("failure: crypto_kem_dec with s=t overlap returns nonzero\n");
      declassify(s2,tlen);
      declassify(c,clen);
      if (memcmp(s2,t,tlen) != 0) fail("failure: crypto_kem_dec does not handle s=t overlap\n");
      memcpy(s2,s,slen);

      c[myrandom() % clen] += 1 + (myrandom() % 255);
      if (crypto_kem_dec(t,c,s) == 0)
        checksum(t,tlen);
      else
        checksum(c,clen);
      c[myrandom() % clen] += 1 + (myrandom() % 255);
      if (crypto_kem_dec(t,c,s) == 0)
        checksum(t,tlen);
      else
        checksum(c,clen);
      c[myrandom() % clen] += 1 + (myrandom() % 255);
      if (crypto_kem_dec(t,c,s) == 0)
        checksum(t,tlen);
      else
        checksum(c,clen);
    }
    checksum_expected(kem_348864f_checksums[checksumbig]);
  }
}

static void test_kem_348864f(void)
{
  if (targeto && strcmp(targeto,"kem")) return;
  if (targetp && strcmp(targetp,"348864f")) return;
  storage_kem_348864f_p = callocplus(crypto_kem_PUBLICKEYBYTES);
  test_kem_348864f_p = (unsigned char *) aligned(storage_kem_348864f_p,crypto_kem_PUBLICKEYBYTES);
  storage_kem_348864f_s = callocplus(crypto_kem_SECRETKEYBYTES);
  test_kem_348864f_s = (unsigned char *) aligned(storage_kem_348864f_s,crypto_kem_SECRETKEYBYTES);
  storage_kem_348864f_k = callocplus(crypto_kem_BYTES);
  test_kem_348864f_k = (unsigned char *) aligned(storage_kem_348864f_k,crypto_kem_BYTES);
  storage_kem_348864f_c = callocplus(crypto_kem_CIPHERTEXTBYTES);
  test_kem_348864f_c = (unsigned char *) aligned(storage_kem_348864f_c,crypto_kem_CIPHERTEXTBYTES);
  storage_kem_348864f_t = callocplus(crypto_kem_BYTES);
  test_kem_348864f_t = (unsigned char *) aligned(storage_kem_348864f_t,crypto_kem_BYTES);
  storage_kem_348864f_p2 = callocplus(crypto_kem_PUBLICKEYBYTES);
  test_kem_348864f_p2 = (unsigned char *) aligned(storage_kem_348864f_p2,crypto_kem_PUBLICKEYBYTES);
  storage_kem_348864f_s2 = callocplus(crypto_kem_SECRETKEYBYTES);
  test_kem_348864f_s2 = (unsigned char *) aligned(storage_kem_348864f_s2,crypto_kem_SECRETKEYBYTES);
  storage_kem_348864f_k2 = callocplus(crypto_kem_BYTES);
  test_kem_348864f_k2 = (unsigned char *) aligned(storage_kem_348864f_k2,crypto_kem_BYTES);
  storage_kem_348864f_c2 = callocplus(crypto_kem_CIPHERTEXTBYTES);
  test_kem_348864f_c2 = (unsigned char *) aligned(storage_kem_348864f_c2,crypto_kem_CIPHERTEXTBYTES);
  storage_kem_348864f_t2 = callocplus(crypto_kem_BYTES);
  test_kem_348864f_t2 = (unsigned char *) aligned(storage_kem_348864f_t2,crypto_kem_BYTES);

  for (long long offset = 0;offset < 2;++offset) {
    if (targetoffset && atol(targetoffset) != offset) continue;
    if (offset && valgrind) break;
    printf("kem_348864f offset %lld\n",offset);
    for (long long impl = -1;impl < mceliece_numimpl_kem_348864f();++impl)
      forked(test_kem_348864f_impl,impl);
    ++test_kem_348864f_p;
    ++test_kem_348864f_s;
    ++test_kem_348864f_k;
    ++test_kem_348864f_c;
    ++test_kem_348864f_t;
    ++test_kem_348864f_p2;
    ++test_kem_348864f_s2;
    ++test_kem_348864f_k2;
    ++test_kem_348864f_c2;
    ++test_kem_348864f_t2;
  }
  free(storage_kem_348864f_t2);
  free(storage_kem_348864f_c2);
  free(storage_kem_348864f_k2);
  free(storage_kem_348864f_s2);
  free(storage_kem_348864f_p2);
  free(storage_kem_348864f_t);
  free(storage_kem_348864f_c);
  free(storage_kem_348864f_k);
  free(storage_kem_348864f_s);
  free(storage_kem_348864f_p);
}
#undef crypto_kem_PUBLICKEYBYTES
#undef crypto_kem_SECRETKEYBYTES
#undef crypto_kem_CIPHERTEXTBYTES
#undef crypto_kem_BYTES

static const char *kem_348864pc_checksums[] = {
  "ddfa65df30bee9c97e153089d24cce158a7979aa01ebdbb7bf374da13bd81feb",
  "9866af598e967b1b3903d9e125bf756a92aed474f750678238b2bb52129cd213",
} ;

#define crypto_kem_PUBLICKEYBYTES mceliece_kem_348864pc_PUBLICKEYBYTES
#define crypto_kem_SECRETKEYBYTES mceliece_kem_348864pc_SECRETKEYBYTES
#define crypto_kem_CIPHERTEXTBYTES mceliece_kem_348864pc_CIPHERTEXTBYTES
#define crypto_kem_BYTES mceliece_kem_348864pc_BYTES

static void *storage_kem_348864pc_p;
static unsigned char *test_kem_348864pc_p;
static void *storage_kem_348864pc_s;
static unsigned char *test_kem_348864pc_s;
static void *storage_kem_348864pc_k;
static unsigned char *test_kem_348864pc_k;
static void *storage_kem_348864pc_c;
static unsigned char *test_kem_348864pc_c;
static void *storage_kem_348864pc_t;
static unsigned char *test_kem_348864pc_t;
static void *storage_kem_348864pc_p2;
static unsigned char *test_kem_348864pc_p2;
static void *storage_kem_348864pc_s2;
static unsigned char *test_kem_348864pc_s2;
static void *storage_kem_348864pc_k2;
static unsigned char *test_kem_348864pc_k2;
static void *storage_kem_348864pc_c2;
static unsigned char *test_kem_348864pc_c2;
static void *storage_kem_348864pc_t2;
static unsigned char *test_kem_348864pc_t2;

static void test_kem_348864pc_impl(long long impl)
{
  unsigned char *p = test_kem_348864pc_p;
  unsigned char *s = test_kem_348864pc_s;
  unsigned char *k = test_kem_348864pc_k;
  unsigned char *c = test_kem_348864pc_c;
  unsigned char *t = test_kem_348864pc_t;
  unsigned char *p2 = test_kem_348864pc_p2;
  unsigned char *s2 = test_kem_348864pc_s2;
  unsigned char *k2 = test_kem_348864pc_k2;
  unsigned char *c2 = test_kem_348864pc_c2;
  unsigned char *t2 = test_kem_348864pc_t2;
  long long plen = crypto_kem_PUBLICKEYBYTES;
  long long slen = crypto_kem_SECRETKEYBYTES;
  long long klen = crypto_kem_BYTES;
  long long clen = crypto_kem_CIPHERTEXTBYTES;
  long long tlen = crypto_kem_BYTES;

  if (targeti && strcmp(targeti,".") && strcmp(targeti,mceliece_dispatch_kem_348864pc_implementation(impl))) return;
  if (targetn && atol(targetn) != impl) return;
  if (impl >= 0) {
    crypto_kem_keypair = mceliece_dispatch_kem_348864pc_keypair(impl);
    crypto_kem_enc = mceliece_dispatch_kem_348864pc_enc(impl);
    crypto_kem_dec = mceliece_dispatch_kem_348864pc_dec(impl);
    printf("kem_348864pc %lld implementation %s compiler %s\n",impl,mceliece_dispatch_kem_348864pc_implementation(impl),mceliece_dispatch_kem_348864pc_compiler(impl));
  } else {
    crypto_kem_keypair = mceliece_kem_348864pc_keypair;
    crypto_kem_enc = mceliece_kem_348864pc_enc;
    crypto_kem_dec = mceliece_kem_348864pc_dec;
    printf("kem_348864pc selected implementation %s compiler %s\n",mceliece_kem_348864pc_implementation(),mceliece_kem_348864pc_compiler());
  }
  for (long long checksumbig = 0;checksumbig < 2;++checksumbig) {
    long long loops = checksumbig ? 64 : 8;

    checksum_clear();

    for (long long loop = 0;loop < loops;++loop) {
      int result;

      output_prepare(p2,p,plen);
      output_prepare(s2,s,slen);
      crypto_kem_keypair(p,s);
      declassify(p,plen);
      declassify(s,slen);
      checksum(p,plen);
      checksum(s,slen);
      output_compare(p2,p,plen,"crypto_kem_keypair");
      output_compare(s2,s,slen,"crypto_kem_keypair");
      output_prepare(c2,c,clen);
      output_prepare(k2,k,klen);
      memcpy(p2,p,plen);
      double_canary(p2,p,plen);
      secret(p,plen);
      result = crypto_kem_enc(c,k,p);
      declassify(&result,sizeof result);
      if (result != 0) fail("failure: crypto_kem_enc returns nonzero\n");
      declassify(p,plen);
      declassify(c,clen);
      declassify(k,klen);
      checksum(c,clen);
      checksum(k,klen);
      output_compare(c2,c,clen,"crypto_kem_enc");
      output_compare(k2,k,klen,"crypto_kem_enc");
      input_compare(p2,p,plen,"crypto_kem_enc");
      output_prepare(t2,t,tlen);
      memcpy(c2,c,clen);
      double_canary(c2,c,clen);
      memcpy(s2,s,slen);
      double_canary(s2,s,slen);
      secret(c,clen);
      secret(s,slen);
      result = crypto_kem_dec(t,c,s);
      declassify(&result,sizeof result);
      if (result != 0) fail("failure: crypto_kem_dec returns nonzero\n");
      declassify(c,clen);
      declassify(s,slen);
      declassify(t,tlen);
      if (memcmp(t,k,klen) != 0) fail("failure: crypto_kem_dec does not match k\n");
      checksum(t,tlen);
      output_compare(t2,t,tlen,"crypto_kem_dec");
      input_compare(c2,c,clen,"crypto_kem_dec");
      input_compare(s2,s,slen,"crypto_kem_dec");

      double_canary(t2,t,tlen);
      double_canary(c2,c,clen);
      double_canary(s2,s,slen);
      secret(c2,clen);
      secret(s2,slen);
      result = crypto_kem_dec(t2,c2,s2);
      declassify(&result,sizeof result);
      if (result != 0) fail("failure: crypto_kem_dec returns nonzero\n");
      declassify(c2,clen);
      declassify(s2,slen);
      declassify(t2,tlen);
      if (memcmp(t2,t,tlen) != 0) fail("failure: crypto_kem_dec is nondeterministic\n");

      double_canary(t2,t,tlen);
      double_canary(c2,c,clen);
      double_canary(s2,s,slen);
      secret(c2,clen);
      secret(s,slen);
      result = crypto_kem_dec(c2,c2,s);
      declassify(&result,sizeof result);
      if (result != 0) fail("failure: crypto_kem_dec with c=t overlap returns nonzero\n");
      declassify(c2,tlen);
      declassify(s,slen);
      if (memcmp(c2,t,tlen) != 0) fail("failure: crypto_kem_dec does not handle c=t overlap\n");
      memcpy(c2,c,clen);
      secret(c,clen);
      secret(s2,slen);
      result = crypto_kem_dec(s2,c,s2);
      declassify(&result,sizeof result);
      if (result != 0) fail("failure: crypto_kem_dec with s=t overlap returns nonzero\n");
      declassify(s2,tlen);
      declassify(c,clen);
      if (memcmp(s2,t,tlen) != 0) fail("failure: crypto_kem_dec does not handle s=t overlap\n");
      memcpy(s2,s,slen);

      c[myrandom() % clen] += 1 + (myrandom() % 255);
      if (crypto_kem_dec(t,c,s) == 0)
        checksum(t,tlen);
      else
        checksum(c,clen);
      c[myrandom() % clen] += 1 + (myrandom() % 255);
      if (crypto_kem_dec(t,c,s) == 0)
        checksum(t,tlen);
      else
        checksum(c,clen);
      c[myrandom() % clen] += 1 + (myrandom() % 255);
      if (crypto_kem_dec(t,c,s) == 0)
        checksum(t,tlen);
      else
        checksum(c,clen);
    }
    checksum_expected(kem_348864pc_checksums[checksumbig]);
  }
}

static void test_kem_348864pc(void)
{
  if (targeto && strcmp(targeto,"kem")) return;
  if (targetp && strcmp(targetp,"348864pc")) return;
  storage_kem_348864pc_p = callocplus(crypto_kem_PUBLICKEYBYTES);
  test_kem_348864pc_p = (unsigned char *) aligned(storage_kem_348864pc_p,crypto_kem_PUBLICKEYBYTES);
  storage_kem_348864pc_s = callocplus(crypto_kem_SECRETKEYBYTES);
  test_kem_348864pc_s = (unsigned char *) aligned(storage_kem_348864pc_s,crypto_kem_SECRETKEYBYTES);
  storage_kem_348864pc_k = callocplus(crypto_kem_BYTES);
  test_kem_348864pc_k = (unsigned char *) aligned(storage_kem_348864pc_k,crypto_kem_BYTES);
  storage_kem_348864pc_c = callocplus(crypto_kem_CIPHERTEXTBYTES);
  test_kem_348864pc_c = (unsigned char *) aligned(storage_kem_348864pc_c,crypto_kem_CIPHERTEXTBYTES);
  storage_kem_348864pc_t = callocplus(crypto_kem_BYTES);
  test_kem_348864pc_t = (unsigned char *) aligned(storage_kem_348864pc_t,crypto_kem_BYTES);
  storage_kem_348864pc_p2 = callocplus(crypto_kem_PUBLICKEYBYTES);
  test_kem_348864pc_p2 = (unsigned char *) aligned(storage_kem_348864pc_p2,crypto_kem_PUBLICKEYBYTES);
  storage_kem_348864pc_s2 = callocplus(crypto_kem_SECRETKEYBYTES);
  test_kem_348864pc_s2 = (unsigned char *) aligned(storage_kem_348864pc_s2,crypto_kem_SECRETKEYBYTES);
  storage_kem_348864pc_k2 = callocplus(crypto_kem_BYTES);
  test_kem_348864pc_k2 = (unsigned char *) aligned(storage_kem_348864pc_k2,crypto_kem_BYTES);
  storage_kem_348864pc_c2 = callocplus(crypto_kem_CIPHERTEXTBYTES);
  test_kem_348864pc_c2 = (unsigned char *) aligned(storage_kem_348864pc_c2,crypto_kem_CIPHERTEXTBYTES);
  storage_kem_348864pc_t2 = callocplus(crypto_kem_BYTES);
  test_kem_348864pc_t2 = (unsigned char *) aligned(storage_kem_348864pc_t2,crypto_kem_BYTES);

  for (long long offset = 0;offset < 2;++offset) {
    if (targetoffset && atol(targetoffset) != offset) continue;
    if (offset && valgrind) break;
    printf("kem_348864pc offset %lld\n",offset);
    for (long long impl = -1;impl < mceliece_numimpl_kem_348864pc();++impl)
      forked(test_kem_348864pc_impl,impl);
    ++test_kem_348864pc_p;
    ++test_kem_348864pc_s;
    ++test_kem_348864pc_k;
    ++test_kem_348864pc_c;
    ++test_kem_348864pc_t;
    ++test_kem_348864pc_p2;
    ++test_kem_348864pc_s2;
    ++test_kem_348864pc_k2;
    ++test_kem_348864pc_c2;
    ++test_kem_348864pc_t2;
  }
  free(storage_kem_348864pc_t2);
  free(storage_kem_348864pc_c2);
  free(storage_kem_348864pc_k2);
  free(storage_kem_348864pc_s2);
  free(storage_kem_348864pc_p2);
  free(storage_kem_348864pc_t);
  free(storage_kem_348864pc_c);
  free(storage_kem_348864pc_k);
  free(storage_kem_348864pc_s);
  free(storage_kem_348864pc_p);
}
#undef crypto_kem_PUBLICKEYBYTES
#undef crypto_kem_SECRETKEYBYTES
#undef crypto_kem_CIPHERTEXTBYTES
#undef crypto_kem_BYTES

static const char *kem_348864pcf_checksums[] = {
  "4dcfc56d5e162873f227befd1e7c51f2b317f9ccf811e931e86e2fcdeea6c10e",
  "48fffebf6cd92a688b4724d88cf989ab199066040c7c62202dab6f30ef188d68",
} ;

#define crypto_kem_PUBLICKEYBYTES mceliece_kem_348864pcf_PUBLICKEYBYTES
#define crypto_kem_SECRETKEYBYTES mceliece_kem_348864pcf_SECRETKEYBYTES
#define crypto_kem_CIPHERTEXTBYTES mceliece_kem_348864pcf_CIPHERTEXTBYTES
#define crypto_kem_BYTES mceliece_kem_348864pcf_BYTES

static void *storage_kem_348864pcf_p;
static unsigned char *test_kem_348864pcf_p;
static void *storage_kem_348864pcf_s;
static unsigned char *test_kem_348864pcf_s;
static void *storage_kem_348864pcf_k;
static unsigned char *test_kem_348864pcf_k;
static void *storage_kem_348864pcf_c;
static unsigned char *test_kem_348864pcf_c;
static void *storage_kem_348864pcf_t;
static unsigned char *test_kem_348864pcf_t;
static void *storage_kem_348864pcf_p2;
static unsigned char *test_kem_348864pcf_p2;
static void *storage_kem_348864pcf_s2;
static unsigned char *test_kem_348864pcf_s2;
static void *storage_kem_348864pcf_k2;
static unsigned char *test_kem_348864pcf_k2;
static void *storage_kem_348864pcf_c2;
static unsigned char *test_kem_348864pcf_c2;
static void *storage_kem_348864pcf_t2;
static unsigned char *test_kem_348864pcf_t2;

static void test_kem_348864pcf_impl(long long impl)
{
  unsigned char *p = test_kem_348864pcf_p;
  unsigned char *s = test_kem_348864pcf_s;
  unsigned char *k = test_kem_348864pcf_k;
  unsigned char *c = test_kem_348864pcf_c;
  unsigned char *t = test_kem_348864pcf_t;
  unsigned char *p2 = test_kem_348864pcf_p2;
  unsigned char *s2 = test_kem_348864pcf_s2;
  unsigned char *k2 = test_kem_348864pcf_k2;
  unsigned char *c2 = test_kem_348864pcf_c2;
  unsigned char *t2 = test_kem_348864pcf_t2;
  long long plen = crypto_kem_PUBLICKEYBYTES;
  long long slen = crypto_kem_SECRETKEYBYTES;
  long long klen = crypto_kem_BYTES;
  long long clen = crypto_kem_CIPHERTEXTBYTES;
  long long tlen = crypto_kem_BYTES;

  if (targeti && strcmp(targeti,".") && strcmp(targeti,mceliece_dispatch_kem_348864pcf_implementation(impl))) return;
  if (targetn && atol(targetn) != impl) return;
  if (impl >= 0) {
    crypto_kem_keypair = mceliece_dispatch_kem_348864pcf_keypair(impl);
    crypto_kem_enc = mceliece_dispatch_kem_348864pcf_enc(impl);
    crypto_kem_dec = mceliece_dispatch_kem_348864pcf_dec(impl);
    printf("kem_348864pcf %lld implementation %s compiler %s\n",impl,mceliece_dispatch_kem_348864pcf_implementation(impl),mceliece_dispatch_kem_348864pcf_compiler(impl));
  } else {
    crypto_kem_keypair = mceliece_kem_348864pcf_keypair;
    crypto_kem_enc = mceliece_kem_348864pcf_enc;
    crypto_kem_dec = mceliece_kem_348864pcf_dec;
    printf("kem_348864pcf selected implementation %s compiler %s\n",mceliece_kem_348864pcf_implementation(),mceliece_kem_348864pcf_compiler());
  }
  for (long long checksumbig = 0;checksumbig < 2;++checksumbig) {
    long long loops = checksumbig ? 64 : 8;

    checksum_clear();

    for (long long loop = 0;loop < loops;++loop) {
      int result;

      output_prepare(p2,p,plen);
      output_prepare(s2,s,slen);
      crypto_kem_keypair(p,s);
      declassify(p,plen);
      declassify(s,slen);
      checksum(p,plen);
      checksum(s,slen);
      output_compare(p2,p,plen,"crypto_kem_keypair");
      output_compare(s2,s,slen,"crypto_kem_keypair");
      output_prepare(c2,c,clen);
      output_prepare(k2,k,klen);
      memcpy(p2,p,plen);
      double_canary(p2,p,plen);
      secret(p,plen);
      result = crypto_kem_enc(c,k,p);
      declassify(&result,sizeof result);
      if (result != 0) fail("failure: crypto_kem_enc returns nonzero\n");
      declassify(p,plen);
      declassify(c,clen);
      declassify(k,klen);
      checksum(c,clen);
      checksum(k,klen);
      output_compare(c2,c,clen,"crypto_kem_enc");
      output_compare(k2,k,klen,"crypto_kem_enc");
      input_compare(p2,p,plen,"crypto_kem_enc");
      output_prepare(t2,t,tlen);
      memcpy(c2,c,clen);
      double_canary(c2,c,clen);
      memcpy(s2,s,slen);
      double_canary(s2,s,slen);
      secret(c,clen);
      secret(s,slen);
      result = crypto_kem_dec(t,c,s);
      declassify(&result,sizeof result);
      if (result != 0) fail("failure: crypto_kem_dec returns nonzero\n");
      declassify(c,clen);
      declassify(s,slen);
      declassify(t,tlen);
      if (memcmp(t,k,klen) != 0) fail("failure: crypto_kem_dec does not match k\n");
      checksum(t,tlen);
      output_compare(t2,t,tlen,"crypto_kem_dec");
      input_compare(c2,c,clen,"crypto_kem_dec");
      input_compare(s2,s,slen,"crypto_kem_dec");

      double_canary(t2,t,tlen);
      double_canary(c2,c,clen);
      double_canary(s2,s,slen);
      secret(c2,clen);
      secret(s2,slen);
      result = crypto_kem_dec(t2,c2,s2);
      declassify(&result,sizeof result);
      if (result != 0) fail("failure: crypto_kem_dec returns nonzero\n");
      declassify(c2,clen);
      declassify(s2,slen);
      declassify(t2,tlen);
      if (memcmp(t2,t,tlen) != 0) fail("failure: crypto_kem_dec is nondeterministic\n");

      double_canary(t2,t,tlen);
      double_canary(c2,c,clen);
      double_canary(s2,s,slen);
      secret(c2,clen);
      secret(s,slen);
      result = crypto_kem_dec(c2,c2,s);
      declassify(&result,sizeof result);
      if (result != 0) fail("failure: crypto_kem_dec with c=t overlap returns nonzero\n");
      declassify(c2,tlen);
      declassify(s,slen);
      if (memcmp(c2,t,tlen) != 0) fail("failure: crypto_kem_dec does not handle c=t overlap\n");
      memcpy(c2,c,clen);
      secret(c,clen);
      secret(s2,slen);
      result = crypto_kem_dec(s2,c,s2);
      declassify(&result,sizeof result);
      if (result != 0) fail("failure: crypto_kem_dec with s=t overlap returns nonzero\n");
      declassify(s2,tlen);
      declassify(c,clen);
      if (memcmp(s2,t,tlen) != 0) fail("failure: crypto_kem_dec does not handle s=t overlap\n");
      memcpy(s2,s,slen);

      c[myrandom() % clen] += 1 + (myrandom() % 255);
      if (crypto_kem_dec(t,c,s) == 0)
        checksum(t,tlen);
      else
        checksum(c,clen);
      c[myrandom() % clen] += 1 + (myrandom() % 255);
      if (crypto_kem_dec(t,c,s) == 0)
        checksum(t,tlen);
      else
        checksum(c,clen);
      c[myrandom() % clen] += 1 + (myrandom() % 255);
      if (crypto_kem_dec(t,c,s) == 0)
        checksum(t,tlen);
      else
        checksum(c,clen);
    }
    checksum_expected(kem_348864pcf_checksums[checksumbig]);
  }
}

static void test_kem_348864pcf(void)
{
  if (targeto && strcmp(targeto,"kem")) return;
  if (targetp && strcmp(targetp,"348864pcf")) return;
  storage_kem_348864pcf_p = callocplus(crypto_kem_PUBLICKEYBYTES);
  test_kem_348864pcf_p = (unsigned char *) aligned(storage_kem_348864pcf_p,crypto_kem_PUBLICKEYBYTES);
  storage_kem_348864pcf_s = callocplus(crypto_kem_SECRETKEYBYTES);
  test_kem_348864pcf_s = (unsigned char *) aligned(storage_kem_348864pcf_s,crypto_kem_SECRETKEYBYTES);
  storage_kem_348864pcf_k = callocplus(crypto_kem_BYTES);
  test_kem_348864pcf_k = (unsigned char *) aligned(storage_kem_348864pcf_k,crypto_kem_BYTES);
  storage_kem_348864pcf_c = callocplus(crypto_kem_CIPHERTEXTBYTES);
  test_kem_348864pcf_c = (unsigned char *) aligned(storage_kem_348864pcf_c,crypto_kem_CIPHERTEXTBYTES);
  storage_kem_348864pcf_t = callocplus(crypto_kem_BYTES);
  test_kem_348864pcf_t = (unsigned char *) aligned(storage_kem_348864pcf_t,crypto_kem_BYTES);
  storage_kem_348864pcf_p2 = callocplus(crypto_kem_PUBLICKEYBYTES);
  test_kem_348864pcf_p2 = (unsigned char *) aligned(storage_kem_348864pcf_p2,crypto_kem_PUBLICKEYBYTES);
  storage_kem_348864pcf_s2 = callocplus(crypto_kem_SECRETKEYBYTES);
  test_kem_348864pcf_s2 = (unsigned char *) aligned(storage_kem_348864pcf_s2,crypto_kem_SECRETKEYBYTES);
  storage_kem_348864pcf_k2 = callocplus(crypto_kem_BYTES);
  test_kem_348864pcf_k2 = (unsigned char *) aligned(storage_kem_348864pcf_k2,crypto_kem_BYTES);
  storage_kem_348864pcf_c2 = callocplus(crypto_kem_CIPHERTEXTBYTES);
  test_kem_348864pcf_c2 = (unsigned char *) aligned(storage_kem_348864pcf_c2,crypto_kem_CIPHERTEXTBYTES);
  storage_kem_348864pcf_t2 = callocplus(crypto_kem_BYTES);
  test_kem_348864pcf_t2 = (unsigned char *) aligned(storage_kem_348864pcf_t2,crypto_kem_BYTES);

  for (long long offset = 0;offset < 2;++offset) {
    if (targetoffset && atol(targetoffset) != offset) continue;
    if (offset && valgrind) break;
    printf("kem_348864pcf offset %lld\n",offset);
    for (long long impl = -1;impl < mceliece_numimpl_kem_348864pcf();++impl)
      forked(test_kem_348864pcf_impl,impl);
    ++test_kem_348864pcf_p;
    ++test_kem_348864pcf_s;
    ++test_kem_348864pcf_k;
    ++test_kem_348864pcf_c;
    ++test_kem_348864pcf_t;
    ++test_kem_348864pcf_p2;
    ++test_kem_348864pcf_s2;
    ++test_kem_348864pcf_k2;
    ++test_kem_348864pcf_c2;
    ++test_kem_348864pcf_t2;
  }
  free(storage_kem_348864pcf_t2);
  free(storage_kem_348864pcf_c2);
  free(storage_kem_348864pcf_k2);
  free(storage_kem_348864pcf_s2);
  free(storage_kem_348864pcf_p2);
  free(storage_kem_348864pcf_t);
  free(storage_kem_348864pcf_c);
  free(storage_kem_348864pcf_k);
  free(storage_kem_348864pcf_s);
  free(storage_kem_348864pcf_p);
}
#undef crypto_kem_PUBLICKEYBYTES
#undef crypto_kem_SECRETKEYBYTES
#undef crypto_kem_CIPHERTEXTBYTES
#undef crypto_kem_BYTES

/* ----- top level */

#include "print_cpuid.inc"

int main(int argc,char **argv)
{
  valgrind_init();
  if (valgrind) limits();

  setvbuf(stdout,0,_IOLBF,0);
  printf("mceliece version %s\n",mceliece_version);
  printf("mceliece arch %s\n",mceliece_arch);
  print_cpuid();

  if (valgrind) {
    printf("valgrind %d",(int) valgrind);
    printf(" declassify %d",(int) crypto_declassify_uses_valgrind);
    if (!crypto_declassify_uses_valgrind)
      printf(" (expect false positives)");
    printf("\n");
  }

  if (*argv) ++argv;
  if (*argv) {
    targeto = *argv++;
    if (*argv) {
      targetp = *argv++;
      if (*argv) {
        targeti = *argv++;
        if (*argv) {
          targetn = *argv++;
          if (*argv) {
            targetoffset = *argv++;
          }
        }
      }
    }
  }

  test_xof_shake256();
  test_xof_bitwrite16();
  test_sort_int16();
  test_sort_int32();
  test_sort_int64();
  test_kem_6960119();
  test_kem_6960119f();
  test_kem_6960119pc();
  test_kem_6960119pcf();
  test_kem_6688128();
  test_kem_6688128f();
  test_kem_6688128pc();
  test_kem_6688128pcf();
  test_kem_8192128();
  test_kem_8192128f();
  test_kem_8192128pc();
  test_kem_8192128pcf();
  test_kem_460896();
  test_kem_460896f();
  test_kem_460896pc();
  test_kem_460896pcf();
  test_kem_348864();
  test_kem_348864f();
  test_kem_348864pc();
  test_kem_348864pcf();

  if (!ok) {
    printf("some tests failed\n");
    return 100;
  }
  printf("all tests succeeded\n");
  return 0;
}
