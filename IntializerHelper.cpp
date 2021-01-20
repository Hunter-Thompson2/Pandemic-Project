//
//  Created by Kale Erickson on 4/7/20.

#include "IntializerHelper.hpp"
//readCSV takes in the desired csv file and reads in the delimited information
//and outputs it to main
using namespace std;
void printMatrix (vector<vector<string>>& regionState, int height, int width) {
    //Print function takes in the vector that wants to be printed
    //Along with the height and width
    cout << " -";
    for(int i = 0 ; i < width; i++) {
        cout << "--" ;
    }
    cout << endl;
    for(int i = 0; i < height; i++) {
        for (int j=0; j < width; j++) {
            if (j==0) cout << "| ";
            cout << regionState[i][j] << " ";
            if (j==(width-1)) cout << "|" ;
        }
        cout << endl;
    }
    cout << " -";
    for(int i = 0 ; i < width; i++) {
        cout << "--" ;
    }
    cout << endl;
}

void printList (vector<vector<string>>& regionState, int height, int width) {
    //Print function takes in the vector that wants to be printed
    //Along with the height and width
    cout << endl;
    for(int i = 1; i < height; i++) {
        cout << i << ": ";
        for (int j=1; j < width; j++) {
            if (stoi(regionState[i][j]) == 1) {
                cout << j << " ";
            }
        }
        cout << endl;
    }
    cout << endl;
}

void printPop (vector<int> popV) {
    cout << "Regional Population" << endl;
    for (int i = 0; i < popV.size(); i++ ) {
        cout << (i+1) << " " << popV[i] << endl;
    }
    cout << endl;
}