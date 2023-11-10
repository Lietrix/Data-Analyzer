#include "DataSet.h"
#include "CCData.h"
#include <fstream>
using namespace std;

int main() {
    //This program will currently only read in Data.txt
    ifstream infile("Data.txt");
    if(!infile) {
        cerr << "Unable to open file Data.txt";
        return 1;
    }

   double cc;
   double year;
    DataSet allData("ALL DATA");
    while (infile >> cc >> year)
    {
        allData.addData(CCData(cc, static_cast<int>(year * 1000000) + 1));
    }
    allData.sortData();
    //allData.printInfo();
    
    infile.close();
    return 0;
}