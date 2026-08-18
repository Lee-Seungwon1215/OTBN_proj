#ifndef crypto_kem_460896pc_h
#define crypto_kem_460896pc_h

#define crypto_kem_460896pc_keypair mceliece_kem_460896pc_keypair
#define crypto_kem_460896pc_enc mceliece_kem_460896pc_enc
#define crypto_kem_460896pc_dec mceliece_kem_460896pc_dec

#define crypto_kem_460896pc_PUBLICKEYBYTES 524160
#define crypto_kem_460896pc_SECRETKEYBYTES 13608
#define crypto_kem_460896pc_CIPHERTEXTBYTES 188
#define crypto_kem_460896pc_BYTES 32

extern void crypto_kem_460896pc_keypair(unsigned char *,unsigned char *);
extern int crypto_kem_460896pc_enc(unsigned char *,unsigned char *,const unsigned char *);
extern int crypto_kem_460896pc_dec(unsigned char *,const unsigned char *,const unsigned char *);

#endif
