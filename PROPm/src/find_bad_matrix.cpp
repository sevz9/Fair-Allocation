#include <iostream>
#include <vector>
#include <random>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <set>

#include "Generate.hpp"
#include "PO_checker.hpp"
#include "Propm_Checker.hpp"
#include "find_bad_matrix.hpp"

using namespace std;

vector<vector<int>> find_bad_matrix(int n, int m, int max_value, bool *correct){
    bool find;
    vector<vector<int>> rand_matrix(n, vector<int>(m, 1));

    for(int k = 0; k < pow(max_value, n * m) - 1; k++){
        find = true;
        vector<int> colors(n, 0);
        vector<set<int>> tmp_allocation(n, set<int>());
        for (int i = 0; i < m; i++) {
            tmp_allocation[colors[i]].insert(i);
        }

        for(int i = 0; i < pow(n, m); i++){



            if(is_PO(rand_matrix, tmp_allocation) && is_propm(rand_matrix, tmp_allocation)) {
                find = false;
                break;
            }
            if(i == pow(n, m) - 1)
                continue;
            colors[0] += 1;

            int j = 0;
            while (colors[j] == n){
                tmp_allocation[0].insert(j);
                tmp_allocation[n-1].erase(j);
                colors[j] = 0;
                colors[j + 1]++;
                j++;
            }
            tmp_allocation[colors[j]].insert(j);
            tmp_allocation[colors[j] - 1].erase(j);

        }
        if(find) {
            *correct = true;
            break;
        }
        rand_matrix[0][0] +=1;
        int j = 0;
        while(rand_matrix[j / m][j % m] == max_value + 1){
            rand_matrix[j / m][j % m] = 1;
            j++;
            rand_matrix[j / m][j % m]++;
        }

            for (int i = 0; i < n; ++i) {
                for (int l = 0; l < m; ++l) {
                    //cout << rand_matrix[i][l] << " ";
                }
                //cout << endl;
            }
            //cout << endl;

    }
    return rand_matrix;

}
