//
//  main.cpp
//  
//
//  Created by Kale Erickson on 4/7/20. Finished later by Hunter Thompson
//#include "main.hpp"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

#include "Map.hpp"
#include "Node.hpp"
#include "Simulator.hpp"
#include "Intializer.hpp"
#include "IntializerHelper.hpp"


using namespace std;

int main(int argc, char *argv[]) {
    
    cout << endl << "===== Beginning Simulation =====" << endl;
    string inputFile;
    //check if file was passed to program
    if (argc > 1) {
        //if the file is passed grab it with inputFile
        inputFile = argv[1];
        cout << "Configuration file entered was : [" << inputFile << "]"<< endl << endl;
    }
    
    //exit if no input file is given
    else if (argc <= 1) {
        cout << "No input file given." << endl;
        return(0);
    }
    
    
    ifstream configFile;
    string   line;
    string   temp;
    
    //open file stream of inputFile
    configFile.open(inputFile);
    if (!configFile) {
        cout << "Unable to open file" << endl;
        exit(1);
    }
    //Process config file
    //counter for grabing config data (first line = refionFile etc)
    stringstream ss;
    string       popFile;
    string       regionFile;
    int          infA;
    int          infP;
    int          cRate;
    int          nVax;
    int          c=0;
    
    //while loop grabs line of inputFile and runs till end of file
    while(getline(configFile, line)){
        ss.str  (line);
        getline (ss, temp, ':');
        getline (ss, temp);
        if(c==0) popFile     = temp;
        if(c==1) regionFile  = temp;
        if(c==3) infA  = stoi(temp);
        if(c==4) infP  = stoi(temp);
        if(c==5) cRate = stoi(temp);
        if(c==6) nVax  = stoi(temp);
        ss.clear();
        c++;
    }
    c=0;
    configFile.close();
    
    cout << "Pop file provided: [" <<popFile << "]" << endl;
    cout << "Region file provided: [" <<regionFile << "]" << endl;
    cout << "Infected Area: "   << infA   << endl;
    cout << "Infectious Period: " << infP << endl;
    cout << "Contact Rate: " << cRate << endl;
    cout << "Number of Vax " << nVax << endl;
    
    //Run intializer constructor and pass inputFile
    Intializer builder(regionFile, popFile);
    //Grab intial CSV vector
    vector<vector<string>> adjMatrix = builder.readCSV();
    
    vector<int> regionPop = builder.readPOP();
    cout << endl << "Intial Region State" << endl;
    //print region of the intialRGS
    printPop(regionPop);
    printMatrix(adjMatrix, (builder.height), (builder.width));
    printList(adjMatrix, (builder.height), (builder.width));





    //Bottom part runs the sim
    //made by Hunter Thompson
    //5/9/2020
    cout << endl;
    adjMatrix.pop_back();
    int size = adjMatrix.size() - 1;
	vector<vector<int>> adjMatrixInt(size, std::vector<int>(size,0));
	for(int i = 1; i < size+1; i++){
		for(int j = 1; j < size+1; j++){
			adjMatrixInt[i-1][j-1] = stoi(adjMatrix[i][j]);
		}
	}
	Map map(adjMatrixInt, regionPop, size);

    Simulator sim(adjMatrixInt, regionPop, size,infA,cRate,infP,nVax);
    sim.runRandom();
    sim.runEqual();
    sim.runDegree();
    sim.runCloseness();
    vector<AfterReport> afterReports;
    afterReports = sim.getAfterReports();
    cout << "\nAfter Report\n";
    for(AfterReport report : afterReports){
        if(report.distribution == 'R')
            cout << "Random Distribution\n";
        else if(report.distribution == 'E')
            cout << "Equal Distribution\n";
        else if(report.distribution == 'D')
            cout << "Degree Centrality Distribution\n";
        else if(report.distribution == 'C')
            cout << "Closeness Centrality Distribution\n";
        cout << "Day of peak infection: " << report.peakDay << endl;
        cout << "Peak infected: " << report.peakInfected << endl;
        cout << "Total infected over simulation: " << report.totalInfected << endl;
        cout << "Last day of infection: " << report.finalDay - 1<< endl << endl;
    }

    return(0);
}
