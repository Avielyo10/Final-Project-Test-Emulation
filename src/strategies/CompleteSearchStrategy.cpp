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
            vector<vector<int>> bunches = splitIntoSubVectors(numOfWorkers, numOfJobs, jobs);
            float tmpCMax = INT_MIN;
            for(auto const& job : bunches) {
                float cMaxFromWorker = Worker(job).work(this -> getLearningFactor());
                if (cMaxFromWorker > tmpCMax) tmpCMax = cMaxFromWorker;
            }
            if (tmpCMax < cMax) {
                cMax = tmpCMax;
                bestBunch = bunches;
            }
        } while (next_permutation(jobs.begin(), jobs.end())); 
    }
    this -> setBestBunch(bestBunch);
    this -> setCMax(cMax);
}

string CompleteSearchStrategy::getName() {
    return "CompleteSearchStrategy";
}

vector<vector<int>> CompleteSearchStrategy::splitIntoSubVectors(int numOfWorkers, int numOfJobs, vector<int> permutation) {
    int remJobs = numOfWorkers - (numOfJobs % numOfWorkers);
    int bunchSize = numOfJobs / numOfWorkers;
    int index = 0;

    vector<vector<int>> bunches(numOfWorkers);
    for(size_t i = 0; i < permutation.size(); i += bunchSize) { 
        remJobs--;
        if (remJobs == 0) bunchSize += 1;
        auto last = min(permutation.size(), i + bunchSize);
        auto& vec = bunches[index++];
        vec.reserve(last - i);
        move(permutation.begin() + i, permutation.begin() + last, back_inserter(vec));  
    }
    return bunches;
}
