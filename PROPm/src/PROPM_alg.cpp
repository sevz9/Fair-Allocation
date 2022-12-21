#include <vector>
#include <set>
#include <iostream>
#include <numeric>
#include "cassert"

#include "PROPM_alg.hpp"
#include "decomposition.hpp"
#include "valuation_matrix.hpp"
#include "aggregate.hpp"

using namespace std;

int update_c(set<int> Nr, int t, vector<vector<int>> bundles,  vector<vector<int>> valuation_matrix, int* bad_agent){
    int n = valuation_matrix.size();
    int c = 0;
    int sum_for_k = 0;
    for(int k : Nr){
        for(int i = 0; i < t; i++){
            for(int item : bundles[i]){
                sum_for_k += valuation_matrix[k][item];
            }
        }
        //cout << "update" << sum_for_k << " " << n << " " <<  sum_for_k << " " << t << " " << sum_kth_row(k, valuation_matrix) << endl;
        if(sum_for_k * n > t * sum_kth_row(k, valuation_matrix)) {
            *bad_agent = k;
            c++;
        }
        sum_for_k = 0;
    }
    return c;
}

vector<vector<int>> PROPm(vector<vector<int>> valuation_matrix){


    int n = valuation_matrix.size();
    int m = valuation_matrix[0].size();
    if(n == 1){
        vector<int> ans(m);
        iota(ans.begin(), ans.end(), 0);
        return {ans};
    }

    int c;
    vector<vector<int>> bundles = get_bundles(valuation_matrix);
    /*
    for(int i = 0; i < n; i++){
        cout << "bundle: " << i + 1 << endl;
        cout << "items: " << endl;
        for(int item : bundles[i])
            cout << item << " ";
        cout << endl;
    }
    */
    Decomposition dec(bundles);
    set<int> Nr;
    int bad_agent;

    for(int i = 1; i < n; i++)
        Nr.insert(i);
    for (int t = 1; t < n + 1; t++) {
        //cout << "t = " << t << endl;
        c = update_c(Nr, t, bundles, valuation_matrix, &bad_agent);
        //cout << "t = " << t << " " << Nr.size() << " " << c << " " << dec.number_of_agents() << " " <<  bad_agent << endl;
        while( c > 0 && dec.number_of_agents() < t){

            dec.update(bundles[t-1], bad_agent, valuation_matrix, &Nr, t);

            c = update_c(Nr, t, bundles, valuation_matrix, &bad_agent);
        }

        //cout << dec.number_of_agents() << " " << c << " " << t << endl;

        if(dec.number_of_agents() < t){

            vector<vector<int>> ans(n);
            ans[0] = bundles[t-1];

            if(Nr.size()) {

                dec.agents_for_bundles.push_back(Nr);
                vector<int> new_bundle;
                for (int i = t; i < n; i++) {
                    new_bundle.push_back(i);
                }
                dec.group_of_bundles.push_back(new_bundle);
                dec.dec_size = dec.group_of_bundles.size();
            }

            for(int i = 0; i < dec.dec_size; i++){

                vector<int> agents(dec.agents_for_bundles[i].begin(), dec.agents_for_bundles[i].end());

                vector<int> bundle;
                for(int bundle_ind : dec.group_of_bundles[i]){
                    for(int item : bundles[bundle_ind]){
                        bundle.push_back(item);
                    }
                }
                vector<vector<int>> sub_valuation_matrix = make_sub_val_matrix(valuation_matrix, bundle, agents);
                vector<vector<int>> prom_sub = PROPm(sub_valuation_matrix);
                for(int j = 0; j < (int)agents.size(); j++){
                    vector<int> v;
                    for(int ind : prom_sub[j])
                        v.push_back(bundle[ind]);
                    ans[agents[j]] = v;
                }
            }
            //cout << "ok1234" << endl;
            return ans;
        }
    }
    assert(dec.number_of_agents() < n);
    return valuation_matrix;
}

