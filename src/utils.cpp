#include "utils.hpp"

using namespace std;

// intsPerFloor keeps track of the amount of integers in each floor of the
// tree.
vector<unsigned int> intsPerFloor;

/* read_moduli_from_csv allocates and initializes the moduli referenced by
 * input_moduli, from the given file.
 */
void read_moduli_from_csv( \
        string filename, vector<mpz_class> *moduli, vector<int>*IDs) {
    cout << "Reading moduli from " << filename << endl;
    FILE* file = fopen(filename.c_str(), "rb");
    assert(file);
    // Iterate through each line and split the content using delimeter
    mpz_t n;
    mpz_init(n);
    int err = 0;
    bool zero = false;
    while(true) {
        int id;
        int bitlen;
        err = fscanf(file, "%d,%d,", &id, &bitlen);
        err = gmp_fscanf(file, "%Zd", n);
        if(mpz_cmp_ui(n, 0) == 0) {
            zero = true;
            cout << "Modulus with id " << id << " equals 0." << endl;
        }
        if(err == EOF) {
            break;
        }
        if (err != 1) {
            cout << "Cannot process moduli file" << endl;
            throw std::exception();
        }
        IDs->push_back(id);
        moduli->push_back(mpz_class(n));
    }
    if(zero) {
        cout << "Cannot process moduli file" << endl;
        exit(1);
    }
    mpz_clear(n);
    fclose(file);
    cout << "Done. Read " << moduli->size() << " moduli" << endl;
}

/* product_tree computes the product tree of the input moduli; the leaves
 * contain the input moduli and the root contains their product.
 * Each level is computed and written to disk in a separate folder.
 * This function returns the amount of levels contained in the tree.
 *
 * Warning: Input IS DESTROYED, in order to use the occupied RAM if necessary.
 */
int product_tree(vector<mpz_class> *X) {
    cout << "Computing product tree of " << X->size() << " moduli." << endl;
    vector<mpz_class> current_level, new_level;
    mpz_class *prod = new(mpz_class);
    int l = 0;
    current_level = *X;
    while (current_level.size() > 1) {
        intsPerFloor.push_back(current_level.size());
        write_level_to_file(l, &current_level);

        // Free new level
        vector<mpz_class>().swap(new_level);

        // Multiply
        cout << "   Multiplying " << current_level.size() << " ints of ";
        cout << mpz_sizeinbase(current_level[0].get_mpz_t(), 2) << " bits ";
        cout << endl;
        multithread_level_mult(&current_level, &new_level);

        // Append orphan node
        if (current_level.size()%2 != 0) {
            new_level.push_back(current_level.back());
        }

        current_level = new_level;
        if (l == 0) {
            // Free leaves after using, in order to get that RAM if necessary.
            vector<mpz_class>().swap(*X);
        }
        l ++;
    }
    delete prod;

    // Last floor
    intsPerFloor.push_back(current_level.size());
    write_level_to_file(l, &current_level);

    vector<mpz_class>().swap(current_level);
    vector<mpz_class>().swap(new_level);
    return l+1;
}

/* multithread_level_mult takes the given level, and computes the next one,
 * i.e.,
 *             _next[i] = _level[2*i] * _level[2*i+1].
 */
void multithread_level_mult(vector<mpz_class> *_level, vector<mpz_class> *_next) {
    _next->resize(_level->size()/2);
    vector<boost::thread> threads;
    // Thread 'j' will handle all products in position eq. j mod N_THREADS.
    for(int j = 0; j < N_THREADS; j++) {
        threads.push_back(
                boost::thread([j, _level, _next]() mutable {
                    for(unsigned int i = j; i < _next->size(); i += N_THREADS) {
                        (*_next)[i] = (*_level)[2*i] * (*_level)[2*i+1];
                    }
                    string s = "     Thread " + to_string(j) + " finished.\n";
                    cout << s;
                    }));
    }
    for(auto& th : threads)
        th.join();
    vector<boost::thread>().swap(threads);
}

/* remainders_squares computes the list remᵢ <- Z mod Xᵢ² where X are the
 * moduli and Z is their product. This list is written to the input address.
 */
void remainders_squares(int levels, vector<mpz_class> *R) {
    remainders_squares_fast(levels, R);
}

// Straightforward but slow, since the internal variable Z is potentially huge.
void remainders_squares_simple(int levels, vector<mpz_class> *R) {
    // Read product
    read_level_from_file(levels-1, R);
    mpz_class Z = (*R)[0];
    read_level_from_file(0, R);
    cout << "   Computing partial remainders ";
    for(unsigned int i = 0; i < R->size(); i++) {
        cout << i << endl;
        (*R)[i] *= (*R)[i];
        (*R)[i] = Z % (*R)[i];
    }
}

/* remainders_squares_fast is Bernstein's suggestion. It uses more RAM.
 * The temporary vector newR uses the same amount of memory as R, and the
 * internal 'square' needs the double of this amount in the first iteration
 * (its first value is Z^2).
 * Consequently, the first iterations are the most tense part of the algorithm
 * in terms of memory.
 */
