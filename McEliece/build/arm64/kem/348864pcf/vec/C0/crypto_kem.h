#ifndef crypto_kem_h
#define crypto_kem_h

#define crypto_kem_keypair CRYPTO_NAMESPACE(kem_keypair)
#define crypto_kem_enc CRYPTO_NAMESPACE(kem_enc)
#define crypto_kem_dec CRYPTO_NAMESPACE(kem_dec)

#define crypto_kem_348864pcf_PUBLICKEYBYTES 261120
#define crypto_kem_348864pcf_SECRETKEYBYTES 6492
#define crypto_kem_348864pcf_CIPHERTEXTBYTES 128
#define crypto_kem_348864pcf_BYTES 32
#define crypto_kem_PUBLICKEYBYTES 261120
#define crypto_kem_SECRETKEYBYTES 6492
#define crypto_kem_CIPHERTEXTBYTES 128
#define crypto_kem_BYTES 32

extern void crypto_kem_keypair(unsigned char *,unsigned char *);
extern int crypto_kem_enc(unsigned char *,unsigned char *,const unsigned char *);
extern int crypto_kem_dec(unsigned char *,const unsigned char *,const unsigned char *);

#endif
