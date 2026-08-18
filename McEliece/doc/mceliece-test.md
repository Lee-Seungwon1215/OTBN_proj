### NAME

mceliece-test - run some libmceliece correctness tests

### SYNOPSIS

    mceliece-test

### DESCRIPTION

`mceliece-test`
runs some tests of the correctness of
the libmceliece implementation of the Classic McEliece cryptosystem.

The `mceliece-test` output format is subject to change.
As examples of the current format, the lines

    kem_6960119 offset 1
    kem_6960119 selected implementation avx compiler clang -Wall -fPIC -fwrapv -Qunused-arguments -O2 -mmmx -msse -msse2 -msse3 -mssse3 -msse4.1 -msse4.2 -mavx -mbmi -mbmi2 -mpopcnt -mavx2 -mtune=haswell; Ubuntu clang version 14.0.0-1ubuntu1; Target: x86_64-pc-linux-gnu; Thread model: posix; InstalledDir: /usr/bin

mean that `mceliece-test` is testing the automatically selected
`avx` implementation of the `6960119` parameter set
with various arrays offset by 1 byte from being aligned,
and a final line saying

    all tests succeeded

means that all tests passed.

### SEE ALSO

**mceliece-fulltest**(1),
**mceliece**(1),
**mceliece**(3)
