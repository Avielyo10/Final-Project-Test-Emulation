#include "strategy.hpp"

using namespace std;

strategy::strategy(int numOfWorkers, vector<int> jobs, float learningFactor) {
    this -> numOfWorkers = numOfWorkers;
    this -> jobs = jobs;
    this -> learningFactor = learningFactor;
} 

const float strategy::getCMax() {
    return cMax;
}

void strategy::setCMax(float cMax) {
    strategy::cMax = cMax;
}

const vector<vector<int>> strategy::getBestBunch() {
    return bestBunch;
}

void strategy::setBestBunch(vector<vector<int>> bestBunch) {
    strategy::bestBunch = bestBunch;
}

const int strategy::getNumOfWorkers() {
    return numOfWorkers;
}

void strategy::setNumOfWorkers(int numOfWorkers) {
    strategy::numOfWorkers = numOfWorkers;
}

const vector<int> strategy::getJobs() {
    return jobs;
}

void strategy::setJobs(vector<int> jobs) {
    strategy::jobs = jobs;
    strategy::jobs.shrink_to_fit();
}

const float strategy::getLearningFactor() {
    return learningFactor;
}

void strategy::setLearningFactor(float learningFactor) {
    strategy::learningFactor = learningFactor;
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
