This document explains the internal structure of libmceliece, and explains
how to add new instruction sets and new implementations. The libmceliece
infrastructure is adapted from the lib25519 infrastructure.

## Primitives

The directories `crypto_*/*` inside libmceliece define the following
primitives:

* `crypto_xof/bitwrite16`: `crypto_xof_bitwrite16(out,outlen,in,inlen)`
  computes bytes `out[0]`, `out[1]`, ..., `out[outlen-1]` from bytes
  `in[0]`, `in[1]`, ..., `in[inlen-1]` as follows.
  The first 2 input bytes are viewed (in little-endian form) as a 16-bit
  integer; the next 2 input bytes are viewed as a 16-bit integer; and so
  on, with any remaining byte ignored. Bit position i in the output is 1
  if i modulo 65536 is one of these 16-bit integers, otherwise 0.

* `crypto_xof/shake256`: `crypto_xof_shake256(out,outlen,in,inlen)`
  computes bytes `out[0]`, `out[1]`, ..., `out[outlen-1]` as the first
  `outlen` bytes of the (infinitely long) SHAKE256 hash of bytes
  `in[0]`, `in[1]`, ..., `in[inlen-1]`.

* `crypto_sort/int16`: `crypto_sort_int16(x,n)` sorts the `int16`
  values `x[0]`, `x[1]`, ..., `x[n-1]`.

* `crypto_sort/int32`: `crypto_sort_int32(x,n)` sorts the `int32`
  values `x[0]`, `x[1]`, ..., `x[n-1]`.

* `crypto_sort/int64`: `crypto_sort_int64(x,n)` sorts the `int64`
  values `x[0]`, `x[1]`, ..., `x[n-1]`.

* `crypto_kem/*`: `crypto_kem_6960119_keypair(pk,sk)` is key generation
  for the `6960119` parameter set, and is provided by the
  [stable API](api.html)
  as `mceliece6960119_keypair`. Similar comments apply to `enc` and `dec`,
  to the `f` variants, and to sizes other than `6960119`.

libmceliece includes a command-line utility `mceliece-test` that runs
some tests for each of these primitives, and another utility
`mceliece-speed` that measures cycle counts for each of these
primitives.

As in SUPERCOP and NaCl, message lengths intentionally use `long long`,
not `size_t`. In libmceliece, as in lib25519, message lengths are
signed.

## Implementations

A single primitive can, and usually does, have multiple implementations.
Each implementation is in its own subdirectory. The implementations are
required to have exactly the same input-output behavior, and to some
extent this is tested, although it is not yet formally verified (except
for some components such as `crypto_sort`).

Different implementations typically offer different tradeoffs between
portability, simplicity, and efficiency. For example,
`crypto_kem/6960119/vec` is portable; `crypto_kem/6960119/avx` is faster
and less portable.

Each unportable implementation has an `architectures` file. Each line in
this file identifies a CPU instruction set (and ABI) where the
implementation works. For example, `crypto_kem/6960119/avx/architectures`
has one line

    amd64 sse3 ssse3 sse41 popcnt avx bmi1 bmi2 avx2

meaning that the implementation works on CPUs that have the Intel/AMD
64-bit instruction set with the SSE3, SSSE3, SSE4.1, POPCNT, AVX, BMI1,
BMI2, and AVX2 instruction-set extensions. The top-level `compilers`
directory shows (among other things) the allowed instruction-set names
such as `bmi2`.

At run time, libmceliece checks the CPU where it is running, and selects
an implementation where `architectures` is compatible with that CPU.
Each primitive makes its own selection once per program startup, using
the compiler's `ifunc` mechanism (or `constructor` on platforms that do
not support `ifunc`). This type of run-time selection means, for
example, that an `amd64` CPU without AVX2 can share binaries with an
`amd64` CPU with AVX2. However, correctness requires instruction sets to
be preserved by migration across cores via the OS kernel, VM migration,
etc.

The compiler has a `target` mechanism that makes an `ifunc` selection
based on CPU architectures. Instead of using the `target` mechanism,
libmceliece uses a more sophisticated mechanism that also accounts for
benchmarks collected in advance of compilation.

## Compilers

libmceliece tries different C compilers for each implementation. For
example, `compilers/default` lists the following compilers:

    gcc -Wall -fPIC -fwrapv -O2
    clang -Wall -fPIC -fwrapv -Qunused-arguments -O2

Sometimes `gcc` produces better code, and sometimes `clang` produces
better code.

As another example, `compilers/amd64+sse3+ssse3+sse41+sse42+popcnt+avx+bmi1+bmi2+avx2`
lists the following compilers:

    gcc -Wall -fPIC -fwrapv -O2 -mmmx -msse -msse2 -msse3 -mssse3 -msse4.1 -msse4.2 -mavx -mbmi -mbmi2 -mpopcnt -mavx2 -mtune=haswell
    clang -Wall -fPIC -fwrapv -Qunused-arguments -O2 -mmmx -msse -msse2 -msse3 -mssse3 -msse4.1 -msse4.2 -mavx -mbmi -mbmi2 -mpopcnt -mavx2 -mtune=haswell

