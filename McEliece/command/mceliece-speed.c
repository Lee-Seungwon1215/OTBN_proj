/* WARNING: auto-generated (by autogen/speed); do not edit */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <time.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/resource.h>
#include <cpucycles.h> /* -lcpucycles */
#include <mceliece.h> /* -lmceliece */
#include <randombytes.h> /* -lrandombytes */

static const char *targeto = 0;
static const char *targetp = 0;
static const char *targeti = 0;

#include "limits.inc"

static void *callocplus(long long len)
{
  void *x = calloc(1,len + 128);
  if (!x) abort();
  return x;
}

static void *aligned(void *x)
{
  unsigned char *y = (unsigned char *) x;
  y += 63 & (-(unsigned long) x);
  return y;
}

static void longlong_sort(long long *x,long long n)
{
  long long top,p,q,r,i;

  if (n < 2) return;
  top = 1;
  while (top < n - top) top += top;

  for (p = top;p > 0;p >>= 1) {
    for (i = 0;i < n - p;++i)
      if (!(i & p))
        if (x[i] > x[i+p]) {
          long long t = x[i];
          x[i] = x[i+p];
          x[i+p] = t;
        }
    i = 0;
    for (q = top;q > p;q >>= 1) {
      for (;i < n - q;++i) {
        if (!(i & p)) {
          long long a = x[i + p];
          for (r = q;r > p;r >>= 1)
            if (a > x[i+r]) {
              long long t = a;
              a = x[i+r];
              x[i+r] = t;
            }
          x[i + p] = a;
        }
      }
    }
  }
}

#define TIMINGS 32 // must be multiple of 4
static long long t[TIMINGS+1];

static void t_print(const char *op,long long impl,long long len)
{
  long long tsort[TIMINGS];
  long long iqm = 0;

  printf("%s",op);
  if (impl >= 0)
    printf(" %lld",impl);
  else
    printf(" selected");
  printf(" %lld",len);
  for (long long i = 0;i < TIMINGS;++i)
    tsort[i] = t[i] = t[i+1]-t[i];
  longlong_sort(tsort,TIMINGS);

  for (long long j = TIMINGS/4;j < 3*TIMINGS/4;++j)
    iqm += tsort[j];
  iqm *= 2;
  iqm += TIMINGS/2;
  iqm /= TIMINGS;

  printf(" %lld ",iqm);
  for (long long i = 0;i < TIMINGS;++i)
    printf("%+lld",t[i]-iqm);
  printf("\n");
  fflush(stdout);
}

#define MAXTEST_BYTES 65536

static void measure_cpucycles(void)
{
  printf("cpucycles selected persecond %lld\n",cpucycles_persecond());
  printf("cpucycles selected implementation %s\n",cpucycles_implementation());

  for (long long i = 0;i <= TIMINGS;++i)
    t[i] = cpucycles();
  t_print("cpucycles",-1,0);
}

static void measure_randombytes(void)
{
  void *mstorage = callocplus(MAXTEST_BYTES);
  unsigned char *m = (unsigned char *) aligned(mstorage);
  long long mlen = 0;

  while (mlen < MAXTEST_BYTES) {
    for (long long i = 0;i <= TIMINGS;++i) {
      t[i] = cpucycles();
      randombytes(m,mlen);
    }
    t_print("randombytes",-1,mlen);
    mlen += 1+mlen/2;
  }
  free(mstorage);
}

static void measure_sort_int16(void)
{
  if (targeto && strcmp(targeto,"sort")) return;
  if (targetp && strcmp(targetp,"int16")) return;
  void *mstorage = callocplus(MAXTEST_BYTES);
  unsigned char *m = (unsigned char *) aligned(mstorage);
  long long mlen;

  for (long long impl = -1;impl < mceliece_numimpl_sort_int16();++impl) {
    void (*crypto_sort)(void *,long long);
    if (targeti && strcmp(targeti,mceliece_dispatch_sort_int16_implementation(impl))) continue;
    if (impl >= 0) {
      crypto_sort = mceliece_dispatch_sort_int16(impl);
      printf("sort_int16 %lld implementation %s compiler %s\n",impl,mceliece_dispatch_sort_int16_implementation(impl),mceliece_dispatch_sort_int16_compiler(impl));
    } else {
      crypto_sort = mceliece_sort_int16;
      printf("sort_int16 selected implementation %s compiler %s\n",mceliece_sort_int16_implementation(),mceliece_sort_int16_compiler());
    }
    randombytes(m,MAXTEST_BYTES);
    mlen = 0;
    while (mceliece_sort_int16_BYTES*mlen <= MAXTEST_BYTES) {
      randombytes(m,mceliece_sort_int16_BYTES*mlen);
      for (long long i = 0;i <= TIMINGS;++i) {
        t[i] = cpucycles();
        crypto_sort(m,mlen);
      }
      t_print("sort_int16",impl,mlen);
      mlen += 1+mlen/2;
    }
  }
  free(mstorage);
}

static void measure_sort_int32(void)
{
  if (targeto && strcmp(targeto,"sort")) return;
  if (targetp && strcmp(targetp,"int32")) return;
  void *mstorage = callocplus(MAXTEST_BYTES);
  unsigned char *m = (unsigned char *) aligned(mstorage);
  long long mlen;

  for (long long impl = -1;impl < mceliece_numimpl_sort_int32();++impl) {
    void (*crypto_sort)(void *,long long);
    if (targeti && strcmp(targeti,mceliece_dispatch_sort_int32_implementation(impl))) continue;
    if (impl >= 0) {
      crypto_sort = mceliece_dispatch_sort_int32(impl);
      printf("sort_int32 %lld implementation %s compiler %s\n",impl,mceliece_dispatch_sort_int32_implementation(impl),mceliece_dispatch_sort_int32_compiler(impl));
    } else {
      crypto_sort = mceliece_sort_int32;
      printf("sort_int32 selected implementation %s compiler %s\n",mceliece_sort_int32_implementation(),mceliece_sort_int32_compiler());
    }
    randombytes(m,MAXTEST_BYTES);
    mlen = 0;
    while (mceliece_sort_int32_BYTES*mlen <= MAXTEST_BYTES) {
      randombytes(m,mceliece_sort_int32_BYTES*mlen);
      for (long long i = 0;i <= TIMINGS;++i) {
        t[i] = cpucycles();
        crypto_sort(m,mlen);
      }
      t_print("sort_int32",impl,mlen);
      mlen += 1+mlen/2;
    }
  }
  free(mstorage);
}

static void measure_sort_int64(void)
{
  if (targeto && strcmp(targeto,"sort")) return;
  if (targetp && strcmp(targetp,"int64")) return;
  void *mstorage = callocplus(MAXTEST_BYTES);
  unsigned char *m = (unsigned char *) aligned(mstorage);
  long long mlen;

  for (long long impl = -1;impl < mceliece_numimpl_sort_int64();++impl) {
    void (*crypto_sort)(void *,long long);
    if (targeti && strcmp(targeti,mceliece_dispatch_sort_int64_implementation(impl))) continue;
    if (impl >= 0) {
      crypto_sort = mceliece_dispatch_sort_int64(impl);
      printf("sort_int64 %lld implementation %s compiler %s\n",impl,mceliece_dispatch_sort_int64_implementation(impl),mceliece_dispatch_sort_int64_compiler(impl));
    } else {
      crypto_sort = mceliece_sort_int64;
      printf("sort_int64 selected implementation %s compiler %s\n",mceliece_sort_int64_implementation(),mceliece_sort_int64_compiler());
    }
    randombytes(m,MAXTEST_BYTES);
    mlen = 0;
    while (mceliece_sort_int64_BYTES*mlen <= MAXTEST_BYTES) {
      randombytes(m,mceliece_sort_int64_BYTES*mlen);
      for (long long i = 0;i <= TIMINGS;++i) {
        t[i] = cpucycles();
        crypto_sort(m,mlen);
      }
      t_print("sort_int64",impl,mlen);
      mlen += 1+mlen/2;
    }
  }
  free(mstorage);
}

