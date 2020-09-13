#include "CompleteSearchStrategy.hpp"

CompleteSearchStrategy::CompleteSearchStrategy(int numOfWorkers, vector<int> jobs, float learningFactor)
    : Strategy(numOfWorkers, jobs, learningFactor) {}

void CompleteSearchStrategy::split() {
    vector<int> jobs = this -> getJobs();
    int numOfWorkers = this -> getNumOfWorkers();
    int numOfJobs = jobs.size();
    float cMax = INT_MAX;
    vector<vector<int>> bestBunch;

    if (numOfWorkers >= numOfJobs) {
        cMax = *max_element(jobs.begin(), jobs.end());
    }
    else {
        sort(jobs.begin(), jobs.end());
        do {
            vector<vector<vector<int>>> subVectors = splitIntoSubVectors(numOfWorkers, numOfJobs, jobs);
            for (auto const& bunches: subVectors) {
                float cMax1 = Worker(bunches[0]).work(this -> getLearningFactor());
                float cMax2 = Worker(bunches[1]).work(this -> getLearningFactor());
                if (cMax1 > cMax2 && cMax1 < cMax) {
                    cMax = cMax1;
                    bestBunch = bunches;
                } else if (cMax2 > cMax1 && cMax2 < cMax) {
                    cMax = cMax2;
                    bestBunch = bunches;
                }
            }
        } while (next_permutation(jobs.begin(), jobs.end())); 
    }
    this -> setBestBunch(bestBunch);
    this -> setCMax(cMax);
}

string CompleteSearchStrategy::getName() {
    return "CompleteSearchStrategy";
}

vector<vector<vector<int>>> CompleteSearchStrategy::splitIntoSubVectors(int numOfWorkers, int numOfJobs, vector<int> permutation) {
    vector<vector<vector<int>>> subVectors;
    size_t iter = 0;
    while (iter < permutation.size()){
        vector<int> jobA(permutation.begin(), permutation.begin() + iter);
        vector<int> jobB(permutation.begin() + iter, permutation.end());
        subVectors.push_back(vector<vector<int>> {jobA, jobB});
        iter++;
    }
    return subVectors;
}
