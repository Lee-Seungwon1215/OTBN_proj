#ifndef crypto_kem_348864pc_h
#define crypto_kem_348864pc_h

#define crypto_kem_348864pc_keypair mceliece_kem_348864pc_keypair
#define crypto_kem_348864pc_enc mceliece_kem_348864pc_enc
#define crypto_kem_348864pc_dec mceliece_kem_348864pc_dec

#define crypto_kem_348864pc_PUBLICKEYBYTES 261120
#define crypto_kem_348864pc_SECRETKEYBYTES 6492
#define crypto_kem_348864pc_CIPHERTEXTBYTES 128
#define crypto_kem_348864pc_BYTES 32

extern void crypto_kem_348864pc_keypair(unsigned char *,unsigned char *);
extern int crypto_kem_348864pc_enc(unsigned char *,unsigned char *,const unsigned char *);
extern int crypto_kem_348864pc_dec(unsigned char *,const unsigned char *,const unsigned char *);

#endif
