### NAME

mceliece - C API for the libmceliece implementation of the Classic McEliece cryptosystem

### SYNOPSIS

Using libmceliece:

    #include <mceliece.h>

Link with `-lmceliece`.

Key generation (for, e.g., `mceliece6960119`):

    unsigned char pk[mceliece6960119_PUBLICKEYBYTES];
    unsigned char sk[mceliece6960119_SECRETKEYBYTES];

    mceliece6960119_keypair(pk,sk);

Encapsulation (for, e.g., `mceliece6960119`):

    unsigned char ct[mceliece6960119_CIPHERTEXTBYTES];
    unsigned char k[mceliece6960119_BYTES];
    const unsigned char pk[mceliece6960119_PUBLICKEYBYTES];
    int ret;

    ret = mceliece6960119_enc(ct,k,pk);

Decapsulation (for, e.g., `mceliece6960119`):

    unsigned char k[mceliece6960119_BYTES];
    const unsigned char ct[mceliece6960119_CIPHERTEXTBYTES];
    const unsigned char sk[mceliece6960119_SECRETKEYBYTES];
    int ret;

    ret = mceliece6960119_dec(k,ct,sk);

### DESCRIPTION

libmceliece is an implementation
of the [Classic McEliece](https://classic.mceliece.org) cryptosystem.
The C API for libmceliece
provides the following functions:

    mceliece{6960119,6688128,8192128,460896,348864}_keypair
    mceliece{6960119,6688128,8192128,460896,348864}_enc
    mceliece{6960119,6688128,8192128,460896,348864}_dec
    mceliece{6960119,6688128,8192128,460896,348864}f_keypair
    mceliece{6960119,6688128,8192128,460896,348864}f_enc
    mceliece{6960119,6688128,8192128,460896,348864}f_dec

All of these functions follow the
[SUPERCOP API for KEMs](https://bench.cr.yp.to/call-kem.html)
except that

* the function names are libmceliece-specific instead of `crypto_kem_*`,
* message lengths are `long long` instead of `unsigned long long`, and
* the `keypair` functions return `void` instead of `int`.

The details below use `mceliece6960119` as an example.

### KEY GENERATION

The `mceliece6960119_keypair` function randomly generates
Alice's secret key
`sk[0]`, `sk[1]`, ..., `sk[mceliece6960119_SECRETKEYBYTES-1]`
and
Alice's corresponding public key
`pk[0]`, `pk[1]`, ..., `pk[mceliece6960119_PUBLICKEYBYTES-1]`.

### ENCAPSULATION

The `mceliece6960119_enc` function randomly generates
a ciphertext `ct[0]`, `ct[1]`, ..., `ct[mceliece6960119_CIPHERTEXTBYTES-1]`
and the corresponding session key
`k[0]`, `k[1]`, ..., `k[mceliece6960119_BYTES-1]`
given Alice's public key
`pk[0]`, `pk[1]`, ..., `pk[mceliece6960119_PUBLICKEYBYTES-1]`.
This function then returns `0`.

Exception:
If the input public key is not "narrowly decodable"
(i.e., if bits at particular positions in `pk` are set),
this function returns `-1`.
Currently the function also handles such public keys
by clearing `ct` and `k`,
but callers should not rely on this.

For `{6688128,8192128,460896,348864}{,f}`,
all byte strings of the correct length are narrowly decodable,
and the return value is always `0`.
For `6960119{,f}`, the return value can be `-1`.

### DECAPSULATION

The `mceliece6960119_dec` function,
given Alice's secret key
`sk[0]`, `sk[1]`, ..., `sk[mceliece6960119_SECRETKEYBYTES-1]`,
computes the session key
`k[0]`, `k[1]`, ..., `k[mceliece6960119_BYTES-1]`
corresponding to a ciphertext
`ct[0]`, `ct[1]`, ..., `ct[mceliece6960119_CIPHERTEXTBYTES-1]`
that was encapsulated to Alice.
This function then returns `0`.

Exception:
If the input ciphertext is not "narrowly decodable"
(i.e., if bits at particular positions in `ct` are set),
this function returns `-1`.
Currently this function also handles such ciphertexts
by setting all bytes of `k` to `255`,
but callers should not rely on this.

For `{6688128,8192128,460896,348864}{,f}`,
all byte strings of the correct length are narrowly decodable,
and the return value is always `0`.
For `6960119{,f}`, the return value can be `-1`.

### THE f VARIANTS

The `f` variants are internally more complicated than the non-`f` variants
but provide faster key generation.
The `f` variants are interoperable with the non-`f` variants:
for example, a key generated with `mceliece6960119f_keypair`
can decapsulate ciphertexts that were encapsulated with `mceliece6960119_enc`.
The secret-key sizes (and formats) are the same,
the `enc` functions are the same, and
the `dec` functions are the same.

### SEE ALSO

**mceliece**(1), **randombytes**(3)