static void measure_xof_shake256(void)
{
  if (targeto && strcmp(targeto,"xof")) return;
  if (targetp && strcmp(targetp,"shake256")) return;
  void *hstorage = callocplus(MAXTEST_BYTES);
  unsigned char *h = (unsigned char *) aligned(hstorage);
  long long hlen;
  void *mstorage = callocplus(MAXTEST_BYTES);
  unsigned char *m = (unsigned char *) aligned(mstorage);
  long long mlen;

  for (long long impl = -1;impl < mceliece_numimpl_xof_shake256();++impl) {
    void (*crypto_xof)(unsigned char *,long long,const unsigned char *,long long);
    if (targeti && strcmp(targeti,mceliece_dispatch_xof_shake256_implementation(impl))) continue;
    if (impl >= 0) {
      crypto_xof = mceliece_dispatch_xof_shake256(impl);
      printf("xof_shake256 %lld implementation %s compiler %s\n",impl,mceliece_dispatch_xof_shake256_implementation(impl),mceliece_dispatch_xof_shake256_compiler(impl));
    } else {
      crypto_xof = mceliece_xof_shake256;
      printf("xof_shake256 selected implementation %s compiler %s\n",mceliece_xof_shake256_implementation(),mceliece_xof_shake256_compiler());
    }
    randombytes(h,MAXTEST_BYTES);
    randombytes(m,MAXTEST_BYTES);
    hlen = 32;
    mlen = 0;
    while (mlen <= MAXTEST_BYTES) {
      randombytes(m,mlen);
      for (long long i = 0;i <= TIMINGS;++i) {
        t[i] = cpucycles();
        crypto_xof(h,hlen,m,mlen);
      }
      t_print("xof_shake256",impl,mlen);
      mlen += 1+mlen/2;
    }
    mlen = 32;
    hlen = 1;
    while (hlen <= MAXTEST_BYTES) {
      randombytes(h,hlen);
      for (long long i = 0;i <= TIMINGS;++i) {
        t[i] = cpucycles();
        crypto_xof(h,hlen,m,mlen);
      }
      t_print("xof_shake256",impl,-hlen);
      hlen += 1+hlen/2;
    }
  }
  free(mstorage);
  free(hstorage);
}

static void measure_xof_bitwrite16(void)
{
  if (targeto && strcmp(targeto,"xof")) return;
  if (targetp && strcmp(targetp,"bitwrite16")) return;
  void *hstorage = callocplus(MAXTEST_BYTES);
  unsigned char *h = (unsigned char *) aligned(hstorage);
  long long hlen;
  void *mstorage = callocplus(MAXTEST_BYTES);
  unsigned char *m = (unsigned char *) aligned(mstorage);
  long long mlen;

  for (long long impl = -1;impl < mceliece_numimpl_xof_bitwrite16();++impl) {
    void (*crypto_xof)(unsigned char *,long long,const unsigned char *,long long);
    if (targeti && strcmp(targeti,mceliece_dispatch_xof_bitwrite16_implementation(impl))) continue;
    if (impl >= 0) {
      crypto_xof = mceliece_dispatch_xof_bitwrite16(impl);
      printf("xof_bitwrite16 %lld implementation %s compiler %s\n",impl,mceliece_dispatch_xof_bitwrite16_implementation(impl),mceliece_dispatch_xof_bitwrite16_compiler(impl));
    } else {
      crypto_xof = mceliece_xof_bitwrite16;
      printf("xof_bitwrite16 selected implementation %s compiler %s\n",mceliece_xof_bitwrite16_implementation(),mceliece_xof_bitwrite16_compiler());
    }
    randombytes(h,MAXTEST_BYTES);
    randombytes(m,MAXTEST_BYTES);
    hlen = 32;
    mlen = 0;
    while (mlen <= MAXTEST_BYTES) {
      randombytes(m,mlen);
      for (long long i = 0;i <= TIMINGS;++i) {
        t[i] = cpucycles();
        crypto_xof(h,hlen,m,mlen);
      }
      t_print("xof_bitwrite16",impl,mlen);
      mlen += 1+mlen/2;
    }
    mlen = 32;
    hlen = 1;
    while (hlen <= MAXTEST_BYTES) {
      randombytes(h,hlen);
      for (long long i = 0;i <= TIMINGS;++i) {
        t[i] = cpucycles();
        crypto_xof(h,hlen,m,mlen);
      }
      t_print("xof_bitwrite16",impl,-hlen);
      hlen += 1+hlen/2;
    }
  }
  free(mstorage);
  free(hstorage);
}

static void measure_kem_6960119(void)
{
  if (targeto && strcmp(targeto,"kem")) return;
  if (targetp && strcmp(targetp,"6960119")) return;
  void *pstorage = callocplus(mceliece_kem_6960119_PUBLICKEYBYTES);
  unsigned char *p = (unsigned char *) aligned(pstorage);
  void *sstorage = callocplus(mceliece_kem_6960119_SECRETKEYBYTES);
  unsigned char *s = (unsigned char *) aligned(sstorage);
  void *cstorage = callocplus(mceliece_kem_6960119_CIPHERTEXTBYTES);
  unsigned char *c = (unsigned char *) aligned(cstorage);
  void *kstorage = callocplus(mceliece_kem_6960119_BYTES);
  unsigned char *k = (unsigned char *) aligned(kstorage);
  void *Tstorage = callocplus(mceliece_kem_6960119_BYTES);
  unsigned char *T = (unsigned char *) aligned(Tstorage);

  for (long long impl = -1;impl < mceliece_numimpl_kem_6960119();++impl) {
    void (*crypto_kem_keypair)(unsigned char *,unsigned char *);
    int (*crypto_kem_enc)(unsigned char *,unsigned char *,const unsigned char *);
    int (*crypto_kem_dec)(unsigned char *,const unsigned char *,const unsigned char *);
    if (targeti && strcmp(targeti,mceliece_dispatch_kem_6960119_implementation(impl))) continue;
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
    randombytes(p,mceliece_kem_6960119_PUBLICKEYBYTES);
    randombytes(s,mceliece_kem_6960119_SECRETKEYBYTES);
    randombytes(c,mceliece_kem_6960119_CIPHERTEXTBYTES);
    randombytes(k,mceliece_kem_6960119_BYTES);
    randombytes(T,mceliece_kem_6960119_BYTES);
    for (long long i = 0;i <= TIMINGS;++i) {
      t[i] = cpucycles();
      crypto_kem_keypair(p,s);
    }
    t_print("kem_6960119_keypair",impl,mceliece_kem_6960119_PUBLICKEYBYTES);
    for (long long i = 0;i <= TIMINGS;++i) {
      t[i] = cpucycles();
      crypto_kem_enc(c,k,p);
    }
    t_print("kem_6960119_enc",impl,mceliece_kem_6960119_CIPHERTEXTBYTES);
    for (long long i = 0;i <= TIMINGS;++i) {
      t[i] = cpucycles();
      crypto_kem_dec(T,c,s);
    }
    t_print("kem_6960119_dec",impl,mceliece_kem_6960119_BYTES);
  }
  free(Tstorage);
  free(kstorage);
  free(cstorage);
  free(sstorage);
  free(pstorage);
}

static void measure_kem_6960119f(void)
{
  if (targeto && strcmp(targeto,"kem")) return;
  if (targetp && strcmp(targetp,"6960119f")) return;
  void *pstorage = callocplus(mceliece_kem_6960119f_PUBLICKEYBYTES);
  unsigned char *p = (unsigned char *) aligned(pstorage);
  void *sstorage = callocplus(mceliece_kem_6960119f_SECRETKEYBYTES);
  unsigned char *s = (unsigned char *) aligned(sstorage);
  void *cstorage = callocplus(mceliece_kem_6960119f_CIPHERTEXTBYTES);
  unsigned char *c = (unsigned char *) aligned(cstorage);
  void *kstorage = callocplus(mceliece_kem_6960119f_BYTES);
  unsigned char *k = (unsigned char *) aligned(kstorage);
  void *Tstorage = callocplus(mceliece_kem_6960119f_BYTES);
  unsigned char *T = (unsigned char *) aligned(Tstorage);

  for (long long impl = -1;impl < mceliece_numimpl_kem_6960119f();++impl) {
    void (*crypto_kem_keypair)(unsigned char *,unsigned char *);
    int (*crypto_kem_enc)(unsigned char *,unsigned char *,const unsigned char *);
    int (*crypto_kem_dec)(unsigned char *,const unsigned char *,const unsigned char *);
    if (targeti && strcmp(targeti,mceliece_dispatch_kem_6960119f_implementation(impl))) continue;
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
    randombytes(p,mceliece_kem_6960119f_PUBLICKEYBYTES);
    randombytes(s,mceliece_kem_6960119f_SECRETKEYBYTES);
    randombytes(c,mceliece_kem_6960119f_CIPHERTEXTBYTES);
    randombytes(k,mceliece_kem_6960119f_BYTES);
    randombytes(T,mceliece_kem_6960119f_BYTES);
    for (long long i = 0;i <= TIMINGS;++i) {
      t[i] = cpucycles();
      crypto_kem_keypair(p,s);
    }
    t_print("kem_6960119f_keypair",impl,mceliece_kem_6960119f_PUBLICKEYBYTES);
    for (long long i = 0;i <= TIMINGS;++i) {
      t[i] = cpucycles();
      crypto_kem_enc(c,k,p);
    }
    t_print("kem_6960119f_enc",impl,mceliece_kem_6960119f_CIPHERTEXTBYTES);
    for (long long i = 0;i <= TIMINGS;++i) {
      t[i] = cpucycles();
      crypto_kem_dec(T,c,s);
    }
    t_print("kem_6960119f_dec",impl,mceliece_kem_6960119f_BYTES);
  }
  free(Tstorage);
  free(kstorage);
  free(cstorage);
  free(sstorage);
  free(pstorage);
}

