#include "utils.hpp"

#define COUT std::cout.width(K);std::cout<<

using namespace std;
using namespace std::chrono;

int main(int argc, char** argv){
    vector<mpz_class> moduli = read_moduli_from_file("data/moduli.csv");
    // 1. Compute the product tree of all Yᵢ
    int levels = product_tree(moduli);

    // 2. Compute the remainders of Z mod Xᵢ²
    vector<mpz_class> R = remainders_squares(levels);

    // 3. Divide the ith remainder by Xᵢ, and compute the gcd of the result with
	// Xᵢ.
    mpz_class _div, _gcd;
    vector<mpz_class> gcds;
    for(unsigned int i = 0; i < moduli.size(); i++) {
        _div = R[i] / moduli[i];
        _gcd = gcd(_div, moduli[i]);
        gcds.push_back(_gcd);
    }
    printvec(gcds);
    return 0;
}
