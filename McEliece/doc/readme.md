libmceliece is a [Classic McEliece](https://classic.mceliece.org)
microlibrary. libmceliece has a very simple stateless API based on the
SUPERCOP API, with wire-format inputs and outputs, providing functions
that directly match the KEM operations provided by Classic McEliece,
such as functions

    mceliece6960119_keypair
    mceliece6960119_enc
    mceliece6960119_dec

for the `mceliece6960119` KEM.

Internally, libmceliece is based on the official Classic McEliece
software, specifically the `vec` implementation (designed to work
portably across CPUs) and the `avx` implementation (designed for higher
performance on Intel/AMD CPUs with AVX2 instructions). libmceliece
includes automatic run-time selection of implementations.

libmceliece is intended to be called by larger multi-function
libraries (such as traditional cryptographic libraries), including
libraries in other languages via FFI. The idea is that libmceliece
takes responsibility for the details of Classic McEliece computation,
including optimization, timing-attack protection, and (in ongoing work)
verification, freeing up the calling libraries to concentrate on
application-specific needs such as protocol integration. Applications
can also call libmceliece directly.

Latest release: [20260622](download.html).
