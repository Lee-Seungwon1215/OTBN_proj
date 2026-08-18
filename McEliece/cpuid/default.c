#include <stdio.h>

__attribute__((visibility("default")))
void mceliece_cpuid(unsigned int *result,long long resultlen)
{
  while (resultlen > 0) { *result++ = 0; --resultlen; }
}
