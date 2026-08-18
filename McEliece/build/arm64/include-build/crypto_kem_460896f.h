#ifndef crypto_kem_460896f_h
#define crypto_kem_460896f_h

#define crypto_kem_460896f_keypair mceliece_kem_460896f_keypair
#define crypto_kem_460896f_enc mceliece_kem_460896f_enc
#define crypto_kem_460896f_dec mceliece_kem_460896f_dec

#define crypto_kem_460896f_PUBLICKEYBYTES 524160
#define crypto_kem_460896f_SECRETKEYBYTES 13608
#define crypto_kem_460896f_CIPHERTEXTBYTES 156
#define crypto_kem_460896f_BYTES 32

extern void crypto_kem_460896f_keypair(unsigned char *,unsigned char *);
extern int crypto_kem_460896f_enc(unsigned char *,unsigned char *,const unsigned char *);
extern int crypto_kem_460896f_dec(unsigned char *,const unsigned char *,const unsigned char *);

#endif
