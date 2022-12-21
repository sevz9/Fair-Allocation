#include <vector>
#include <set>
#include <iostream>

#include "decomposition.hpp"
#include "aggregate.hpp"

using namespace std;



Decomposition::Decomposition(vector<vector<int>> _bundles){
    dec_size = 0;
    bundles = _bundles;
}
void Decomposition::show_bundles(){
    for(int i = 0; i < dec_size; i++){
        cout << "group_number: " << i + 1 << endl;
        cout << "bundles_numbers: " << endl;
        for(int bundle_number : group_of_bundles[i])
            cout << bundle_number << " ";
        cout << endl << "agents: " << endl;
        for(int agent : agents_for_bundles[i])
            cout << agent << " ";
        cout << endl;
    }
}
int Decomposition::number_of_agents(){
    int number = 0;
    for(auto agents : agents_for_bundles){
        number += agents.size();
    }
    return number;
}
void Decomposition::add_agent(int agent, int bundle_number){
    agents_for_bundles[bundle_number].insert(agent);
}
void Decomposition::remove_agent(int agent, int bundle_number){
    agents_for_bundles[bundle_number].erase(agent);
}
void Decomposition::dfs(vector<vector<int>> g, vector<bool>* vis, vector<int>* parents, int start, pair<int, int> *swap, int t, vector<vector<int>> valuation_matrix){
    (*vis)[start] = true;
    if(start < dec_size) {
        for (int agent: agents_for_bundles[start]) {
            int n = valuation_matrix.size();
            int sum_for_agent = 0;
            for (int i = 0; i < t; i++) {
                for (int item: bundles[i]) {
                    sum_for_agent += valuation_matrix[agent][item];
                }
            }
            //cout << start << " " << agent << " " << sum_for_agent << " " << sum_kth_row(agent, valuation_matrix) << " " << n << " " << t << endl;
            if (sum_for_agent * n <= t * sum_kth_row(agent, valuation_matrix)) {
                *swap = {start, agent};
            }
        }
    }
    for(int i = 0; i < (int)g[start].size(); i++){
        if(g[start][i] != -1 && !(*vis)[i]){
            (*parents)[i] = start;
            dfs(g, vis, parents, i, swap, t, valuation_matrix);
        }
    }
}

void Decomposition::update(vector<int> S_t, int bad_agent, vector<vector<int>> valuation_matrix, set<int>* Nr, int t){

    vector<vector<int>> g(dec_size + 2, vector<int>(dec_size + 2, -1));
    int n = valuation_matrix.size();
    for(int i = 0; i < dec_size; i++){
        for(int j = 0; j < dec_size; j++){
            if(i == j)
                continue;
            for(int agent : agents_for_bundles[i]){
                if(agent_val_for_group_of_bundle(agent, group_of_bundles[j], valuation_matrix, bundles) * n
                   >= (int)group_of_bundles[j].size() * sum_kth_row(agent, valuation_matrix)){
                    g[i][j] = agent;
                    break;
                }
            }

            for(int agent : agents_for_bundles[j]){
                if(agent_val_for_group_of_bundle(agent, group_of_bundles[i], valuation_matrix, bundles) * n >=
                   (int)group_of_bundles[i].size() * sum_kth_row(agent, valuation_matrix)){
                    g[j][i] = agent;
                    break;
                }
            }
        }
    }
    for(int i = 0; i < dec_size; i++) {
        if(agent_val_for_group_of_bundle(bad_agent, group_of_bundles[i], valuation_matrix, bundles) * n >=
           (int)group_of_bundles[i].size() * sum_kth_row(bad_agent, valuation_matrix)){
            g[dec_size + 1][i] = bad_agent;
        }
    }

    for(int i = 0; i < dec_size; i++) {
        for(int agent : agents_for_bundles[i]) {
            if (agent_val_for_bundle(agent, S_t, valuation_matrix) * n >=
                sum_kth_row(agent, valuation_matrix)) {
                g[i][dec_size] = agent;
                break;
            }
        }
    }
    if(agent_val_for_bundle(bad_agent, S_t, valuation_matrix) * n >=
       sum_kth_row(bad_agent, valuation_matrix) ){
        g[dec_size + 1][dec_size] = bad_agent;
    }

    //create grath g
    /*
    cout << "g: \n";
    for(int i = 0; i < dec_size + 2; i++){
        for (int j = 0; j < dec_size + 2; ++j) {
            cout << g[i][j] << " ";
        }
        cout << endl;
    }

    cout << "vis: \n";
    for(int i = 0; i < dec_size + 2; i++) {
        cout << vis[i] << " ";
    }
    cout << "\n parents: \n";
    for(int i = 0; i < dec_size + 2; i++) {
        cout << parents[i] << " ";
    }
    cout << endl;
     */
    vector<bool> vis(dec_size + 2, false);
    vector<int> parents(dec_size + 2, -1);
    pair<int, int> swap = {-1, -1};

    dfs(g, &vis, &parents, dec_size + 1, &swap, t, valuation_matrix);


    if(vis[dec_size]){
        //cout << "update 1" << endl;
        group_of_bundles.push_back({t-1});
        agents_for_bundles.push_back({});
        int cur_vertex = dec_size;
        int prev_vertex = parents[dec_size];
        while (cur_vertex != dec_size + 1){
            //cout << "cur: " << cur_vertex << " prev: " << prev_vertex << " dec_size: " << dec_size << endl;
            if(prev_vertex != dec_size + 1)
                remove_agent(g[prev_vertex][cur_vertex], prev_vertex);
            add_agent(g[prev_vertex][cur_vertex], cur_vertex);
            cur_vertex = prev_vertex;
            if(prev_vertex != dec_size + 1)
                prev_vertex = parents[prev_vertex];
        }

        Nr->erase(bad_agent);
        dec_size = group_of_bundles.size();
        //show_bundles();
    }
    else if(swap.first != -1){
        //cout << "update 2" << endl;
        //cout << swap.first << " " << swap.second << endl;
        int cur_vertex = swap.first;
        int prev_vertex = parents[swap.first];
        while (cur_vertex != dec_size + 1){
            if(prev_vertex != dec_size + 1)
                remove_agent(g[prev_vertex][cur_vertex], prev_vertex);
            add_agent(g[prev_vertex][cur_vertex], cur_vertex);
            cur_vertex = prev_vertex;
            if(prev_vertex != dec_size + 1)
                prev_vertex = parents[prev_vertex];
        }
        remove_agent(swap.second, swap.first);
        Nr->insert(swap.second);

        //show_bundles();

    } else{
        //cout << "update 3" << endl;
        vector<set<int>> new_agents_for_bundle = {{bad_agent}};
        vector<vector<int>> new_bundles = {{t-1}};
        for(int i = 0; i < (int)agents_for_bundles.size(); i++){
            if(!vis[i]){
                new_agents_for_bundle.push_back(agents_for_bundles[i]);
                new_bundles.push_back(group_of_bundles[i]);
            }
            else {
                for (int agent: agents_for_bundles[i]) {
                    new_agents_for_bundle[0].insert(agent);
                }
                for (int item: group_of_bundles[i]) {
                    new_bundles[0].push_back(item);
                }
            }
        }

        group_of_bundles = new_bundles;
        agents_for_bundles = new_agents_for_bundle;
        dec_size = group_of_bundles.size();
        Nr->erase(bad_agent);
        //show_bundles();
    }
}
