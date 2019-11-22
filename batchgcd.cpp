#include "utils.hpp"

#define COUT std::cout.width(K);std::cout<<

using namespace std;
using namespace std::chrono;

extern vector<mpz_class> input_moduli;

int main(int argc, char** argv){
    struct timespec start, finish;
    double elapsed;

    clock_gettime(CLOCK_MONOTONIC, &start);

    input_moduli = read_moduli_from_file("data/moduli.csv");
    // 1. Compute the product tree of all Yᵢ
    cout << "-----------------------------------------------" << endl;
    cout << "Part (A) - Computing product tree of all moduli" << endl;
    cout << "-----------------------------------------------" << endl;
    int levels = product_tree(input_moduli);

    cout << "End Part (A)" << endl;

    clock_gettime(CLOCK_MONOTONIC, &finish);

    elapsed = (finish.tv_sec - start.tv_sec);
    elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;
    cout << "Time elapsed (s): " << elapsed << endl;

    clock_gettime(CLOCK_MONOTONIC, &start);
    // 2. Compute the remainders of Z mod Xᵢ²
    cout << "------------------------------------------------" << endl;
    cout << "Part (B) - Computing the remainders of Z mod Xᵢ²" << endl;
    cout << "------------------------------------------------" << endl;
    vector<mpz_class> R = remainders_squares(levels);
    cout << "End Part (B)" << endl;
    clock_gettime(CLOCK_MONOTONIC, &finish);

    elapsed = (finish.tv_sec - start.tv_sec);
    elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;
    cout << "Time elapsed (s): " << elapsed << endl;

    clock_gettime(CLOCK_MONOTONIC, &start);
    // 3. Divide the ith remainder by Xᵢ, and compute the gcd of the result with
	// Xᵢ.
    cout << "-----------------------"<< endl;
    cout << " - Computing final GCDs" << endl;
    cout << "-----------------------"<< endl;
    // Recover moduli
    cout << "Sanity check: " << input_moduli.size() << " input moduli." << endl;
    mpz_class _div, _gcd;
    vector<mpz_class> gcds;
    for(unsigned int i = 0; i < input_moduli.size(); i++) {
        _div = R[i] / input_moduli[i];
        _gcd = gcd(_div, input_moduli[i]);
        gcds.push_back(_gcd);
    }
    cout << "Done. Compromised keys (IDs):" << endl;
    int c = 0;
    for(int i = 0; i < int(gcds.size()); i++) {
        if(gcds[i] != 1) {
            c ++ ;
        }
    }
    cout << c << endl;
    clock_gettime(CLOCK_MONOTONIC, &finish);

    elapsed = (finish.tv_sec - start.tv_sec);
    elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;
    cout << "Time elapsed (s): " << elapsed << endl;
    return 0;
}
