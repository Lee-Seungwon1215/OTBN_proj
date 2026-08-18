#include "crypto_kem.h"
#include "operations.h"

void crypto_kem_keypair
(
       unsigned char *pk,
       unsigned char *sk 
)
{
  operation_keypair(pk,sk);
}
