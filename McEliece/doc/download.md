To download and unpack the latest version of libmceliece:

    wget -m https://lib.mceliece.org/libmceliece-latest-version.txt
    version=$(cat lib.mceliece.org/libmceliece-latest-version.txt)
    wget -m https://lib.mceliece.org/libmceliece-$version.tar.gz
    tar -xzf lib.mceliece.org/libmceliece-$version.tar.gz
    cd libmceliece-$version

Then [install](install.html)
and [test](test.html).

### Archives and changelog (reverse chronological) {#changelog}

[`libmceliece-20260622.tar.gz`](libmceliece-20260622.tar.gz) [browse](libmceliece-20260622.html)

Import `avx2` and `neon` code from `djbsort-20260210` for `int32` and `int64`.

Use `cryptoint` more in `crypto_kem/*/*/kem_dec.c`.

Allow more base instructions in `checkinsns`.

Tweak `checkinsns` to work around `capstone` not understanding `vbroadcasti128`.

Recognize `ppc64el` in `configure`.

Support Python 3.14 in `fulltest`,
copying djbsort patch supplied by Georg Sauthoff.

Add initial support for `$CROSS` and `$DESTDIR`.

Add initial tweaks for Fil-C support.
(But Fil-C is starting to add support for inline assembly so some of these tweaks can disappear later.)

Include auto-generator for `compilers/*`.

Change HTML style, in particular for better usability on phones.

---

[`libmceliece-20250507.tar.gz`](libmceliece-20250507.tar.gz) [browse](libmceliece-20250507.html)

Upgrade to `cryptoint 20250414`.

Use `cryptoint` more in `crypto_xof/bitwrite16` implementations.

In preparation for potential `-Wc++-compat`,
avoid C++ reserved words and include some explicit conversions.

In preparation for potential `-Wshadow`,
rename a `controlbits` variable.

Tweak constructor priority in `dispatch`.

