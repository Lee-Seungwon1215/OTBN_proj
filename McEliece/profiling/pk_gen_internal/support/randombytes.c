#include "randombytes.h"

#include <stdlib.h>

void randombytes(void *buf, long long len)
{
  arc4random_buf(buf, (size_t) len);
}
