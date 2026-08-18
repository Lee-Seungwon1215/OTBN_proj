extern const char *mceliece_sort_int64_implementation(void);
extern const char *mceliece_sort_int64_compiler(void);
extern const char *mceliece_dispatch_sort_int64_implementation(long long) __attribute__((visibility("default")));
extern const char *mceliece_dispatch_sort_int64_compiler(long long) __attribute__((visibility("default")));
extern long long mceliece_numimpl_sort_int64(void) __attribute__((visibility("default")));
extern void mceliece_sort_int64(void *,long long);
extern void (*mceliece_dispatch_sort_int64(long long))(void *,long long) __attribute__((visibility("default")));

extern void mceliece_sort_int64_neon_C0_sort(void *,long long) __attribute__((visibility("default")));
extern void mceliece_sort_int64_neon_C1_sort(void *,long long) __attribute__((visibility("default")));
extern void mceliece_sort_int64_portable4_C0_sort(void *,long long) __attribute__((visibility("default")));
extern void mceliece_sort_int64_portable4_C1_sort(void *,long long) __attribute__((visibility("default")));

void (*mceliece_dispatch_sort_int64(long long impl))(void *,long long)
{
  if (impl >= 0) {
    if (!impl--) return mceliece_sort_int64_neon_C0_sort;
    if (!impl--) return mceliece_sort_int64_neon_C1_sort;
    if (!impl--) return mceliece_sort_int64_portable4_C0_sort;
    if (!impl--) return mceliece_sort_int64_portable4_C1_sort;
  }
  return mceliece_sort_int64;
}

const char *mceliece_dispatch_sort_int64_implementation(long long impl)
{
  if (impl >= 0) {
    if (!impl--) return "neon";
    if (!impl--) return "neon";
    if (!impl--) return "portable4";
    if (!impl--) return "portable4";
  }
  return mceliece_sort_int64_implementation();
}

const char *mceliece_dispatch_sort_int64_compiler(long long impl)
{
  if (impl >= 0) {
    if (!impl--) return "gcc -Wall -fPIC -fwrapv -O2; Apple clang version 21.0.0 (clang-2100.1.1.101); Target: arm64-apple-darwin25.5.0; Thread model: posix; InstalledDir: /Library/Developer/CommandLineTools/usr/bin";
    if (!impl--) return "clang -Wall -fPIC -fwrapv -Qunused-arguments -O2; Apple clang version 21.0.0 (clang-2100.1.1.101); Target: arm64-apple-darwin25.5.0; Thread model: posix; InstalledDir: /Library/Developer/CommandLineTools/usr/bin";
    if (!impl--) return "gcc -Wall -fPIC -fwrapv -O2; Apple clang version 21.0.0 (clang-2100.1.1.101); Target: arm64-apple-darwin25.5.0; Thread model: posix; InstalledDir: /Library/Developer/CommandLineTools/usr/bin";
    if (!impl--) return "clang -Wall -fPIC -fwrapv -Qunused-arguments -O2; Apple clang version 21.0.0 (clang-2100.1.1.101); Target: arm64-apple-darwin25.5.0; Thread model: posix; InstalledDir: /Library/Developer/CommandLineTools/usr/bin";
  }
  return mceliece_sort_int64_compiler();
}

long long mceliece_numimpl_sort_int64(void)
{
  return 4;
}
