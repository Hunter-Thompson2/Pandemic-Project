/*
Map header file
Project 2, CSCE 2110
created by Hunter Thompson
4/9/2020

The map is the main structure that holds all of the region nodes while in each node is all of the adjacent nodes
*/
#ifndef map_h
#define map_h
#include<string>
#include<iostream>
#include<vector>
#include"Node.hpp"


class Map{
    public:
        Map();
        Map(std::vector<std::vector<int>> tempMatrix, std::vector<int> tempPop, int size);  //constructors
        Node* getRegionAt(int index);                                                       //returns a specifc region
        int BFS(Node *nodeStart, Node *nodeEnd);                                            //breadthfirstsearch that returns distance
        void BFSClearer();                                                         //support function for bfs
        int shortest(Node *start, Node *end);                                   //combines BFS and clearer to get rid of some variable values in the nodes
        void setupRandom(int vaccines);                                 //the simulation with a random distribution of vaccine
        void setupEqual(int vaccines);                                  //simulation with equal distribution

        void cleaner();                                             //clears the map at the start of a simulation

        void closeness(int vaccines);                                 
        void degreeCentrality(int vaccines);                                    
        
        int getSize(){return size;};
    private:
        std::vector<Node> map;                                  //map of regions
        int size;                                               //size is how many regions


};
#endif
