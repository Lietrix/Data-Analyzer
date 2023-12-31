#include "DataSet.h"


DataSet::DataSet() {
    // initiate empty Data Set
    this->title = "NO NAME";
}

DataSet::DataSet(std::string name) {
    this->title = name;
}

 DataSet::~DataSet() {
    //destructor
 }

void DataSet::addData(const CCData &data){
    this->CCDataSet.push_back(data);
}

const void DataSet::printInfo(){
    //std::cout << "Set: " << this->title << std::endl;
    std::cout << "-------------------------------------" << std::endl;
    std::cout << "Time Range(millions): " << this->newestTime() << " - " << this->oldestTime() << std::endl;
    std::cout << "CC Range: " << this->smallestCC() << " - " << this->largestCC() << std::endl;
    std::cout << "CV: " << this->cv() << std::endl;
    std::cout << "-------------------------------------" << std::endl << std::endl;
}

const void DataSet::printCSV(std::ofstream &ofile) {
    // Time Range
    ofile << this->newestTime() << " - " << this->oldestTime() << ", ";
    // CC Range
    ofile << this->smallestCC() << " - " << this->largestCC() << ", ";
    // CV
    ofile << this->cv() << std::endl;
}

void DataSet::sortData() {
    std::sort(CCDataSet.begin(), CCDataSet.end(), [](const CCData& a, const CCData& b) {
        return a.year < b.year;
    });
}


const double DataSet::getOldestTime() const {
    return oldestTime();
}
    
const double DataSet::getNewestTime() const {
    return newestTime();
}

std::vector<CCData> DataSet::getDataSet() const {
    return CCDataSet;
}

bool DataSet::isEmpty() {
    return CCDataSet.empty();
}

const double DataSet::largestCC() {
    double maxCC = 0;
    // This value should get overwritten

    for (const auto& data : CCDataSet) {
        if (data.cc > maxCC) {
            maxCC = data.cc;
        }
    }
    return maxCC;
}

const double DataSet::smallestCC(){
    int minCC = 10000;
    // This value should get overwritten

    for (const auto& data : CCDataSet) {
        if (data.cc < minCC) {
            minCC = data.cc;
        }
    }
    return minCC;
}

const double DataSet::oldestTime() const {
    double oldestYear = 0;
    // This value should get overwritten

    for (const auto& data : CCDataSet) {
        if (data.year > oldestYear) {
            oldestYear = data.year;
        }
    }
    return oldestYear;
}

const double DataSet::newestTime() const {
    double newestYear = 100000;
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
    if (CCDataSet.size() == 1) return 0.0;
    double m = this->mean();
    return this->stdDev() / m;
}