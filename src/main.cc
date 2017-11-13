#include "../include/MakeDAQFile.h"

#include <sstream>

using namespace std;

int main(int argc ,char *argv[]){
    stringstream converter;
    converter << argv[0];
    string program;
    converter >> program;
    converter.clear();

    if(argc != 2){
        cout << "[Reform] expects to have 2 parameters\n";
        cout << "[Reform] USAGE is : " << program << " /path/to/file/to/split\n";
        return -1;
    } else if(argc == 2){
        converter << argv[1];
        string fName;
        converter >> fName;
        converter.clear();

        MakeDAQFile(fName);

        return 0;
    }
}
