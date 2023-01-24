#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunknown-pragmas"
#pragma ide diagnostic ignored "NullDereference"
#pragma ide diagnostic ignored "cert-msc50-cpp"
#pragma ide diagnostic ignored "cppcoreguidelines-narrowing-conversions"
#include "Simulation.h"

Simulation::Simulation(const int d, const vector<string>& t, const int s, const int time) : dimension(d), target(t), popSize(s), simulationTime(time){}

void Simulation::addVirus(SarsCov2* v) {
    firstGeneration.push_back(v);
}

void Simulation::fitTest() {
    double h;
    for (SarsCov2* virus : currPopulation) {
        h = 0;
        auto it = target.begin();
        for (const string& ch : virus->virusComb) {
            if (ch == *it) h++;
            it++;
       }
        virus->fit = h/dimension;
    }
}

void Simulation::individualUpdate(SarsCov2* virus) const {
    switch (virus->type) {
        case 'a' :{
            for (int i=0; i<dimension;i++) {
                if (virus->virusComb[i] == "A") virus->virusComb[i] = "T";
                else if (virus->virusComb[i] == "T") virus->virusComb[i] = "A";
            }
            break;
        }
        case 'd' :{
            for (int i=0; i<dimension;i++) {
                if (virus->virusComb[i] == "A") virus->virusComb[i] = "T";
                else if (virus->virusComb[i] == "C") virus->virusComb[i] = "G";
                else if (virus->virusComb[i] == "G") virus->virusComb[i] = "C";
            }
            break;
        }
        case 'o' : {
            for (int i=0; i<dimension;i++) {
                if (virus->virusComb[i] == "T") virus->virusComb[i] = "A";
                else if (virus->virusComb[i] == "C") virus->virusComb[i] = "G";
                else if (virus->virusComb[i] == "G") virus->virusComb[i] = "C";
            }
            break;
        }
    }
}

void Simulation::groupUpdate(int weak1, int weak2) {
    //generating two random numbers
    int pos1 = getArandomNum(0,popSize-1);
    int pos2 = getArandomNum(0,popSize-1);
    while (pos1 == pos2) pos2 = getArandomNum(1,popSize); //in case that we got the generated the same number in rand1 and rand2
    int i = getArandomNum(0,dimension-1);
    int j = getArandomNum(0,dimension-1);
    int start = i;
    int end = j;
    if (i > j) {
        start = j;
        end = i;
    }
    //duplicates of the two ancestors that were chosen
    auto* newVirus1 = new SarsCov2(firstGeneration[pos1]);
    auto* newVirus2 = new SarsCov2(firstGeneration[pos2]);
    delete currPopulation[weak1];
    delete currPopulation[weak2];
    start++;
    while (start <= end) {
        newVirus1->virusComb[start] = firstGeneration[pos2]->virusComb[start];
        newVirus2->virusComb[start] = firstGeneration[pos1]->virusComb[start];
        start++;
    }
    currPopulation[weak1] = newVirus1;
    currPopulation[weak2] = newVirus2;
}

int Simulation::getArandomNum(int lowest, int highest) {
    int range = (highest - lowest)+1;
    return range * (rand() / (RAND_MAX + 1.0));
}

bool Simulation::probRes(double prob) {
    if (getArandomNum(1,100) <= prob*100) return true;
    return false;
}

void Simulation::start() {
    bool stop = false;
    //creating a vector of the current virus population
    for (SarsCov2* virus : firstGeneration) {
        auto *v = new SarsCov2(virus->virusComb, virus->type, virus->prob);
        v->ancestor = virus;
        currPopulation.push_back(v);
    }
    fitTest();
    while (simulationTime >= 0) {
        double smallest1 = 1, smallest2 = 1;
        int weakPos1, weakPos2, curr=0;
        for (SarsCov2* virus : currPopulation) {
            if (virus->fit == 1) {
               stop = true;
               break;
           }
           if (smallest1 >= smallest2) {
                if (virus->fit < smallest1) {
                    smallest1 = virus->fit;
                    weakPos1 = curr;
                }
           } else if (smallest2 > smallest1) {
               if (virus->fit < smallest2) {
                   smallest2 = virus->fit;
                   weakPos2 = curr;
               }
           }
           curr++;
        }
        if (stop) break;
        for (SarsCov2* virus : currPopulation) {
            if (probRes(virus->prob)) individualUpdate(virus);
        }
        groupUpdate(weakPos1, weakPos2);
        simulationTime--;
        fitTest();
        for (SarsCov2* virus : currPopulation) {
            if (strongest == nullptr) {
                strongest = new SarsCov2(virus);
            } else if (virus->fit > strongest->fit) {
                delete strongest;
                strongest = new SarsCov2(virus);
            }
        }
    }
    printGen();
}

void Simulation::printGen() {
    for (SarsCov2* virus : currPopulation) {
        cout << virus->type << " ";
        for (const string& s : virus->virusComb) {
            cout << s << " ";
        }
        cout << endl;
    }
    cout << endl;
    for (SarsCov2* virus : firstGeneration) {
        cout << virus->type << " ";
        for (const string& s : virus->virusComb) {
            cout << s << " ";
        }
        cout << virus->getRefCount() <<  endl;
    }
    cout << endl;
    cout << strongest->type << " ";
    for (const string& s : strongest->virusComb) {
        cout << s << " ";
    }
    cout << endl;
}
#pragma clang diagnostic pop