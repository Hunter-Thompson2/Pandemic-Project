#include"Node.hpp"

Node::Node(int population, int size){       //constructor that just makes default value with a blank population
    this->population = population;
    vaccinated = 0;
    removed = 0;
    infected = 0;
    susceptible = population;
    visited = false;
    this->size = size;
    distanceSrc = 0;
    for(int i = 0; i < population; i++){    //blank agents that start as susceptible and 0 timer
        agents.push_back(Agent());
    }
}

void Node::addAdj(Node *noder){         //adds to adjacency table
    adjacent.push_back(noder);
}

