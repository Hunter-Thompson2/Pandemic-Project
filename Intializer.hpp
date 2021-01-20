//
//  Created by Kale Erickson on 4/7/20.

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

class Intializer {
    std::string inputFile;
    std::string popFile;
public:
    Intializer(std::string inputFile, std::string popFile):
        inputFile(inputFile),
        popFile(popFile)
    {}
    std::vector<std::vector<std::string>> readCSV();
    std::vector<int> readPOP();
    int height = 0;
    int width  = 0;
};
