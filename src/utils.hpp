/* Copyright (C) 2020 Francisco Vial - All Rights Reserved
 * You may use, distribute and modify this code under the
 * terms of the WTFPL.
 */

#ifndef SRC_UTILS_HPP_
#define SRC_UTILS_HPP_

#include <iostream>
#include <string>
#include <vector>
#include <gmp.h>
#include <gmpxx.h>
#include <boost/thread.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/filesystem.hpp>

extern int N_THREADS;

using std::vector;
using std::string;

void read_moduli_from_csv(string, vector<mpz_class>*, vector<string>*, int);
int product_tree(vector<mpz_class>*);
int product_tree_multithread(vector<mpz_class>*);
int product_tree_seq(vector<mpz_class>*);
void write_level_to_file(int l, vector<mpz_class> *);
void read_level_from_file(int, vector<mpz_class> *);
void read_variable_from_file(int level, int index, mpz_class *x);
void remainders_squares(int, vector<mpz_class> *);
void remainders_squares_simple(int, vector<mpz_class> *);
void remainders_squares_fast(int, vector<mpz_class> *);
void remainders_squares_fast_multithread(int levels, vector<mpz_class> *R);
void remainders_squares_fast_seq(int levels, vector<mpz_class> *R);
void mt_level_mult(vector<mpz_class> *, vector<mpz_class> *);
void partial_remainders(int, vector<mpz_class>*, vector<mpz_class>*);

void my_mpz_inp_raw(mpz_class &, FILE *);

#endif /* SRC_UTILS_HPP_ */
