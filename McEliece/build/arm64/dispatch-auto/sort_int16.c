extern const char *mceliece_sort_int16_implementation(void) __attribute__((visibility("default")));
extern const char *mceliece_sort_int16_compiler(void) __attribute__((visibility("default")));
extern void mceliece_sort_int16(void *,long long) __attribute__((visibility("default")));

extern void mceliece_sort_int16_portable4_C1_sort(void *,long long) __attribute__((visibility("default")));

void *mceliece_auto_sort_int16(void)
{
  return mceliece_sort_int16_portable4_C1_sort;
}

static void (*mceliece_sort_int16_pointer)(void *,long long) = mceliece_sort_int16_portable4_C1_sort;

__attribute__((constructor(25521)))
static void mceliece_sort_int16_pointer_constructor(void)
{
  mceliece_sort_int16_pointer = mceliece_auto_sort_int16();
}

__attribute__((visibility("default")))
void mceliece_sort_int16(void *arg0,long long arg1)
{
  mceliece_sort_int16_pointer(arg0,arg1);
}

const char *mceliece_sort_int16_implementation(void)
{
  return "portable4";
}

const char *mceliece_sort_int16_compiler(void)
{
  return "clang -Wall -fPIC -fwrapv -Qunused-arguments -O2; Apple clang version 21.0.0 (clang-2100.1.1.101); Target: arm64-apple-darwin25.5.0; Thread model: posix; InstalledDir: /Library/Developer/CommandLineTools/usr/bin";
}
