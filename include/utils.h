#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <cstdlib>
#include <sstream>
#include <fstream>
#include <map>
#include <string>
#include <vector>
#include <unistd.h>
#include <iomanip>

using namespace std;

bool    existFile(string fName);

typedef unsigned int Uint;

struct RAWData {
    int            iEvent;   //Event i
    int            TDCNHits; //Number of hits in event i
    vector<int>    *TDCCh;    //List of channels giving hits per event
    vector<float>  *TDCTS;    //List of the corresponding time stamps
};

#endif // UTILS_H