static void measure_kem_6960119pc(void)
{
  if (targeto && strcmp(targeto,"kem")) return;
  if (targetp && strcmp(targetp,"6960119pc")) return;
  void *pstorage = callocplus(mceliece_kem_6960119pc_PUBLICKEYBYTES);
  unsigned char *p = (unsigned char *) aligned(pstorage);
  void *sstorage = callocplus(mceliece_kem_6960119pc_SECRETKEYBYTES);
  unsigned char *s = (unsigned char *) aligned(sstorage);
  void *cstorage = callocplus(mceliece_kem_6960119pc_CIPHERTEXTBYTES);
  unsigned char *c = (unsigned char *) aligned(cstorage);
  void *kstorage = callocplus(mceliece_kem_6960119pc_BYTES);
  unsigned char *k = (unsigned char *) aligned(kstorage);
  void *Tstorage = callocplus(mceliece_kem_6960119pc_BYTES);
  unsigned char *T = (unsigned char *) aligned(Tstorage);

  for (long long impl = -1;impl < mceliece_numimpl_kem_6960119pc();++impl) {
    void (*crypto_kem_keypair)(unsigned char *,unsigned char *);
    int (*crypto_kem_enc)(unsigned char *,unsigned char *,const unsigned char *);
    int (*crypto_kem_dec)(unsigned char *,const unsigned char *,const unsigned char *);
    if (targeti && strcmp(targeti,mceliece_dispatch_kem_6960119pc_implementation(impl))) continue;
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
    randombytes(p,mceliece_kem_6960119pc_PUBLICKEYBYTES);
    randombytes(s,mceliece_kem_6960119pc_SECRETKEYBYTES);
    randombytes(c,mceliece_kem_6960119pc_CIPHERTEXTBYTES);
    randombytes(k,mceliece_kem_6960119pc_BYTES);
    randombytes(T,mceliece_kem_6960119pc_BYTES);
    for (long long i = 0;i <= TIMINGS;++i) {
      t[i] = cpucycles();
      crypto_kem_keypair(p,s);
    }
    t_print("kem_6960119pc_keypair",impl,mceliece_kem_6960119pc_PUBLICKEYBYTES);
    for (long long i = 0;i <= TIMINGS;++i) {
      t[i] = cpucycles();
      crypto_kem_enc(c,k,p);
    }
    t_print("kem_6960119pc_enc",impl,mceliece_kem_6960119pc_CIPHERTEXTBYTES);
    for (long long i = 0;i <= TIMINGS;++i) {
      t[i] = cpucycles();
      crypto_kem_dec(T,c,s);
    }
    t_print("kem_6960119pc_dec",impl,mceliece_kem_6960119pc_BYTES);
  }
  free(Tstorage);
  free(kstorage);
  free(cstorage);
  free(sstorage);
  free(pstorage);
}

static void measure_kem_6960119pcf(void)
{
  if (targeto && strcmp(targeto,"kem")) return;
  if (targetp && strcmp(targetp,"6960119pcf")) return;
  void *pstorage = callocplus(mceliece_kem_6960119pcf_PUBLICKEYBYTES);
  unsigned char *p = (unsigned char *) aligned(pstorage);
  void *sstorage = callocplus(mceliece_kem_6960119pcf_SECRETKEYBYTES);
  unsigned char *s = (unsigned char *) aligned(sstorage);
  void *cstorage = callocplus(mceliece_kem_6960119pcf_CIPHERTEXTBYTES);
  unsigned char *c = (unsigned char *) aligned(cstorage);
  void *kstorage = callocplus(mceliece_kem_6960119pcf_BYTES);
  unsigned char *k = (unsigned char *) aligned(kstorage);
  void *Tstorage = callocplus(mceliece_kem_6960119pcf_BYTES);
  unsigned char *T = (unsigned char *) aligned(Tstorage);

  for (long long impl = -1;impl < mceliece_numimpl_kem_6960119pcf();++impl) {
    void (*crypto_kem_keypair)(unsigned char *,unsigned char *);
    int (*crypto_kem_enc)(unsigned char *,unsigned char *,const unsigned char *);
    int (*crypto_kem_dec)(unsigned char *,const unsigned char *,const unsigned char *);
    if (targeti && strcmp(targeti,mceliece_dispatch_kem_6960119pcf_implementation(impl))) continue;
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
    randombytes(p,mceliece_kem_6960119pcf_PUBLICKEYBYTES);
    randombytes(s,mceliece_kem_6960119pcf_SECRETKEYBYTES);
    randombytes(c,mceliece_kem_6960119pcf_CIPHERTEXTBYTES);
    randombytes(k,mceliece_kem_6960119pcf_BYTES);
    randombytes(T,mceliece_kem_6960119pcf_BYTES);
    for (long long i = 0;i <= TIMINGS;++i) {
      t[i] = cpucycles();
      crypto_kem_keypair(p,s);
    }
    t_print("kem_6960119pcf_keypair",impl,mceliece_kem_6960119pcf_PUBLICKEYBYTES);
    for (long long i = 0;i <= TIMINGS;++i) {
      t[i] = cpucycles();
      crypto_kem_enc(c,k,p);
    }
    t_print("kem_6960119pcf_enc",impl,mceliece_kem_6960119pcf_CIPHERTEXTBYTES);
    for (long long i = 0;i <= TIMINGS;++i) {
      t[i] = cpucycles();
      crypto_kem_dec(T,c,s);
    }
    t_print("kem_6960119pcf_dec",impl,mceliece_kem_6960119pcf_BYTES);
  }
  free(Tstorage);
  free(kstorage);
  free(cstorage);
  free(sstorage);
  free(pstorage);
}

static void measure_kem_6688128(void)
{
  if (targeto && strcmp(targeto,"kem")) return;
  if (targetp && strcmp(targetp,"6688128")) return;
  void *pstorage = callocplus(mceliece_kem_6688128_PUBLICKEYBYTES);
  unsigned char *p = (unsigned char *) aligned(pstorage);
  void *sstorage = callocplus(mceliece_kem_6688128_SECRETKEYBYTES);
  unsigned char *s = (unsigned char *) aligned(sstorage);
  void *cstorage = callocplus(mceliece_kem_6688128_CIPHERTEXTBYTES);
  unsigned char *c = (unsigned char *) aligned(cstorage);
  void *kstorage = callocplus(mceliece_kem_6688128_BYTES);
  unsigned char *k = (unsigned char *) aligned(kstorage);
  void *Tstorage = callocplus(mceliece_kem_6688128_BYTES);
  unsigned char *T = (unsigned char *) aligned(Tstorage);

  for (long long impl = -1;impl < mceliece_numimpl_kem_6688128();++impl) {
    void (*crypto_kem_keypair)(unsigned char *,unsigned char *);
    int (*crypto_kem_enc)(unsigned char *,unsigned char *,const unsigned char *);
    int (*crypto_kem_dec)(unsigned char *,const unsigned char *,const unsigned char *);
    if (targeti && strcmp(targeti,mceliece_dispatch_kem_6688128_implementation(impl))) continue;
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
    randombytes(p,mceliece_kem_6688128_PUBLICKEYBYTES);
    randombytes(s,mceliece_kem_6688128_SECRETKEYBYTES);
    randombytes(c,mceliece_kem_6688128_CIPHERTEXTBYTES);
    randombytes(k,mceliece_kem_6688128_BYTES);
    randombytes(T,mceliece_kem_6688128_BYTES);
    for (long long i = 0;i <= TIMINGS;++i) {
      t[i] = cpucycles();
      crypto_kem_keypair(p,s);
    }
    t_print("kem_6688128_keypair",impl,mceliece_kem_6688128_PUBLICKEYBYTES);
    for (long long i = 0;i <= TIMINGS;++i) {
      t[i] = cpucycles();
      crypto_kem_enc(c,k,p);
    }
    t_print("kem_6688128_enc",impl,mceliece_kem_6688128_CIPHERTEXTBYTES);
    for (long long i = 0;i <= TIMINGS;++i) {
      t[i] = cpucycles();
      crypto_kem_dec(T,c,s);
    }
    t_print("kem_6688128_dec",impl,mceliece_kem_6688128_BYTES);
  }
  free(Tstorage);
  free(kstorage);
  free(cstorage);
  free(sstorage);
  free(pstorage);
}

