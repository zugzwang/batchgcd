
# `(C++)+GMP` BatchGCD algorithm

## Description 

(C++)+GMP implementation of the [Batch GCD algorithm](http://facthacks.cr.yp.to/batchgcd.html), by [Daniel Bernstein](https://cr.yp.to/djb.html). This algorithm, described in [How To Find Smooth Parts Of Integers](https://cr.yp.to/factorization/smoothparts-20040510.pdf), allows to compute pairwise GCDs of a list of integers. See e.g. [factorable.net](https://factorable.net), which also provides source code.

## Updated patch for GMP binary I/O

If you have a large database (8M 2048-bit moduli), current `gmp` won't swap some intermediate values correctly. The reason an undocumented raw binary I/O limit of `2**31` bytes. 

The reference implementation [factorable.net](https://factorable.net) patched this for `gmp-5.0.5`, and we provide a similar patch for the current latest (`gmp-6.1.2`), which is a more optimized and C++ friendly version. 

Both `mpz_inp_raw` and `mpz_out_raw` are modified with the patch to admit integers up to `2**63` bytes; consequently, this **breaks compatibility** with regular `gmp` binary files.

_Note that `mpz_inp_raw` and `mpz_out_raw` have changed since `gmp-5.0.5`, which makes the [factorable.net](https://factorable.net) patch incompatible with current versions of `gmp`, hence the update._


Using the current `gmp` and the updated patch, this implementation is slightly faster than the one given in [factorable.net](https://factorable.net). Please, **do not rely on the patched library** for other purposes. The install script, which is an updated version of the [factorable.net](https://factorable.net) script, downloads `gmp-6.1.2`, applies the patch, and builds from source.

This patch has **not** been tested in 32-bit systems. 

## Usage

You need `g++, boost, boost::thread` installed. Also, you need a csv file, containing integers in the following format
```
<ID>,<bit length>,<modulus in base 10>\n
```

Clone and `cd` to the repo. Run
```
make install
```
This will only create necessary folders for `gmp` I/O. Run the download-patch-build-install script
```
./patch_gmp.sh
```

Compile with `make`, and **after reading the disclaimer below**, run with `./batchgcd <your target csv file>`.

Results **contain no factors** (this is made on purpose, see the disclaimer below), and are stored by ID in `compromised.csv, duplicates.csv`.  

## Disclaimer
Feel free to use, alter, or reproduce this implementation **AT YOUR OWN RISK**.

This implementation uses the C++ wrapper around GMP arbitrary precision
library, since it needs to handle potentially huge numbers. It favors
writing intermediate variables to disk, so beware that, assuming that all
`n` input integers are of bit length `l`, it efficiently writes a total disk
memory of
```M = l * n * log(n)```
bits. That's 10.7 GB of information if you're targeting 2 million 2048-bit
integers. Please **do the numbers** and use/modify
**AT YOUR OWN RISK**.

Suggestions/comments/questions are more than welcome.

## Benchmarks
(TODO)
