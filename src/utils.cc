#include <cmath>
#include "../include/utils.h"

using namespace std;


bool existFile(string fName){
	ifstream file(fName.c_str());
	return file.good();
}

string getFileName(string fName, string type){
	unsigned int scan_length = fName.find_first_of("_");
	string ScanID = fName.substr(0,scan_length);

	unsigned int hv_position = fName.find_last_of("HV") - 1;
	unsigned int hv_length =fName.find_last_of("_") - hv_position;
	string HVStep = fName.substr(hv_position,hv_length);

	string outputName = ScanID + "_" + HVStep + "_" + type + ".root";
	return outputName;
}

void getGapList(vector<string>& GapList){
	if(existFile("Gap-list.csv")){
		ifstream CSVList("Gap-list.csv");

		string gap;

		while(CSVList.good()){
			gap.clear();

			CSVList >> gap;

			if(gap.size() > 1) GapList.push_back(gap);
		}
	}
}
