#include "../include/MakeDAQFile.h"

#include "TFile.h"
#include "TTree.h"
#include "TH1D.h"
#include "TH1I.h"
#include "TString.h"

using namespace std;

void MakeDAQFile(string fName){
	if(existFile(fName)){
		TFile* input = new TFile(fName.c_str(),"READ");

		TTree* RAWDataTree = (TTree*)input->Get("RAWData");
		TTree* RunParameters = (TTree*)input->Get("RunParameters");

		string outputName = getFileName(fName,"DAQ");
		TFile* output = new TFile(outputName.c_str(),"RECREATE");

		TTree* newRAWDataTree = RAWDataTree->CloneTree();
		TTree* newRunParameters = RunParameters->CloneTree();

		TH1D* ID = (TH1D*)input->Get("ID");
		TH1I* Triggers = (TH1I*)input->Get("Triggers");
		TH1I* Thrs = (TH1I*)input->Get("Thrs");

		newRAWDataTree->Write();
		newRunParameters->Write();
		ID->Write();
		Triggers->Write();
		Thrs->Write();

		output->Close();
		input->Close();
	}
}
