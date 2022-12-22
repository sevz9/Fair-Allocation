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
    int n = 4;
    int m = 4;
    bool correct = false;
    vector<vector<int>> bad_matrix =  find_bad_matrix(n, m, 5, &correct);
    if(correct) {
        cout << "контр пример: " << endl;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                cout << bad_matrix[i][j] << " ";
            }
            cout << endl;
        }
    }
    else{
        cout << "НЕТУ" << endl;
    }


    //vector<vector<int>> val_m = {{1, 0, 3}, {0, 1, 3}};
    //vector<vector<int>> alloc1 = {{2}, {0, 1}};
    //vector<set<int>> alloc2 = {{2, 0}, {1}};

    //cout << is_PO(val_m, alloc1) << endl;
    //cout << allocation_comp(val_m, alloc2, alloc1) << endl;
}
