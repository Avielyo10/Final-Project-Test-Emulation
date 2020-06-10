#include "CompleteSearchStrategy.hpp"

CompleteSearchStrategy::CompleteSearchStrategy(int numOfWorkers, vector<int> jobs, float learningFactor)
    : Strategy(numOfWorkers, jobs, learningFactor) {}
    
vector<vector<int>> CompleteSearchStrategy::getPermutations() {
    return permutation;
}

void CompleteSearchStrategy::split() {
    findPermutations();
    
    int numOfWorkers = this -> getNumOfWorkers();
    vector<vector<int>> permutations = this -> getPermutations();
    int numOfJobs = permutations.at(0).size();
    float cMax = INT_MAX;
    vector<vector<int>> bestBunch;

    if (numOfWorkers >= numOfJobs) {
        vector<int> firstPermutation = permutations.at(0);
        cMax = *max_element(firstPermutation.begin(), firstPermutation.end());
    }
    else {
        for (auto permutation: permutations) {
            vector<vector<int>> bunches = splitIntoSubVectors(numOfWorkers, numOfJobs, permutation);
            float tmpCMax = INT_MIN;
            for(auto const& job : bunches) {
	            float cMaxFromWorker = Worker(job).work(this -> getLearningFactor());
                if (cMaxFromWorker > tmpCMax) tmpCMax = cMaxFromWorker;
	        }
            if (tmpCMax < cMax) {
                cMax = tmpCMax;
                bestBunch = bunches;
            }
        }
    }
    this -> setBestBunch(bestBunch);
    this -> setCMax(cMax);
}

void CompleteSearchStrategy::findPermutations() {
    vector<int> jobs = this -> getJobs();

    sort(jobs.begin(), jobs.end());
    do { 
        permutation.push_back(jobs);
    } while (next_permutation(jobs.begin(), jobs.end())); 
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
