#ifndef crypto_kem_6960119_h
#define crypto_kem_6960119_h

#define crypto_kem_6960119_keypair mceliece_kem_6960119_keypair
#define crypto_kem_6960119_enc mceliece_kem_6960119_enc
#define crypto_kem_6960119_dec mceliece_kem_6960119_dec

#define crypto_kem_6960119_PUBLICKEYBYTES 1047319
#define crypto_kem_6960119_SECRETKEYBYTES 13948
#define crypto_kem_6960119_CIPHERTEXTBYTES 194
#define crypto_kem_6960119_BYTES 32

extern void crypto_kem_6960119_keypair(unsigned char *,unsigned char *);
extern int crypto_kem_6960119_enc(unsigned char *,unsigned char *,const unsigned char *);
extern int crypto_kem_6960119_dec(unsigned char *,const unsigned char *,const unsigned char *);

#endif
