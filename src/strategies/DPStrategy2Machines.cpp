#include "DPStrategy2Machines.hpp"

DPStrategy2Machines::DPStrategy2Machines(int numOfWorkers, vector<int> jobs, float learningFactor)
    : Strategy(numOfWorkers, jobs, learningFactor) {}

void DPStrategy2Machines::split() {
    vector<int>::size_type numOfWorkers = this->getNumOfWorkers();
    vector<int> jobs = this->getJobs();
    vector<int>::size_type numOfJobs = jobs.size();
    sort(jobs.begin(), jobs.end());

    if (numOfWorkers >= numOfJobs) {
        vector<vector<int>> bestBunch;
        vector<int> bunch;
        for (vector<int>::size_type i = 0; i < numOfWorkers; ++i) {
            if (i < numOfJobs)
                bunch.push_back(jobs.at(i));
            bestBunch.push_back(bunch);
        }
        this->setBestBunch(bestBunch);
        this->setCMax(jobs.back());
        return;
    }
    vector<vector<float>> costMap = getCostMap(jobs);
    
    vector<vector<vector<Bin>>> map 
        (numOfJobs + 1, vector<vector<Bin>>(numOfJobs, vector<Bin>(1, Bin())));
    // init
    Bin initBin (make_pair(jobs.at(0), 0));
    initBin.setM1BestBunch(vector<int> (1, jobs.at(0)));
    map.at(1).at(0) = vector<Bin> { initBin };
    initFirstRow(map, costMap, jobs, numOfJobs);
    initFirstColumn(map, costMap, jobs, numOfJobs);
    
    // DP algorithm
    for (long unsigned int i = 2; i < numOfJobs + 1; ++i) {
        for (long unsigned int j = 1; j < numOfJobs; ++j) {
            if (i + j <= numOfJobs) {
                vector<Bin> binCollection;
                addBinsFromLeft(binCollection, map, costMap, jobs, i, j);
                addBinsFromTop(binCollection, map, costMap, jobs, i, j);
                map.at(i).at(j) = binCollection;
            }
        }
    }

    // get bestBin that contains the correct answer
    Bin bestBin = getBestBinFromMap(map, numOfJobs);
    this->setCMax(bestBin.getCmax());
    this->setBestBunch(bestBin.getBunches());
}

string DPStrategy2Machines::getName() {
    return "DPStrategy2Machines";
}

vector<vector<float>> DPStrategy2Machines::getCostMap(vector<int> jobs) {
    vector<float> fJobs;
    for (auto &job : jobs) {
        fJobs.push_back((float)job);
    }
    vector<vector<float>> jobsMap;
    jobsMap.push_back(fJobs);

    for (vector<int>::size_type i = 1; i < fJobs.size(); ++i) {
        vector<float> tmp;
        int iter = 0;
        for (auto &job : fJobs) {
            tmp.push_back(job * pow(i + 1, this->getLearningFactor()));
            iter++;
        }
        jobsMap.push_back(tmp);
    }
    return jobsMap;
}

void DPStrategy2Machines::initFirstRow(vector<vector<vector<Bin>>>& map, 
    vector<vector<float>>& costMap, vector<int>& jobs, long unsigned int numOfJobs){
    for (long unsigned int j = 1; j < numOfJobs; ++j) {
        Bin tmpBin (make_pair(jobs.at(0), map.at(1).at(j - 1).at(0).getCmax2() + costMap.at(j - 1).at(j)));
        vector<int> m2BestBunch = map.at(1).at(j - 1).at(0).getM2BestBunch();
        m2BestBunch.push_back(jobs.at(j));
        tmpBin.setM1BestBunch(vector<int> (1, jobs.at(0)));
        tmpBin.setM2BestBunch(m2BestBunch);
        map.at(1).at(j) = vector<Bin> { tmpBin };
    }
}

void DPStrategy2Machines::initFirstColumn(vector<vector<vector<Bin>>>& map, 
    vector<vector<float>>& costMap, vector<int>& jobs, long unsigned int numOfJobs){
    for (long unsigned int i = 2; i < numOfJobs + 1; ++i) {
        Bin tmpBin (make_pair(map.at(i - 1).at(0).at(0).getCmax1() + costMap.at(i - 1).at(i - 1), 0));
        vector<int> m1BestBunch = map.at(i - 1).at(0).at(0).getM1BestBunch();
        m1BestBunch.push_back(jobs.at(i - 1));
        tmpBin.setM1BestBunch(m1BestBunch);
        tmpBin.setM2BestBunch(vector<int> (0));
        map.at(i).at(0) = vector<Bin> { tmpBin };
    }
}

Bin DPStrategy2Machines::getBestBinFromMap(vector<vector<vector<Bin>>>& map, int numOfJobs) {
    Bin bestBin;
    if (numOfJobs % 2 != 0){ // odd
        int i = numOfJobs / 2;
        int j = i + 1;
        for (auto& bin: map.at(i).at(j)) {
            if(bin < bestBin) bestBin = bin;
        }
        for (auto& bin: map.at(j).at(i)) {
            if(bin < bestBin) bestBin = bin;
        }
    }
    else { // even
        int i = numOfJobs / 2;
        for (auto& bin: map.at(i).at(i)) {
            if(bin < bestBin) bestBin = bin;
        }
    }
    return bestBin;
}

void DPStrategy2Machines::addBinsFromLeft(vector<Bin>& binCollection, vector<vector<vector<Bin>>>& map, 
    vector<vector<float>>& costMap, vector<int>& jobs,
    long unsigned int i, long unsigned int j) {
    for (auto& bin: map.at(i).at(j - 1)) {
        float cmax1 = bin.getCmax1();
        float cmax2 = bin.getCmax2() + costMap.at(j - 1).at(i + j - 1);

        Bin tmpBin(make_pair(cmax1, cmax2));
        vector<int> m2BestBunch = bin.getM2BestBunch();
        m2BestBunch.push_back(jobs.at(i + j - 1));

        tmpBin.setM1BestBunch(bin.getM1BestBunch());
        tmpBin.setM2BestBunch(m2BestBunch);
        binCollection.push_back(tmpBin);
    }
}

void DPStrategy2Machines::addBinsFromTop(vector<Bin>& binCollection, vector<vector<vector<Bin>>>& map, 
    vector<vector<float>>& costMap, vector<int>& jobs,
    long unsigned int i, long unsigned int j) {
    for (auto& bin: map.at(i - 1).at(j)) {
        float cmax1 = bin.getCmax1() + costMap.at(i - 1).at(i + j - 1);
        float cmax2 = bin.getCmax2();

        Bin tmpBin(make_pair(cmax1, cmax2));
        vector<int> m1BestBunch = bin.getM1BestBunch();
        m1BestBunch.push_back(jobs.at(i + j - 1));

        tmpBin.setM1BestBunch(m1BestBunch);
        tmpBin.setM2BestBunch(bin.getM2BestBunch());
        binCollection.push_back(tmpBin);
    }
}
