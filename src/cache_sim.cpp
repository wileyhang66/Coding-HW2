#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

static int findIndex(vector<int>& cache, int x){
    for(int i = 0; i < (int)cache.size(); i++){
        if(cache[i] == x){
            return i;
        }
    }
    return -1;
}

static void readInput(string filename, int k, int m, vector<int> req){
    ifstream in (filename);
    if(!in){
        cerr << "Error" << filename << "\n";
        exit(1);
    }
    in >> k >> m;
    req.resize(m);
    for(int i = 0; i < m; i++) in >> req[i];
}

//FIFO 
//If miss and cache is full, kick the one that entered earliest..
static int sim_FIFO(int k, vector<int> req){
    vector<int> cache;
    vector<int> insertedTime;
    int misses = 0;
    int t = 0;
    for(int x: req){
        t++;
        int idx = findIndex(cache, x);
        if(idx != -1){
            continue;
        }
    
        misses++;
        if(cache.size() < k){
            cache.push_back(x);
            insertedTime.push_back(t);
        }
        else{
            int victimPos = 0;
            for(int i = 1; i < k; i++){
                if(insertedTime[i] < insertedTime[victimPos]) victimPos = i;
            }
            cache[victimPos] = x;
            insertedTime[victimPos] = t;
        }
    }
    return misses;
}