static void measure_kem_6688128f(void)
{
  if (targeto && strcmp(targeto,"kem")) return;
  if (targetp && strcmp(targetp,"6688128f")) return;
  void *pstorage = callocplus(mceliece_kem_6688128f_PUBLICKEYBYTES);
  unsigned char *p = (unsigned char *) aligned(pstorage);
  void *sstorage = callocplus(mceliece_kem_6688128f_SECRETKEYBYTES);
  unsigned char *s = (unsigned char *) aligned(sstorage);
  void *cstorage = callocplus(mceliece_kem_6688128f_CIPHERTEXTBYTES);
  unsigned char *c = (unsigned char *) aligned(cstorage);
  void *kstorage = callocplus(mceliece_kem_6688128f_BYTES);
  unsigned char *k = (unsigned char *) aligned(kstorage);
  void *Tstorage = callocplus(mceliece_kem_6688128f_BYTES);
  unsigned char *T = (unsigned char *) aligned(Tstorage);

  for (long long impl = -1;impl < mceliece_numimpl_kem_6688128f();++impl) {
    void (*crypto_kem_keypair)(unsigned char *,unsigned char *);
    int (*crypto_kem_enc)(unsigned char *,unsigned char *,const unsigned char *);
    int (*crypto_kem_dec)(unsigned char *,const unsigned char *,const unsigned char *);
    if (targeti && strcmp(targeti,mceliece_dispatch_kem_6688128f_implementation(impl))) continue;
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
    randombytes(p,mceliece_kem_6688128f_PUBLICKEYBYTES);
    randombytes(s,mceliece_kem_6688128f_SECRETKEYBYTES);
    randombytes(c,mceliece_kem_6688128f_CIPHERTEXTBYTES);
    randombytes(k,mceliece_kem_6688128f_BYTES);
    randombytes(T,mceliece_kem_6688128f_BYTES);
    for (long long i = 0;i <= TIMINGS;++i) {
      t[i] = cpucycles();
      crypto_kem_keypair(p,s);
    }
    t_print("kem_6688128f_keypair",impl,mceliece_kem_6688128f_PUBLICKEYBYTES);
    for (long long i = 0;i <= TIMINGS;++i) {
      t[i] = cpucycles();
      crypto_kem_enc(c,k,p);
    }
    t_print("kem_6688128f_enc",impl,mceliece_kem_6688128f_CIPHERTEXTBYTES);
    for (long long i = 0;i <= TIMINGS;++i) {
      t[i] = cpucycles();
      crypto_kem_dec(T,c,s);
    }
    t_print("kem_6688128f_dec",impl,mceliece_kem_6688128f_BYTES);
  }
  free(Tstorage);
  free(kstorage);
  free(cstorage);
  free(sstorage);
  free(pstorage);
}

static void measure_kem_6688128pc(void)
{
  if (targeto && strcmp(targeto,"kem")) return;
  if (targetp && strcmp(targetp,"6688128pc")) return;
  void *pstorage = callocplus(mceliece_kem_6688128pc_PUBLICKEYBYTES);
  unsigned char *p = (unsigned char *) aligned(pstorage);
  void *sstorage = callocplus(mceliece_kem_6688128pc_SECRETKEYBYTES);
  unsigned char *s = (unsigned char *) aligned(sstorage);
  void *cstorage = callocplus(mceliece_kem_6688128pc_CIPHERTEXTBYTES);
  unsigned char *c = (unsigned char *) aligned(cstorage);
  void *kstorage = callocplus(mceliece_kem_6688128pc_BYTES);
  unsigned char *k = (unsigned char *) aligned(kstorage);
  void *Tstorage = callocplus(mceliece_kem_6688128pc_BYTES);
  unsigned char *T = (unsigned char *) aligned(Tstorage);

  for (long long impl = -1;impl < mceliece_numimpl_kem_6688128pc();++impl) {
    void (*crypto_kem_keypair)(unsigned char *,unsigned char *);
    int (*crypto_kem_enc)(unsigned char *,unsigned char *,const unsigned char *);
    int (*crypto_kem_dec)(unsigned char *,const unsigned char *,const unsigned char *);
    if (targeti && strcmp(targeti,mceliece_dispatch_kem_6688128pc_implementation(impl))) continue;
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
    randombytes(p,mceliece_kem_6688128pc_PUBLICKEYBYTES);
    randombytes(s,mceliece_kem_6688128pc_SECRETKEYBYTES);
    randombytes(c,mceliece_kem_6688128pc_CIPHERTEXTBYTES);
    randombytes(k,mceliece_kem_6688128pc_BYTES);
    randombytes(T,mceliece_kem_6688128pc_BYTES);
    for (long long i = 0;i <= TIMINGS;++i) {
      t[i] = cpucycles();
      crypto_kem_keypair(p,s);
    }
    t_print("kem_6688128pc_keypair",impl,mceliece_kem_6688128pc_PUBLICKEYBYTES);
    for (long long i = 0;i <= TIMINGS;++i) {
      t[i] = cpucycles();
      crypto_kem_enc(c,k,p);
    }
    t_print("kem_6688128pc_enc",impl,mceliece_kem_6688128pc_CIPHERTEXTBYTES);
    for (long long i = 0;i <= TIMINGS;++i) {
      t[i] = cpucycles();
      crypto_kem_dec(T,c,s);
    }
    t_print("kem_6688128pc_dec",impl,mceliece_kem_6688128pc_BYTES);
  }
  free(Tstorage);
  free(kstorage);
  free(cstorage);
  free(sstorage);
  free(pstorage);
}

static void measure_kem_6688128pcf(void)
{
  if (targeto && strcmp(targeto,"kem")) return;
  if (targetp && strcmp(targetp,"6688128pcf")) return;
  void *pstorage = callocplus(mceliece_kem_6688128pcf_PUBLICKEYBYTES);
  unsigned char *p = (unsigned char *) aligned(pstorage);
  void *sstorage = callocplus(mceliece_kem_6688128pcf_SECRETKEYBYTES);
  unsigned char *s = (unsigned char *) aligned(sstorage);
  void *cstorage = callocplus(mceliece_kem_6688128pcf_CIPHERTEXTBYTES);
  unsigned char *c = (unsigned char *) aligned(cstorage);
  void *kstorage = callocplus(mceliece_kem_6688128pcf_BYTES);
  unsigned char *k = (unsigned char *) aligned(kstorage);
  void *Tstorage = callocplus(mceliece_kem_6688128pcf_BYTES);
  unsigned char *T = (unsigned char *) aligned(Tstorage);

  for (long long impl = -1;impl < mceliece_numimpl_kem_6688128pcf();++impl) {
    void (*crypto_kem_keypair)(unsigned char *,unsigned char *);
    int (*crypto_kem_enc)(unsigned char *,unsigned char *,const unsigned char *);
    int (*crypto_kem_dec)(unsigned char *,const unsigned char *,const unsigned char *);
    if (targeti && strcmp(targeti,mceliece_dispatch_kem_6688128pcf_implementation(impl))) continue;
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
    randombytes(p,mceliece_kem_6688128pcf_PUBLICKEYBYTES);
    randombytes(s,mceliece_kem_6688128pcf_SECRETKEYBYTES);
    randombytes(c,mceliece_kem_6688128pcf_CIPHERTEXTBYTES);
    randombytes(k,mceliece_kem_6688128pcf_BYTES);
    randombytes(T,mceliece_kem_6688128pcf_BYTES);
    for (long long i = 0;i <= TIMINGS;++i) {
      t[i] = cpucycles();
      crypto_kem_keypair(p,s);
    }
    t_print("kem_6688128pcf_keypair",impl,mceliece_kem_6688128pcf_PUBLICKEYBYTES);
    for (long long i = 0;i <= TIMINGS;++i) {
      t[i] = cpucycles();
      crypto_kem_enc(c,k,p);
    }
    t_print("kem_6688128pcf_enc",impl,mceliece_kem_6688128pcf_CIPHERTEXTBYTES);
    for (long long i = 0;i <= TIMINGS;++i) {
      t[i] = cpucycles();
      crypto_kem_dec(T,c,s);
    }
    t_print("kem_6688128pcf_dec",impl,mceliece_kem_6688128pcf_BYTES);
  }
  free(Tstorage);
  free(kstorage);
  free(cstorage);
  free(sstorage);
  free(pstorage);
}

