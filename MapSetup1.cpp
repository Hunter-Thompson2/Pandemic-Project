/*
MapSetup source
Project 2, CSCE 2110
created by Hunter Thompson
4/11/2020

This file is an extension to the Map source files to add new functions related to a specific component
The Components are Random distribution and Equal Distribution

*/
#include"Map.hpp"

void Map::setupRandom(int vaccines){            //sets up a random distribution based on its location in the vector

    cleaner();                                      //clears any previous simulation data
    for(int i = 0; i < size; i++){                      //loops thorugh teh map
        if(vaccines >= map[i].getPopulation()){         //checks if theres enough vaccine for teh whole region
            map[i].setVaccinated(map[i].getPopulation());   //if there is, the whole population gets changed to vaccinate
            map[i].setSusceptible(0);                          //no more suscpetible after vaccination
            vaccines = vaccines - map[i].getPopulation();       //subjects vaccines
            for(int j = 0; j < map[i].getPopulation(); j++){   //makes changes to the actual agents 
                map[i].getAgents()->at(j).health = 'V';
            }
        }
        else
        {
            for(int j = 0; j < map[i].getPopulation(); j++){        //loops through population of node that is the last stop
                if(vaccines > 0 && map[i].getAgents()->at(j).health != 'V'){  //checks if they arent already vaccinated and that there are vaccines left
                    map[i].setVaccinated(map[i].getVaccinated() + 1);           //increments one at a time
                    map[i].setSusceptible(map[i].getSusceptible() -1);      //subtracts a susceptible population total
                    map[i].getAgents()->at(j).health = 'V';          //sets the agents health to vaccinated       
                    vaccines--;
                }
                if(vaccines==0)                     //stops it if it runs out of vaccines
                    return;
            }
        }
        
    }

}

void Map::setupEqual(int vaccines){  //sets up simulation where its equal
    cleaner();
    int i = 0;                          //index keeper for the map
    int k[size] = {0};              //an array of indexs for each individual region to know where to put a vaccine in the agent table
    int count = 0;                  //an iterator that gets reset everytime a vaccine is taken. This is to end the loop if theres no more spots for vaccines
    while(vaccines){                        //just loops until out of vaccines. The goal is to give one vaccine to every region every loop
        if(map[i%size].getPopulation()>map[i%size].getVaccinated()){    //checks if the whole population is vaccinated already
            map[i%size].setVaccinated(map[i%size].getVaccinated()+1);   //adds one vaccinated
            map[i%size].getAgents()->at(k[i%size]).health = 'V';
            //map[i].getAgents()->at(j).health = 'V';
            k[i%size] += 1;                         //increments for this specifc counter to keep its place for this region only
            map[i%size].setSusceptible(map[i%size].getSusceptible() - 1);  //subtracts one susceptible
            vaccines--;
            count = 0;
        }
        else
        {
            count++;
        }
        
        i++;
        if(count==size-1)
            break;

    }
}

void Map::cleaner(){            //cleans the map after a simulation by replacing the nodes with new ones that have the same population
    for(int i = 0; i < size; i++){
        map[i].setInfected(0);
        map[i].setRemoved(0);
        map[i].setVaccinated(0);
        map[i].setSusceptible(map[i].getPopulation());
        for(int j = 0; j < map[i].getPopulation(); j++){
            if(!(map[i].getAgents()->at(j).health == 'S'))
                map[i].getAgents()->at(j).health = 'S';
            map[i].getAgents()->at(j).period = 1;
        }
        //Node temp(map[i].getPopulation(), size);
        //map[i] = temp;
    }
}