#include <vector>
#include <set>
#include <iostream>
#include <numeric>
#include <algorithm>

#include "valuation_matrix.hpp"


using namespace std;

vector<vector<int>> make_sub_val_matrix(vector<vector<int>> valuation_matrix, vector<int> bundle, vector<int> agents){

    vector<vector<int>> sub_matrix(agents.size(), vector<int>(bundle.size()));
    for(int i = 0; i < (int)agents.size(); i++){
        for (int j = 0; j < (int)bundle.size(); j++) {
            sub_matrix[i][j] = valuation_matrix[agents[i]][bundle[j]];
        }
    }
    return sub_matrix;
}


vector<vector<int>> get_bundles(vector<vector<int>> valuation_matrix){
    int n = valuation_matrix.size();
    int m = valuation_matrix[0].size();
    vector<int> sort_ind(m);
    iota(sort_ind.begin(), sort_ind.end(), 0);
    sort(sort_ind.begin(), sort_ind.end(), [&](int x, int y){
        return valuation_matrix[0][x] < valuation_matrix[0][y];
    });
    int sum_in_row = 0;
    for(int i = 0; i < m; i++){
        sum_in_row += valuation_matrix[0][i];
    }
    int sum = 0, ind = 0;
    vector<vector<int>> ans(n);
    vector<int> bundle;
    for(int i = 0; i < m; i++){
        //cout << i << " " << sort_ind[i] << " "  << valuation_matrix[0][sort_ind[i]] << " " << sum << " " << sum_in_row << endl;
        if((sum + valuation_matrix[0][sort_ind[i]]) * (n - ind) > sum_in_row){

            ans[ind] = bundle;
            ind++;
            bundle.clear();
            sum_in_row -= sum;
            sum = 0;
            i--;
            continue;
        }
        bundle.push_back(sort_ind[i]);
        sum += valuation_matrix[0][sort_ind[i]];

    }
    ans[ind] = bundle;
    /*
    for (int i = 0; i < (int)ans.size(); ++i) {
        cout << "ok" << endl;
        for (int j = 0; j < (int)ans[i].size(); ++j) {
            cout << ans[i][j] << " ";
        }
        cout << endl;
    }
    */
    return ans;
}
