#pragma once

#include <bits/stdc++.h> 
#include "Strategy.hpp"

using namespace std;

class CompleteSearchStrategy : public Strategy {
private:
    vector<vector<int>> permutation;
    
public:
    CompleteSearchStrategy(int, vector<int>, float);
    vector<vector<int>> getPermutations();
    void findPermutations();
    void split();
    string getName();
    vector<vector<int>> splitIntoSubVectors(int, int, vector<int>);
};