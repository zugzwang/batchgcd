#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <thread>
#include <vector>
#include <gmp.h>
#include <gmpxx.h>
#include <boost/algorithm/string.hpp>
#include <boost/filesystem.hpp>

extern int N_THREADS;

using namespace std;

int product_tree(std::vector<mpz_class>*);
int product_tree_multithread(std::vector<mpz_class>*);
int product_tree_seq(std::vector<mpz_class>*);
void read_moduli_from_csv(std::string, vector<mpz_class> *, vector<int> *);
void write_level_to_file(int l, std::vector<mpz_class> *);
void read_level_from_file(int, std::vector<mpz_class> *);
void read_variable_from_file(int level, int index, mpz_class &x);
void remainders_squares(int, std::vector<mpz_class> *);
void remainders_squares_simple(int, std::vector<mpz_class> *);
void remainders_squares_fast(int, std::vector<mpz_class> *);
void remainders_squares_fast_multithread(int levels, vector<mpz_class> *R);
void remainders_squares_fast_seq(int levels, vector<mpz_class> *R);
void multithread_level_mult(vector<mpz_class> *, vector<mpz_class> *);
void multithread_partial_remainders(int, vector<mpz_class>*, vector<mpz_class>*);

void my_mpz_inp_raw(mpz_class &, FILE *);

#endif /* UTILS_HPP */
