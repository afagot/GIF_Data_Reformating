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

        // Deactivate all branches
        RAWDataTree->SetBranchStatus("*",0);

        // Activate all the branches exept the QFlag one
        RAWDataTree->SetBranchStatus("EventNumber*",1);
        RAWDataTree->SetBranchStatus("number_of_hits*",1);
        RAWDataTree->SetBranchStatus("TDC_channel*",1);
        RAWDataTree->SetBranchStatus("TDC_TimeStamp*",1);

        TFile* output = new TFile(fName.c_str(),"RECREATE");

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
