#include <vector>
#include <cmath>
#include <set>
#include <iostream>

#include "PO_checker.hpp"

using namespace std;

bool allocation_comp(vector<vector<int>> valuation_matrix, vector<set<int>> allocation1, vector<vector<int>> allocation2){
    int n = valuation_matrix.size();
    bool more = false;
    int sum1 = 0;
    int sum2 = 0;
    for(int agent = 0; agent < n; agent++){

        for(int item : allocation1[agent])
            sum1 += valuation_matrix[agent][item];

        for(int item : allocation2[agent])
            sum2 += valuation_matrix[agent][item];
        //cout << sum1 << " " << sum2 << endl;
        if(sum2 > sum1)
            return false;

        more = sum1 > sum2;

        sum1 = 0;
        sum2 = 0;
    }
    return more;
}

bool is_PO(vector<vector<int>> valuation_matrix, vector<vector<int>> allocation){
    int n = valuation_matrix.size();
    int m = valuation_matrix[0].size();
    vector<int> colors(m, 0);
    vector<set<int>> tmp_allocation(n, set<int>());
    for (int i = 0; i < m; i++) {
        tmp_allocation[colors[i]].insert(i);
    }

    for(int i = 0; i < pow(n, m); i++){

        /*
        cout << "tmp_alloc:" << endl;
        for(int agent = 0; agent < n; agent++){
            for(int item : tmp_allocation[agent]){
                cout << item << " ";
            }
            cout << endl;
        }
        */
        if(allocation_comp(valuation_matrix, tmp_allocation, allocation))
            return false;
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
    return true;
}

bool allocation_comp(vector<vector<int>> valuation_matrix, vector<set<int>> allocation1, vector<set<int>> allocation2){
    int n = valuation_matrix.size();
    bool more = false;
    int sum1 = 0;
    int sum2 = 0;
    for(int agent = 0; agent < n; agent++){

        for(int item : allocation1[agent])
            sum1 += valuation_matrix[agent][item];

        for(int item : allocation2[agent])
            sum2 += valuation_matrix[agent][item];
        //cout << sum1 << " " << sum2 << endl;
        if(sum2 > sum1)
            return false;

        more = sum1 > sum2;

        sum1 = 0;
        sum2 = 0;
    }
    return more;
}

bool is_PO(vector<vector<int>> valuation_matrix, vector<set<int>> allocation){
    int n = valuation_matrix.size();
    int m = valuation_matrix[0].size();
    vector<int> colors(m, 0);
    vector<set<int>> tmp_allocation(n, set<int>());
    for (int i = 0; i < m; i++) {
        tmp_allocation[colors[i]].insert(i);
    }

    for(int i = 0; i < pow(n, m); i++){

        /*
        cout << "tmp_alloc:" << endl;
        for(int agent = 0; agent < n; agent++){
            for(int item : tmp_allocation[agent]){
                cout << item << " ";
            }
            cout << endl;
        }
        */
        if(allocation_comp(valuation_matrix, tmp_allocation, allocation))
            return false;
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
    return true;
}

