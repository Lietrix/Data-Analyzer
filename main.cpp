#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include <utility>
#include <algorithm>  // For the min_element function
using namespace std;

// Function prototypes
bool readFile(const string &fileName, vector<int> &ccData, vector<int> &yearData);
void seperateYears(const vector<int> &ccData, const vector<int> &yearData, vector<pair<int, vector<int>>> &yearIntervals);
void findLargestCC(const vector<int> &ccData, int &largestCC);
void findSmallestCC(const vector<int> &ccData, int &smallestCC);
double calculateMean(const vector<int> &ccData);
double calculateStdDev(const vector<int> &ccData, double mean);
double calculateCV(double stdDeviation, double mean);
void displayStatsForYearIntervals(const vector<pair<int, vector<int>>> &yearIntervals);

int main() {
    string fileName;
    cout << "Enter the name of the file to read: ";
    cin >> fileName;

    vector<int> ccData;  // Store CC values
    vector<int> yearData;  // Store corresponding years
    vector<pair<int, vector<int>>> yearIntervals;

    if (!readFile(fileName, ccData, yearData)) {
        return 1;
    }

    seperateYears(ccData, yearData, yearIntervals);
    displayStatsForYearIntervals(yearIntervals);

    return 0;  
}

bool readFile(const string &fileName, vector<int> &ccData, vector<int> &yearData) {
    ifstream inFile(fileName);  
    if (!inFile) {
        cerr << "Failed to open " << fileName << endl;
        return false;
    }

    int cc, kya;
    while (inFile >> cc >> kya) {
        ccData.push_back(cc);
        yearData.push_back(kya);
    }
    inFile.close();
    return true;
}

void seperateYears(const vector<int> &ccData, const vector<int> &yearData, vector<pair<int, vector<int>>> &yearIntervals) {
    if(yearData.empty() || ccData.empty() || yearData.size() != ccData.size()) {
        return;
    }

    int currentYear = yearData[0];
    vector<int> currentYearCCs = {ccData[0]};

    for (int i = 1; i < yearData.size(); i++) {
        if(yearData[i] == currentYear) {
            currentYearCCs.push_back(ccData[i]);
        } else {
            yearIntervals.push_back({currentYear, currentYearCCs});
            currentYear = yearData[i];
            currentYearCCs = {ccData[i]};
        }
    }
    yearIntervals.push_back({currentYear, currentYearCCs});
}

void findLargestCC(const vector<int> &ccData, int &largestCC) {
    largestCC = ccData[0];
    for (int i = 1; i < ccData.size(); i++) {
        if (ccData[i] > largestCC) {
            largestCC = ccData[i];
        }
    }
}

void findSmallestCC(const vector<int> &ccData, int &smallestCC) {
    smallestCC = ccData[0];
    for (int i = 1; i < ccData.size(); i++) {
        if (ccData[i] < smallestCC) {
            smallestCC = ccData[i];
        }
    }
}

double calculateMean(const vector<int> &ccData) {
    double totalCC = 0;
    for (int i = 0; i < ccData.size(); i++) {
        totalCC += ccData[i];
    }
    return totalCC / static_cast<double>(ccData.size());
}

double calculateStdDev(const vector<int> &ccData, double mean) {
    double variance = 0.0;
    for (int i = 0; i < ccData.size(); i++) {
        variance += (ccData[i] - mean) * (ccData[i] - mean);
    }
    variance /= ccData.size();
    return sqrt(variance);
}

double calculateCV(double stdDeviation, double mean) {
    return (stdDeviation / mean) * 100.0;
}

void displayStatsForYearIntervals(const vector<pair<int, vector<int>>> &yearIntervals) {
    for (const auto &interval : yearIntervals) {
        int year = interval.first;
        const vector<int>& ccValues = interval.second;

        double meanCC = calculateMean(ccValues);
        cout << "Year: " << year << endl << "Mean CC: " << meanCC << endl;

        double stdDev = calculateStdDev(ccValues, meanCC);
        cout << "Standard Deviation CC: " << stdDev << endl;

        double CV = calculateCV(stdDev, meanCC);
        cout << "Coefficient of Variation (CV): " << CV << "%" << endl;

        int largest;
        findLargestCC(ccValues, largest);
        cout << "Largest CC: " << largest << endl;

        int smallest;
        findSmallestCC(ccValues, smallest);
        cout << "Smallest CC: " << smallest << endl;

        cout << "----------------------------" << endl;
    }
}