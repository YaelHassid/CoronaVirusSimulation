#ifndef CORONAVIRUSSIMULATION_SARSCOV2_H
#define CORONAVIRUSSIMULATION_SARSCOV2_H
#include <vector>
#include <iostream>
using namespace std;


class SarsCov2 {
public:
    SarsCov2(const vector<string> &virusComb, char t, double p); //c'tor
    explicit SarsCov2(SarsCov2* virus); //c'tor
    virtual ~SarsCov2(); //d'tor
    int getRefCount() const;
    vector<string> virusComb;
    double fit{};
    char type;
    double prob;
    SarsCov2* ancestor = nullptr;
private:
    int refCount;


};



#endif //CORONAVIRUSSIMULATION_SARSCOV2_H
