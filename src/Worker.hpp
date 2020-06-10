#pragma once

#include <vector>
#include <cmath>

using namespace std;

class Worker {
private:
    vector<int> jobs;

public:
    Worker(vector<int>);
    float work(const float);
};