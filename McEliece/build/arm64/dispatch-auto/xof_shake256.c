extern const char *mceliece_xof_shake256_implementation(void) __attribute__((visibility("default")));
extern const char *mceliece_xof_shake256_compiler(void) __attribute__((visibility("default")));
extern void mceliece_xof_shake256(unsigned char *,long long,const unsigned char *,long long) __attribute__((visibility("default")));

extern void mceliece_xof_shake256_unrollround_C1_xof(unsigned char *,long long,const unsigned char *,long long) __attribute__((visibility("default")));

void *mceliece_auto_xof_shake256(void)
{
  return mceliece_xof_shake256_unrollround_C1_xof;
}

static void (*mceliece_xof_shake256_pointer)(unsigned char *,long long,const unsigned char *,long long) = mceliece_xof_shake256_unrollround_C1_xof;

__attribute__((constructor(25521)))
static void mceliece_xof_shake256_pointer_constructor(void)
{
  mceliece_xof_shake256_pointer = mceliece_auto_xof_shake256();
}

__attribute__((visibility("default")))
void mceliece_xof_shake256(unsigned char *arg0,long long arg1,const unsigned char *arg2,long long arg3)
{
  mceliece_xof_shake256_pointer(arg0,arg1,arg2,arg3);
}

const char *mceliece_xof_shake256_implementation(void)
{
  return "unrollround";
}

const char *mceliece_xof_shake256_compiler(void)
{
  return "clang -Wall -fPIC -fwrapv -Qunused-arguments -O2; Apple clang version 21.0.0 (clang-2100.1.1.101); Target: arm64-apple-darwin25.5.0; Thread model: posix; InstalledDir: /Library/Developer/CommandLineTools/usr/bin";
}
