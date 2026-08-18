#ifndef crypto_kem_348864_h
#define crypto_kem_348864_h

#define crypto_kem_348864_keypair mceliece_kem_348864_keypair
#define crypto_kem_348864_enc mceliece_kem_348864_enc
#define crypto_kem_348864_dec mceliece_kem_348864_dec

#define crypto_kem_348864_PUBLICKEYBYTES 261120
#define crypto_kem_348864_SECRETKEYBYTES 6492
#define crypto_kem_348864_CIPHERTEXTBYTES 96
#define crypto_kem_348864_BYTES 32

extern void crypto_kem_348864_keypair(unsigned char *,unsigned char *);
extern int crypto_kem_348864_enc(unsigned char *,unsigned char *,const unsigned char *);
extern int crypto_kem_348864_dec(unsigned char *,const unsigned char *,const unsigned char *);

#endif
