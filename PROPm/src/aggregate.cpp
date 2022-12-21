#include <vector>
#include <set>

#include "aggregate.hpp"

using namespace std;

int sum_kth_row(int k, vector<vector<int>> valuation_matrix){
    int sum = 0;
    for(int item : valuation_matrix[k])
        sum += item;
    return sum;
}

int agent_val_for_bundle(int agent, vector<int> bundle, vector<vector<int>> valuation_matrix){
    int sum_for_agent = 0;
    for(int item : bundle)
        sum_for_agent += valuation_matrix[agent][item];

    return sum_for_agent;
}

int agent_val_for_bundle(int agent, set<int> bundle, vector<vector<int>> valuation_matrix){
    int sum_for_agent = 0;
    for(int item : bundle)
        sum_for_agent += valuation_matrix[agent][item];

    return sum_for_agent;
}

int agent_val_for_group_of_bundle(int agent, vector<int> bundles_ind, vector<vector<int>> valuation_matrix, vector<vector<int>> bundles){
    int sum = 0;
    for(int ind : bundles_ind){
        for(int item : bundles[ind]){
            sum += valuation_matrix[agent][item];
        }
    }
    return sum;
}
