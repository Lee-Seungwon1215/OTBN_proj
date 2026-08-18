extern const char *mceliece_kem_6960119pc_implementation(void) __attribute__((visibility("default")));
extern const char *mceliece_kem_6960119pc_compiler(void) __attribute__((visibility("default")));
extern void mceliece_kem_6960119pc_keypair(unsigned char *,unsigned char *) __attribute__((visibility("default")));

extern void mceliece_kem_6960119pc_vec_C1_kem_keypair(unsigned char *,unsigned char *) __attribute__((visibility("default")));

void *mceliece_auto_kem_6960119pc_keypair(void)
{
  return mceliece_kem_6960119pc_vec_C1_kem_keypair;
}

static void (*mceliece_kem_6960119pc_keypair_pointer)(unsigned char *,unsigned char *) = mceliece_kem_6960119pc_vec_C1_kem_keypair;

__attribute__((constructor(25521)))
static void mceliece_kem_6960119pc_keypair_pointer_constructor(void)
{
  mceliece_kem_6960119pc_keypair_pointer = mceliece_auto_kem_6960119pc_keypair();
}

__attribute__((visibility("default")))
void mceliece_kem_6960119pc_keypair(unsigned char *arg0,unsigned char *arg1)
{
  mceliece_kem_6960119pc_keypair_pointer(arg0,arg1);
}

extern int mceliece_kem_6960119pc_enc(unsigned char *,unsigned char *,const unsigned char *) __attribute__((visibility("default")));

extern int mceliece_kem_6960119pc_vec_C1_kem_enc(unsigned char *,unsigned char *,const unsigned char *) __attribute__((visibility("default")));

void *mceliece_auto_kem_6960119pc_enc(void)
{
  return mceliece_kem_6960119pc_vec_C1_kem_enc;
}

static int (*mceliece_kem_6960119pc_enc_pointer)(unsigned char *,unsigned char *,const unsigned char *) = mceliece_kem_6960119pc_vec_C1_kem_enc;

__attribute__((constructor(25521)))
static void mceliece_kem_6960119pc_enc_pointer_constructor(void)
{
  mceliece_kem_6960119pc_enc_pointer = mceliece_auto_kem_6960119pc_enc();
}

__attribute__((visibility("default")))
int mceliece_kem_6960119pc_enc(unsigned char *arg0,unsigned char *arg1,const unsigned char *arg2)
{
  return mceliece_kem_6960119pc_enc_pointer(arg0,arg1,arg2);
}

extern int mceliece_kem_6960119pc_dec(unsigned char *,const unsigned char *,const unsigned char *) __attribute__((visibility("default")));

extern int mceliece_kem_6960119pc_vec_C1_kem_dec(unsigned char *,const unsigned char *,const unsigned char *) __attribute__((visibility("default")));

void *mceliece_auto_kem_6960119pc_dec(void)
{
  return mceliece_kem_6960119pc_vec_C1_kem_dec;
}

static int (*mceliece_kem_6960119pc_dec_pointer)(unsigned char *,const unsigned char *,const unsigned char *) = mceliece_kem_6960119pc_vec_C1_kem_dec;

__attribute__((constructor(25521)))
static void mceliece_kem_6960119pc_dec_pointer_constructor(void)
{
  mceliece_kem_6960119pc_dec_pointer = mceliece_auto_kem_6960119pc_dec();
}

__attribute__((visibility("default")))
int mceliece_kem_6960119pc_dec(unsigned char *arg0,const unsigned char *arg1,const unsigned char *arg2)
{
  return mceliece_kem_6960119pc_dec_pointer(arg0,arg1,arg2);
}

const char *mceliece_kem_6960119pc_implementation(void)
{
  return "vec";
}

const char *mceliece_kem_6960119pc_compiler(void)
{
  return "clang -Wall -fPIC -fwrapv -Qunused-arguments -O2; Apple clang version 21.0.0 (clang-2100.1.1.101); Target: arm64-apple-darwin25.5.0; Thread model: posix; InstalledDir: /Library/Developer/CommandLineTools/usr/bin";
}
