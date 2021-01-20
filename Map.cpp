/*
Map source
Project 2, CSCE 2110
created by Hunter Thompson
4/11/2020

This file is the source code for the Map class

*/

#include"Map.hpp"

Map::Map(){}
Map::Map(std::vector<std::vector<int>> tempMatrix, std::vector<int> tempPop, int size){ //constructor makes the map
    this->size = size;
    for(int i = 0; i < size; i++){                          //this makes the nodes in the map
        Node node(tempPop[i], size);
        node.setID(i);
        map.push_back(node);
    }
    for(int i = 0; i < size; i++){                          //this makes their adjacency tables 
        for(int j = 0; j < size; j++){
            if(tempMatrix[i][j] == 1)
                map[i].addAdj(&map[j]);
        }
    }
}
Node* Map::getRegionAt(int index){          //returns specific node
    //return (new Node());
    return &map[index];
}

int Map::BFS(Node *nodeStart, Node *nodeEnd){       //breadth first search that returns shortest distance from start to end
                    
    std::vector<Node*> backlog;                     //stores teh next nodes to be visited

    int j = 0;                                   //iterator for the backlog
    if(nodeStart==nodeEnd)                       //returns 0 if theyre the same
        return 0;    
    for(int i = 0; i < size; i++){                 //loops through whole map
        for(Node *iter : nodeStart->getAdj()){         //loops through adjacency table to visit every node it connects to
            if(!(iter->getVisited())){                 //checks if its been here
                iter->setDistanceSrc(nodeStart->getDistanceSrc()+1);        //bases the distance of this node to the source off of how far the node that called it is and adding 1
                iter->setVisited(1);                            //marks it as visited
                if(iter == nodeEnd)                             //checks if its the node
                    return iter->getDistanceSrc();                 //returns distance in that node because that will be the shortest distance
                backlog.push_back(iter);                        //keeps going and adds it to back log if not
            }
        }
        if(backlog.size() > 0)
            nodeStart = backlog[j];
        j++;
        //backlog.erase(backlog.begin());
    }
    return -1;
}

void Map::BFSClearer(){                     //clears the nodes of visited and distance data
    for(int i = 0; i < size; i++){
        map[i].setDistanceSrc(0);
        map[i].setVisited(0);
    }
}

int Map::shortest(Node *start, Node *end){
    int returner;                                   //save the value returned by the bfs before its cleared
    returner = BFS(start, end);
    BFSClearer();                                   //clears the nodes of data like if they were visited
    return returner;    

}