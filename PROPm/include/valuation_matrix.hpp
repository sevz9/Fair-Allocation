#pragma once

#include <vector>

using namespace std;

vector<vector<int>> make_sub_val_matrix(vector<vector<int>> valuation_matrix, vector<int> bundle, vector<int> agents);

vector<vector<int>> get_bundles(vector<vector<int>> valuation_matrix);
