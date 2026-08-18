libmceliece is intended to become a central target for verification of
full functional correctness of implementations of Classic McEliece. This
file tracks what has been verified so far and what has not.

The [Classic McEliece specification](https://classic.mceliece.org/spec.html)
is in English and is not currently computer-comprehensible. However,
there is a [Sage package](https://classic.mceliece.org/spec.html) that
has been manually checked line by line against the specification. Full
functional correctness of software X means that X computes the same
output as the Sage package for all possible inputs.

Changes in C compilers and in assemblers often change the behavior of
software and might introduce bugs where no bugs existed before. Some
tools address this by verifying correctness at the machine-language
level. It is important to re-run these tools whenever new binaries are
produced.

Changes in CPUs can also introduce bugs where no bugs existed before.
Verification is always relative to a model of CPU behavior, and physical
CPUs often deviate from these models, sometimes in problematic ways.

There is also a risk that current or future versions of Sage do not
correctly compute the documented Sage functions used by the Sage package.
This can interfere with falsifiability: even if the CPU matches the
model, a bug in a Classic McEliece implementation could be hidden by a
bug in Sage.

The `supercop-20221025/crypto_kem/mceliece*` checksums match the
checksums produced by libmceliece and checksums produced by the Sage
package. These checksums are hashes of outputs for various pseudorandomly
generated inputs (with randomness treated as another input). However,
there could be bugs for other inputs.

Separate tests on the official software have specifically checked bad
public-key padding and bad ciphertext padding (not just the specified
return value rejecting these inputs, but also the documented handling of
output buffers). The SUPERCOP checksum inputs also include bad
ciphertext padding and invalid ciphertexts. However, there could be
other types of inputs triggering bugs.

Various runs under `valgrind` and `asan` have not detected any abnormal
use of RAM. However, `valgrind` will not notice overflows from a C
variable into an adjacent C variable; `asan` will not notice overflows
in assembly language; and neither tool addresses the risk of bugs for
rare inputs.

<https://cr.yp.to/papers.html#goppadecoding>
presents computer-verified HOL Light proofs and computer-verified Lean
proofs for decoding formulas for classical binary Goppa codes. However,
there could be a mismatch between the software and these formulas.

<https://cr.yp.to/papers.html#controlbits>
presents computer-verified HOL Light proofs for the main formulas used
to compute control bits. However, there could be a mismatch between the
software and these formulas.

<https://github.com/linesthatinterlace/verif-cb/blob/main/src/verif-cb.lean>
presents computer-verified Lean proofs for the same control-bits formulas.

<https://sorting.cr.yp.to/verif.html>
presents tools that have been used to computer-verify machine-language
sorting software for all sizes of interest. However, there could be bugs
in these tools.

<https://github.com/linesthatinterlace/pqc-verification/tree/main/classic-mceliece/verification>
presents computer verification, using the SAW tool, that various C
functions match shorter descriptions in the Cryptol language. However,
this verification covers only some C functions, mainly finite-field
arithmetic and root-finding.