static void measure_kem_8192128(void)
{
  if (targeto && strcmp(targeto,"kem")) return;
  if (targetp && strcmp(targetp,"8192128")) return;
  void *pstorage = callocplus(mceliece_kem_8192128_PUBLICKEYBYTES);
  unsigned char *p = (unsigned char *) aligned(pstorage);
  void *sstorage = callocplus(mceliece_kem_8192128_SECRETKEYBYTES);
  unsigned char *s = (unsigned char *) aligned(sstorage);
  void *cstorage = callocplus(mceliece_kem_8192128_CIPHERTEXTBYTES);
  unsigned char *c = (unsigned char *) aligned(cstorage);
  void *kstorage = callocplus(mceliece_kem_8192128_BYTES);
  unsigned char *k = (unsigned char *) aligned(kstorage);
  void *Tstorage = callocplus(mceliece_kem_8192128_BYTES);
  unsigned char *T = (unsigned char *) aligned(Tstorage);

  for (long long impl = -1;impl < mceliece_numimpl_kem_8192128();++impl) {
    void (*crypto_kem_keypair)(unsigned char *,unsigned char *);
    int (*crypto_kem_enc)(unsigned char *,unsigned char *,const unsigned char *);
    int (*crypto_kem_dec)(unsigned char *,const unsigned char *,const unsigned char *);
    if (targeti && strcmp(targeti,mceliece_dispatch_kem_8192128_implementation(impl))) continue;
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
    randombytes(p,mceliece_kem_8192128_PUBLICKEYBYTES);
    randombytes(s,mceliece_kem_8192128_SECRETKEYBYTES);
    randombytes(c,mceliece_kem_8192128_CIPHERTEXTBYTES);
    randombytes(k,mceliece_kem_8192128_BYTES);
    randombytes(T,mceliece_kem_8192128_BYTES);
    for (long long i = 0;i <= TIMINGS;++i) {
      t[i] = cpucycles();
      crypto_kem_keypair(p,s);
    }
    t_print("kem_8192128_keypair",impl,mceliece_kem_8192128_PUBLICKEYBYTES);
    for (long long i = 0;i <= TIMINGS;++i) {
      t[i] = cpucycles();
      crypto_kem_enc(c,k,p);
    }
    t_print("kem_8192128_enc",impl,mceliece_kem_8192128_CIPHERTEXTBYTES);
    for (long long i = 0;i <= TIMINGS;++i) {
      t[i] = cpucycles();
      crypto_kem_dec(T,c,s);
    }
    t_print("kem_8192128_dec",impl,mceliece_kem_8192128_BYTES);
  }
  free(Tstorage);
  free(kstorage);
  free(cstorage);
  free(sstorage);
  free(pstorage);
}

static void measure_kem_8192128f(void)
{
  if (targeto && strcmp(targeto,"kem")) return;
  if (targetp && strcmp(targetp,"8192128f")) return;
  void *pstorage = callocplus(mceliece_kem_8192128f_PUBLICKEYBYTES);
  unsigned char *p = (unsigned char *) aligned(pstorage);
  void *sstorage = callocplus(mceliece_kem_8192128f_SECRETKEYBYTES);
  unsigned char *s = (unsigned char *) aligned(sstorage);
  void *cstorage = callocplus(mceliece_kem_8192128f_CIPHERTEXTBYTES);
  unsigned char *c = (unsigned char *) aligned(cstorage);
  void *kstorage = callocplus(mceliece_kem_8192128f_BYTES);
  unsigned char *k = (unsigned char *) aligned(kstorage);
  void *Tstorage = callocplus(mceliece_kem_8192128f_BYTES);
  unsigned char *T = (unsigned char *) aligned(Tstorage);

  for (long long impl = -1;impl < mceliece_numimpl_kem_8192128f();++impl) {
    void (*crypto_kem_keypair)(unsigned char *,unsigned char *);
    int (*crypto_kem_enc)(unsigned char *,unsigned char *,const unsigned char *);
    int (*crypto_kem_dec)(unsigned char *,const unsigned char *,const unsigned char *);
    if (targeti && strcmp(targeti,mceliece_dispatch_kem_8192128f_implementation(impl))) continue;
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
    randombytes(p,mceliece_kem_8192128f_PUBLICKEYBYTES);
    randombytes(s,mceliece_kem_8192128f_SECRETKEYBYTES);
    randombytes(c,mceliece_kem_8192128f_CIPHERTEXTBYTES);
    randombytes(k,mceliece_kem_8192128f_BYTES);
    randombytes(T,mceliece_kem_8192128f_BYTES);
    for (long long i = 0;i <= TIMINGS;++i) {
      t[i] = cpucycles();
      crypto_kem_keypair(p,s);
    }
    t_print("kem_8192128f_keypair",impl,mceliece_kem_8192128f_PUBLICKEYBYTES);
    for (long long i = 0;i <= TIMINGS;++i) {
      t[i] = cpucycles();
      crypto_kem_enc(c,k,p);
    }
    t_print("kem_8192128f_enc",impl,mceliece_kem_8192128f_CIPHERTEXTBYTES);
    for (long long i = 0;i <= TIMINGS;++i) {
      t[i] = cpucycles();
      crypto_kem_dec(T,c,s);
    }
    t_print("kem_8192128f_dec",impl,mceliece_kem_8192128f_BYTES);
  }
  free(Tstorage);
  free(kstorage);
  free(cstorage);
  free(sstorage);
  free(pstorage);
}

static void measure_kem_8192128pc(void)
{
  if (targeto && strcmp(targeto,"kem")) return;
  if (targetp && strcmp(targetp,"8192128pc")) return;
  void *pstorage = callocplus(mceliece_kem_8192128pc_PUBLICKEYBYTES);
  unsigned char *p = (unsigned char *) aligned(pstorage);
  void *sstorage = callocplus(mceliece_kem_8192128pc_SECRETKEYBYTES);
  unsigned char *s = (unsigned char *) aligned(sstorage);
  void *cstorage = callocplus(mceliece_kem_8192128pc_CIPHERTEXTBYTES);
  unsigned char *c = (unsigned char *) aligned(cstorage);
  void *kstorage = callocplus(mceliece_kem_8192128pc_BYTES);
  unsigned char *k = (unsigned char *) aligned(kstorage);
  void *Tstorage = callocplus(mceliece_kem_8192128pc_BYTES);
  unsigned char *T = (unsigned char *) aligned(Tstorage);

  for (long long impl = -1;impl < mceliece_numimpl_kem_8192128pc();++impl) {
    void (*crypto_kem_keypair)(unsigned char *,unsigned char *);
    int (*crypto_kem_enc)(unsigned char *,unsigned char *,const unsigned char *);
    int (*crypto_kem_dec)(unsigned char *,const unsigned char *,const unsigned char *);
    if (targeti && strcmp(targeti,mceliece_dispatch_kem_8192128pc_implementation(impl))) continue;
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
    randombytes(p,mceliece_kem_8192128pc_PUBLICKEYBYTES);
    randombytes(s,mceliece_kem_8192128pc_SECRETKEYBYTES);
    randombytes(c,mceliece_kem_8192128pc_CIPHERTEXTBYTES);
    randombytes(k,mceliece_kem_8192128pc_BYTES);
    randombytes(T,mceliece_kem_8192128pc_BYTES);
    for (long long i = 0;i <= TIMINGS;++i) {
      t[i] = cpucycles();
      crypto_kem_keypair(p,s);
    }
    t_print("kem_8192128pc_keypair",impl,mceliece_kem_8192128pc_PUBLICKEYBYTES);
    for (long long i = 0;i <= TIMINGS;++i) {
      t[i] = cpucycles();
      crypto_kem_enc(c,k,p);
    }
    t_print("kem_8192128pc_enc",impl,mceliece_kem_8192128pc_CIPHERTEXTBYTES);
    for (long long i = 0;i <= TIMINGS;++i) {
      t[i] = cpucycles();
      crypto_kem_dec(T,c,s);
    }
    t_print("kem_8192128pc_dec",impl,mceliece_kem_8192128pc_BYTES);
  }
  free(Tstorage);
  free(kstorage);
  free(cstorage);
  free(sstorage);
  free(pstorage);
}

