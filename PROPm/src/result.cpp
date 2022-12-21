#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <numeric>
#include <random>
#include <cassert>
#include <fstream>

#include "result.hpp"
#include "PROPM_alg.hpp"
#include "Propm_Checker.hpp"
#include "PO_checker.hpp"

using namespace std;

void print_result(string filename_out, string sample_name){
    ifstream input(sample_name);
    ofstream output(filename_out);
    int po = 0;
    int count = 0, n, m;

    input >> count;
    input >> n >> m;
    vector<vector<int>> valuation_matrix(n, vector<int>(m));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            input >> valuation_matrix[i][j];
        }
    }
    vector<vector<int>> valuation_matrix_propm = PROPm(valuation_matrix);
    if(is_PO(valuation_matrix, valuation_matrix_propm))
        po++;
    //output.seekg(output, output.end);
    output << sample_name << endl << "total_matrix: " << count << endl;
    output << "po: " << po << endl;
    output << "percent: " << po*(1.0) / count << endl;

}
