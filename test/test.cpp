#include <bits/stdc++.h>
#include <nlohmann/json.hpp>
#include "../src/Worker.hpp"
#include "../src/strategies/CompleteSearchStrategy.hpp"
#include "../src/strategies/DPStrategy2Machines.hpp"

using namespace std; 
using namespace chrono;
using json = nlohmann::json;

int main() {
    json tests;
    ifstream testsPayload("test/resources/testsPayload.json");
    testsPayload >> tests;

    for (auto& test: tests) {
        int numOfWorkers = test["numOfWorkers"].get<int>();
        float learningFactor = test["learningFactor"].get<float>();
        vector<int> jobs = test["jobs"].get<vector<int>>();
        
        vector<shared_ptr<Strategy>> strategies;
        strategies.push_back(make_shared<CompleteSearchStrategy>(numOfWorkers, jobs, learningFactor));
        strategies.push_back(make_shared<DPStrategy2Machines>(numOfWorkers, jobs, learningFactor));
        
        for (auto& strategy: strategies){
            cout << "Testing " << strategy->getName() << ": "<< test << endl;
            high_resolution_clock::time_point startSplit = high_resolution_clock::now();
            strategy->split();
            high_resolution_clock::time_point endSplit = high_resolution_clock::now();
            duration<double> timeSpan = duration_cast<duration<double>>(endSplit - startSplit);
            cout << "CMAX = " << strategy->getCMax() 
                << "\nBEST BUNCH = " << strategy->getBestBunch() 
                << "\nDURATION (milliseconds) = " << timeSpan.count() * 1000 << endl << endl;
        }
    }   
    return 0;
}
