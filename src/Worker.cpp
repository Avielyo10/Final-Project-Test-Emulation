#include "Worker.hpp"

Worker::Worker(vector<int> jobs) {
    Worker::jobs = jobs;
}

float Worker::work(const float learningFactor) {
    // Return the CMAX by formula
    float ans = 0;
    for (vector<int>::size_type i = 0; i < jobs.size(); ++i) {
        ans += jobs.at(i) * pow(i+1, learningFactor);
    }
    return ans;
}
