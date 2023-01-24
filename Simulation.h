#ifndef CORONAVIRUSSIMULATION_SIMULATION_H
#define CORONAVIRUSSIMULATION_SIMULATION_H
#include "SarsCov2.h"
#include <vector>

using namespace std;

class Simulation {
public:
    Simulation(int d, const vector<string>& t, int s, int time); //c'tor
    void addVirus(SarsCov2* v); //a function that builds the first generation of the simulation
    void fitTest(); //a function that checks the fit of each virus in the current population
    void start();
    static int getArandomNum(int lowest, int highest);
    static bool probRes(double prob);
    void individualUpdate(SarsCov2* virus) const;
    void groupUpdate(int weak1, int weak2);
    void printGen();
private:
    vector<SarsCov2*> currPopulation;
    vector<SarsCov2*> firstGeneration;
    vector<string> target;
    double dimension;
    int popSize;
    int simulationTime;
    SarsCov2* strongest = nullptr;
};


#endif //CORONAVIRUSSIMULATION_SIMULATION_H
