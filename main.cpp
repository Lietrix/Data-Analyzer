#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include <utility>
using namespace std;

// Function prototypes
bool readFile(const string &fileName, vector<int> &ccData, vector<int> &yearData);
void findLargestCC(const vector<int> &ccData, const vector<int> &yearData, int &largestCC, int &correspondingYear);
double calculateMean(const vector<int> &ccData);
double calculateStdDev(const vector<int> &ccData, double mean);
double calculateCV(double stdDeviation, double mean);
void seperateYears(const vector<int> &yearData, vector<pair<int, int>> &yearIntervals);

int main() {
    string fileName;
    // Prompt user for file name
    cout << "Enter the name of the file to read: ";
    cin >> fileName;

    vector<int> ccData;  // Store CC values
    vector<int> yearData;  // Store corresponding years
    vector<pair<int,int>> yearIntervals;  // Store year and its occurrence count

    // Read data from file
    if (!readFile(fileName, ccData, yearData)) {
        return 1;  // Exit if file reading failed
    }

    // If data is not empty, process and display results
    if(!ccData.empty()){
        int largestCC, correspondingYear;
        
        // Find and display largest CC value and its corresponding year
        findLargestCC(ccData, yearData, largestCC, correspondingYear);
        cout << "Largest CC: " << largestCC << endl;
        cout << "Kya: " << correspondingYear << endl;

        // Calculate and display mean CC
        double meanCC = calculateMean(ccData);
        cout << "Mean CC: " << meanCC << endl;

        // Calculate and display standard deviation of CC
        double stdDeviation = calculateStdDev(ccData, meanCC);
        cout << "Standard Deviation CC: " << stdDeviation << endl;

        // Calculate and display coefficient of variation
        double CV = calculateCV(stdDeviation, meanCC);
        cout << "Coefficient of Variation (CV): " << CV << "%" << endl;
    }
    else {
        cout << "No data found." << endl;
    }

    return 0;  
}

// Read data from file and store in provided vectors
bool readFile(const string &fileName, vector<int> &ccData, vector<int> &yearData) {
    ifstream inFile(fileName);  
    if (!inFile) {
        cerr << "Failed to open " << fileName << endl;
        return false;
    }

    int cc, kya;
    // Read CC and year data pairs from file
    while (inFile >> cc >> kya) {
        ccData.push_back(cc);
        yearData.push_back(kya);
    }
    inFile.close();
    return true;
}

// Find the largest CC value and its corresponding year
void findLargestCC(const vector<int> &ccData, const vector<int> &yearData, int &largestCC, int &correspondingYear) {
    largestCC = ccData[0];
    int index = 0;
    for (int i = 1; i < ccData.size(); i ++) {
        if (ccData[i] > largestCC) {
            largestCC = ccData[i];
            index = i;
        }
    }
    correspondingYear = yearData[index];
}

// Calculate the mean of the CC values
double calculateMean(const vector<int> &ccData) {
    double totalCC = 0;
    for (int i = 0; i < ccData.size(); i++) {
        totalCC += ccData[i];
    }
    return totalCC / static_cast<double>(ccData.size());
}

// Calculate the standard deviation of the CC values
double calculateStdDev(const vector<int> &ccData, double mean) {
    double variance = 0.0;
    for (int i = 0; i < ccData.size(); i++) {
        variance += (ccData[i] - mean) * (ccData[i] - mean);
    }
    variance /= ccData.size();
    return sqrt(variance);
}

// Calculate the coefficient of variation
double calculateCV(double stdDeviation, double mean) {
    return (stdDeviation / mean) * 100.0;
}

// Separate years and count occurrences
void seperateYears(const vector<int> &yearData, vector<pair<int, int>> &yearIntervals) {
    if(yearData.empty()) {
        return;
    }

    int currentYear = yearData[0];
    int count = 1;

    for (int i = 1; i < yearData.size(); i++) {
        if(yearData[i] == currentYear) {
            count++;
        } else {
            yearIntervals.push_back({currentYear, count});
            currentYear = yearData[i];
            count = 1;
        }
    }
    yearIntervals.push_back({currentYear, count});
}