static void measure_kem_8192128pcf(void)
{
  if (targeto && strcmp(targeto,"kem")) return;
  if (targetp && strcmp(targetp,"8192128pcf")) return;
  void *pstorage = callocplus(mceliece_kem_8192128pcf_PUBLICKEYBYTES);
  unsigned char *p = (unsigned char *) aligned(pstorage);
  void *sstorage = callocplus(mceliece_kem_8192128pcf_SECRETKEYBYTES);
  unsigned char *s = (unsigned char *) aligned(sstorage);
  void *cstorage = callocplus(mceliece_kem_8192128pcf_CIPHERTEXTBYTES);
  unsigned char *c = (unsigned char *) aligned(cstorage);
  void *kstorage = callocplus(mceliece_kem_8192128pcf_BYTES);
  unsigned char *k = (unsigned char *) aligned(kstorage);
  void *Tstorage = callocplus(mceliece_kem_8192128pcf_BYTES);
  unsigned char *T = (unsigned char *) aligned(Tstorage);

  for (long long impl = -1;impl < mceliece_numimpl_kem_8192128pcf();++impl) {
    void (*crypto_kem_keypair)(unsigned char *,unsigned char *);
    int (*crypto_kem_enc)(unsigned char *,unsigned char *,const unsigned char *);
    int (*crypto_kem_dec)(unsigned char *,const unsigned char *,const unsigned char *);
    if (targeti && strcmp(targeti,mceliece_dispatch_kem_8192128pcf_implementation(impl))) continue;
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
    randombytes(p,mceliece_kem_8192128pcf_PUBLICKEYBYTES);
    randombytes(s,mceliece_kem_8192128pcf_SECRETKEYBYTES);
    randombytes(c,mceliece_kem_8192128pcf_CIPHERTEXTBYTES);
    randombytes(k,mceliece_kem_8192128pcf_BYTES);
    randombytes(T,mceliece_kem_8192128pcf_BYTES);
    for (long long i = 0;i <= TIMINGS;++i) {
      t[i] = cpucycles();
      crypto_kem_keypair(p,s);
    }
    t_print("kem_8192128pcf_keypair",impl,mceliece_kem_8192128pcf_PUBLICKEYBYTES);
    for (long long i = 0;i <= TIMINGS;++i) {
      t[i] = cpucycles();
      crypto_kem_enc(c,k,p);
    }
    t_print("kem_8192128pcf_enc",impl,mceliece_kem_8192128pcf_CIPHERTEXTBYTES);
    for (long long i = 0;i <= TIMINGS;++i) {
      t[i] = cpucycles();
      crypto_kem_dec(T,c,s);
    }
    t_print("kem_8192128pcf_dec",impl,mceliece_kem_8192128pcf_BYTES);
  }
  free(Tstorage);
  free(kstorage);
  free(cstorage);
  free(sstorage);
  free(pstorage);
}

static void measure_kem_460896(void)
{
  if (targeto && strcmp(targeto,"kem")) return;
  if (targetp && strcmp(targetp,"460896")) return;
  void *pstorage = callocplus(mceliece_kem_460896_PUBLICKEYBYTES);
  unsigned char *p = (unsigned char *) aligned(pstorage);
  void *sstorage = callocplus(mceliece_kem_460896_SECRETKEYBYTES);
  unsigned char *s = (unsigned char *) aligned(sstorage);
  void *cstorage = callocplus(mceliece_kem_460896_CIPHERTEXTBYTES);
  unsigned char *c = (unsigned char *) aligned(cstorage);
  void *kstorage = callocplus(mceliece_kem_460896_BYTES);
  unsigned char *k = (unsigned char *) aligned(kstorage);
  void *Tstorage = callocplus(mceliece_kem_460896_BYTES);
  unsigned char *T = (unsigned char *) aligned(Tstorage);

  for (long long impl = -1;impl < mceliece_numimpl_kem_460896();++impl) {
    void (*crypto_kem_keypair)(unsigned char *,unsigned char *);
    int (*crypto_kem_enc)(unsigned char *,unsigned char *,const unsigned char *);
    int (*crypto_kem_dec)(unsigned char *,const unsigned char *,const unsigned char *);
    if (targeti && strcmp(targeti,mceliece_dispatch_kem_460896_implementation(impl))) continue;
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
    randombytes(p,mceliece_kem_460896_PUBLICKEYBYTES);
    randombytes(s,mceliece_kem_460896_SECRETKEYBYTES);
    randombytes(c,mceliece_kem_460896_CIPHERTEXTBYTES);
    randombytes(k,mceliece_kem_460896_BYTES);
    randombytes(T,mceliece_kem_460896_BYTES);
    for (long long i = 0;i <= TIMINGS;++i) {
      t[i] = cpucycles();
      crypto_kem_keypair(p,s);
    }
    t_print("kem_460896_keypair",impl,mceliece_kem_460896_PUBLICKEYBYTES);
    for (long long i = 0;i <= TIMINGS;++i) {
      t[i] = cpucycles();
      crypto_kem_enc(c,k,p);
    }
    t_print("kem_460896_enc",impl,mceliece_kem_460896_CIPHERTEXTBYTES);
    for (long long i = 0;i <= TIMINGS;++i) {
      t[i] = cpucycles();
      crypto_kem_dec(T,c,s);
    }
    t_print("kem_460896_dec",impl,mceliece_kem_460896_BYTES);
  }
  free(Tstorage);
  free(kstorage);
  free(cstorage);
  free(sstorage);
  free(pstorage);
}

static void measure_kem_460896f(void)
{
  if (targeto && strcmp(targeto,"kem")) return;
  if (targetp && strcmp(targetp,"460896f")) return;
  void *pstorage = callocplus(mceliece_kem_460896f_PUBLICKEYBYTES);
  unsigned char *p = (unsigned char *) aligned(pstorage);
  void *sstorage = callocplus(mceliece_kem_460896f_SECRETKEYBYTES);
  unsigned char *s = (unsigned char *) aligned(sstorage);
  void *cstorage = callocplus(mceliece_kem_460896f_CIPHERTEXTBYTES);
  unsigned char *c = (unsigned char *) aligned(cstorage);
  void *kstorage = callocplus(mceliece_kem_460896f_BYTES);
  unsigned char *k = (unsigned char *) aligned(kstorage);
  void *Tstorage = callocplus(mceliece_kem_460896f_BYTES);
  unsigned char *T = (unsigned char *) aligned(Tstorage);

  for (long long impl = -1;impl < mceliece_numimpl_kem_460896f();++impl) {
    void (*crypto_kem_keypair)(unsigned char *,unsigned char *);
    int (*crypto_kem_enc)(unsigned char *,unsigned char *,const unsigned char *);
    int (*crypto_kem_dec)(unsigned char *,const unsigned char *,const unsigned char *);
    if (targeti && strcmp(targeti,mceliece_dispatch_kem_460896f_implementation(impl))) continue;
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
    randombytes(p,mceliece_kem_460896f_PUBLICKEYBYTES);
    randombytes(s,mceliece_kem_460896f_SECRETKEYBYTES);
    randombytes(c,mceliece_kem_460896f_CIPHERTEXTBYTES);
    randombytes(k,mceliece_kem_460896f_BYTES);
    randombytes(T,mceliece_kem_460896f_BYTES);
    for (long long i = 0;i <= TIMINGS;++i) {
      t[i] = cpucycles();
      crypto_kem_keypair(p,s);
    }
    t_print("kem_460896f_keypair",impl,mceliece_kem_460896f_PUBLICKEYBYTES);
    for (long long i = 0;i <= TIMINGS;++i) {
      t[i] = cpucycles();
      crypto_kem_enc(c,k,p);
    }
    t_print("kem_460896f_enc",impl,mceliece_kem_460896f_CIPHERTEXTBYTES);
    for (long long i = 0;i <= TIMINGS;++i) {
      t[i] = cpucycles();
      crypto_kem_dec(T,c,s);
    }
    t_print("kem_460896f_dec",impl,mceliece_kem_460896f_BYTES);
  }
  free(Tstorage);
  free(kstorage);
  free(cstorage);
  free(sstorage);
  free(pstorage);
}

