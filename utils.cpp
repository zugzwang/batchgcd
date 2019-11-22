#include "utils.hpp"

using namespace std;

vector<unsigned int> filesPerFloor;

int product_tree(vector<mpz_class> X){
    cout << "Computing product tree of " << X.size() << " moduli." << endl;
    vector<mpz_class> current_level;
    vector<mpz_class> new_level;
    current_level = X;
    int l = 0;
    mpz_class prod;
    while (current_level.size() > 1) {
        filesPerFloor.push_back(current_level.size());
        write_level_to_file(l, current_level);
        new_level.clear();
        cout << "   Multiplying " << current_level.size() << " ints of ";
        cout << mpz_sizeinbase(current_level[0].get_mpz_t(), 2) << " bits ";
        cout << endl;
        for (unsigned int i = 0; i < current_level.size()-1; i+=2) {
            prod = current_level[i] * current_level[i+1];
            new_level.push_back(prod);
        }
        if (current_level.size()%2 != 0) {
            new_level.push_back(current_level.back());
        }
        current_level = new_level;
        l ++;
    }
    filesPerFloor.push_back(current_level.size());
    write_level_to_file(l, current_level);
    cout << "Done." << endl;
    return l+1;
}

vector<mpz_class> remainders_squares(int levels) {
    vector<mpz_class> R, newR, Y;
    mpz_class square, rem;
    R = read_level_from_file(levels-1);
    for(int l = levels-2; l >= 0; l--) {
        newR.clear();
        Y.clear();
        Y = read_level_from_file(l);
        cout << "  Computing remainders ..." << endl;
        for(unsigned int i = 0; i < Y.size(); i++) {
            square = Y[i] * Y[i];
            rem = R[i/2] % square;
            newR.push_back(rem);
        }
        R = newR;
    }
    return R;
}

vector<mpz_class> read_moduli_from_file(string filename) {
    cout << "Reading moduli from " << filename << endl;
    ifstream file(filename);
    vector<mpz_class> moduli;
	string line = "";
	// Iterate through each line and split the content using delimeter
	while (getline(file, line))
	{
        Modulus mod(line);
        moduli.push_back(mod.n);
	}
	// Close the File
	file.close();

    cout << "Done. Read " << moduli.size() << " moduli" << endl;
	return moduli;
}

void write_level_to_file(int l, vector<mpz_class> X) {
    string dir = "data/product_tree/level" + to_string(l) + "/";
    boost::filesystem::create_directory(dir.c_str());
    cout << "   Writing product tree level to " << dir << " (length ";
    cout << X.size() << ")" << endl;
    string filename;
    for(unsigned int i = 0; i < X.size(); i++) {
        filename = dir + to_string(i) + ".gmp";
        FILE* file = fopen(filename.c_str(), "w+");
        mpz_out_raw(file, X[i].get_mpz_t());
        fclose(file);
    }
}

vector<mpz_class> read_level_from_file(int l) {
    string dir = "data/product_tree/level" + to_string(l) + "/";
    cout << "   Reading product tree level from " << dir << endl;
    ifstream file(dir);
    vector<mpz_class> moduli;
    string filename;
    mpz_t aux;
    mpz_init(aux);
    for(unsigned int i = 0; i < filesPerFloor[l]; i++) {
        filename = dir + to_string(i) + ".gmp";
        FILE* file = fopen(filename.c_str(), "r");
        mpz_inp_raw(aux, file);
        mpz_class mod = mpz_class(aux);
        fclose(file);
        moduli.push_back(mod);
    }
    cout << "   ok, read " << moduli.size() << " ints of ";
    cout << mpz_sizeinbase(moduli[0].get_mpz_t(), 2) << " bits" << endl;

	return moduli;
}

void write_level_to_file_str(int l, vector<mpz_class> X) {
    string filename = "data/product_tree/level" + to_string(l) + ".csv";
    cout << "   Writing product tree level to " << filename << " (length ";
    cout << X.size() << ")" << endl;
    ofstream file;
    file.open(filename);
    for(auto const& mod: X) {
        file << mod.get_str() << endl;
    }
    file.close();
}


vector<mpz_class> read_level_from_file_str(int l) {
    string filename = "data/product_tree/level" + to_string(l) + ".csv";
    cout << "   Reading product tree level from " << filename << endl;
    ifstream file(filename);
    vector<mpz_class> moduli;
	string line = "";
	// Iterate through each line and split the content using delimeter
	while (getline(file, line))
	{
        mpz_class mod(line);
        moduli.push_back(mod);
	}
	// Close the File
	file.close();
    cout << "   Read " << moduli.size() << " ints of ";
    cout << mpz_sizeinbase(moduli[0].get_mpz_t(), 2) << " bits" << endl;

	return moduli;
}

// Helper func
void printvec(vector<mpz_class> X) {
    for(auto const& val: X){
        cout << val.get_str() << " ";
    }
    cout << endl;
}
