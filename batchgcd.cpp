#include "utils.hpp"

#define COUT std::cout.width(K);std::cout<<

using namespace std;
using namespace std::chrono;

int main(int argc, char** argv){
    vector<mpz_class> moduli = read_moduli_from_file("data/moduli.csv");
    // 1. Compute the product tree of all Yᵢ
    cout << "-----------------------------------------------" << endl;
    cout << "Part (A) - Computing product tree of all moduli" << endl;
    cout << "-----------------------------------------------" << endl;
    int levels = product_tree(moduli);
    cout << "End Part (A)" << endl;

    // 2. Compute the remainders of Z mod Xᵢ²
    cout << "-----------------------------------------------" << endl;
    cout << "Part (B) - Computing the remainders of Z mod Xᵢ²" << endl;
    cout << "-----------------------------------------------" << endl;
    vector<mpz_class> R = remainders_squares(levels);
    cout << "End Part (B)" << endl;

    // 3. Divide the ith remainder by Xᵢ, and compute the gcd of the result with
	// Xᵢ.
    cout << "-----------------------"<< endl;
    cout << " - Computing final GCDs" << endl;
    cout << "-----------------------"<< endl;
    mpz_class _div, _gcd;
    vector<mpz_class> gcds;
    for(unsigned int i = 0; i < moduli.size(); i++) {
        _div = R[i] / moduli[i];
        _gcd = gcd(_div, moduli[i]);
        gcds.push_back(_gcd);
    }
    cout << "Done. Compromised keys (IDs):" << endl;
    for(unsigned int i = 0; i < gcds.size(); i++) {
        if(gcds[i] != 1) {
            cout << i << endl;
        }
    }
    return 0;
}