static void measure_kem_460896pc(void)
{
  if (targeto && strcmp(targeto,"kem")) return;
  if (targetp && strcmp(targetp,"460896pc")) return;
  void *pstorage = callocplus(mceliece_kem_460896pc_PUBLICKEYBYTES);
  unsigned char *p = (unsigned char *) aligned(pstorage);
  void *sstorage = callocplus(mceliece_kem_460896pc_SECRETKEYBYTES);
  unsigned char *s = (unsigned char *) aligned(sstorage);
  void *cstorage = callocplus(mceliece_kem_460896pc_CIPHERTEXTBYTES);
  unsigned char *c = (unsigned char *) aligned(cstorage);
  void *kstorage = callocplus(mceliece_kem_460896pc_BYTES);
  unsigned char *k = (unsigned char *) aligned(kstorage);
  void *Tstorage = callocplus(mceliece_kem_460896pc_BYTES);
  unsigned char *T = (unsigned char *) aligned(Tstorage);

  for (long long impl = -1;impl < mceliece_numimpl_kem_460896pc();++impl) {
    void (*crypto_kem_keypair)(unsigned char *,unsigned char *);
    int (*crypto_kem_enc)(unsigned char *,unsigned char *,const unsigned char *);
    int (*crypto_kem_dec)(unsigned char *,const unsigned char *,const unsigned char *);
    if (targeti && strcmp(targeti,mceliece_dispatch_kem_460896pc_implementation(impl))) continue;
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
    randombytes(p,mceliece_kem_460896pc_PUBLICKEYBYTES);
    randombytes(s,mceliece_kem_460896pc_SECRETKEYBYTES);
    randombytes(c,mceliece_kem_460896pc_CIPHERTEXTBYTES);
    randombytes(k,mceliece_kem_460896pc_BYTES);
    randombytes(T,mceliece_kem_460896pc_BYTES);
    for (long long i = 0;i <= TIMINGS;++i) {
      t[i] = cpucycles();
      crypto_kem_keypair(p,s);
    }
    t_print("kem_460896pc_keypair",impl,mceliece_kem_460896pc_PUBLICKEYBYTES);
    for (long long i = 0;i <= TIMINGS;++i) {
      t[i] = cpucycles();
      crypto_kem_enc(c,k,p);
    }
    t_print("kem_460896pc_enc",impl,mceliece_kem_460896pc_CIPHERTEXTBYTES);
    for (long long i = 0;i <= TIMINGS;++i) {
      t[i] = cpucycles();
      crypto_kem_dec(T,c,s);
    }
    t_print("kem_460896pc_dec",impl,mceliece_kem_460896pc_BYTES);
  }
  free(Tstorage);
  free(kstorage);
  free(cstorage);
  free(sstorage);
  free(pstorage);
}

static void measure_kem_460896pcf(void)
{
  if (targeto && strcmp(targeto,"kem")) return;
  if (targetp && strcmp(targetp,"460896pcf")) return;
  void *pstorage = callocplus(mceliece_kem_460896pcf_PUBLICKEYBYTES);
  unsigned char *p = (unsigned char *) aligned(pstorage);
  void *sstorage = callocplus(mceliece_kem_460896pcf_SECRETKEYBYTES);
  unsigned char *s = (unsigned char *) aligned(sstorage);
  void *cstorage = callocplus(mceliece_kem_460896pcf_CIPHERTEXTBYTES);
  unsigned char *c = (unsigned char *) aligned(cstorage);
  void *kstorage = callocplus(mceliece_kem_460896pcf_BYTES);
  unsigned char *k = (unsigned char *) aligned(kstorage);
  void *Tstorage = callocplus(mceliece_kem_460896pcf_BYTES);
  unsigned char *T = (unsigned char *) aligned(Tstorage);

  for (long long impl = -1;impl < mceliece_numimpl_kem_460896pcf();++impl) {
    void (*crypto_kem_keypair)(unsigned char *,unsigned char *);
    int (*crypto_kem_enc)(unsigned char *,unsigned char *,const unsigned char *);
    int (*crypto_kem_dec)(unsigned char *,const unsigned char *,const unsigned char *);
    if (targeti && strcmp(targeti,mceliece_dispatch_kem_460896pcf_implementation(impl))) continue;
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
    randombytes(p,mceliece_kem_460896pcf_PUBLICKEYBYTES);
    randombytes(s,mceliece_kem_460896pcf_SECRETKEYBYTES);
    randombytes(c,mceliece_kem_460896pcf_CIPHERTEXTBYTES);
    randombytes(k,mceliece_kem_460896pcf_BYTES);
    randombytes(T,mceliece_kem_460896pcf_BYTES);
    for (long long i = 0;i <= TIMINGS;++i) {
      t[i] = cpucycles();
      crypto_kem_keypair(p,s);
    }
    t_print("kem_460896pcf_keypair",impl,mceliece_kem_460896pcf_PUBLICKEYBYTES);
    for (long long i = 0;i <= TIMINGS;++i) {
      t[i] = cpucycles();
      crypto_kem_enc(c,k,p);
    }
    t_print("kem_460896pcf_enc",impl,mceliece_kem_460896pcf_CIPHERTEXTBYTES);
    for (long long i = 0;i <= TIMINGS;++i) {
      t[i] = cpucycles();
      crypto_kem_dec(T,c,s);
    }
    t_print("kem_460896pcf_dec",impl,mceliece_kem_460896pcf_BYTES);
  }
  free(Tstorage);
  free(kstorage);
  free(cstorage);
  free(sstorage);
  free(pstorage);
}

static void measure_kem_348864(void)
{
  if (targeto && strcmp(targeto,"kem")) return;
  if (targetp && strcmp(targetp,"348864")) return;
  void *pstorage = callocplus(mceliece_kem_348864_PUBLICKEYBYTES);
  unsigned char *p = (unsigned char *) aligned(pstorage);
  void *sstorage = callocplus(mceliece_kem_348864_SECRETKEYBYTES);
  unsigned char *s = (unsigned char *) aligned(sstorage);
  void *cstorage = callocplus(mceliece_kem_348864_CIPHERTEXTBYTES);
  unsigned char *c = (unsigned char *) aligned(cstorage);
  void *kstorage = callocplus(mceliece_kem_348864_BYTES);
  unsigned char *k = (unsigned char *) aligned(kstorage);
  void *Tstorage = callocplus(mceliece_kem_348864_BYTES);
  unsigned char *T = (unsigned char *) aligned(Tstorage);

  for (long long impl = -1;impl < mceliece_numimpl_kem_348864();++impl) {
    void (*crypto_kem_keypair)(unsigned char *,unsigned char *);
    int (*crypto_kem_enc)(unsigned char *,unsigned char *,const unsigned char *);
    int (*crypto_kem_dec)(unsigned char *,const unsigned char *,const unsigned char *);
    if (targeti && strcmp(targeti,mceliece_dispatch_kem_348864_implementation(impl))) continue;
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
    randombytes(p,mceliece_kem_348864_PUBLICKEYBYTES);
    randombytes(s,mceliece_kem_348864_SECRETKEYBYTES);
    randombytes(c,mceliece_kem_348864_CIPHERTEXTBYTES);
    randombytes(k,mceliece_kem_348864_BYTES);
    randombytes(T,mceliece_kem_348864_BYTES);
    for (long long i = 0;i <= TIMINGS;++i) {
      t[i] = cpucycles();
      crypto_kem_keypair(p,s);
    }
    t_print("kem_348864_keypair",impl,mceliece_kem_348864_PUBLICKEYBYTES);
    for (long long i = 0;i <= TIMINGS;++i) {
      t[i] = cpucycles();
      crypto_kem_enc(c,k,p);
    }
    t_print("kem_348864_enc",impl,mceliece_kem_348864_CIPHERTEXTBYTES);
    for (long long i = 0;i <= TIMINGS;++i) {
      t[i] = cpucycles();
      crypto_kem_dec(T,c,s);
    }
    t_print("kem_348864_dec",impl,mceliece_kem_348864_BYTES);
  }
  free(Tstorage);
  free(kstorage);
  free(cstorage);
  free(sstorage);
  free(pstorage);
}

