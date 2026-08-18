#ifndef crypto_kem_348864pcf_h
#define crypto_kem_348864pcf_h

#define crypto_kem_348864pcf_keypair mceliece_kem_348864pcf_keypair
#define crypto_kem_348864pcf_enc mceliece_kem_348864pcf_enc
#define crypto_kem_348864pcf_dec mceliece_kem_348864pcf_dec

#define crypto_kem_348864pcf_PUBLICKEYBYTES 261120
#define crypto_kem_348864pcf_SECRETKEYBYTES 6492
#define crypto_kem_348864pcf_CIPHERTEXTBYTES 128
#define crypto_kem_348864pcf_BYTES 32

extern void crypto_kem_348864pcf_keypair(unsigned char *,unsigned char *);
extern int crypto_kem_348864pcf_enc(unsigned char *,unsigned char *,const unsigned char *);
extern int crypto_kem_348864pcf_dec(unsigned char *,const unsigned char *,const unsigned char *);

#endif
