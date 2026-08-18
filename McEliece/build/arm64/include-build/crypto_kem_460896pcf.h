#ifndef crypto_kem_460896pcf_h
#define crypto_kem_460896pcf_h

#define crypto_kem_460896pcf_keypair mceliece_kem_460896pcf_keypair
#define crypto_kem_460896pcf_enc mceliece_kem_460896pcf_enc
#define crypto_kem_460896pcf_dec mceliece_kem_460896pcf_dec

#define crypto_kem_460896pcf_PUBLICKEYBYTES 524160
#define crypto_kem_460896pcf_SECRETKEYBYTES 13608
#define crypto_kem_460896pcf_CIPHERTEXTBYTES 188
#define crypto_kem_460896pcf_BYTES 32

extern void crypto_kem_460896pcf_keypair(unsigned char *,unsigned char *);
extern int crypto_kem_460896pcf_enc(unsigned char *,unsigned char *,const unsigned char *);
extern int crypto_kem_460896pcf_dec(unsigned char *,const unsigned char *,const unsigned char *);

#endif
