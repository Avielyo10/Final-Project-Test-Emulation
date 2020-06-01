#pragma once

#include <vector>
#include <limits.h>
#include <bits/stdc++.h>

using namespace std;

class strategy {
private:
    float cMax = INT_MAX;
    vector<vector<int>> bestBunch;
    float learningFactor;
    int numOfWorkers;
    vector<int> jobs;
    
public:
    strategy(int numOfWorkers, vector<int> jobs, float learningFactor);
    virtual void split() = 0;
    const float getCMax();
    void setCMax(float cMax);
    const vector<vector<int>> getBestBunch();
    void setBestBunch(vector<vector<int>> bestBunch);
    const int getNumOfWorkers();
    void setNumOfWorkers(int numOfWorkers);
    const vector<int> getJobs();
    void setJobs(vector<int> jobs);
    const float getLearningFactor();
    void setLearningFactor(float learningFactor);
};
ostream& operator<<(ostream& out, vector<vector<int>> permutations);