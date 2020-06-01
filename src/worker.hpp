#pragma once

#include <vector>
#include <cmath>

using namespace std;

class worker {
private:
    vector<int> jobs;

public:
    worker(vector<int>);
    float work(const float);
};