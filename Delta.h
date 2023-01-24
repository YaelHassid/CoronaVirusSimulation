#ifndef CORONAVIRUSSIMULATION_DELTA_H
#define CORONAVIRUSSIMULATION_DELTA_H
#include "SarsCov2.h"
#include <iostream>
#include <vector>
using namespace std;

class Delta : public SarsCov2{
public:
    Delta(const vector<string> &virusComb, char t, double p);

};


#endif //CORONAVIRUSSIMULATION_DELTA_H
