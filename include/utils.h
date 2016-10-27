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
string	getFileName(string fName, string type);
void	getGapList(vector<string>& GapList);

#endif // UTILS_H
