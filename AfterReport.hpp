/*
after Reports struct
Project 2, CSCE 2110
created by Hunter Thompson
5/9/2020

This struct saves all the data collected during the experiment

*/
#ifndef afterReport_h
#define afterReport_h

struct AfterReport{
    AfterReport():peakInfected(0),peakDay(0), finalDay(0), totalInfected(0), distribution('a'){}
    int peakInfected;       //saves the peak infected
    int peakDay;            //the day of the peak infected
    int finalDay;           //last day of the sim
    int totalInfected;      //how many got infected overall
    char distribution;      //marks which distribution its saving for

};
#endif