/*
MapSetup source
Project 2, CSCE 2110
created by Hunter Thompson
5/7/2020

This file is an extension to the Map source files to add new functions related to a specific component
The Components are Adjacency centrality and distance centrality

*/
#include "Map.hpp"


//distribution according to degree centrality. Degree being the degree of the node
void Map::degreeCentrality(int vaccines){
    //std::cout<< "this works" << std::endl;
    cleaner();          //clears the map if it isnt already
    //vector<Node *> sorter;
    std::vector<Node *> sorter;     //a vector that will be sorted so that the nodes can have vaccines distributed more like the random distribution
    int degrees[size];      //saves the node degrees while also being sorted in the same way
    //loads all the regions in the map into the sorter vector as pointers so that their contents can still be modified wihtout changing map order
    for(int i = 0; i < size; i++){
        sorter.push_back(&map[i]);
        degrees[i] = map[i].getAdj().size();        //saves each nodes degree
    }
    //sorts the sorter vector
    for(int i = 0; i < size; i++){
        int biggest = i;        //tracks the index of the biggest degree
        for(int j = i; j < size; j++){          //starts from i because everything behind it is already sorted
            if(degrees[j] > degrees[biggest])   //finds the biggest one after the i position
                biggest = j;
        }
        int temp = degrees[i];              //the next couple lines just handle the swapping in the two vectors
        Node *tempNode = sorter[i];
        degrees[i] = degrees[biggest];
        sorter[i] = sorter[biggest];
        degrees[biggest] = temp;
        sorter[biggest] = tempNode;
    }

    for(int i = 0; i < size; i++){                      //loops thorugh teh map
        if(vaccines >= sorter[i]->getPopulation()){         //checks if theres enough vaccine for teh whole region
            sorter[i]->setVaccinated(sorter[i]->getPopulation());   //if there is, the whole population gets changed to vaccinate
            sorter[i]->setSusceptible(0);                          //no more suscpetible after vaccination
            vaccines = vaccines - sorter[i]->getPopulation();       //subjects vaccines
            for(int j = 0; j < sorter[i]->getPopulation(); j++){   //makes changes to the actual agents 
                sorter[i]->getAgents()->at(j).health = 'V';
            }
        }
        else
        {
            for(int j = 0; j < sorter[i]->getPopulation(); j++){        //loops through population of node that is the last stop
                if(vaccines > 0 && sorter[i]->getAgents()->at(j).health != 'V'){  //checks if they arent already vaccinated and that there are vaccines left
                    sorter[i]->setVaccinated(sorter[i]->getVaccinated() + 1);           //increments one at a time
                    sorter[i]->setSusceptible(sorter[i]->getSusceptible() -1);      //subtracts a susceptible population total
                    sorter[i]->getAgents()->at(j).health = 'V';          //sets the agents health to vaccinated       
                    vaccines--;
                }
                if(vaccines==0)                     //stops it if it runs out of vaccines
                    return;
            }
        }
        
    }


    //for(int i = 0; i < size; i++)
    //    std::cout << degrees[i] << std::endl;
    //for(Node *temp : sorter)
    //    std::cout << temp->getPopulation() << std::endl;
}

//sorts by closeness centrality. closeness meaning the nodes with the shortest average distance to every other node
void Map::closeness(int vaccines){
    cleaner();              //clears the map if it isnt already
    std::vector<Node *> sorter;     //same as before
    double dist[size];          //saved as doubles because it makes the averages more accurate
    //loads them into sorter
    for(int i = 0; i < size; i++)
        sorter.push_back(&map[i]);
    //this section determines the shortest average distance for each node using the shortest fucntion in map
    for(int i = 0; i < size; i++){          //loops through every node for every node
        int sum = 0;                        //the sum of all the shortest distances to every other node
        for(int j = 0; j < size; j++){          //loops through every node
            sum += shortest(sorter[i], sorter[j]);      //adds the shortest distance to every node 
        }
        dist[i] = sum / (double)(size - 1);         //saves the average
    }


    //sorts like the last one except by smallest value instead of largest
    for(int i = 0; i < size; i++){
        int smallest = i;
        for(int j = i; j < size; j++){
            if(dist[j] < dist[smallest])
                smallest = j;
            //else if(dist[j] == dist[smallest] && )
        }
        double temp = dist[i];
        Node *tempNode = sorter[i];
        dist[i] = dist[smallest];
        sorter[i] = sorter[smallest];
        dist[smallest] = temp;
        sorter[smallest] = tempNode;
    }
    /*for(int i = 0; i < size; i++){
        int smallest = i;
        for(int j = i; j <size; j++){
            if(dist[j] < dist[smallest] )
                smallest = j;
        }
        int temp = dist[i];
        

    }*/

    for(int i = 0; i < size; i++){                      //loops thorugh teh map
        if(vaccines >= sorter[i]->getPopulation()){         //checks if theres enough vaccine for teh whole region
            sorter[i]->setVaccinated(sorter[i]->getPopulation());   //if there is, the whole population gets changed to vaccinate
            sorter[i]->setSusceptible(0);                          //no more suscpetible after vaccination
            vaccines = vaccines - sorter[i]->getPopulation();       //subjects vaccines
            for(int j = 0; j < sorter[i]->getPopulation(); j++){   //makes changes to the actual agents 
                sorter[i]->getAgents()->at(j).health = 'V';
            }
        }
        else
        {
            for(int j = 0; j < sorter[i]->getPopulation(); j++){        //loops through population of node that is the last stop
                if(vaccines > 0 && sorter[i]->getAgents()->at(j).health != 'V'){  //checks if they arent already vaccinated and that there are vaccines left
                    sorter[i]->setVaccinated(sorter[i]->getVaccinated() + 1);           //increments one at a time
                    sorter[i]->setSusceptible(sorter[i]->getSusceptible() -1);      //subtracts a susceptible population total
                    sorter[i]->getAgents()->at(j).health = 'V';          //sets the agents health to vaccinated       
                    vaccines--;
                }
                if(vaccines==0)                     //stops it if it runs out of vaccines
                    return;
            }
        }
        
    }





}