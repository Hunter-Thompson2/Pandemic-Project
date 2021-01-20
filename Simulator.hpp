/*
Simulator class
Project 2, CSCE 2110
created by Hunter Thompson
5/9/2020

This is the header file to the simulator class. This class contains a map object and handles the running of the simulation

*/
#ifndef Sim_h
#define Sim_h
#include<string>
#include<iostream>
#include<vector>
#include <iomanip>
#include"Map.hpp"
#include"AfterReport.hpp"


class Simulator{
    public:
        Simulator(std::vector<std::vector<int>> tempMatrix, std::vector<int> tempPop, int size, int infectedArea, int infectionRate, int cureTime, int vaccines);
        void runEqual();    //runs the equal distribution method
        void runRandom();   //runs random distribution
        void runDegree();   //runs degree centrality distribution
        void runCloseness();    // runs closeness centrality distribution
        void runDay();          //runs each individual day of the simulation
        void runner(char distribution);     //this function gets called in the run functions after the map setup to start the sim
        std::vector<AfterReport> getAfterReports(){return afterReports;};   //returns the after reports
    private:
        Map map;        //the map that contains the regions and agents
        std::vector<AfterReport> afterReports;  //a vector of structures that keep track of all the results to be displayed after
        int infectedArea;           //the start region of the infection
        int infectionRate;          //the rate at which agents spread the infection
        int cureTime;               //how long theyre infected
        int vaccines;               //how many vaccines available

};
#endif