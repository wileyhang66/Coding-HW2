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

//LRU function
//if miss and cache is full: kick the one with the smallest lastusedtime

static int sim_LRU(int k, vector<int> req){
    vector<int> cache;
    vector<int> lastUsedTime;
    int misses = 0;
    int t = 0;
    
    for(int x : req){
        t++;
        int idx = findIndex(cache, x);
        if(idx != -1){
            lastUsedTime[idx] = t;
            continue;
        }

        misses++;

        if(cache.size() < k){
            cache.push_back(x);
            lastUsedTime.push_back(t);
        }
        else{
            int victimPos = 0;
            for(int i = 1; i < k; i++){
                if(lastUsedTime[i] < lastUsedTime[victimPos]) victimPos = i;

            }
            cache[victimPos] = x;
            lastUsedTime[victimPos] = t;

        }
    }
    return misses;
}

/*
OPTFF
if miss and cache is full, 
for each item in cache, look ahead in the request sequence, find when it will be used next.
kick the one used farthest in the future or never will be used*/

static int sim_OPTFF(int k, vector<int> req){
    vector<int> cache;
    int misses = 0;

    for(int i = 0; i < req.size(); i++){
        int x = req[i];
        int idx = findIndex(cache,x);
        if(idx != -1){
            continue;
        }
        misses++;

        if ((int)cache.size() < k) {
            cache.push_back(x);
        }
        else{
            int victimPos = 0;
            int farthest = -1;

            for(int c = 0; c < k; c++){
                int item = cache[c];
                int nextUse = 1000000000;
                for(int j = i+1; j<req.size(); j++){
                    if(req[j] == item){
                        nextUse = j;
                        break;
                    }
                }
                if(nextUse > farthest){
                    farthest = nextUse;
                    victimPos = c;
                }
            }
            cache[victimPos] = x;
        }
    }
    return misses;
}

int main(int argc, char** argv){
    if(argc != 2){
        cerr << "Usage: " << argv[0] << "<input_file>\n";
        return 1;
    }

    int k, m;
    vector<int> req;
    readInput(argv[1], k, m, req);
    int fifo_miss = sim_FIFO(k, req);
    int lru_miss = sim_LRU(k, req);
    int optff_miss = sim_OPTFF(k, req);
    cout << "FIFO Misses: " << fifo_miss << "\n";
    cout << "LRU Misses: " << lru_miss << "\n";
    cout << "OPTFF Misses: " << optff_miss << "\n";

    return 0;
}