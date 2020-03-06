#include <bits/stdc++.h>
#include <nlohmann/json.hpp>
#include "../src/worker.cpp"
#include "../src/strategies/completeSearchStrategy.cpp"

using namespace std; 
using json = nlohmann::json;

int main() {
    json tests;
    ifstream testsPayload("test/resources/testsPayload.json");
    testsPayload >> tests;

    for (auto& test: tests) {
        cout << "Testing completeSearchStrategyTest: " << test << endl;
        int numOfWorkers = test["numOfWorkers"].get<int>();
        float learningFactor = test["learningFactor"].get<float>();
        vector<int> jobs = test["jobs"].get<vector<int>>();
        
        completeSearchStrategy css = completeSearchStrategy(numOfWorkers, jobs, learningFactor);
        css.split();
        cout << "CMAX = " << css.getCMax() 
            << "\nBEST BUNCH = " << css.getBestBunch() << endl << endl;
    }   
    return 0;
}
