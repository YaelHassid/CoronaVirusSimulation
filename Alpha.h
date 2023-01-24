
#ifndef CORONAVIRUSSIMULATION_ALPHA_H
#define CORONAVIRUSSIMULATION_ALPHA_H
#include "SarsCov2.h"
#include <iostream>
#include <vector>
using namespace std;

class Alpha : public SarsCov2{
public:
    Alpha(const vector<string> &virusComb, char t, double p);

};



#endif //CORONAVIRUSSIMULATION_ALPHA_H
