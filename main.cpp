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
void displayStatsForYearIntervals(const vector<pair<int, vector<int>>> &yearIntervals, const string &writeFileName);
void writeIntervalComparison(const vector<pair<int, vector<int>>> &group1, 
                             const vector<pair<int, vector<int>>> &group2, 
                             ofstream &outFile);

int main() {
    string readName, writeName;
    cout << "Enter the name of the file to read: ";
    cin >> readName;
    cout << endl << "Enter the name of the file to write to: ";
    cin >> writeName;

    vector<int> ccData;  // Store CC values
    vector<int> yearData;  // Store corresponding years
    vector<pair<int, vector<int>>> yearIntervals;

    if (!readFile(readName, ccData, yearData)) {
        return 1;
    }

    seperateYears(ccData, yearData, yearIntervals);

    ofstream outFile(writeName);
    if (!outFile) {
        cerr << "Failed to open " << writeName << " for writing." << endl;
        return 1;
    }

    // Optional: Write header to the file
    outFile << "Subset1 Years, n, Mean, StdDev, CV, Max, Min, Subset2 Years, n, Mean, StdDev, CV, Max, Min\n";

    for (int i = 0; i < yearIntervals.size(); ++i) {
        vector<pair<int, vector<int>>> group1(yearIntervals.begin(), yearIntervals.begin() + i + 1);
        vector<pair<int, vector<int>>> group2(yearIntervals.begin() + i + 1, yearIntervals.end());
        
        if (!group2.empty()) {
            writeIntervalComparison(group1, group2, outFile);
        }
    }

    outFile.close();
    //write complete, no errors!
    cout << "Data written to " << writeName;

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

void displayStatsForYearIntervals(const vector<pair<int, vector<int>>> &yearIntervals, const string &writeFileName) {
    ofstream outFile(writeFileName);
    if (!outFile) {
        cerr << "Failed to open " << writeFileName << " for writing." << endl;
        return;
    }

    // Optional: write header row
    outFile << "Year, n, Mean, StdDev, CV, Max, Min\n";

    for (const auto &interval : yearIntervals) {
        int year = interval.first;
        const vector<int>& ccValues = interval.second;

        double meanCC = calculateMean(ccValues);
        double stdDev = calculateStdDev(ccValues, meanCC);
        double CV = calculateCV(stdDev, meanCC);

        int largest;
        findLargestCC(ccValues, largest);
        int smallest;
        findSmallestCC(ccValues, smallest);

        outFile << year << ", " << ccValues.size() << ", " << meanCC << ", " 
                << stdDev << ", " << CV << ", " << largest << ", " << smallest << "\n";
    }

    outFile.close();
    cout << "Statistics written to " << writeFileName << endl;
}

void writeIntervalComparison(const vector<pair<int, vector<int>>> &group1, 
                             const vector<pair<int, vector<int>>> &group2, 
                             ofstream &outFile) {
    // Compute and write stats for group1
    vector<int> combinedCC1;
    int startYear1 = group1.front().first;
    int endYear1 = group1.back().first;
    for (const auto &interval : group1) {
        combinedCC1.insert(combinedCC1.end(), interval.second.begin(), interval.second.end());
    }
    outFile << startYear1 << "-" << endYear1 << ", " << combinedCC1.size() 
            << ", " << calculateMean(combinedCC1) << ", " 
            << calculateStdDev(combinedCC1, calculateMean(combinedCC1)) << ", " 
            << calculateCV(calculateStdDev(combinedCC1, calculateMean(combinedCC1)), calculateMean(combinedCC1)) << ", " 
            << *max_element(combinedCC1.begin(), combinedCC1.end()) << ", " 
            << *min_element(combinedCC1.begin(), combinedCC1.end()) << ", ";

    // Compute and write stats for group2
    vector<int> combinedCC2;
    int startYear2 = group2.front().first;
    int endYear2 = group2.back().first;
    for (const auto &interval : group2) {
        combinedCC2.insert(combinedCC2.end(), interval.second.begin(), interval.second.end());
    }
    outFile << startYear2 << "-" << endYear2 << ", " << combinedCC2.size() 
            << ", " << calculateMean(combinedCC2) << ", " 
            << calculateStdDev(combinedCC2, calculateMean(combinedCC2)) << ", " 
            << calculateCV(calculateStdDev(combinedCC2, calculateMean(combinedCC2)), calculateMean(combinedCC2)) << ", " 
            << *max_element(combinedCC2.begin(), combinedCC2.end()) << ", " 
            << *min_element(combinedCC2.begin(), combinedCC2.end()) << "\n";
}