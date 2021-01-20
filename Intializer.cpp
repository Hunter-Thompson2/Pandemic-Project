//
//  Created by Kale Erickson on 4/7/20.


#include "Intializer.hpp"
//readCSV takes in the desired csv file and reads in the delimited information
//and outputs it to main
using namespace std;
vector<vector<string>> Intializer::readCSV() {
    vector<vector<string>> region;
    string   line;
    string   token;
    
    ifstream csvFile;
    csvFile.open(inputFile);
    //check if CSV file opens
    if (!csvFile) {
        cout << "Unable to open csv file exiting" << endl;
        exit(1);
    }
    stringstream ssc;
    //skips the first line of the csv since its just numbering
    //getline(csvFile, line);
    while(getline(csvFile, line)){
        ssc.str(line);
        region.push_back(vector<string>());
        int i = 0;
        //getline(ssc, token, ',')
        while(getline(ssc, token, ',')){
            region[height].push_back(token);
            i++;
        }
        width = i;
        ssc.clear();
        height++;
    }
    region.push_back(vector<string>());
    //cout << "Height of rectangle: " << height << endl;
    //cout << "Width  of rectangle: " << width << endl;
    csvFile.close();
    return region;
}

vector<int> Intializer::readPOP() {
    vector<int> popV;
    string   line;
    string   token;
    
    ifstream pFile;
    pFile.open(popFile);
    
    //check if CSV file opens
    if (!pFile) {
        cout << "Unable to open pop file exiting" << endl;
        exit(1);
    }
    stringstream ssp;
    while(getline(pFile, line)){
        ssp.str  (line);
        getline (ssp, line, ':');
        getline (ssp, line);
        popV.push_back(stoi(line));
        ssp.clear();
    }
    pFile.close();
    return popV;
    
}