#include "../include/MakeCAENFile.h"

#include "TFile.h"
#include "TH1F.h"

using namespace std;

void MakeCAENFile(string fName, vector<string> GapList){
	if(existFile(fName)){
		TFile input(fName.c_str(),"READ");

		string outputName = getFileName(fName,"CAEN");
		TFile* output = new TFile(outputName.c_str(),"RECREATE");

		for(unsigned int g = 0; g<GapList.size(); g++){
                    string HVeffHisto = "HVeff-" + GapList[g];
                    string newNameFormat = "HVeff_" + GapList[g];

                    if(input.GetListOfKeys()->Contains(HVeffHisto.c_str())){
                            TH1F* HVeff = (TH1F*)input.Get(HVeffHisto.c_str());
                            HVeff->SetName(newNameFormat.c_str());

                            HVeff->Write();
                    }
		}

		output->Close();
		input.Close();
	}
}
