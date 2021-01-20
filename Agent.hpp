/*
Agent header file
Project 2, CSCE 2110
created by Hunter Thompson
4/11/2020

The agent struct is to simulate a person in a population. Each one is an individual entity with a health status.
This file doesn't need a cpp.
*/
#ifndef agent_h
#define agent_h
struct Agent{
    Agent():health('S'),period(1){}         //contructor to make it susceptible and start the timer at 0
    char health;                            //tells the status of the individual
    int period;                             //how long they're gonna be sick
};
#endif