#pragma once

#include <vector>
#include <set>

using namespace std;

bool allocation_comp(vector<vector<int>> valuation_matrix, vector<set<int>> allocation1, vector<vector<int>> allocation2);

bool is_PO(vector<vector<int>> valuation_matrix, vector<vector<int>> allocation);

bool is_PO(vector<vector<int>> valuation_matrix, vector<set<int>> allocation);

