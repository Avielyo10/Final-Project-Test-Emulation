#include "worker.hpp"

worker::worker(vector<int> jobs) {
    worker::jobs = jobs;
}

float worker::work(const float learningFactor) {
    // Return the CMAX by formula
    float ans = 0;
    for (vector<int>::size_type i = 0; i < jobs.size(); ++i) {
        ans += jobs.at(i) * pow(i+1, learningFactor);
    }
    return ans;
}