void remainders_squares_fast(int levels, vector<mpz_class> *R) {
    vector<mpz_class> newR;
    read_level_from_file(levels-1, R);
    // Sanity check
    if(int(R->size()) != 1) {
        cout << "Fatal error: Incomplete product tree" << endl;
        throw std::exception();
    }
    for(int l = levels-2; l >= 0; l--) {
        vector<mpz_class>().swap(newR);
        cout << "   Computing partial remainders ";
        cout << levels-2-l << " of " << levels-2 << endl;
        multithread_partial_remainders(l, R, &newR);
        *R = newR;
    }
    // Free used memory
    vector<mpz_class>().swap(newR);
}

/* multithread_partial_remaiders sets _new[k] = R[k/2] % (a square) for all k */
void multithread_partial_remainders(int l, vector<mpz_class> *_R, vector<mpz_class> *_new) {
    _new->resize(intsPerFloor[l]);
    string dir = "data/product_tree/level";
    string filename = dir + to_string(l) + ".gmp";
    FILE* file = fopen(filename.c_str(), "r");
    int pos = 0;
    for(unsigned int i = 0; i < _new->size(); i += N_THREADS) {
        vector<boost::thread> threads;
        for(int j = 0; j < N_THREADS; j++) {
            pos = i + j;
            if(i+j >= _new->size()) {
                break;
            }
            // Define operands for this thread
            mpz_t _square;
            mpz_init(_square);
            mpz_inp_raw(_square, file);
            mpz_class square(_square);
            mpz_class *operand = &(_R->at(pos/2));
            mpz_class *result = &(_new->at(pos));
            threads.push_back(boost::thread([square, operand, result]() mutable {
                        square *= square;
                        *result = *operand % square;
                        }));
            mpz_clear(_square);
        }
        for(unsigned int j = 0; j < threads.size(); j++) {
            threads.at(j).join();
        }
    }
    fclose(file);
}

void remainders_squares_fast_seq(int levels, vector<mpz_class> *R) {
    vector<mpz_class> newR;
    read_level_from_file(levels-1, R);
    // Sanity check
    if(int(R->size()) != 1) {
        cout << "Fatal error: Incomplete product tree" << endl;
        throw std::exception();
    }
    string dir = "data/product_tree/level";
    mpz_t _square;
    mpz_init(_square);
    mpz_class square;
    for(int l = levels-2; l >= 0; l--) {
        vector<mpz_class>().swap(newR);
        cout << "   Computing partial remainders ";
        cout << levels-2-l << " of " << levels-2 << endl;
        unsigned int lengthY = intsPerFloor[l];
        string filename = dir + to_string(l) + ".gmp";
        FILE* file = fopen(filename.c_str(), "r");
        for(unsigned int i = 0; i < lengthY; i++) {
            mpz_inp_raw(_square, file);
            square = mpz_class(_square);
            square *= square;
            square = (*R)[i/2] % square;
            newR.push_back(square);
        }
        *R = newR;
    }
    // Free used memory
    mpz_clear(_square);
    vector<mpz_class>().swap(newR);
}

/*
 * write_level_to_file takes an array of integers stored in the input address
 * and writes them to data/product_level/level<given index>.gmp.
 */
void write_level_to_file(int l, vector<mpz_class> *X) {
    string dir = "data/product_tree/level" + to_string(l) + ".gmp";
    cout << "   Writing product tree level to " << dir << endl;
    FILE* file = fopen(dir.c_str(), "wb");
    assert(file);
    for(unsigned int i = 0; i < X->size(); i++) {
        mpz_out_raw(file, (*X)[i].get_mpz_t());
    }
    fclose(file);
}

/* read_level_from_file imports level 'l' from binary file, and initializes the
 * given vector with these values.
 */
void read_level_from_file(int l, vector<mpz_class> *moduli) {
    string dir = "data/product_tree/level" + to_string(l) + ".gmp";
    cout << "   Reading product tree level from " << dir << endl;
    // ifstream file(dir);
    vector<mpz_class>().swap(*moduli);
    mpz_t mod;
    mpz_init(mod);

    FILE* file = fopen(dir.c_str(), "r");
    for(unsigned int i = 0; i < intsPerFloor[l]; i++) {
        mpz_inp_raw(mod, file);
        moduli->push_back(mpz_class(mod));
    }
    fclose(file);
    mpz_clear(mod);
    cout << "   ok, read " << moduli->size() << " ints of ";
    cout << mpz_sizeinbase((*moduli)[0].get_mpz_t(), 2) << " bits" << endl;
}

void my_mpz_inp_raw(mpz_class &x, FILE* file) {
    std::ifstream source("eraseme.txt", std::ios_base::binary);
    int byte, next_byte;
    source.get();
    source.get();
    source.get();
    source.get();
    next_byte = source.get();
    while (source) {
        byte = next_byte;
        next_byte = source.get();
        x <<= 8;
        x += byte;
        if (next_byte == -1) {
            continue;
        }
    }
}
