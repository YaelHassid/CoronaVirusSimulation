
#ifndef CORONAVIRUSSIMULATION_OMICRON_H
#define CORONAVIRUSSIMULATION_OMICRON_H
#include "SarsCov2.h"
#include <iostream>
#include <vector>
using namespace std;

class Omicron : public SarsCov2{

public:
    Omicron(const vector<string> &virusComb, char t, double p);
};



#endif //CORONAVIRUSSIMULATION_OMICRON_H
