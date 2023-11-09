#ifndef DATA_SET_H
#define DATA_SET_H

#include <iostream>
#include <string>
#include <vector>
#include <CCData.h>

class DataSet {
 public:
    //constructors
    DataSet();
    DataSet(std::string name);

    //destructor
    ~DataSet();

    void addData(const CCData &data);
    const void printInfo();
    
 private:

    std::string title;
    std::vector<CCData> CCDataSet;
    const int largestCC();
    const int smallestCC();
    const int oldestTime();
    const int newestTime();
    const double mean();
    const double stdDev();
    const double cv();
};

#endif