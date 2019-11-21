#include "utils.hpp"

using namespace std;

int product_tree(vector<mpz_class> X){
    vector<mpz_class> current_level;
    vector<mpz_class> new_level;
    current_level = X;
    int l = 0;
    mpz_class prod;
    while (current_level.size() > 1) {
        write_level_to_file(l, current_level);
        new_level.clear();
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
    write_level_to_file(l, current_level);
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

	return moduli;
}

void write_level_to_file(int l, vector<mpz_class> X) {
    string filename = "data/product_tree/level" + to_string(l) + ".csv";
    ofstream file;
    file.open(filename);
    for(auto const& mod: X) {
        file << mod.get_str() << endl;
    }
    file.close();
}

vector<mpz_class> read_level_from_file(int l) {
    string filename = "data/product_tree/level" + to_string(l) + ".csv";
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

	return moduli;
}

// Helper func
void printvec(vector<mpz_class> X) {
    for(auto const& val: X){
        cout << val.get_str() << " ";
    }
    cout << endl;
}
