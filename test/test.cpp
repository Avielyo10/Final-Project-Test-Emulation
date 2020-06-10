#include <bits/stdc++.h>
#include <nlohmann/json.hpp>
#include "../src/worker.hpp"
#include "../src/strategies/completeSearchStrategy.hpp"

using namespace std; 
using json = nlohmann::json;

int main() {
    json tests;
    ifstream testsPayload("test/resources/testsPayload.json");
    testsPayload >> tests;

    for (auto& test: tests) {
        int numOfWorkers = test["numOfWorkers"].get<int>();
        float learningFactor = test["learningFactor"].get<float>();
        vector<int> jobs = test["jobs"].get<vector<int>>();
        
        vector<shared_ptr<strategy>> strategies;
        strategies.push_back(shared_ptr<strategy>(new completeSearchStrategy(numOfWorkers, jobs, learningFactor)));
        
        for (auto& strategy: strategies){
            cout << "Testing " << strategy->getName() << ": "<< test << endl;
            strategy->split();
            cout << "CMAX = " << strategy->getCMax() 
                << "\nBEST BUNCH = " << strategy->getBestBunch() << endl << endl;
        }
    }   
    return 0;
}
