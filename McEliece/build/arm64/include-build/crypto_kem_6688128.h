#ifndef crypto_kem_6688128_h
#define crypto_kem_6688128_h

#define crypto_kem_6688128_keypair mceliece_kem_6688128_keypair
#define crypto_kem_6688128_enc mceliece_kem_6688128_enc
#define crypto_kem_6688128_dec mceliece_kem_6688128_dec

#define crypto_kem_6688128_PUBLICKEYBYTES 1044992
#define crypto_kem_6688128_SECRETKEYBYTES 13932
#define crypto_kem_6688128_CIPHERTEXTBYTES 208
#define crypto_kem_6688128_BYTES 32

extern void crypto_kem_6688128_keypair(unsigned char *,unsigned char *);
extern int crypto_kem_6688128_enc(unsigned char *,unsigned char *,const unsigned char *);
extern int crypto_kem_6688128_dec(unsigned char *,const unsigned char *,const unsigned char *);

#endif