Integrate revamped `checkinsns` that uses `python3-capstone`
(or that skips instruction-set tests if `python3-capstone` isn't installed).

Improve platform support in `hostsanitize`.

For `checknamespace`,
skip `n` symbols for FreeBSD;
skip `__sparc_get_pc_thunk`, empty section names, and `f` symbols for Solaris;
skip `-p` sorting (on Solaris, `-p` and `-P` are incompatible);
support class `D` for PPC.

---

[`libmceliece-20241009.tar.gz`](libmceliece-20241009.tar.gz) [browse](libmceliece-20241009.html)

Upgrade to `cryptoint 20241003`.

Use `cryptoint` for variable shifts in the `f` variants.

Say `full tests succeeded` in `mceliece-fulltest` documentation.

---

[`libmceliece-20240812.tar.gz`](libmceliece-20240812.tar.gz) [browse](libmceliece-20240812.html)

Restructure `gf` for simpler code:
`gf.h` is now shared across all parameter sets;
each of the two field sizes has one `gf_params.h`, one `gf.c`, one `gf_2m_mul.c`, and one `gf_2m_mul2.c`;
each of the four extension-field sizes has one `gf_2mt_mul.c`.

Support finer-grained command-line splits in `mceliece-test`,
and use those for more parallelization inside `mceliece-fulltest`.

Proactively rewrite many 1-bit data paths via `cryptoint`.

Update to latest `cryptoint` from SUPERCOP (renamed from `inttypes`).

Fix comment on `minmax_rows`.

Remove some unused `#include` lines.

---

[`libmceliece-20240726.tar.gz`](libmceliece-20240726.tar.gz) [browse](libmceliece-20240726.html)

Add `mceliece-fulltest` script, and designate passing `mceliece-fulltest` as required for support.

Make `--valgrind` default, and designate disabling it as unsupported.

Split off `doc/test.md`.

Update to latest `inttypes` from SUPERCOP.

Use `inttypes` more in `pk_gen.c`.

Move comments to the top in `encrypt.c`.

Rename `--no` as `--no-`.

Rename `ALIGN` as `CRYPTO_ALIGN`.

Document more subroutines in `doc/internals.md`.

---

[`libmceliece-20240513.tar.gz`](libmceliece-20240513.tar.gz) [browse](libmceliece-20240513.html)

Support `valgrind` in `mceliece-test`,
with help from `configure`.
(Subsequent plans:
use variable-length `malloc`
for variable-length functions.)

Cover `shared` directories for `checkinsns` and `checknamespace`.

Sort `ofiles` for reproducibility.
Thanks to Jan Mojzis for the suggestion.

Hide more symbols in `.so`.

MacOS X port:
`dylib`;
deal with `s` and `S` in `checknamespace`;
use `-flat_namespace` so `mceliece-test` can substitute `randombytes`.
(Infrastructure copied from lib25519.)

Support empty compiler lists.
(Infrastructure copied from lib25519.)

For compatibility with musl etc.,
support `constructor` as an alternative to `ifunc` for dispatch.
Select `constructor` automatically if an `ifunc` compile-time test fails,
or if `--notryifunc` is passed to `./configure`.
(Infrastructure copied from lib25519.)

Add `note.GNU-stack` to assembly.

Recognize `sun4v` as `sparc64`.

Port to CPUs that do not allow unaligned access.

Revamp `inttypes` support.
Make more use of the `inttypes` functions.

Factor `crypto_xof/bitwrite16`
out of `*/encrypt.c`,
and add new `bitwrite16` implementations.
Also support `nooverlap` option in `mceliece-test`,
and increase `maxtest` for `xof` to 16384.

Switch `avx/encrypt.c`
from `syndrome_asm` to new `xor_mat_vec256`.
Add support functions such as
`vec256_8x_shr`.

Factor `crypto_sort_int16`
out of `vec/encrypt.c`.
(Subsequent plans:
add faster `crypto_sort/int16` implementations,
and switch `avx/encrypt.c` from `int32` to `int16`.)

Factor `crypto_sort_int64`
out of `pk_gen.c`.

Use `crypto_sort_int32` directly without the `int32_sort` renaming.

Split `vec128_gf.h` and `vec256_gf.h`
out of `vec128.h` and `vec256.h`.
Distinguish `vec_mul_gf`
from `vec_mul_gf_using_64`
to allow more `.h` merging across sizes.

In `autogen/speed`,
allocate only `mceliece_kem_BYTES` for `T`
rather than `mceliece_kem_CIPHERTEXTBYTES`.

Switch speed measurements from medians to interquartile means.

Add page with examples of current speeds.

Add auto-generation warnings
for `mceliece*.c`.

Add manual pages for `mceliece-test` and `mceliece-speed`.

Improve readability of code blocks in HTML.

Remove unused `KAT` code segments.

Remove unused `bitrev`.

Remove unused `perm_check`.
Thanks to Simon Josefsson for the suggestion.

More explicitly initialize `pivots`
to silence an incorrect compiler warning.
Thanks to Simon Josefsson for the suggestion.

---

[`libmceliece-20230612.tar.gz`](libmceliece-20230612.tar.gz) [browse](libmceliece-20230612.html)

In `*/avx/pk_gen.c`,
use merge exchange in `sort_rows()`
and slightly reduce the number of lines of `minmax_rows()`.

Rename `encrypt()` as `pke_encrypt()`,
to more portably avoid name collision with POSIX `encrypt()`.

Add more 0-initialization in the `to_bitslicing` functions.
This doesn't help a full correctness proof,
but it does make it easier to see that undefined data is not used.
Thanks to Thom Wiggers for the suggestion.

For MacOS portability,
move `#include "encrypt.h"` after other inclusions,
and change `.hidden` to `.private_extern` (via a new `ASM_HIDDEN`)
if `__APPLE__` is defined.
Thanks to Thom Wiggers for the suggestions.

Specify 32-byte alignment for some arrays passed to `.S` files
in the `avx` implementations.
The `.S` files use `movdqu` instead of `movdqa`,
so they don't need alignment,
but the alignment could avoid warnings
from a compiler that checks for potentially inadequate alignment.
Thanks to Thom Wiggers for the suggestion.

Remove an unused pointer increment at the end of `benes.c`.
Thanks to Thom Wiggers for the suggestion.

Add various `linker` lines in `.c` files and `.S` files;
split `operations.c` into `kem_{keypair,enc,dec}.c` and `wrap_{keypair,enc,dec}.c`;
and split big constant arrays from `fft.c`, `fft_tr.c`
into separate `shared-*.c` files.
The `linker` lines trigger an infrastructure mechanism
to unify compiled code across implementations,
reducing `.so` size;
the splits improve the effectiveness of this mechanism,
and reduce the amount of code linked
into programs that use only one or two of `{keypair,enc,dec}`.
Further changes to the infrastructure may remove the need for `wrap*.c`.

Add `const` to prototypes for input pointers for some functions.
More can be done here.

Change prototypes from `*` and `[]` to, e.g., `[GFBITS]`
when necessary to eliminate compiler warnings.

Move `gf_mul2` to `crypto_kem/6688128/avx/gf.h` from `gf.c`.

Consistently define `nBlocksI` as a macro rather than a const.
This is a step towards portability to compilers that fail to support C99.

Extend information in `architectures` files.
This supports libmceliece's run-time selection of implementations.

Switch from `CRYPTO_NAMESPACE` to `CRYPTO_SHARED_NAMESPACE`
for symbols defined in `.S` files.

Rename `crypto_hash.h` as `hash.h`,
and rewrite `hash.h` as a wrapper around `crypto_xof_shake256()`.

Switch `keypair` return value to `void`.

Remove `namespacing` files, `goal-*` files, and `api.h`.

Rename `kem/mceliece*` as `kem/*`.

Starting point:
`vec` and `avx` implementations
from official round-4 software release
(in `supercop-20221025`),
plus `crypto_sort/int32`
and `crypto_xof/shake256`,
plus infrastructure based on lib25519 infrastructure.