static void measure_kem_348864f(void)
{
  if (targeto && strcmp(targeto,"kem")) return;
  if (targetp && strcmp(targetp,"348864f")) return;
  void *pstorage = callocplus(mceliece_kem_348864f_PUBLICKEYBYTES);
  unsigned char *p = (unsigned char *) aligned(pstorage);
  void *sstorage = callocplus(mceliece_kem_348864f_SECRETKEYBYTES);
  unsigned char *s = (unsigned char *) aligned(sstorage);
  void *cstorage = callocplus(mceliece_kem_348864f_CIPHERTEXTBYTES);
  unsigned char *c = (unsigned char *) aligned(cstorage);
  void *kstorage = callocplus(mceliece_kem_348864f_BYTES);
  unsigned char *k = (unsigned char *) aligned(kstorage);
  void *Tstorage = callocplus(mceliece_kem_348864f_BYTES);
  unsigned char *T = (unsigned char *) aligned(Tstorage);

  for (long long impl = -1;impl < mceliece_numimpl_kem_348864f();++impl) {
    void (*crypto_kem_keypair)(unsigned char *,unsigned char *);
    int (*crypto_kem_enc)(unsigned char *,unsigned char *,const unsigned char *);
    int (*crypto_kem_dec)(unsigned char *,const unsigned char *,const unsigned char *);
    if (targeti && strcmp(targeti,mceliece_dispatch_kem_348864f_implementation(impl))) continue;
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
    randombytes(p,mceliece_kem_348864f_PUBLICKEYBYTES);
    randombytes(s,mceliece_kem_348864f_SECRETKEYBYTES);
    randombytes(c,mceliece_kem_348864f_CIPHERTEXTBYTES);
    randombytes(k,mceliece_kem_348864f_BYTES);
    randombytes(T,mceliece_kem_348864f_BYTES);
    for (long long i = 0;i <= TIMINGS;++i) {
      t[i] = cpucycles();
      crypto_kem_keypair(p,s);
    }
    t_print("kem_348864f_keypair",impl,mceliece_kem_348864f_PUBLICKEYBYTES);
    for (long long i = 0;i <= TIMINGS;++i) {
      t[i] = cpucycles();
      crypto_kem_enc(c,k,p);
    }
    t_print("kem_348864f_enc",impl,mceliece_kem_348864f_CIPHERTEXTBYTES);
    for (long long i = 0;i <= TIMINGS;++i) {
      t[i] = cpucycles();
      crypto_kem_dec(T,c,s);
    }
    t_print("kem_348864f_dec",impl,mceliece_kem_348864f_BYTES);
  }
  free(Tstorage);
  free(kstorage);
  free(cstorage);
  free(sstorage);
  free(pstorage);
}

static void measure_kem_348864pc(void)
{
  if (targeto && strcmp(targeto,"kem")) return;
  if (targetp && strcmp(targetp,"348864pc")) return;
  void *pstorage = callocplus(mceliece_kem_348864pc_PUBLICKEYBYTES);
  unsigned char *p = (unsigned char *) aligned(pstorage);
  void *sstorage = callocplus(mceliece_kem_348864pc_SECRETKEYBYTES);
  unsigned char *s = (unsigned char *) aligned(sstorage);
  void *cstorage = callocplus(mceliece_kem_348864pc_CIPHERTEXTBYTES);
  unsigned char *c = (unsigned char *) aligned(cstorage);
  void *kstorage = callocplus(mceliece_kem_348864pc_BYTES);
  unsigned char *k = (unsigned char *) aligned(kstorage);
  void *Tstorage = callocplus(mceliece_kem_348864pc_BYTES);
  unsigned char *T = (unsigned char *) aligned(Tstorage);

  for (long long impl = -1;impl < mceliece_numimpl_kem_348864pc();++impl) {
    void (*crypto_kem_keypair)(unsigned char *,unsigned char *);
    int (*crypto_kem_enc)(unsigned char *,unsigned char *,const unsigned char *);
    int (*crypto_kem_dec)(unsigned char *,const unsigned char *,const unsigned char *);
    if (targeti && strcmp(targeti,mceliece_dispatch_kem_348864pc_implementation(impl))) continue;
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
    randombytes(p,mceliece_kem_348864pc_PUBLICKEYBYTES);
    randombytes(s,mceliece_kem_348864pc_SECRETKEYBYTES);
    randombytes(c,mceliece_kem_348864pc_CIPHERTEXTBYTES);
    randombytes(k,mceliece_kem_348864pc_BYTES);
    randombytes(T,mceliece_kem_348864pc_BYTES);
    for (long long i = 0;i <= TIMINGS;++i) {
      t[i] = cpucycles();
      crypto_kem_keypair(p,s);
    }
    t_print("kem_348864pc_keypair",impl,mceliece_kem_348864pc_PUBLICKEYBYTES);
    for (long long i = 0;i <= TIMINGS;++i) {
      t[i] = cpucycles();
      crypto_kem_enc(c,k,p);
    }
    t_print("kem_348864pc_enc",impl,mceliece_kem_348864pc_CIPHERTEXTBYTES);
    for (long long i = 0;i <= TIMINGS;++i) {
      t[i] = cpucycles();
      crypto_kem_dec(T,c,s);
    }
    t_print("kem_348864pc_dec",impl,mceliece_kem_348864pc_BYTES);
  }
  free(Tstorage);
  free(kstorage);
  free(cstorage);
  free(sstorage);
  free(pstorage);
}

static void measure_kem_348864pcf(void)
{
  if (targeto && strcmp(targeto,"kem")) return;
  if (targetp && strcmp(targetp,"348864pcf")) return;
  void *pstorage = callocplus(mceliece_kem_348864pcf_PUBLICKEYBYTES);
  unsigned char *p = (unsigned char *) aligned(pstorage);
  void *sstorage = callocplus(mceliece_kem_348864pcf_SECRETKEYBYTES);
  unsigned char *s = (unsigned char *) aligned(sstorage);
  void *cstorage = callocplus(mceliece_kem_348864pcf_CIPHERTEXTBYTES);
  unsigned char *c = (unsigned char *) aligned(cstorage);
  void *kstorage = callocplus(mceliece_kem_348864pcf_BYTES);
  unsigned char *k = (unsigned char *) aligned(kstorage);
  void *Tstorage = callocplus(mceliece_kem_348864pcf_BYTES);
  unsigned char *T = (unsigned char *) aligned(Tstorage);

  for (long long impl = -1;impl < mceliece_numimpl_kem_348864pcf();++impl) {
    void (*crypto_kem_keypair)(unsigned char *,unsigned char *);
    int (*crypto_kem_enc)(unsigned char *,unsigned char *,const unsigned char *);
    int (*crypto_kem_dec)(unsigned char *,const unsigned char *,const unsigned char *);
    if (targeti && strcmp(targeti,mceliece_dispatch_kem_348864pcf_implementation(impl))) continue;
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
    randombytes(p,mceliece_kem_348864pcf_PUBLICKEYBYTES);
    randombytes(s,mceliece_kem_348864pcf_SECRETKEYBYTES);
    randombytes(c,mceliece_kem_348864pcf_CIPHERTEXTBYTES);
    randombytes(k,mceliece_kem_348864pcf_BYTES);
    randombytes(T,mceliece_kem_348864pcf_BYTES);
    for (long long i = 0;i <= TIMINGS;++i) {
      t[i] = cpucycles();
      crypto_kem_keypair(p,s);
    }
    t_print("kem_348864pcf_keypair",impl,mceliece_kem_348864pcf_PUBLICKEYBYTES);
    for (long long i = 0;i <= TIMINGS;++i) {
      t[i] = cpucycles();
      crypto_kem_enc(c,k,p);
    }
    t_print("kem_348864pcf_enc",impl,mceliece_kem_348864pcf_CIPHERTEXTBYTES);
    for (long long i = 0;i <= TIMINGS;++i) {
      t[i] = cpucycles();
      crypto_kem_dec(T,c,s);
    }
    t_print("kem_348864pcf_dec",impl,mceliece_kem_348864pcf_BYTES);
  }
  free(Tstorage);
  free(kstorage);
  free(cstorage);
  free(sstorage);
  free(pstorage);
}

#include "print_cpuid.inc"

int main(int argc,char **argv)
{
  printf("mceliece version %s\n",mceliece_version);
  printf("mceliece arch %s\n",mceliece_arch);
  print_cpuid();

  if (*argv) ++argv;
  if (*argv) {
    targeto = *argv++;
    if (*argv) {
      targetp = *argv++;
      if (*argv) {
        targeti = *argv++;
      }
    }
  }

  measure_cpucycles();
  measure_randombytes();
  limits();
  measure_sort_int16();
  measure_sort_int32();
  measure_sort_int64();
  measure_xof_shake256();
  measure_xof_bitwrite16();
  measure_kem_6960119();
  measure_kem_6960119f();
  measure_kem_6960119pc();
  measure_kem_6960119pcf();
  measure_kem_6688128();
  measure_kem_6688128f();
  measure_kem_6688128pc();
  measure_kem_6688128pcf();
  measure_kem_8192128();
  measure_kem_8192128f();
  measure_kem_8192128pc();
  measure_kem_8192128pcf();
  measure_kem_460896();
  measure_kem_460896f();
  measure_kem_460896pc();
  measure_kem_460896pcf();
  measure_kem_348864();
  measure_kem_348864f();
  measure_kem_348864pc();
  measure_kem_348864pcf();

  return 0;
}
