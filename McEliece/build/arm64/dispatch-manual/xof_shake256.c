extern const char *mceliece_xof_shake256_implementation(void);
extern const char *mceliece_xof_shake256_compiler(void);
extern const char *mceliece_dispatch_xof_shake256_implementation(long long) __attribute__((visibility("default")));
extern const char *mceliece_dispatch_xof_shake256_compiler(long long) __attribute__((visibility("default")));
extern long long mceliece_numimpl_xof_shake256(void) __attribute__((visibility("default")));
extern void mceliece_xof_shake256(unsigned char *,long long,const unsigned char *,long long);
extern void (*mceliece_dispatch_xof_shake256(long long))(unsigned char *,long long,const unsigned char *,long long) __attribute__((visibility("default")));

extern void mceliece_xof_shake256_tweet_C0_xof(unsigned char *,long long,const unsigned char *,long long) __attribute__((visibility("default")));
extern void mceliece_xof_shake256_tweet_C1_xof(unsigned char *,long long,const unsigned char *,long long) __attribute__((visibility("default")));
extern void mceliece_xof_shake256_unrollround_C0_xof(unsigned char *,long long,const unsigned char *,long long) __attribute__((visibility("default")));
extern void mceliece_xof_shake256_unrollround_C1_xof(unsigned char *,long long,const unsigned char *,long long) __attribute__((visibility("default")));

void (*mceliece_dispatch_xof_shake256(long long impl))(unsigned char *,long long,const unsigned char *,long long)
{
  if (impl >= 0) {
    if (!impl--) return mceliece_xof_shake256_tweet_C0_xof;
    if (!impl--) return mceliece_xof_shake256_tweet_C1_xof;
    if (!impl--) return mceliece_xof_shake256_unrollround_C0_xof;
    if (!impl--) return mceliece_xof_shake256_unrollround_C1_xof;
  }
  return mceliece_xof_shake256;
}

const char *mceliece_dispatch_xof_shake256_implementation(long long impl)
{
  if (impl >= 0) {
    if (!impl--) return "tweet";
    if (!impl--) return "tweet";
    if (!impl--) return "unrollround";
    if (!impl--) return "unrollround";
  }
  return mceliece_xof_shake256_implementation();
}

const char *mceliece_dispatch_xof_shake256_compiler(long long impl)
{
  if (impl >= 0) {
    if (!impl--) return "gcc -Wall -fPIC -fwrapv -O2; Apple clang version 21.0.0 (clang-2100.1.1.101); Target: arm64-apple-darwin25.5.0; Thread model: posix; InstalledDir: /Library/Developer/CommandLineTools/usr/bin";
    if (!impl--) return "clang -Wall -fPIC -fwrapv -Qunused-arguments -O2; Apple clang version 21.0.0 (clang-2100.1.1.101); Target: arm64-apple-darwin25.5.0; Thread model: posix; InstalledDir: /Library/Developer/CommandLineTools/usr/bin";
    if (!impl--) return "gcc -Wall -fPIC -fwrapv -O2; Apple clang version 21.0.0 (clang-2100.1.1.101); Target: arm64-apple-darwin25.5.0; Thread model: posix; InstalledDir: /Library/Developer/CommandLineTools/usr/bin";
    if (!impl--) return "clang -Wall -fPIC -fwrapv -Qunused-arguments -O2; Apple clang version 21.0.0 (clang-2100.1.1.101); Target: arm64-apple-darwin25.5.0; Thread model: posix; InstalledDir: /Library/Developer/CommandLineTools/usr/bin";
  }
  return mceliece_xof_shake256_compiler();
}

long long mceliece_numimpl_xof_shake256(void)
{
  return 4;
}
