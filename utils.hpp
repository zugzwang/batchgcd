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
void read_moduli_from_file(std::string, vector<mpz_class> *);
void write_level_to_file(int l, std::vector<mpz_class> *);
void read_variable_from_file(int level, int index, mpz_class &x);
void read_level_from_file(int, std::vector<mpz_class> *);
void remainders_squares(int, std::vector<mpz_class> *);

class Modulus {
    public:
        int ID;
        int bit_length;
        mpz_class n;

        Modulus() { };
        Modulus(mpz_class x, int bl, int id) {
            ID = id;
            bit_length = bl;
            n = x;
        };
        // Read from csv line
        Modulus(string line) {
            vector<string> vec;
            boost::algorithm::split(vec, line, boost::is_any_of(","));
            ID = stoi(vec[0]);
            bit_length = stoi(vec[1]);
            n = mpz_class(vec[2]);
        };
        ~Modulus() {
        };
};

#endif /* UTILS_HPP */
