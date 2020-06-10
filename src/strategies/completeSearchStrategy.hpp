#pragma once

#include <bits/stdc++.h> 
#include "strategy.hpp"
#include "../worker.hpp"

using namespace std;

class completeSearchStrategy : public strategy {
private:
    vector<vector<int>> permutation;
    
public:
    completeSearchStrategy(int, vector<int>, float);
    vector<vector<int>> getPermutations();
    void findPermutations();
    void split();
    string getName();
    vector<vector<int>> splitIntoSubVectors(int, int, vector<int>);
};