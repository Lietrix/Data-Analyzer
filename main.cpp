#include "DataSet.h"
#include "CCData.h"
using namespace std;

vector<DataSet> IntervalDataSets(const DataSet& allData, double interval);
vector<DataSet> ConstantDataSets(const DataSet& allData, int constant);

int constant = 50;
double interval = 0.5;

int main() {
    //This program will currently only read in Data.txt
    ifstream infile("Data.txt");
    if(!infile) {
        cerr << "Unable to open file Data.txt";
        return 1;
    }
    ofstream ofile("Write.txt");
    if(!ofile) {
        cerr << "Unable to write to file Write.txt";
        return 1;
    }

   double cc;
   double year;
    DataSet allData("ALL DATA");
    while (infile >> cc >> year)
    {
        allData.addData(CCData(cc, year));
    }

    infile.close();
    allData.sortData();


    // Create interval DataSets
    //vector<DataSet> intervals = IntervalDataSets(allData, interval);

    // Create constant DataSets
    vector<DataSet> constants = ConstantDataSets(allData, constant);

    // Print Information of non-empty data sets
    for (auto& dataset : constants) {
        if(dataset.isEmpty()){
            continue;
        }
        dataset.printCSV(ofile);
    }

    ofile.close();
    
    return 0;
}

vector<DataSet> IntervalDataSets(const DataSet& allData, double interval) {
    double oldestYear = allData.getOldestTime();
    double newestYear = allData.getNewestTime();

    // Calculate the number of intervals
    int numberOfIntervals = (oldestYear - newestYear) / interval;
    // Vector to hold all the different datasets
    vector<DataSet> intervalDataSets;

    // Create a new dataset for each interval
    for (int i = 0; i <= numberOfIntervals; ++i) {
        double startYear = newestYear + (i * interval);
        double endYear = startYear + interval;
        
        // Create a meaningful title for each dataset
        string title = to_string(startYear) + " to " + to_string(endYear);
        DataSet intervalData(title);

        // Add the appropriate data to the interval dataset
        for (const auto& data : allData.getDataSet()) {
            if (data.year >= startYear && data.year < endYear) {
                intervalData.addData(data);
            }
        }

        // Add the interval dataset to the vector
        intervalDataSets.push_back(intervalData);
    }

    return intervalDataSets;
}

vector<DataSet> ConstantDataSets(const DataSet& allData, int constant) {
    vector<DataSet> constantDataSets;
    const auto& allDataPoints = allData.getDataSet();

    // Calculate the number of subsets
    int totalDataPoints = allDataPoints.size();
    int numberOfSubsets = (totalDataPoints + constant - 1) / constant; // Ceiling division

    // Loop to create each subset
    for (int i = 0; i < numberOfSubsets; ++i) {
        // Create a meaningful title for each dataset
        string title = "Subset " + to_string(i + 1);
        DataSet subset(title);

        // Add data points to the subset
        for (int j = i * constant; j < (i + 1) * constant && j < totalDataPoints; ++j) {
            subset.addData(allDataPoints[j]);
        }

        // Add the subset to the vector
        constantDataSets.push_back(subset);
    }

    return constantDataSets;
}