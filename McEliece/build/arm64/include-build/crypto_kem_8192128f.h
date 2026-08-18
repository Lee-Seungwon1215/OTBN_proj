#ifndef crypto_kem_8192128f_h
#define crypto_kem_8192128f_h

#define crypto_kem_8192128f_keypair mceliece_kem_8192128f_keypair
#define crypto_kem_8192128f_enc mceliece_kem_8192128f_enc
#define crypto_kem_8192128f_dec mceliece_kem_8192128f_dec

#define crypto_kem_8192128f_PUBLICKEYBYTES 1357824
#define crypto_kem_8192128f_SECRETKEYBYTES 14120
#define crypto_kem_8192128f_CIPHERTEXTBYTES 208
#define crypto_kem_8192128f_BYTES 32

extern void crypto_kem_8192128f_keypair(unsigned char *,unsigned char *);
extern int crypto_kem_8192128f_enc(unsigned char *,unsigned char *,const unsigned char *);
extern int crypto_kem_8192128f_dec(unsigned char *,const unsigned char *,const unsigned char *);

#endif
