#ifndef crypto_kem_8192128_h
#define crypto_kem_8192128_h

#define crypto_kem_8192128_keypair mceliece_kem_8192128_keypair
#define crypto_kem_8192128_enc mceliece_kem_8192128_enc
#define crypto_kem_8192128_dec mceliece_kem_8192128_dec

#define crypto_kem_8192128_PUBLICKEYBYTES 1357824
#define crypto_kem_8192128_SECRETKEYBYTES 14120
#define crypto_kem_8192128_CIPHERTEXTBYTES 208
#define crypto_kem_8192128_BYTES 32

extern void crypto_kem_8192128_keypair(unsigned char *,unsigned char *);
extern int crypto_kem_8192128_enc(unsigned char *,unsigned char *,const unsigned char *);
extern int crypto_kem_8192128_dec(unsigned char *,const unsigned char *,const unsigned char *);

#endif
