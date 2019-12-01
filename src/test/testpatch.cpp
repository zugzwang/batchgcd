#include "../utils.hpp"

using namespace std;
int N_THREADS = 1;

void check_gmp_import_overflow(){
    cout << "Checking mpz_inp_raw" << endl;
    mpz_t y;
    mpz_init(y);
    struct timespec start, finish;
    double elapsed;
    mpz_class Y = mpz_class(0);
    mpz_class X = mpz_class("26260501492055003879090391148004259823668635955434940022240258423696972549087016976752741339581688667116285774789874965785477453615444090337309187413036370189140994737011441584670955662781635132759980523310138734737307258076009827470257979133586680521639320415528310921798062062373359095503578858718997775793827432391641667052497696724948747137134661578015238047990967731934660718227627803874984645637904353370058830616916834689206916806975827756356442055029361147529113398133136299120164869948173129966790462188820613998260570826459291086946318100842679711014724407434914501418235750786671160222080472818057103702049");
    for(int i = 0; i < 25; i++) {
        cout << "================================" << endl;
        cout << "Level " << i << endl;
        cout << "|X|: " << mpz_sizeinbase(X.get_mpz_t(), 2) << " bits." << endl;
        cout << "================================" << endl;
        // Export to file
        cout << "Exporting X to file" << endl;
        clock_gettime(CLOCK_MONOTONIC, &start);
        FILE* file = fopen("data/testpatch.mpz", "w+");
        mpz_out_raw(file, X.get_mpz_t());
        fclose(file);
        clock_gettime(CLOCK_MONOTONIC, &finish);
        elapsed = finish.tv_sec - start.tv_sec;
        elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;
        cout << "Writing took (s): " << elapsed << endl;
        // // Import back
        cout << "Importing X from file" << endl;
        clock_gettime(CLOCK_MONOTONIC, &start);
        file = fopen("data/testpatch.mpz", "r");
        mpz_inp_raw(y, file);
        fclose(file);
        clock_gettime(CLOCK_MONOTONIC, &finish);
        elapsed = finish.tv_sec - start.tv_sec;
        elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;
        cout << "Reading took (s): " << elapsed << endl;
        Y = mpz_class(y);
        if(X == Y){
            cout << "(OK, retrieved X)" << endl;
        } else {
            cout << "Could not retrieve X!" << endl;
            exit(1);
            break;
        }
        cout << "Squaring" << endl;
        clock_gettime(CLOCK_MONOTONIC, &start);
        X *= X;
        clock_gettime(CLOCK_MONOTONIC, &finish);
        elapsed = finish.tv_sec - start.tv_sec;
        elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;
        cout << "Squaring took (s): " << elapsed << endl;
    }
}

int main(int argc, char** argv){
    check_gmp_import_overflow();
    return 0;
}

