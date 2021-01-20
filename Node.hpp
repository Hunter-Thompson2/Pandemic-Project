/*
Node header file
Project 2, CSCE 2110
created by Hunter Thompson
4/9/2020
this is the node class that makes up the map. It represents one region 
*/
#ifndef node_h
#define node_h
#include<string>
#include<iostream>
#include<vector>
#include "Agent.hpp"

class Node{
    public:
        Node(int population, int size);
        void addAdj(Node *noder);           //adds a node to the adjacency list

        //lists
        std::vector<Node*> getAdj(){return adjacent;};
        std::vector<Agent>* getAgents(){return &agents;};
        //population totals
        int getPopulation(){return population;};
        void setPopulation(int temp){population = temp;};
        int getVaccinated(){return vaccinated;};
        void setVaccinated(int temp){vaccinated = temp;};
        int getRemoved(){return removed;};
        void setRemoved(int temp){removed = temp;};
        int getInfected(){return infected;};
        void setInfected(int temp){infected = temp;};
        int getSusceptible(){return susceptible;};
        void setSusceptible(int temp){susceptible = temp;};
        //variables for search
        bool getVisited(){return visited;};
        void setVisited(int temp){visited=temp;};
        int getDistanceSrc(){return distanceSrc;};
        void setDistanceSrc(int temp){distanceSrc = temp;};
        int getID(){return ID;};
        void setID(int temp){ID = temp;};
    private:
        int population; //total population
        int vaccinated;  //total vaccinated
        int removed;    //total removed
        int infected;   //total infected
        int susceptible;    //total susceptible
        std::vector<Node*> adjacent;    //adjacency table
        std::vector<Agent> agents;  //the population of agents
        int size;   //size of the map, not really used much
        bool visited;   //visited for search
        int distanceSrc;    //distance from search start for BFS
        int ID;


};
#endif