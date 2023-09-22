#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
using namespace std;

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

int main() {
    string fileName;
    cout << "Enter the name of the file to read: ";
    cin >> fileName;

    vector<int> ccData;
    vector<int> yearData;

    if (!readFile(fileName, ccData, yearData)) {
        return 1;
    }

    if(!ccData.empty()){
        int largestCC, correspondingYear;
        findLargestCC(ccData, yearData, largestCC, correspondingYear);
        cout << "Largest CC: " << largestCC << endl;
        cout << "Kya: " << correspondingYear << endl;

        double meanCC = calculateMean(ccData);
        cout << "Mean CC: " << meanCC << endl;

        double stdDeviation = calculateStdDev(ccData, meanCC);
        cout << "Standard Deviation CC: " << stdDeviation << endl;

        double CV = calculateCV(stdDeviation, meanCC);
        cout << "Coefficient of Variation (CV): " << CV << "%" << endl;
    }
    else {
        cout << "No data found." << endl;
    }

    return 0;  
}