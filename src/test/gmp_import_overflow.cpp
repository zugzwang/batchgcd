#include <iostream>
#include <gmp.h>
#include <gmpxx.h>
#include "../utils.hpp"

using namespace std;

void check_native_gmp_import_overflow(){
    cout << "Checking mpz_inp_raw" << endl;
    mpz_class X = mpz_class("26260501492055003879090391148004259823668635955434940022240258423696972549087016976752741339581688667116285774789874965785477453615444090337309187413036370189140994737011441584670955662781635132759980523310138734737307258076009827470257979133586680521639320415528310921798062062373359095503578858718997775793827432391641667052497696724948747137134661578015238047990967731934660718227627803874984645637904353370058830616916834689206916806975827756356442055029361147529113398133136299120164869948173129966790462188820613998260570826459291086946318100842679711014724407434914501418235750786671160222080472818057103702049");
    for(int i = 0; i < 25; i++) {
        cout << i << endl;
        cout << "Multiplying" << endl;
        X *= X;
        // Export to file
        cout << "Exporting to file" << endl;
        FILE* file = fopen("eraseme.txt", "w+");
        mpz_out_raw(file, X.get_mpz_t());
        fclose(file);
        // Import back
        cout << "Importing from file" << endl;
        file = fopen("eraseme.txt", "r");
        mpz_t y;
        mpz_init(y);
        mpz_inp_raw(y, file);
        mpz_class Y = mpz_class(y);
        if(X == Y){
            cout << "Equal" << endl;
        } else {
            cout << "NOT EQUAL" << endl;
        }
    }
}

void check_gmp_import_overflow(){
    cout << "Checking mpz_inp_raw" << endl;
    mpz_class X = mpz_class("26260501492055003879090391148004259823668635955434940022240258423696972549087016976752741339581688667116285774789874965785477453615444090337309187413036370189140994737011441584670955662781635132759980523310138734737307258076009827470257979133586680521639320415528310921798062062373359095503578858718997775793827432391641667052497696724948747137134661578015238047990967731934660718227627803874984645637904353370058830616916834689206916806975827756356442055029361147529113398133136299120164869948173129966790462188820613998260570826459291086946318100842679711014724407434914501418235750786671160222080472818057103702049");
    for(int i = 0; i < 25; i++) {
        cout << i << endl;
        // Export to file
        cout << "Exporting to file" << endl;
        FILE* file = fopen("eraseme.txt", "w+");
        mpz_out_raw(file, X.get_mpz_t());
        fclose(file);
        // Import back
        cout << "Importing from file" << endl;
        file = fopen("eraseme.txt", "r");
        mpz_class Y;
        my_mpz_inp_raw(Y, file);
        if(X == Y){
            cout << "Equal" << endl;
        } else {
            cout << "NOT EQUAL" << endl;
            cout << X << endl;
            cout << Y << endl;
            break;
        }
        cout << "Squaring" << endl;
        X *= X;
    }
}

int main(int argc, char** argv){
    check_gmp_import_overflow();
    return 0;
}

