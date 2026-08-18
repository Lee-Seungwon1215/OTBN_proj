#ifndef crypto_kem_6960119pcf_h
#define crypto_kem_6960119pcf_h

#define crypto_kem_6960119pcf_keypair mceliece_kem_6960119pcf_keypair
#define crypto_kem_6960119pcf_enc mceliece_kem_6960119pcf_enc
#define crypto_kem_6960119pcf_dec mceliece_kem_6960119pcf_dec

#define crypto_kem_6960119pcf_PUBLICKEYBYTES 1047319
#define crypto_kem_6960119pcf_SECRETKEYBYTES 13948
#define crypto_kem_6960119pcf_CIPHERTEXTBYTES 226
#define crypto_kem_6960119pcf_BYTES 32

extern void crypto_kem_6960119pcf_keypair(unsigned char *,unsigned char *);
extern int crypto_kem_6960119pcf_enc(unsigned char *,unsigned char *,const unsigned char *);
extern int crypto_kem_6960119pcf_dec(unsigned char *,const unsigned char *,const unsigned char *);

#endif
