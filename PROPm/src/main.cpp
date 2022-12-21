#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <numeric>
#include <random>
#include <cassert>

#include "PROPM_alg.hpp"
#include "Propm_Checker.hpp"
#include "PO_checker.hpp"
#include "Generate.hpp"
#include "find_bad_matrix.hpp"

using namespace std;

int main() {
    /*
    generate_sample("samples/sample_2_m.txt", 1000, 2, 10, "res.txt", 1);
    generate_sample("samples/sample_3_m.txt", 1000, 3, 7, "res.txt", 1);
    generate_sample("samples/sample_4_m.txt", 1000, 4, 5, "res.txt", 1);
    generate_sample("samples/sample_5_m.txt", 1000, 5, 5, "res.txt", 1);

    generate_sample("samples/sample_2_m_2value.txt", 1000, 2, 10, "res.txt", 2);
    generate_sample("samples/sample_3_m_2value.txt", 1000, 3, 7, "res.txt", 2);
    generate_sample("samples/sample_4_m_2value.txt", 1000, 4, 5, "res.txt", 2);
    generate_sample("samples/sample_5_m_2value.txt", 1000, 5, 5, "res.txt", 2);
    */
    int size = 3;
    vector<vector<int>> bad_matrix =  find_bad_matrix(size);
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            cout << bad_matrix[i][j] << " ";
        }
        cout << endl;
    }
}
