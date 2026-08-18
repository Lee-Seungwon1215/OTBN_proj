/* WARNING: auto-generated (by autogen/cli); do not edit */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "mceliece.h" /* -lmceliece */
#include "limits.inc"

static unsigned char sk[mceliece8192128_SECRETKEYBYTES];
static unsigned char c[mceliece8192128_CIPHERTEXTBYTES];
static unsigned char k[mceliece8192128_BYTES];

static void die_temp(const char *why,const char *why2)
{
  if (why2)
    fprintf(stderr,"mceliece8192128-dec: fatal: %s: %s\n",why,why2);
  else
    fprintf(stderr,"mceliece8192128-dec: fatal: %s\n",why);
  exit(111);
}

int main()
{
  FILE *skfile;
  FILE *kfile;

  limits();

  skfile = fdopen(8,"r");
  if (!skfile) {
    fprintf(stderr,"mceliece8192128-dec: usage: mceliece8192128-dec 7>sessionkey <ciphertext 8<secretkey\n");
    die_temp("fdopen 8 failed",strerror(errno));
  }

  kfile = fdopen(7,"w");
  if (!kfile) {
    fprintf(stderr,"mceliece8192128-dec: usage: mceliece8192128-dec 7>sessionkey <ciphertext 8<secretkey\n");
    die_temp("fdopen 7 failed",strerror(errno));
  }

  if (fread(sk,1,sizeof sk,skfile) < sizeof sk) {
    if (ferror(skfile))
      die_temp("read secretkey failed",strerror(errno));
    die_temp("read secretkey failed","end of file");
  }
  fclose(skfile);

  if (fread(c,1,sizeof c,stdin) < sizeof c) {
    if (ferror(stdin))
      die_temp("read ciphertext failed",strerror(errno));
    die_temp("read ciphertext failed","end of file");
  }
  fclose(stdin);

  if (mceliece8192128_dec(k,c,sk)) die_temp("decapsulation failed",0);

  if (fwrite(k,1,sizeof k,kfile) < sizeof k)
    die_temp("write sessionkey failed",strerror(errno));
  if (fflush(kfile))
    die_temp("write sessionkey failed",strerror(errno));
  fclose(kfile);

  return 0;
}
