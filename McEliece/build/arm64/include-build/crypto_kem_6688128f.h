#ifndef crypto_kem_6688128f_h
#define crypto_kem_6688128f_h

#define crypto_kem_6688128f_keypair mceliece_kem_6688128f_keypair
#define crypto_kem_6688128f_enc mceliece_kem_6688128f_enc
#define crypto_kem_6688128f_dec mceliece_kem_6688128f_dec

#define crypto_kem_6688128f_PUBLICKEYBYTES 1044992
#define crypto_kem_6688128f_SECRETKEYBYTES 13932
#define crypto_kem_6688128f_CIPHERTEXTBYTES 208
#define crypto_kem_6688128f_BYTES 32

extern void crypto_kem_6688128f_keypair(unsigned char *,unsigned char *);
extern int crypto_kem_6688128f_enc(unsigned char *,unsigned char *,const unsigned char *);
extern int crypto_kem_6688128f_dec(unsigned char *,const unsigned char *,const unsigned char *);

#endif
