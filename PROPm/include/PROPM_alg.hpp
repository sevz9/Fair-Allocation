#pragma once

#include <vector>
#include <set>

using namespace std;

int update_c(set<int> Nr, int t, vector<vector<int>> bundles,  vector<vector<int>> valuation_matrix, int* bad_agent);

vector<vector<int>> PROPm(vector<vector<int>> valuation_matrix);

