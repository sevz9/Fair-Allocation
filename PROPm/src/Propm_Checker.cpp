#include <iostream>
#include <vector>
#include <set>

#include "Propm_Checker.hpp"
#include "aggregate.hpp"


using namespace std;

bool is_propm(vector<vector<int>> valuation_matrix, vector<vector<int>> allocation){
    int n = valuation_matrix.size();
    vector<int> max_min(n);
    for (int i = 0; i < n; ++i) {
        int _max_min = 0;
        for (int j = 0; j < n; ++j) {
            int _min = 100000;
            if(i == j || allocation[j].size() == 0)
                continue;
            for(int item : allocation[j])
                _min = min(_min, valuation_matrix[i][item]);
            _max_min = max(_max_min, _min);
        }
        max_min[i] = _max_min;
    }
    for (int i = 0; i < n; ++i) {
        if((agent_val_for_bundle(i, allocation[i], valuation_matrix) + max_min[i]) * n < sum_kth_row(i, valuation_matrix)) {
            cout << "failed for " << i << " " << " max_min = " << max_min[i] << " sum for agent = " << agent_val_for_bundle(i, allocation[i], valuation_matrix) <<
                 " " << " sum in str = " << sum_kth_row(i, valuation_matrix) << endl;
            return false;
        }
    }
    return true;
}

bool is_propm(vector<vector<int>> valuation_matrix, vector<set<int>> allocation){
    int n = valuation_matrix.size();
    vector<int> max_min(n);
    for (int i = 0; i < n; ++i) {
        int _max_min = 0;
        for (int j = 0; j < n; ++j) {
            int _min = 100000;
            if(i == j || allocation[j].size() == 0)
                continue;
            for(int item : allocation[j])
                _min = min(_min, valuation_matrix[i][item]);
            _max_min = max(_max_min, _min);
        }
        max_min[i] = _max_min;
    }
    for (int i = 0; i < n; ++i) {
        if((agent_val_for_bundle(i, allocation[i], valuation_matrix) + max_min[i]) * n < sum_kth_row(i, valuation_matrix)) {
            //cout << "failed for " << i << " " << " max_min = " << max_min[i] << " sum for agent = " << agent_val_for_bundle(i, allocation[i], valuation_matrix) <<
            //    " " << " sum in str = " << sum_kth_row(i, valuation_matrix) << endl;
            return false;
        }
    }
    return true;
}