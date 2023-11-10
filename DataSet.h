#ifndef DATA_SET_H
#define DATA_SET_H

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
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
    const void printCSV(std::ofstream &ofile);
    void sortData();
    const double getOldestTime() const;
    const double getNewestTime() const;
    std::vector<CCData> getDataSet() const; 
    bool isEmpty();
    
 private:

    std::string title;
    std::vector<CCData> CCDataSet;
    const double largestCC();
    const double smallestCC();
    const double oldestTime() const;
    const double newestTime() const;
    const double mean();
    const double stdDev();
    const double cv();
};

#endif