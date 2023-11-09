#include <DataSet.h>

DataSet::DataSet() {
    // initiate empty Data Set
    this->title = "NO NAME";
}

DataSet::DataSet(std::string name) {
    this->title = name;
}


void DataSet::addData(const CCData &data){
    this->CCDataSet.push_back(data);
}

const void DataSet::printInfo(){
    
}

const int DataSet::largestCC() {
    int maxCC = 0;
    // This value should get overwritten

    for (const auto& data : CCDataSet) {
        if (data.cc > maxCC) {
            maxCC = data.cc;
        }
    }
    return maxCC;
}

const int DataSet::smallestCC(){
    int minCC = 10000;
    // This value should get overwritten

    for (const auto& data : CCDataSet) {
        if (data.cc < minCC) {
            minCC = data.cc;
        }
    }
    return minCC;
}

const int DataSet::oldestTime() {
    int oldestYear = 0;
    // This value should get overwritten

    for (const auto& data : CCDataSet) {
        if (data.year > oldestYear) {
            oldestYear = data.year;
        }
    }
    return oldestYear;
}

const int DataSet::newestTime() {
    int newestYear = 10000000000;
    // This value should get overwritten

    for (const auto& data : CCDataSet) {
        if (data.year < newestYear) {
            newestYear = data.year;
        }
    }
    return newestYear;
}

const double DataSet::mean() {
    if (CCDataSet.empty()) return 0.0;

    int sum = 0;
    for (const auto& data : CCDataSet) {
        sum += data.cc;
    }
    
    return sum / CCDataSet.size();
}

const double DataSet::stdDev() {
    if (CCDataSet.empty()) return 0.0;

    double m = mean();
    double variance = 0.0;

    for (const auto& data : CCDataSet) {
        variance += ((data.cc - m) * (data.cc - m));
    }

    // Sample standard deviation
    variance /= (CCDataSet.size() - 1);

    return sqrt(variance);
}

const double DataSet::cv() {
    double m = this->mean();
    return this->stdDev() / m;
}