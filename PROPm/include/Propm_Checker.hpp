#pragma once

#include <vector>
#include <set>

using namespace std;

bool is_propm(vector<vector<int>> valuation_matrix, vector<vector<int>> allocation);

bool is_propm(vector<vector<int>> valuation_matrix, vector<set<int>> allocation);
