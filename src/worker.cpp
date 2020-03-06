#ifndef WORKER
#define WORKER

#include <vector>
#include <cmath>

using namespace std;

class worker {
private:
    vector<int> jobs;

public:
    worker(vector<int>);
    float work(const float);
};

worker::worker(vector<int> jobs) {
    worker::jobs = jobs;
}

float worker::work(const float learningFactor) {
    // Return the CMAX by formula
    float ans = 0;
    for (int i = 0; i < jobs.size(); ++i) {
        ans += jobs.at(i) * pow(i+1, learningFactor);
    }
    return ans;
}
#endif
