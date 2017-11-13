#include <cmath>
#include "../include/utils.h"

using namespace std;


bool existFile(string fName){
    ifstream file(fName.c_str());
    return file.good();
}
