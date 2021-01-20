#include "Simulator.hpp"
using namespace std;
Simulator::Simulator(std::vector<std::vector<int>> tempMatrix, std::vector<int> tempPop, int size, int infectedArea, int infectionRate, int cureTime, int vaccines){

    map = Map(tempMatrix, tempPop, size);           //generates the map from the parameters
    this->infectedArea = infectedArea - 1;          //the area is designated by the index in the actual object
    this->infectionRate = infectionRate;
    this->cureTime = cureTime;
    this->vaccines = vaccines;
}
//handles running equal distribution
void Simulator::runEqual(){
    struct AfterReport temp;                //this adds a new after report to be saved in the afterReports vector
    temp.distribution = 'E';                //marks it as an equal distribution test
    afterReports.push_back(temp);           
    cout << "\nRunning Simulation with Equal Distribution" << endl;
    map.setupEqual(vaccines);               //distributes vaccines
    runner('E');                            //tells the runner what the type of distribution is
}
//handles running random distribution
void Simulator::runRandom(){
    struct AfterReport temp;                //same structure as before
    temp.distribution = 'R';
    afterReports.push_back(temp);    
    cout << "\nRunning Simulation with Random Distribution" << endl;
    map.setupRandom(vaccines);
    runner('R');
}
//handles running degree centrality distribution
void Simulator::runDegree(){            //same structure as before
    struct AfterReport temp;
    temp.distribution = 'D';
    afterReports.push_back(temp);
    cout <<"\nRunning Simulation with Highest Degree Centrality Distribution " << endl;
    map.degreeCentrality(vaccines);
    runner('D');
}
//handles running closeness centrality distribution
void Simulator::runCloseness(){             //same structure as before
    struct AfterReport temp;
    temp.distribution = 'C';
    afterReports.push_back(temp);
    cout << "\nRunning Simulation with Closeness Centrality Distribution" << endl;
    map.closeness(vaccines);
    runner('C');
}
//handles actually running the sim. This functino is usually called in the distribution runners
void Simulator::runner(char distribution){          //takes the char that marks the type of distribution for the after reports
    //map.setupRandom(vaccines);
    int finalInfect = 0;                          //tracks how many infected over whole sim
    int totalInfected = 1;                          //trackes how many infected per day(Not the best name)
    //for(int i = 0; i < map.getSize(); i++){
    //    totalInfect += map.getRegionAt(i)->getInfected();
    //}
    //cout << infectedArea << endl;
    if(map.getRegionAt(infectedArea)->getVaccinated() != map.getRegionAt(infectedArea)->getPopulation()){       //sets the first infected
        map.getRegionAt(infectedArea)->setInfected(1);                                                          //doesnt start if theyre vaccinated
        map.getRegionAt(infectedArea)->setSusceptible( map.getRegionAt(infectedArea)->getSusceptible()-1);
        map.getRegionAt(infectedArea)->getAgents()->at(map.getRegionAt(infectedArea)->getAgents()->size()-1).health = 'I';
    }
    else{

    }
    cout << "\nDay " << 0 << endl;                  //prints the current day which is 0
    for(int j = 0; j < map.getSize(); j++){         //prints current state
        cout << j + 1 << "POP: " << left << setw(6) << map.getRegionAt(j)->getPopulation();
        cout << "S: " << left << setw(6) << map.getRegionAt(j)->getSusceptible();
        cout << "I: " << left << setw(6) << map.getRegionAt(j)->getInfected();
        cout << "R: " << left << setw(6) << map.getRegionAt(j)->getRemoved();
        cout << "V: " << left << setw(6) << map.getRegionAt(j)->getVaccinated();
        cout << endl;
    }
    int dayCount = 1;                       //tracks the day
    while(totalInfected != 0){              //handles the loop for each day. stops when no one still infected 
        totalInfected = 0;              //resets it everyday
        runDay();                       //runs the day sim
        for(int i = 0; i < map.getSize(); i++){         //retracks the totalinfected to see if it should keep looping the next time
            totalInfected += map.getRegionAt(i)->getInfected();
            finalInfect += map.getRegionAt(i)->getInfected();               //adds to the final infected without reseting every turn
        }
        cout << "\nDay " << dayCount << endl;               //prints the day
        for(int i = 0; i < afterReports.size(); i++){       //saves to the after report for the 
            if(afterReports[i].distribution == distribution){         //checks if the marks match  
                if(totalInfected > afterReports[i].peakInfected){   //only saves if it is larger than whats currently saved
                    afterReports[i].peakInfected = totalInfected;       //saves highest infected
                    afterReports[i].peakDay = dayCount;             //saves the day of the highest infected
                }
            }
        }
        dayCount++;                 //increases day count
        for(int j = 0; j < map.getSize(); j++){             //prints current state
            cout << j + 1 << "POP: " << left << setw(6) << map.getRegionAt(j)->getPopulation();
            cout << "S: " << left << setw(6) << map.getRegionAt(j)->getSusceptible();
            cout << "I: " << left << setw(6) << map.getRegionAt(j)->getInfected();
            cout << "R: " << left << setw(6) << map.getRegionAt(j)->getRemoved();
            cout << "V: " << left << setw(6) << map.getRegionAt(j)->getVaccinated();
            cout << endl;
        }
    }
    for(int i = 0; i < afterReports.size(); i++){               //after the whole sim runs, it saves data on the last day 
        if(afterReports[i].distribution == distribution){
            afterReports[i].finalDay = dayCount;
            afterReports[i].totalInfected = finalInfect;            //saves how many were infected in total
        }
    }
}
void Simulator::runDay(){
    //Map temp = map;
    int justTurned[map.getSize()]{0};               //saves which regions just got infected for every day

    //infects adjacent nodes
    for(int i = 0; i < map.getSize(); i++){            //loops through every regoin 
        //cout << 1 << endl;        
        if(map.getRegionAt(i)->getInfected() > map.getRegionAt(i)->getPopulation() / 2){        //spreads infection if it reaches half the population in a region
            for(Node *temp : map.getRegionAt(i)->getAdj()){     //loops through the vector of pointer nodes saved in each node to know what its adjacent to
                //cout << 11 << endl;
                if(temp->getInfected() == 0 && temp->getSusceptible() > 0){     //if theyre not infected, it infects them
                    //cout << 12 << endl;
                    temp->setInfected(1);
                    temp->setSusceptible( temp->getSusceptible()-1);
                    temp->getAgents()->at(temp->getAgents()->size()-1).health = 'I';
                    justTurned[temp->getID()] = 1;
                }
            }
        }
        //infects agents in the node
        int infectedTurn;       //variable that saves how many new infected need to be added this turn
        infectedTurn = map.getRegionAt(i)->getInfected() * infectionRate;// + map.getRegionAt(i)->getInfected();
        int iter = 0;           //iterator for the agents vector
        while(infectedTurn != 0 && justTurned[i] != 1){         //loops until it distributes all the infections
            if(map.getRegionAt(i)->getAgents()->at(iter).health == 'S'){        //checks if an agent is susceptible
                map.getRegionAt(i)->setInfected(map.getRegionAt(i)->getInfected() + 1);     //changes totals
                map.getRegionAt(i)->setSusceptible(map.getRegionAt(i)->getSusceptible() - 1);   //changes totals
                map.getRegionAt(i)->getAgents()->at(iter).health = 'I';         //sets the agent to infected
                infectedTurn--;         //subtracts one from how many infections need to be distributed
                
            }
            iter++;
            if(iter == map.getRegionAt(i)->getPopulation())             //ends loop if there arent any more susceptibles
                break;
        }
        //cures infected agents who reach the cure time
        if(map.getRegionAt(i)->getInfected() > 0){          //if the region is infected
            for(int j = 0; j < map.getRegionAt(i)->getPopulation(); j++){   //loops through population of agents
                //checks if hte agent has reached the cure time and if it hasnt, it adds a day. 
               if(map.getRegionAt(i)->getAgents()->at(j).health == 'I' && map.getRegionAt(i)->getAgents()->at(j).period == cureTime){
                    map.getRegionAt(i)->getAgents()->at(j).health = 'R';        //sets it to removed
                    map.getRegionAt(i)->setRemoved(map.getRegionAt(i)->getRemoved() + 1);   //changes totals
                   map.getRegionAt(i)->setInfected(map.getRegionAt(i)->getInfected() - 1);
               }
               else if(map.getRegionAt(i)->getAgents()->at(j).health == 'I' && justTurned[i] != 1)      //checks if the agent is infected
              {
                   map.getRegionAt(i)->getAgents()->at(j).period++;     //adds a day closer to the cure time for the agent
               }
            
            }
        }

    }


}