#include "Strategy.hpp"

using namespace std;

Strategy::Strategy(int numOfWorkers, vector<int> jobs, float learningFactor) {
    this -> numOfWorkers = numOfWorkers;
    this -> jobs = jobs;
    this -> learningFactor = learningFactor;
} 

const float Strategy::getCMax() {
    return cMax;
}

void Strategy::setCMax(float cMax) {
    Strategy::cMax = cMax;
}

const vector<vector<int>> Strategy::getBestBunch() {
    return bestBunch;
}

void Strategy::setBestBunch(vector<vector<int>> bestBunch) {
    Strategy::bestBunch = bestBunch;
}

const int Strategy::getNumOfWorkers() {
    return numOfWorkers;
}

void Strategy::setNumOfWorkers(int numOfWorkers) {
    Strategy::numOfWorkers = numOfWorkers;
}

const vector<int> Strategy::getJobs() {
    return jobs;
}

void Strategy::setJobs(vector<int> jobs) {
    Strategy::jobs = jobs;
    Strategy::jobs.shrink_to_fit();
}

const float Strategy::getLearningFactor() {
    return learningFactor;
}

void Strategy::setLearningFactor(float learningFactor) {
    Strategy::learningFactor = learningFactor;
}

ostream& operator<<(ostream& out, vector<vector<int>> permutations) {
    stringstream display;
    display << "{";
    string separator = "";
    
    for (auto permutation: permutations) {
        display << separator << "[";
        string comma = "";
        for (auto job: permutation) {
            display << comma << job;
            comma = ", ";
        }
        display << "]";
        separator = ", ";
    }
    display << "}";
    return out << display.str();
}
