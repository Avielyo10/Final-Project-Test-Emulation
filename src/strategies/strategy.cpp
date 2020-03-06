#include <vector>
#include <limits.h>

using namespace std;

class strategy {
private:
    float cMax = INT_MAX;
    vector<vector<int>> bestBunch;
    float learningFactor;
    int numOfWorkers;
    vector<int> jobs;
    
public:
    strategy(int numOfWorkers, vector<int> jobs, float learningFactor) {
        this -> numOfWorkers = numOfWorkers;
        this -> jobs = jobs;
        this -> learningFactor = learningFactor;
    } 
    virtual void split() = 0;

    const float getCMax() {
        return cMax;
    }

    void setCMax(float cMax) {
        strategy::cMax = cMax;
    }

    const vector<vector<int>> getBestBunch() {
        return bestBunch;
    }

    void setBestBunch(vector<vector<int>> bestBunch) {
        strategy::bestBunch = bestBunch;
    }

    const int getNumOfWorkers() {
        return numOfWorkers;
    }

    void setNumOfWorkers(int numOfWorkers) {
        strategy::numOfWorkers = numOfWorkers;
    }

    const vector<int> getJobs() {
        return jobs;
    }

    void setJobs(vector<int> jobs) {
        strategy::jobs = jobs;
        strategy::jobs.shrink_to_fit();
    }

    const float getLearningFactor() {
        return learningFactor;
    }

    void setLearningFactor(float learningFactor) {
        strategy::learningFactor = learningFactor;
    }
};

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
