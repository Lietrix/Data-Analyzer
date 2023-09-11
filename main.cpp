#include <iostream>
#include <fstream>
#include <string>

int main() {
    std::string fileName;
    std::cout << "Enter the name of the file to read: ";
    std::cin >> fileName;

    std::ifstream inFile(fileName);  // Open the file for reading

    if (!inFile) {  // Check if the file was opened successfully
        std::cerr << "Failed to open " << fileName << std::endl;
        return 1;  // Exit with an error code
    }

    std::string line;
    while (std::getline(inFile, line)) {  // Read the file line by line
        std::cout << line << std::endl;   // Display each line
    }

    inFile.close();  // Close the file

    return 0;  // Exit successfully
}