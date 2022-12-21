#pragma once

#include <vector>
#include <set>

using namespace std;

int sum_kth_row(int k, vector<vector<int>> valuation_matrix);

int agent_val_for_bundle(int agent, vector<int> bundle, vector<vector<int>> valuation_matrix);

int agent_val_for_bundle(int agent, set<int> bundle, vector<vector<int>> valuation_matrix);

int agent_val_for_group_of_bundle(int agent, vector<int> bundles_ind, vector<vector<int>> valuation_matrix, vector<vector<int>> bundles);

