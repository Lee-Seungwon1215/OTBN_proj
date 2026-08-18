extern const char *mceliece_sort_int64_implementation(void) __attribute__((visibility("default")));
extern const char *mceliece_sort_int64_compiler(void) __attribute__((visibility("default")));
extern void mceliece_sort_int64(void *,long long) __attribute__((visibility("default")));

extern void mceliece_sort_int64_neon_C0_sort(void *,long long) __attribute__((visibility("default")));

void *mceliece_auto_sort_int64(void)
{
  return mceliece_sort_int64_neon_C0_sort;
}

static void (*mceliece_sort_int64_pointer)(void *,long long) = mceliece_sort_int64_neon_C0_sort;

__attribute__((constructor(25521)))
static void mceliece_sort_int64_pointer_constructor(void)
{
  mceliece_sort_int64_pointer = mceliece_auto_sort_int64();
}

__attribute__((visibility("default")))
void mceliece_sort_int64(void *arg0,long long arg1)
{
  mceliece_sort_int64_pointer(arg0,arg1);
}

const char *mceliece_sort_int64_implementation(void)
{
  return "neon";
}

const char *mceliece_sort_int64_compiler(void)
{
  return "gcc -Wall -fPIC -fwrapv -O2; Apple clang version 21.0.0 (clang-2100.1.1.101); Target: arm64-apple-darwin25.5.0; Thread model: posix; InstalledDir: /Library/Developer/CommandLineTools/usr/bin";
}
