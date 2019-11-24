#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <vector>
#include <gmp.h>
#include <gmpxx.h>
#include <boost/algorithm/string.hpp>
#include <boost/filesystem.hpp>

using namespace std;

int product_tree(std::vector<mpz_class>*);
void read_moduli_from_csv(std::string, vector<mpz_class> *, vector<int> *);
void write_level_to_file(int l, std::vector<mpz_class> *);
void read_level_from_file(int, std::vector<mpz_class> *);
void read_variable_from_file(int level, int index, mpz_class &x);
void remainders_squares(int, std::vector<mpz_class> *);

#endif /* UTILS_HPP */
