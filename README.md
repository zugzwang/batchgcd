# 

# cpp-batchgcd - Work in progress

## Description 

(C++)+GMP implementation of the [Batch GCD algorithm](http://facthacks.cr.yp.to/batchgcd.html), by [Daniel Bernstein](https://cr.yp.to/djb.html). This algorithm, described in [How To Find Smooth Parts Of Integers](https://cr.yp.to/factorization/smoothparts-20040510.pdf), allows to compute pairwise GCDs of a list of integers. See e.g. [this well-known experiment](https://factorable.net).

## Usage

You need `g++, cmake, gmp, boost` installed. 

Clone and `cd` to the repo. Inside the `build` folder, create a `/data/product_tree/` directory.
Put a file named `moduli.csv` inside the `data` folder, containing your integers in the following format
```
<ID>,<bit length>,<modulus in base 10>\n
```
Now `cd` to `build`, run 
```cmake -G "Unix Makefiles" ..```
(replace `Unix Makefiles` by another generator name if needed, for this run `cmake --help`).

Compile with `make`, and **after reading the disclaimer below**, run with `./batchgcd`.

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
