#ifndef crypto_kem_6688128pc_h
#define crypto_kem_6688128pc_h

#define crypto_kem_6688128pc_keypair mceliece_kem_6688128pc_keypair
#define crypto_kem_6688128pc_enc mceliece_kem_6688128pc_enc
#define crypto_kem_6688128pc_dec mceliece_kem_6688128pc_dec

#define crypto_kem_6688128pc_PUBLICKEYBYTES 1044992
#define crypto_kem_6688128pc_SECRETKEYBYTES 13932
#define crypto_kem_6688128pc_CIPHERTEXTBYTES 240
#define crypto_kem_6688128pc_BYTES 32

extern void crypto_kem_6688128pc_keypair(unsigned char *,unsigned char *);
extern int crypto_kem_6688128pc_enc(unsigned char *,unsigned char *,const unsigned char *);
extern int crypto_kem_6688128pc_dec(unsigned char *,const unsigned char *,const unsigned char *);

#endif
