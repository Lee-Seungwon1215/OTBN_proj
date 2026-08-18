Cryptosystem security model: Classic McEliece is a KEM designed for
IND-CCA2 security, upgrading from the original McEliece design goal of
OW-CPA security. Some applications need other security notions;
typically these can be provided by generic wrappers on top of IND-CCA2.

[Cryptosystem security review](https://classic.mceliece.org/mceliece-security-20221023.pdf):
The McEliece cryptosystem has a stable security track record.
[Extensive cryptanalysis](https://classic.mceliece.org/papers.html)
over half a century has produced only
[minor changes](https://classic.mceliece.org/comparison.html)
in the McEliece security level,
backed by
[high-assurance analyses](https://cr.yp.to/papers.html#cat)
of attack costs.
The QROM IND-CCA2 security level of Classic McEliece
is
[provably](https://classic.mceliece.org/mceliece-security-20221023.pdf)
close to the OW-CPA security level of the original McEliece system.
Classic McEliece addresses the risk of
IND-CCA2 attacks beyond QROM IND-CCA2 attacks
by choosing a well-studied, high-security, "unstructured" hash function,
namely SHAKE256.

Security level: The 6688128 and 6960119 parameter sets are
[recommended for long-term security](https://classic.mceliece.org/mceliece-impl-20221023.pdf#subsection.3.2)
and provide a large security margin against known attacks, including
quantum attacks.

Software verification: Covered [separately](verification.html).

Timing attacks: libmceliece is designed to avoid all data flow from
secret data to memory addresses and branch conditions. libmceliece uses
operations that naturally avoid such data flow, and includes valgrind
tests (based on TIMECOP from SUPERCOP) designed to catch any such data
flow introduced by compilers. Fully protecting the user against timing
attacks requires addressing more issues, such as the following:

* Other CPU instructions can take variable time. For example, there are
  some CPUs, especially embedded CPUs, where integer multiplication
  takes variable time. Most cryptographic libraries rely on source-level
  integer multiplications with secret inputs, and compiler optimizations
  can introduce further multiplications with secret inputs. libmceliece
  avoids source-level data flow from secrets to integer multiplications
  and has some source-level defenses against problems introduced by
  compilers, but the test suite does not yet scan for multiplications.

* Many CPUs include dynamic frequency-selection mechanisms such as Turbo
  Boost, exposing power information via timing information. Fortunately,
  these CPUs are normally shipped with simple options to disable Turbo
  Boost etc., closing this leak; unfortunately, Turbo Boost is enabled
  by default on CPUs that support it.

* Cryptographic keys are normally handled by cryptographic software, but
  other user secrets are handled by many different pieces of software.

See [https://timing.attacks.cr.yp.to](https://timing.attacks.cr.yp.to)
for a timing-attack survey and many references.

Speculative-execution attacks: Some countermeasures against
speculative-execution attacks are planned but are not included in the
current version of libmceliece. Full protection again requires
addressing issues at other system layers.

Further side-channel attacks: Even if all legitimate user sensors are
successfully kept isolated from attackers, attackers can set up their
own power sensors, electromagnetic sensors, acoustic sensors, etc.
Keeping cryptographic operations physically separated from sensors tends
to make such attacks much more expensive but is often infeasible.
"Masking" cryptographic computations seems to help and can be
affordable, although the security of masking is difficult to evaluate
and there are many broken masked implementations. Currently libmceliece
does not include any masked implementations, so presumably it is easily
breakable by power attacks in environments where attackers can see power
consumption.

Further attacks: Presumably libmceliece is easily breakable by fault
attacks in environments where attackers can trigger faults. Beyond
attacker-triggered faults, natural DRAM faults occur surprisingly often.
Implicit rejection [fails](https://cr.yp.to/papers.html#ntrw) to
provide IND-CCA2 security when DRAM faults corrupt the secret key used
for implicit rejection. On the defense side, error correction is
recommended (and often not provided by hardware), and there is a
general-purpose [libsecded](https://pqsrc.cr.yp.to/downloads.html)
library that applies error correction to any array, although this does
not catch errors that occur during computations.
