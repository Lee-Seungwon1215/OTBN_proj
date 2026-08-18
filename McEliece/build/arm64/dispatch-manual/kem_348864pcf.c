extern const char *mceliece_kem_348864pcf_implementation(void);
extern const char *mceliece_kem_348864pcf_compiler(void);
extern const char *mceliece_dispatch_kem_348864pcf_implementation(long long) __attribute__((visibility("default")));
extern const char *mceliece_dispatch_kem_348864pcf_compiler(long long) __attribute__((visibility("default")));
extern long long mceliece_numimpl_kem_348864pcf(void) __attribute__((visibility("default")));
extern void mceliece_kem_348864pcf_keypair(unsigned char *,unsigned char *);
extern void (*mceliece_dispatch_kem_348864pcf_keypair(long long))(unsigned char *,unsigned char *) __attribute__((visibility("default")));

extern void mceliece_kem_348864pcf_vec_C0_kem_keypair(unsigned char *,unsigned char *) __attribute__((visibility("default")));
extern void mceliece_kem_348864pcf_vec_C1_kem_keypair(unsigned char *,unsigned char *) __attribute__((visibility("default")));

void (*mceliece_dispatch_kem_348864pcf_keypair(long long impl))(unsigned char *,unsigned char *)
{
  if (impl >= 0) {
    if (!impl--) return mceliece_kem_348864pcf_vec_C0_kem_keypair;
    if (!impl--) return mceliece_kem_348864pcf_vec_C1_kem_keypair;
  }
  return mceliece_kem_348864pcf_keypair;
}

extern int mceliece_kem_348864pcf_enc(unsigned char *,unsigned char *,const unsigned char *);
extern int (*mceliece_dispatch_kem_348864pcf_enc(long long))(unsigned char *,unsigned char *,const unsigned char *) __attribute__((visibility("default")));

extern int mceliece_kem_348864pcf_vec_C0_kem_enc(unsigned char *,unsigned char *,const unsigned char *) __attribute__((visibility("default")));
extern int mceliece_kem_348864pcf_vec_C1_kem_enc(unsigned char *,unsigned char *,const unsigned char *) __attribute__((visibility("default")));

int (*mceliece_dispatch_kem_348864pcf_enc(long long impl))(unsigned char *,unsigned char *,const unsigned char *)
{
  if (impl >= 0) {
    if (!impl--) return mceliece_kem_348864pcf_vec_C0_kem_enc;
    if (!impl--) return mceliece_kem_348864pcf_vec_C1_kem_enc;
  }
  return mceliece_kem_348864pcf_enc;
}

extern int mceliece_kem_348864pcf_dec(unsigned char *,const unsigned char *,const unsigned char *);
extern int (*mceliece_dispatch_kem_348864pcf_dec(long long))(unsigned char *,const unsigned char *,const unsigned char *) __attribute__((visibility("default")));

extern int mceliece_kem_348864pcf_vec_C0_kem_dec(unsigned char *,const unsigned char *,const unsigned char *) __attribute__((visibility("default")));
extern int mceliece_kem_348864pcf_vec_C1_kem_dec(unsigned char *,const unsigned char *,const unsigned char *) __attribute__((visibility("default")));

int (*mceliece_dispatch_kem_348864pcf_dec(long long impl))(unsigned char *,const unsigned char *,const unsigned char *)
{
  if (impl >= 0) {
    if (!impl--) return mceliece_kem_348864pcf_vec_C0_kem_dec;
    if (!impl--) return mceliece_kem_348864pcf_vec_C1_kem_dec;
  }
  return mceliece_kem_348864pcf_dec;
}

const char *mceliece_dispatch_kem_348864pcf_implementation(long long impl)
{
  if (impl >= 0) {
    if (!impl--) return "vec";
    if (!impl--) return "vec";
  }
  return mceliece_kem_348864pcf_implementation();
}

const char *mceliece_dispatch_kem_348864pcf_compiler(long long impl)
{
  if (impl >= 0) {
    if (!impl--) return "gcc -Wall -fPIC -fwrapv -O2; Apple clang version 21.0.0 (clang-2100.1.1.101); Target: arm64-apple-darwin25.5.0; Thread model: posix; InstalledDir: /Library/Developer/CommandLineTools/usr/bin";
    if (!impl--) return "clang -Wall -fPIC -fwrapv -Qunused-arguments -O2; Apple clang version 21.0.0 (clang-2100.1.1.101); Target: arm64-apple-darwin25.5.0; Thread model: posix; InstalledDir: /Library/Developer/CommandLineTools/usr/bin";
  }
  return mceliece_kem_348864pcf_compiler();
}

long long mceliece_numimpl_kem_348864pcf(void)
{
  return 2;
}
