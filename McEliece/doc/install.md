Prerequisites:

* `python3` (for: build, test)
* recommended `python3-capstone` (for: build)
* `gcc` and/or `clang` (for: build)
* `valgrind` (for: build, test)
* [`libcpucycles`](https://cpucycles.cr.yp.to) (for: build, bench)
* [`librandombytes`](https://randombytes.cr.yp.to) (for: build, test, bench, run)

Make sure to [test](test.html) the compiled library.
The tests check for subtle security problems that can be created by compilers.
A compiled version of libmceliece is **not supported** unless it passes the full test suite.

### For sysadmins

To install in `/usr/local/{include,lib,bin,man}`:

    ./configure && make -j8 install

### For developers with an unprivileged account

Typically you'll already have

    export LD_LIBRARY_PATH="$HOME/lib"
    export LIBRARY_PATH="$HOME/lib"
    export CPATH="$HOME/include"
    export MANPATH="$HOME/man"
    export PATH="$HOME/bin:$PATH"

in `$HOME/.profile`. To install in `$HOME/{include,lib,bin,man}`:

    ./configure --prefix=$HOME && make -j8 install

### For distributors creating a package

Run

    ./configure --prefix=/usr && make -j8

and then follow your usual packaging procedures for the
`build/0/package` files:

    build/0/package/include/mceliece.h
    build/0/package/lib/libmceliece*
    build/0/package/bin/mceliece*
    build/0/package/man/man3/*.3
    build/0/package/man/man1/*.1

### More options, part 1: architectures

You can run

    ./configure --host=amd64

to override `./configure`'s guess of the architecture that it should
compile for.

Inside the `build` directory, `0` is symlinked to `amd64` for
`--host=amd64`. Running `make clean` removes `build/amd64`. Re-running
`./configure` automatically starts with `make clean`.

A subsequent `./configure --host=arm64` will create `build/arm64` and
symlink `0 -> arm64`, without touching an existing `build/amd64`. However,
cross-compilers aren't yet selected automatically.

### More options, part 2

One further `./configure` option is supported for
[developers](internals.html):
`--no-trim`.

All `./configure` options not listed above are experimental and **not supported**.
Use them at your own risk.
