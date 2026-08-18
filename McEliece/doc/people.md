libmceliece is based on the official Classic McEliece software, which
was written by Tung Chou. See the following papers for the major
algorithms used for speed inside that software:

* Daniel J. Bernstein, Tung Chou, Peter Schwabe. "McBits: fast
  constant-time code-based cryptography." CHES 2013.
  [https://tungchou.github.io/papers/mcbits.pdf](https://tungchou.github.io/papers/mcbits.pdf)

* Tung Chou. "McBits revisited." CHES 2017.
  [https://tungchou.github.io/papers/mcbits_revisited.pdf](https://tungchou.github.io/papers/mcbits_revisited.pdf)

The official Classic McEliece software includes `ref`, `vec`, `sse`, and
`avx` implementations; libmceliece includes only `vec` and `avx`.

The following components of libmceliece are from Daniel J. Bernstein:

* Small [changes](download.html#changelog)
  for namespacing, portability, etc.

* Software to compute control bits (also used in the official software).
  See the following paper: Daniel J. Bernstein. "Verified fast formulas
  for control bits for permutation networks." 2020.
  [https://cr.yp.to/papers.html#controlbits](https://cr.yp.to/papers.html#controlbits)

* Infrastructure to build a library with automatic run-time selection of
  implementations based on the run-time CPU and a database of
  benchmarks. This infrastructure was introduced in
  [`lib25519`](https://lib25519.cr.yp.to), with some extensions and
  adaptations in libmceliece.

* Various software for tests and benchmarks. This is based on
  public-domain code in the SUPERCOP benchmarking framework.

* The underlying subroutines
  `crypto_sort`
  (based on [https://sorting.cr.yp.to](https://sorting.cr.yp.to)),
  `crypto_xof/bitwrite16`,
  and `crypto_xof/shake256/unrollround`.

A separate SHAKE256 implementation,
`crypto_xof/shake256/tweet`,
is based on
[https://twitter.com/tweetfips202](https://twitter.com/tweetfips202)
by Daniel J. Bernstein, Peter Schwabe, and Gilles Van Assche.
