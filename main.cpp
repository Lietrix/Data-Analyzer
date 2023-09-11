#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

int main() {
    string fileName;
    cout << "Enter the name of the file to read: ";
    cin >> fileName;

    ifstream inFile(fileName);  // Open the file for reading

    if (!inFile) {  // Check if the file was opened successfully
        cerr << "Failed to open " << fileName << endl;
        return 1;  // Exit with an error code
    }
    
    vector<int> ccData;
    vector<int> yearData;

    int cc, kya;
    while (inFile >> cc >> kya) {  
        ccData.push_back(cc);
        yearData.push_back(kya);
    }


    if(!ccData.empty()){
        // Largest CC 
        int largest_cc = ccData[0];
        int index = 0;
        for (int i = 1; i < ccData.size(); i ++) {
            if (ccData[i] > largest_cc) {
                largest_cc = ccData[i];
                index = i;
            }
        }
        cout << "Largest CC: " << largest_cc << endl;
        cout << "Kya: " << yearData[index] << endl;

        // Mean CC
        double meanCC;
        for (int i = 0;)

    }
    else {
        cout << "No data found." << endl;
    }


    

    inFile.close();  // Close the file

    return 0;  
}