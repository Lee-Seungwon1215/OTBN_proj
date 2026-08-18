#ifndef crypto_kem_6960119f_h
#define crypto_kem_6960119f_h

#define crypto_kem_6960119f_keypair mceliece_kem_6960119f_keypair
#define crypto_kem_6960119f_enc mceliece_kem_6960119f_enc
#define crypto_kem_6960119f_dec mceliece_kem_6960119f_dec

#define crypto_kem_6960119f_PUBLICKEYBYTES 1047319
#define crypto_kem_6960119f_SECRETKEYBYTES 13948
#define crypto_kem_6960119f_CIPHERTEXTBYTES 194
#define crypto_kem_6960119f_BYTES 32

extern void crypto_kem_6960119f_keypair(unsigned char *,unsigned char *);
extern int crypto_kem_6960119f_enc(unsigned char *,unsigned char *,const unsigned char *);
extern int crypto_kem_6960119f_dec(unsigned char *,const unsigned char *,const unsigned char *);

#endif
