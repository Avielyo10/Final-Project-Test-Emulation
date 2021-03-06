#pragma once

#include <bits/stdc++.h> 
#include "Strategy.hpp"

using namespace std;

struct Bin {
    pair<float, float> cmax;
    vector<vector<int>> bunches;
    Bin() : cmax(MAXFLOAT, MAXFLOAT), bunches(2) {}
    Bin(pair<float, float> cMax) : cmax(cMax.first, cMax.second), bunches(2) {}
    void setCmax1(float cmax1) {
        cmax.first = cmax1;
    }
    float getCmax1() const{
        return cmax.first;
    }
    void setCmax2(float cmax2) {
        cmax.second = cmax2;
    }
    float getCmax2() const{
        return cmax.second;
    }
    void setM1BestBunch(const vector<int>& bunch) {
        bunches.at(0) = bunch;
    }
    vector<int> getM1BestBunch() const{
        return bunches.at(0);
    }
    void setM2BestBunch(const vector<int>& bunch) {
        bunches.at(1) = bunch;
    }
    vector<int> getM2BestBunch() const{
        return bunches.at(1);
    }
    float getCmax() {
        return max(this->getCmax1(), this->getCmax2());
    }
    vector<vector<int>> getBunches() const{
        return bunches;
    }
    bool operator<(const Bin& bin) {
        return max(this->getCmax1(), this->getCmax2()) <
            max(bin.getCmax1(), bin.getCmax2());
    }
    Bin& operator=(const Bin& bin) {
        this->setCmax1(bin.getCmax1());
        this->setCmax2(bin.getCmax2());
        this->setM1BestBunch(bin.getM1BestBunch());
        this->setM2BestBunch(bin.getM2BestBunch());
        return *this;
    }
    friend ostream& operator<<(ostream& out, const Bin& bin) {
        return out << "Bin(cmax1 = " << bin.getCmax1() << 
            ", cmax2 = " << bin.getCmax2() << ")";
    }
};

struct BinCollection {
    vector<Bin> collection;
    BinCollection() = default;
    BinCollection(int sz, const Bin& bin) : collection(sz, bin) {}
    BinCollection(initializer_list<Bin> lst) : collection (lst.size()) {
        copy(lst.begin(), lst.end(), collection.begin());
    }
    void addBin(const Bin& bin) {
        collection.push_back(bin);
    }
    Bin at(int index){
        return collection.at(index);
    }
    vector<Bin>::iterator begin(){
        return collection.begin();
    }
    vector<Bin>::iterator end(){
        return collection.end();
    }
};

class DPStrategy2Machines : public Strategy {
public:
    DPStrategy2Machines(int, vector<int>, float);
    void split();
    string getName();
    void initFirstRow(vector<vector<BinCollection>>&, 
        vector<vector<float>>&, vector<int>&, long unsigned int);
    void initFirstColumn(vector<vector<BinCollection>>&, 
        vector<vector<float>>&, vector<int>&, long unsigned int);
    vector<vector<float>> getCostMap(vector<int>);
    void addBinsFromLeft(BinCollection&, vector<vector<BinCollection>>&, 
        vector<vector<float>>&, vector<int>&, Bin&,
        long unsigned int, long unsigned int);
    void addBinsFromTop(BinCollection&, vector<vector<BinCollection>>&, 
        vector<vector<float>>&, vector<int>&, Bin&,
        long unsigned int, long unsigned int);
};
