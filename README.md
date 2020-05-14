# `(C++)+GMP` BatchGCD algorithm

## Description

(C++)+GMP implementation of the [Batch GCD
algorithm](http://facthacks.cr.yp.to/batchgcd.html), by [Daniel
Bernstein](https://cr.yp.to/djb.html). This algorithm, described in [How To
Find Smooth Parts Of
Integers](https://cr.yp.to/factorization/smoothparts-20040510.pdf), allows to
compute pairwise GCDs of a list of integers in quasilinear time and memory. See
e.g. [factorable.net](https://factorable.net), which also provides source code.

## Updated patch for GMP binary I/O

For large datasets (~ 8M 2048-bit moduli), current `gmp` won't swap some
intermediate values correctly. The reason is an undocumented raw binary I/O
limit of `2**31` bytes.

The implementation of [factorable.net](https://factorable.net) patched this for
`gmp-5.0.5`, and we provide a similar patch for the current latest
(`gmp-6.1.2`), which is a more optimized and C++ friendly version.
This implementation is slightly faster than the one given in
[factorable.net](https://factorable.net).
Note that `mpz_inp_raw` and `mpz_out_raw` have changed since `gmp-5.0.5`,
which makes the [factorable.net](https://factorable.net) patch incompatible
with current versions of `gmp`. This patch has not been tested in 32-bit
systems. Both `mpz_inp_raw` and `mpz_out_raw` are modified with the patch to admit
integers up to `2**63` bytes; consequently, this breaks compatibility with
regular `gmp` binary files.

## Requirements

### Dependencies

You need `g++, curl, m4, gmp, boost::thread`:
```
apt-get install curl m4 libgmp3-dev libboost-thread-dev
```
### Input file

You need a csv file, containing integers in the following format
```
<ID>,<modulus in base 16>\n
```
You can also use
```
<ID>,<modulus in base 10>\n
```
and set the `-base10` option when running.

## Usage

These instructions have been tested in `Ubuntu 18.04, 19.10` and `Debian
GNU/Linux 9.9 (stretch)`.

### Install

Clone and `cd` to the repo. Run
```
make install
```
This will download `gmp-6.1.2`, check the `sha1` fingerprint, and apply our
updated patch.

### Test

Perform a toy test run with
```
make test
```
This should expose 8 compromised moduli and 2 duplicates out of the 15 samples.

### Run

Compile with `make batchgcd` and run with
```
./batchgcd /path/to/csv/file [-base10]
```
Without the `-base10` option, the default is base 16. Results **contain no
factors**, only IDs are stored in `compromised.csv, duplicates.csv`.

If there are duplicates, you may want to filter them out *before* running the
algorithm, since any number sharing all of its factors may appear as duplicate
without really being duplicate. For instance; if `n = pq, m = pr, h = qr` all
of them will appear as duplicates, and more work is needed to factorise (of
course, naïve pairwise GCDs will do).
