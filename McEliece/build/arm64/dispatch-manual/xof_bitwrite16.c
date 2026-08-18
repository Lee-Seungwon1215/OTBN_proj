extern const char *mceliece_xof_bitwrite16_implementation(void);
extern const char *mceliece_xof_bitwrite16_compiler(void);
extern const char *mceliece_dispatch_xof_bitwrite16_implementation(long long) __attribute__((visibility("default")));
extern const char *mceliece_dispatch_xof_bitwrite16_compiler(long long) __attribute__((visibility("default")));
extern long long mceliece_numimpl_xof_bitwrite16(void) __attribute__((visibility("default")));
extern void mceliece_xof_bitwrite16(unsigned char *,long long,const unsigned char *,long long);
extern void (*mceliece_dispatch_xof_bitwrite16(long long))(unsigned char *,long long,const unsigned char *,long long) __attribute__((visibility("default")));

extern void mceliece_xof_bitwrite16_64_C0_xof(unsigned char *,long long,const unsigned char *,long long) __attribute__((visibility("default")));
extern void mceliece_xof_bitwrite16_64_C1_xof(unsigned char *,long long,const unsigned char *,long long) __attribute__((visibility("default")));
extern void mceliece_xof_bitwrite16_64x4_C0_xof(unsigned char *,long long,const unsigned char *,long long) __attribute__((visibility("default")));
extern void mceliece_xof_bitwrite16_64x4_C1_xof(unsigned char *,long long,const unsigned char *,long long) __attribute__((visibility("default")));
extern void mceliece_xof_bitwrite16_64x4x2_C0_xof(unsigned char *,long long,const unsigned char *,long long) __attribute__((visibility("default")));
extern void mceliece_xof_bitwrite16_64x4x2_C1_xof(unsigned char *,long long,const unsigned char *,long long) __attribute__((visibility("default")));
extern void mceliece_xof_bitwrite16_ref_C0_xof(unsigned char *,long long,const unsigned char *,long long) __attribute__((visibility("default")));
extern void mceliece_xof_bitwrite16_ref_C1_xof(unsigned char *,long long,const unsigned char *,long long) __attribute__((visibility("default")));

void (*mceliece_dispatch_xof_bitwrite16(long long impl))(unsigned char *,long long,const unsigned char *,long long)
{
  if (impl >= 0) {
    if (!impl--) return mceliece_xof_bitwrite16_64_C0_xof;
    if (!impl--) return mceliece_xof_bitwrite16_64_C1_xof;
    if (!impl--) return mceliece_xof_bitwrite16_64x4_C0_xof;
    if (!impl--) return mceliece_xof_bitwrite16_64x4_C1_xof;
    if (!impl--) return mceliece_xof_bitwrite16_64x4x2_C0_xof;
    if (!impl--) return mceliece_xof_bitwrite16_64x4x2_C1_xof;
    if (!impl--) return mceliece_xof_bitwrite16_ref_C0_xof;
    if (!impl--) return mceliece_xof_bitwrite16_ref_C1_xof;
  }
  return mceliece_xof_bitwrite16;
}

const char *mceliece_dispatch_xof_bitwrite16_implementation(long long impl)
{
  if (impl >= 0) {
    if (!impl--) return "64";
    if (!impl--) return "64";
    if (!impl--) return "64x4";
    if (!impl--) return "64x4";
    if (!impl--) return "64x4x2";
    if (!impl--) return "64x4x2";
    if (!impl--) return "ref";
    if (!impl--) return "ref";
  }
  return mceliece_xof_bitwrite16_implementation();
}

const char *mceliece_dispatch_xof_bitwrite16_compiler(long long impl)
{
  if (impl >= 0) {
    if (!impl--) return "gcc -Wall -fPIC -fwrapv -O2; Apple clang version 21.0.0 (clang-2100.1.1.101); Target: arm64-apple-darwin25.5.0; Thread model: posix; InstalledDir: /Library/Developer/CommandLineTools/usr/bin";
    if (!impl--) return "clang -Wall -fPIC -fwrapv -Qunused-arguments -O2; Apple clang version 21.0.0 (clang-2100.1.1.101); Target: arm64-apple-darwin25.5.0; Thread model: posix; InstalledDir: /Library/Developer/CommandLineTools/usr/bin";
    if (!impl--) return "gcc -Wall -fPIC -fwrapv -O2; Apple clang version 21.0.0 (clang-2100.1.1.101); Target: arm64-apple-darwin25.5.0; Thread model: posix; InstalledDir: /Library/Developer/CommandLineTools/usr/bin";
    if (!impl--) return "clang -Wall -fPIC -fwrapv -Qunused-arguments -O2; Apple clang version 21.0.0 (clang-2100.1.1.101); Target: arm64-apple-darwin25.5.0; Thread model: posix; InstalledDir: /Library/Developer/CommandLineTools/usr/bin";
    if (!impl--) return "gcc -Wall -fPIC -fwrapv -O2; Apple clang version 21.0.0 (clang-2100.1.1.101); Target: arm64-apple-darwin25.5.0; Thread model: posix; InstalledDir: /Library/Developer/CommandLineTools/usr/bin";
    if (!impl--) return "clang -Wall -fPIC -fwrapv -Qunused-arguments -O2; Apple clang version 21.0.0 (clang-2100.1.1.101); Target: arm64-apple-darwin25.5.0; Thread model: posix; InstalledDir: /Library/Developer/CommandLineTools/usr/bin";
    if (!impl--) return "gcc -Wall -fPIC -fwrapv -O2; Apple clang version 21.0.0 (clang-2100.1.1.101); Target: arm64-apple-darwin25.5.0; Thread model: posix; InstalledDir: /Library/Developer/CommandLineTools/usr/bin";
    if (!impl--) return "clang -Wall -fPIC -fwrapv -Qunused-arguments -O2; Apple clang version 21.0.0 (clang-2100.1.1.101); Target: arm64-apple-darwin25.5.0; Thread model: posix; InstalledDir: /Library/Developer/CommandLineTools/usr/bin";
  }
  return mceliece_xof_bitwrite16_compiler();
}

long long mceliece_numimpl_xof_bitwrite16(void)
{
  return 8;
}
