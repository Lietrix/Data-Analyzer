#ifndef DATA_SET_H
#define DATA_SET_H

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
#include "CCData.h"

class DataSet {
 public:
    //constructors
    DataSet();
    DataSet(std::string name);

    //destructor
    ~DataSet();

    void addData(const CCData &data);
    const void printInfo();
    void sortData();
    
 private:

    std::string title;
    std::vector<CCData> CCDataSet;
    const double largestCC();
    const double smallestCC();
    const int oldestTime();
    const int newestTime();
    const double mean();
    const double stdDev();
    const double cv();
};

#endif