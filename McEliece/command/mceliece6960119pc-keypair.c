/* WARNING: auto-generated (by autogen/cli); do not edit */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "mceliece.h" /* -lmceliece */
#include "limits.inc"

static unsigned char pk[mceliece6960119pc_PUBLICKEYBYTES];
static unsigned char sk[mceliece6960119pc_SECRETKEYBYTES];

static void die_temp(const char *why,const char *why2)
{
  if (why2)
    fprintf(stderr,"mceliece6960119pc-keypair: fatal: %s: %s\n",why,why2);
  else
    fprintf(stderr,"mceliece6960119pc-keypair: fatal: %s\n",why);
  exit(111);
}

int main()
{
  FILE *pkfile;
  FILE *skfile;

  limits();

  pkfile = fdopen(5,"w");
  if (!pkfile) {
    fprintf(stderr,"mceliece6960119pc-keypair: usage: mceliece6960119pc-keypair 5>publickey 9>secretkey\n");
    die_temp("fdopen 5 failed",strerror(errno));
  }

  skfile = fdopen(9,"w");
  if (!skfile) {
    fprintf(stderr,"mceliece6960119pc-keypair: usage: mceliece6960119pc-keypair 5>publickey 9>secretkey\n");
    die_temp("fdopen 9 failed",strerror(errno));
  }

  mceliece6960119pc_keypair(pk,sk);

  if (fwrite(pk,1,sizeof pk,pkfile) < sizeof pk)
    die_temp("write publickey failed",strerror(errno));
  if (fflush(pkfile))
    die_temp("write publickey failed",strerror(errno));
  fclose(pkfile);

  if (fwrite(sk,1,sizeof sk,skfile) < sizeof sk)
    die_temp("write secretkey failed",strerror(errno));
  if (fflush(skfile))
    die_temp("write secretkey failed",strerror(errno));
  fclose(skfile);

  return 0;
}
