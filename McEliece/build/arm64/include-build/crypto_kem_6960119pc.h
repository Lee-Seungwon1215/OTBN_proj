#ifndef crypto_kem_6960119pc_h
#define crypto_kem_6960119pc_h

#define crypto_kem_6960119pc_keypair mceliece_kem_6960119pc_keypair
#define crypto_kem_6960119pc_enc mceliece_kem_6960119pc_enc
#define crypto_kem_6960119pc_dec mceliece_kem_6960119pc_dec

#define crypto_kem_6960119pc_PUBLICKEYBYTES 1047319
#define crypto_kem_6960119pc_SECRETKEYBYTES 13948
#define crypto_kem_6960119pc_CIPHERTEXTBYTES 226
#define crypto_kem_6960119pc_BYTES 32

extern void crypto_kem_6960119pc_keypair(unsigned char *,unsigned char *);
extern int crypto_kem_6960119pc_enc(unsigned char *,unsigned char *,const unsigned char *);
extern int crypto_kem_6960119pc_dec(unsigned char *,const unsigned char *,const unsigned char *);

#endif