The `-mavx2` option tells these compilers that they are free to use the
AVX2 instruction-set extension.

Code compiled using the compilers in
`compilers/amd64+sse3+ssse3+sse41+sse42+popcnt+avx+bmi1+bmi2+avx2`
will be considered at run time by the libmceliece selection mechanism if
the `supports()` function in
`compilers/amd64+sse3+ssse3+sse41+sse42+popcnt+avx+bmi1+bmi2+avx2.c`
returns nonzero. This function checks whether the run-time CPU supports
AVX2 (and SSE3 and so on, and OSXSAVE with XMM/YMM being saved;
[https://gcc.gnu.org/bugzilla/show_bug.cgi?id=85100](https://gcc.gnu.org/bugzilla/show_bug.cgi?id=85100)
says that all versions of gcc until 2018 handled this incorrectly in
`target`). Similar comments apply to other `compilers/*` files.

If some compilers fail (for example, clang is not installed, or the
compiler version is too old to support the compiler options used in
libmceliece), the libmceliece compilation process will try its best to
produce a working library using the remaining compilers, even if this
means lower performance.

## Trimming

By default, to reduce size of the compiled library, the libmceliece
compilation process trims the library down to the implementations that
are selected by libmceliece's selection mechanism.

For example, if the selection mechanism decides that CPUs with AVX2
should use `6960119/avx` with `clang` and that other CPUs should use
`6960119/vec` with `gcc`, then trimming will remove `6960119/avx`
compiled with `gcc` and `6960119/vec` compiled with `clang`.

This trimming is handled at link time rather than compile time to
increase the chance that, even if some implementations are broken by
compiler "upgrades", the library will continue to build successfully.

To avoid this trimming, pass the `--no-trim` option to `./configure`. 
All implementations that compile are then included in the library,
tested by `mceliece-test`, and measured by `mceliece-speed`. You'll want
to avoid trimming if you're adding new instruction sets or new
implementations (see below), so that you can run tests and benchmarks of
code that isn't selected yet.

## How to recompile after changes

If you make changes in the libmceliece source directory, the fully
supported recompilation mechanism is to run `./configure` again to clean
and repopulate the build directory, and then run `make` again to
recompile everything.

This can be on the scale of seconds if you have enough cores, but maybe
you're developing on a slower machine. Three options are currently
available to accelerate the edit-compile cycle:

   * There is an experimental `--no-clean` option to `./configure` that,
     for some simple types of changes, can produce a successful build
     without cleaning.

   * Running `make` without `./configure` can work for some particularly
     simple types of changes. However, not all dependencies are
     currently expressed in `Makefile`, and some types of dependencies
     that `./configure` understands would be difficult to express in the
     `Makefile` language.

   * You can disable the implementations you're not using by setting
     sticky bits on the source directories for those implementations:
     e.g., `chmod +t crypto_kem/*/avx`.

Make sure to reenable all implementations and do a full clean build if
you're collecting data to add to the source `benchmarks` directory.

## How to add new instruction sets

Adding another file `compilers/amd64+foo`, along with a `supports()`
implementation in `compilers/amd64+foo.c`, will support a new
instruction set. Do not assume that the new `foo` instruction set
implies support for older instruction sets (the idea of "levels" of
instruction sets); instead make sure to include the older instruction
sets in `+` tags, as illustrated by
`compilers/amd64+sse3+ssse3+sse41+sse42+popcnt+avx+bmi1+bmi2+avx2`.

In the compiler options, always make sure to include `-fPIC` to support
shared libraries, and `-fwrapv` to switch to a slightly less dangerous
version of C.

The `foo` tags don't have to be instruction sets. For example, if a CPU
has the same instruction set but wants different optimizations because
of differences in instruction timings, you can make a tag for those
optimizations, using, e.g., CPU IDs or benchmarks in the corresponding
`supports()` function to decide whether to enable those optimizations.
Benchmarks tend to be more future-proof than a list of CPU IDs, but the
time taken for benchmarks at program startup has to be weighed against
the subsequent speedup from the resulting optimizations.

To see how well libmceliece performs with the new compilers, run
`mceliece-speed` on the target machine and look for the `foo` lines in
the output. If the new performance is better than the performance shown
on the `selected` lines:

   * Copy the `mceliece-speed` output into a file on the `benchmarks`
     directory, typically named after the hostname of the target
     machine.

   * Run `./prioritize` in the top-level directory to create `priority`
     files. These files tell libmceliece which implementations to select
     for any given architecture.

   * Reconfigure (again with `--no-trim`), recompile, rerun
     `mceliece-test`, and rerun `mceliece-speed` to check that the
     `selected` lines now use the `foo` compiler.

If the `foo` implementation is outperformed by other implementations,
then these steps don't help except for documenting this fact. The same
implementation might turn out to be useful for subsequent `foo` CPUs.

## How to add new implementations

Taking full advantage of the `foo` instruction set usually requires
writing new implementations. Sometimes there are also ideas for taking
better advantage of existing instruction sets.

Structurally, adding a new implementation of a primitive is a simple
matter of adding a new subdirectory with the code for that
implementation. Most of the work is optimizing the use of `foo`
intrinsics in `.c` files or `foo` instructions in `.S` files. Make sure
to include an `architectures` file saying, e.g., `amd64 avx2 foo`.

Names of implementation directories can use letters, digits, dashes, and
underscores. Do not use two implementation names that are the same when
dashes and underscores are removed.

All `.c` and `.S` files in the implementation directory are compiled and
linked. There is no need to edit a separate list of these files. You can
also use `.h` files via the C preprocessor.

If an implementation is actually more restrictive than indicated in
`architectures` then the resulting compiled library will fail on some
machines (although perhaps that implementation will not be used by
default). Putting unnecessary restrictions into `architectures` will not
create such failures, but can unnecessarily limit performance.

Some, but not all, mistakes in `architectures` will produce warnings
from the `checkinsns` script that runs automatically when libmceliece is
compiled. Running the `mceliece-test` program tries all implementations,
but only on the CPU where `mceliece-test` is being run;
also, `mceliece-test` does not guarantee code coverage.

`amd64` implies little-endian, and implies architectural support for
unaligned loads and stores. Beware, however, that the Intel/AMD
vectorized `load`/`store` intrinsics (and the underlying `movdqa`
instruction) require alignment; if in doubt, use `loadu`/`storeu` (and
`movdqu`). The `mceliece-test` program checks unaligned inputs and
outputs, but can miss issues with unaligned stack variables.

To test your implementation, compile everything, check for compiler
warnings and errors, run `mceliece-test` (or just `mceliece-test xof` to
test a `crypto_xof` implementation), and check for a line saying `all
tests succeeded`. To use AddressSanitizer (for catching, at run time,
buffer overflows in C code), add `-fsanitize=address` to the `gcc` and
`clang` lines in `compilers/*`; you may also have to add `return;` at
the beginning of the `limits()` function in `command/limits.inc`.

To see the performance of your implementation, run `mceliece-speed`. If
the new performance is better than the performance shown on the
`selected` lines, follow the same steps as for a new instruction set:
copy the `mceliece-speed` output into a file on the `benchmarks`
directory; run `./prioritize` in the top-level directory to create
`priority` files; reconfigure (again with `--no-trim`); recompile; rerun
`mceliece-test`; rerun `mceliece-speed`; check that the `selected` lines
now use the new implementation.

## How to handle namespacing

As in SUPERCOP and NaCl, to call `crypto_sort_int32()`, you have to
include `crypto_sort_int32.h`; but to write an implementation of
`crypto_sort_int32()`, you have to instead include `crypto_sort.h` and
define `crypto_sort`. Similar comments apply to other primitives.

The function name that's actually linked might end up as, e.g.,
`libmceliece_sort_int32_avx2_C2` where `avx2` indicates the
implementation and `C2` indicates the compiler. Don't try to build this
name into your implementation.

If you have another global symbol `x` (for example, a non-`static`
function in a `.c` file, or a non-`static` variable outside functions in
a `.c` file), you have to replace it with `CRYPTO_NAMESPACE(x)`, for
example with `#define x CRYPTO_NAMESPACE(x)`.

For global symbols in `.S` files and `shared-*.c` files, use
`CRYPTO_SHARED_NAMESPACE` instead of `CRYPTO_NAMESPACE`. For `.S` files
that define both `x` and `_x` to handle platforms where `x` in C is `_x`
in assembly, use `CRYPTO_SHARED_NAMESPACE(x)` and
`_CRYPTO_SHARED_NAMESPACE(x)`; `CRYPTO_SHARED_NAMESPACE(_x)` is not
sufficient.

libmceliece includes a mechanism to recognize files that are copied
across implementations (possibly of different primitives) and to unify
those into a file compiled only once, reducing the overall size of the
compiled library and possibly improving cache utilization. To request
this mechanism, include a line
```
// linker define x
```
for any global
symbol `x` defined in the file, and a line
```
// linker use x
```
for any
global symbol `x` used in the file from the same implementation (not
`crypto_*` subroutines that you're calling, `randombytes`, etc.). This
mechanism tries very hard, perhaps too hard, to avoid improperly
unifying files: for example, even a slight difference in a `.h` file
included by a file defining a used symbol will disable the mechanism.

Typical namespacing mistakes will produce either linker failures or
warnings from the `checknamespace` script that runs automatically when
libmceliece is compiled.
