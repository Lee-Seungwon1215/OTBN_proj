extern const char *mceliece_xof_bitwrite16_implementation(void) __attribute__((visibility("default")));
extern const char *mceliece_xof_bitwrite16_compiler(void) __attribute__((visibility("default")));
extern void mceliece_xof_bitwrite16(unsigned char *,long long,const unsigned char *,long long) __attribute__((visibility("default")));

extern void mceliece_xof_bitwrite16_64_C1_xof(unsigned char *,long long,const unsigned char *,long long) __attribute__((visibility("default")));

void *mceliece_auto_xof_bitwrite16(void)
{
  return mceliece_xof_bitwrite16_64_C1_xof;
}

static void (*mceliece_xof_bitwrite16_pointer)(unsigned char *,long long,const unsigned char *,long long) = mceliece_xof_bitwrite16_64_C1_xof;

__attribute__((constructor(25521)))
static void mceliece_xof_bitwrite16_pointer_constructor(void)
{
  mceliece_xof_bitwrite16_pointer = mceliece_auto_xof_bitwrite16();
}

__attribute__((visibility("default")))
void mceliece_xof_bitwrite16(unsigned char *arg0,long long arg1,const unsigned char *arg2,long long arg3)
{
  mceliece_xof_bitwrite16_pointer(arg0,arg1,arg2,arg3);
}

const char *mceliece_xof_bitwrite16_implementation(void)
{
  return "64";
}

const char *mceliece_xof_bitwrite16_compiler(void)
{
  return "clang -Wall -fPIC -fwrapv -Qunused-arguments -O2; Apple clang version 21.0.0 (clang-2100.1.1.101); Target: arm64-apple-darwin25.5.0; Thread model: posix; InstalledDir: /Library/Developer/CommandLineTools/usr/bin";
}
