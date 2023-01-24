#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunknown-pragmas"
#pragma ide diagnostic ignored "hicpp-multiway-paths-covered"
#include <iostream>
#include <fstream>
#include <vector>
#include "Alpha.h"
#include "Delta.h"
#include "Omicron.h"
#include "Simulation.h"
using namespace std;

vector<string> split (const string& s, const string& delimiter) {
    size_t pos_start = 0, pos_end, delim_len = delimiter.length();
    string token;
    vector<string> res;

    while ((pos_end = s.find (delimiter, pos_start)) != string::npos) {
        token = s.substr (pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        res.push_back (token);
    }

    res.push_back (s.substr (pos_start));
    return res;
}
int main(__attribute__((unused)) int argc, char** argv) {
    string dimension, target, t, populationSize, virus2parse;
    char type;
    //file handelings:
    ifstream  configuration;
    configuration.open(argv[1]); //enter the entire path
    ifstream  firstGeneration;
    firstGeneration.open(argv[2]); //enter the entire path
    if (!configuration || !firstGeneration) {
        cerr << "could'nt open the file" << endl;
        return 0;
    }
    //getting the simulation parameters:
    getline(configuration, dimension);
    dimension.erase(dimension.length()-1);
    getline(configuration, target);
    target.erase(target.length()-1);
    vector<string> splitted_target = split(target, " ");
    getline(configuration, t);
    getline(firstGeneration, populationSize);
    populationSize.erase(populationSize.length()-1);
    Simulation simulation(stoi(dimension), splitted_target,stoi(populationSize), stoi(t));
    //getting the first generation of viruses:
    while (!firstGeneration.eof()) {
        getline(firstGeneration, virus2parse);
        type = virus2parse[0];
        switch (type) {
            case 'a' :{
                auto* virus = new Alpha(split(virus2parse.substr(2, 2*stoi(dimension)-1), " "), type, 0.37);
                simulation.addVirus(virus);
                break;
            }
            case 'd' :{
                auto* virus = new Delta(split(virus2parse.substr(2, 2*stoi(dimension)-1), " "), type, 1.0/stoi(dimension));
                simulation.addVirus(virus);
                break;
            }
            case 'o' : {
                auto* virus = new Omicron(split(virus2parse.substr(2, 2*stoi(dimension)-1), " "), type, 2.0/stoi(dimension));
                simulation.addVirus(virus);
                break;
            }
        }
    }
    simulation.start();
    return 0;
}



#pragma clang diagnostic pop