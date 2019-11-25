# 

# cpp-batchgcd - Work in progress

## Description 

(C++)+GMP implementation of the [Batch GCD algorithm](http://facthacks.cr.yp.to/batchgcd.html), by [Daniel Bernstein](https://cr.yp.to/djb.html). This algorithm, based on [How To Find Smooth Parts Of Integers](https://cr.yp.to/factorization/smoothparts-20040510.pdf), allows to compute pairwise GCDs of a list of integers. See e.g. [this well-known experiment](https://factorable.net).

## Usage

You need `g++, gmp, boost` installed. 

Clone and `cd` to the repo. Run 
```make install``` 
(This will only create the `./data/product_tree` folder.)
Put a file named `moduli.csv` inside the `data` folder, containing your integers in the following format
```
<ID>,<bit length>,<modulus in base 10>\n
```
Compile with `make`, and **after reading the disclaimer below**, run with `./batchgcd.o`.

## Disclaimer
Feel free to use, alter, or reproduce this implementation **AT YOUR OWN RISK**.

This implementation uses the C++ wrapper around GMP arbitrary precision
library, since it needs to handle potentially huge numbers. It favors
writing intermediate variables to disk, so beware that, assuming that all
`n` input integers are of bit length `l`, it efficiently writes `~2n`
separate files, using total disk memory of 
```M = l * n * log(n)```
bits. That's 10.7 GB of information in around 4 million separate files if
you're targeting 2 million 2048-bit integers. Please **do the numbers** and use/modify
**AT YOUR OWN RISK**.

Also, as claimed in [Mining Your Ps and Qs: Detection of Widespread Weak Keys in Network Devices](https://factorable.net/weakkeys12.extended.pdf), GMP has a memory limitation on its raw I/O of integers, which is the most efficient way of writing to disk. This limits the amount keys that the algorithm can handle. If you need more, consider patching the GMP library or contacting me.

If you are targeting RSA public keys, which is the main use-case of this algorithm
and the reason that integers within the code are referred to as 'moduli', please
consider **not storing/reading the factors** (the library won't write them to
disk directly, but they will of course be on your RAM) and more importantly,
**informing compromised key owners** so that they have a chance to revoke their
keys / fix their implementations.

Please **don't** use this code if you're targeting a set of keys with
bad intentions.

Suggestions/comments/questions are more than welcome.

## Benchmarks
(TODO)
