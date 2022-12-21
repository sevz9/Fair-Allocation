#pragma once

#include <vector>
#include <set>
#include <iostream>

using namespace std;

class Decomposition{
public:
    vector<set<int>> agents_for_bundles;
    vector<vector<int>> group_of_bundles;
    vector<vector<int>> bundles;
    int dec_size;
    Decomposition(vector<vector<int>> _bundles);

    void show_bundles();

    int number_of_agents();

    void add_agent(int agent, int bundle_number);

    void remove_agent(int agent, int bundle_number);

    void dfs(vector<vector<int>> g, vector<bool>* vis, vector<int>* parents, int start, pair<int, int> *swap, int t, vector<vector<int>> valuation_matrix);

    void update(vector<int> S_t, int bad_agent, vector<vector<int>> valuation_matrix, set<int>* Nr, int t);
};