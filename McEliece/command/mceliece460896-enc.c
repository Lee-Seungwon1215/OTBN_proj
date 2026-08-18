/* WARNING: auto-generated (by autogen/cli); do not edit */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "mceliece.h" /* -lmceliece */
#include "limits.inc"

static unsigned char pk[mceliece460896_PUBLICKEYBYTES];
static unsigned char c[mceliece460896_CIPHERTEXTBYTES];
static unsigned char k[mceliece460896_BYTES];

static void die_temp(const char *why,const char *why2)
{
  if (why2)
    fprintf(stderr,"mceliece460896-enc: fatal: %s: %s\n",why,why2);
  else
    fprintf(stderr,"mceliece460896-enc: fatal: %s\n",why);
  exit(111);
}

int main()
{
  FILE *pkfile;
  FILE *kfile;

  limits();

  pkfile = fdopen(4,"r");
  if (!pkfile) {
    fprintf(stderr,"mceliece460896-enc: usage: mceliece460896-enc >ciphertext 7>sessionkey 4<publickey\n");
    die_temp("fdopen 4 failed",strerror(errno));
  }

  kfile = fdopen(7,"w");
  if (!kfile) {
    fprintf(stderr,"mceliece460896-enc: usage: mceliece460896-enc >ciphertext 7>sessionkey 4<publickey\n");
    die_temp("fdopen 7 failed",strerror(errno));
  }

  if (fread(pk,1,sizeof pk,pkfile) < sizeof pk) {
    if (ferror(pkfile))
      die_temp("read publickey failed",strerror(errno));
    die_temp("read publickey failed","end of file");
  }
  fclose(pkfile);

  if (mceliece460896_enc(c,k,pk)) die_temp("encapsulation failed",0);

  if (fwrite(c,1,sizeof c,stdout) < sizeof c)
    die_temp("write ciphertext failed",strerror(errno));
  if (fflush(stdout))
    die_temp("write ciphertext failed",strerror(errno));
  fclose(stdout);

  if (fwrite(k,1,sizeof k,kfile) < sizeof k)
    die_temp("write sessionkey failed",strerror(errno));
  if (fflush(kfile))
    die_temp("write sessionkey failed",strerror(errno));
  fclose(kfile);

  return 0;
}
