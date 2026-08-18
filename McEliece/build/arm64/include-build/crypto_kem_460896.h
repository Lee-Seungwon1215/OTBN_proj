#ifndef crypto_kem_460896_h
#define crypto_kem_460896_h

#define crypto_kem_460896_keypair mceliece_kem_460896_keypair
#define crypto_kem_460896_enc mceliece_kem_460896_enc
#define crypto_kem_460896_dec mceliece_kem_460896_dec

#define crypto_kem_460896_PUBLICKEYBYTES 524160
#define crypto_kem_460896_SECRETKEYBYTES 13608
#define crypto_kem_460896_CIPHERTEXTBYTES 156
#define crypto_kem_460896_BYTES 32

extern void crypto_kem_460896_keypair(unsigned char *,unsigned char *);
extern int crypto_kem_460896_enc(unsigned char *,unsigned char *,const unsigned char *);
extern int crypto_kem_460896_dec(unsigned char *,const unsigned char *,const unsigned char *);

#endif
