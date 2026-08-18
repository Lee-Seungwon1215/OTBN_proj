### NAME

mceliece - command-line interface for the libmceliece implementation of the Classic McEliece cryptosystem

### SYNOPSIS

Key generation (for, e.g., `mceliece6960119`):

    mceliece6960119-keypair 5>publickey 9>secretkey

Encapsulation (for, e.g., `mceliece6960119`):

    mceliece6960119-enc >ciphertext 7>sessionkey 4<publickey
  
Decapsulation (for, e.g., `mceliece6960119`):

    mceliece6960119-dec 7>sessionkey <ciphertext 8<secretkey

### DESCRIPTION

libmceliece is an implementation
of the [Classic McEliece](https://classic.mceliece.org) cryptosystem.
The command-line interface for libmceliece
provides the following command-line tools:

    mceliece{6960119,6688128,8192128,460896,348864}-keypair
    mceliece{6960119,6688128,8192128,460896,348864}f-keypair
    mceliece{6960119,6688128,8192128,460896,348864}-enc
    mceliece{6960119,6688128,8192128,460896,348864}-dec

Each tool exits 0 on success, nonzero on failure.

These tools allow libmceliece
to be easily used from shell scripts.
Other languages can also use libmceliece via these tools,
but languages typically have good support for FFI
and can use the C interface directly.

The details below use `mceliece6960119` as an example.

### KEY GENERATION

Alice runs the `mceliece6960119-keypair` command.
This command randomly generates
Alice's secret key and Alice's corresponding public key.
It writes the public key to file descriptor 5,
and then writes the secret key to file descriptor 9.

The `mceliece6960119f-keypair` command
is internally more complicated
than the `mceliece6960119-keypair` command
but provides faster key generation.
The commands are interoperable.

### ENCAPSULATION

Bob runs the `mceliece6960119-enc` command.
This command
reads Alice's public key from file descriptor 4.
It randomly generates
a ciphertext and the corresponding session key.
It writes the ciphertext to stdout,
and then writes the session key to file descriptor 7.

### DECAPSULATION

Alice runs the `mceliece6960119-dec` command.
This command
reads Alice's secret key from file descriptor 8,
and then reads a ciphertext from stdin.
It computes the corresponding session key,
which it writes to file descriptor 7.

### SEE ALSO

**mceliece**(3)
