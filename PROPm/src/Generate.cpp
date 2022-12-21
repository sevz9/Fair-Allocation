#include <iostream>
#include <vector>
#include <random>
#include <stdio.h>
#include <stdlib.h>
#include <string>

#include "Generate.hpp"
#include "PO_checker.hpp"
#include "PROPM_alg.hpp"

using namespace std;

vector<vector<int>> generate_random_matrix(int n, int m){
    random_device dev;
    mt19937 rng(dev());
    uniform_int_distribution<std::mt19937::result_type> dist(1,10000);

    vector<vector<int>> matrix(n, vector<int>(m));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            matrix[i][j] = dist(rng);
            //cout << matrix[i][j] << " ";
        }
        //cout << endl;
    }
    return matrix;
}

int generate_item(int type){
    random_device dev;
    mt19937 rng(dev());
    uniform_int_distribution<std::mt19937::result_type> random_item(1,100);
    if (type == 1)
        return random_item(rng);
    else{
        return random_item(rng) > 50 ? 1 : 0;
    }

}

void generate_sample(string filename_out, int count, int agent_number, int item_max, string filename_res, int type){
    random_device dev;
    mt19937 rng(dev());
    uniform_int_distribution<std::mt19937::result_type> random_item(1,100);
    uniform_int_distribution<std::mt19937::result_type> random_item_number(1,item_max);



    FILE *file = fopen(filename_out.c_str(), "w");
    FILE *file_res = fopen(filename_res.c_str(), "a");

    vector<vector<int>> val_matrix(agent_number, vector<int>());
    vector<vector<int>> propm_matrix;

    int po_number = 0;
    int rand;
    for(int k = 0; k < count; k++){
        int item_number = random_item_number(rng);
        for (int i = 0; i < agent_number; ++i) {
            for (int j = 0; j < item_number - 1; ++j) {
                rand = generate_item(type);
                fprintf(file, "%d ", rand);
                val_matrix[i].push_back(rand);
                //cout << matrix[i][j] << " ";
            }
            rand = generate_item(type);
            fprintf(file, "%d\n", rand);
            val_matrix[i].push_back(rand);
            //cout << endl;
        }


        fprintf(file, "\n");
        propm_matrix = PROPm(val_matrix);

        if(is_PO(val_matrix, propm_matrix)){
            po_number++;
        }
        for(int i = 0; i < agent_number; i++)
            val_matrix[i].clear();
    }

    fprintf(file_res, "%s\n", filename_out.c_str());
    fprintf(file_res, "samples count: %d\n", count);
    fprintf(file_res, "po count: %d\n", po_number);
    fprintf(file_res, "po percent: %f\n\n", 1.0 * po_number / count);
    fclose(file_res);


}