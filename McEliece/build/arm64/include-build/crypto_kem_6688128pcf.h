#ifndef crypto_kem_6688128pcf_h
#define crypto_kem_6688128pcf_h

#define crypto_kem_6688128pcf_keypair mceliece_kem_6688128pcf_keypair
#define crypto_kem_6688128pcf_enc mceliece_kem_6688128pcf_enc
#define crypto_kem_6688128pcf_dec mceliece_kem_6688128pcf_dec

#define crypto_kem_6688128pcf_PUBLICKEYBYTES 1044992
#define crypto_kem_6688128pcf_SECRETKEYBYTES 13932
#define crypto_kem_6688128pcf_CIPHERTEXTBYTES 240
#define crypto_kem_6688128pcf_BYTES 32

extern void crypto_kem_6688128pcf_keypair(unsigned char *,unsigned char *);
extern int crypto_kem_6688128pcf_enc(unsigned char *,unsigned char *,const unsigned char *);
extern int crypto_kem_6688128pcf_dec(unsigned char *,const unsigned char *,const unsigned char *);

#endif
