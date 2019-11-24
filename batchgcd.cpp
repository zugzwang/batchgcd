/*
 * C++ implementation of the BatchGCD algorithm
 * --------------------------------------------
 *
 *  The batch GCD algorithm, created by Daniel Bernstein [1], allows the
 *  computation of pairwise GCDs of a list of integers in quasilinear time.
 *
 *  This implementation uses the C++ wrapper around GMP arbitrary precision
 *  library.
 *
 *  Feel free to reproduce
 */
#include "utils.hpp"

using namespace std;

int main(int argc, char** argv){

    // Set timer
    struct timespec start, finish;
    double elapsedA, elapsedB, elapsedC;

    cout << "----------------------------------------------" << endl;
    cout << "Part (A) - Compute product tree of all moduli " << endl;
    cout << "----------------------------------------------" << endl;
    clock_gettime(CLOCK_MONOTONIC, &start);
    vector<mpz_class> input_moduli;
    read_moduli_from_file("data/moduli.csv", &input_moduli);
    int levels = product_tree(&input_moduli);
    clock_gettime(CLOCK_MONOTONIC, &finish);
    cout << "End Part (A)" << endl;
    elapsedA = finish.tv_sec - start.tv_sec;
    elapsedA += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;
    cout << "Time elapsed (s): " << elapsedA << endl << endl;

    cout << "----------------------------------------------" << endl;
    cout << "Part (B) - Compute the remainders of Z mod Xᵢ²" << endl;
    cout << "----------------------------------------------" << endl;
    clock_gettime(CLOCK_MONOTONIC, &start);
    vector<mpz_class> R;
    remainders_squares(levels, &R);
    cout << "End Part (B)" << endl;
    clock_gettime(CLOCK_MONOTONIC, &finish);
    elapsedB = (finish.tv_sec - start.tv_sec);
    elapsedB += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;
    cout << "Time elapsed (s): " << elapsedB << endl << endl;

    cout << "-----------------------------------------------" << endl;
    cout << " - Computing final GCDs (remᵢ<- remᵢ/Xᵢ mod Xᵢ)" << endl;
    cout << "-----------------------------------------------" << endl;
    clock_gettime(CLOCK_MONOTONIC, &start);
    cout << "Re-reading moduli (destroyed to use memory in part B)" << endl;
    read_level_from_file(0, &input_moduli);
    for(unsigned int i = 0; i < input_moduli.size(); i++) {
        R[i] = R[i] / input_moduli[i];
        R[i] = gcd(R[i], input_moduli[i]);
    }
    clock_gettime(CLOCK_MONOTONIC, &finish);
    elapsedC = (finish.tv_sec - start.tv_sec);
    elapsedC += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;

    cout << "|-------------|" << endl;
    cout << "|-- Results --|" << endl;
    cout << "|-------------|" << endl << endl;
    vector<mpz_class> compromised;
    for(int i = 0; i < int(input_moduli.size()); i++) {
        if(R[i] != 1) {
            compromised.push_back(R[i]);
        }
    }
    cout << "Amount of compromised keys" << endl;
    cout << compromised.size() << endl;
    cout << "Total time elapsed (s): ";
    int totalSec = int(elapsedA + elapsedB + elapsedC);
    int totalMin = totalSec / 60;
    int totalHour = totalMin / 60;
    totalSec %= 60;
    totalMin %= 60;
    cout << totalHour << "h " << totalMin << "m " << totalSec << "s " << endl;
    return 0;
}
