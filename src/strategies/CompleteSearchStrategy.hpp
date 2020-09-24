#pragma once

#include <bits/stdc++.h> 
#include "Strategy.hpp"

using namespace std;

class CompleteSearchStrategy : public Strategy {
public:
    CompleteSearchStrategy(int, vector<int>, float);
    void split();
    string getName();
    vector<vector<vector<int>>> splitIntoSubVectors(int, int, vector<int>);
};