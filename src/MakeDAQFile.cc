#include "../include/MakeDAQFile.h"
#include "../include/utils.h"

#include "TFile.h"
#include "TTree.h"
#include "TH1D.h"
#include "TH1I.h"
#include "TString.h"

using namespace std;

void MakeDAQFile(string fName){
    if(existFile(fName)){
        TFile* input = new TFile(fName.c_str(),"READ");

        TTree* oldRAWDataTree = (TTree*)input->Get("RAWData");
        TH1D* ID = (TH1D*)input->Get("ID");
        TH1I* Triggers = (TH1I*)input->Get("Triggers");
        TH1I* Thrs = (TH1I*)input->Get("Thrs");

        TTree* oldRunParameters = (TTree*)input->Get("RunParameters");
        TTree* newRunParameters = oldRunParameters->CloneTree();

        RAWData olddata;

        olddata.TDCCh = new vector<Uint>;
        olddata.TDCTS = new vector<float>;
        olddata.TDCCh->clear();
        olddata.TDCTS->clear();

        oldRAWDataTree->SetBranchAddress("EventNumber",    &olddata.iEvent);
        oldRAWDataTree->SetBranchAddress("number_of_hits", &olddata.TDCNHits);
        oldRAWDataTree->SetBranchAddress("TDC_channel",    &olddata.TDCCh);
        oldRAWDataTree->SetBranchAddress("TDC_TimeStamp",  &olddata.TDCTS);

        string newfName = "test.root";
        TFile* output = new TFile(newfName.c_str(),"RECREATE");

        TTree* newRAWDataTree = new TTree("RAWData","RAWData");

        int           EventCount = -9;  //Event tag
        int           nHits = -8;       //Number of fired TDC channels in event
        vector<int>   TDCCh;            //List of fired TDC channels in event
        vector<float> TDCTS;            //list of fired TDC channels time stamps

        TDCCh.clear();
        TDCTS.clear();

        //Set the branches that will contain the previously defined variables
        newRAWDataTree->Branch("EventNumber",    &EventCount, "EventNumber/I");
        newRAWDataTree->Branch("number_of_hits", &nHits,      "number_of_hits/I");
        newRAWDataTree->Branch("TDC_channel",    &TDCCh);
        newRAWDataTree->Branch("TDC_TimeStamp",  &TDCTS);

        Uint nEntries = oldRAWDataTree->GetEntries();
        int lastEvent = -1;

        for(Uint i=0; i<nEntries; i++){
            oldRAWDataTree->GetEntry(i);

            cout << olddata.iEvent << " " << lastEvent << endl;

            if(lastEvent == -1){
                EventCount = olddata.iEvent;
                nHits = olddata.TDCNHits;
                TDCCh.insert(TDCCh.end(),olddata.TDCCh->begin(),olddata.TDCCh->end());
                TDCTS.insert(TDCTS.end(),olddata.TDCTS->begin(),olddata.TDCTS->end());

                lastEvent = olddata.iEvent;
            } else if(olddata.iEvent == lastEvent){
                EventCount = olddata.iEvent;
                nHits = nHits + olddata.TDCNHits;
                TDCCh.insert(TDCCh.end(),olddata.TDCCh->begin(),olddata.TDCCh->end());
                TDCTS.insert(TDCTS.end(),olddata.TDCTS->begin(),olddata.TDCTS->end());
            } else {
                newRAWDataTree->Fill();

                EventCount = olddata.iEvent;
                nHits = olddata.TDCNHits;
                TDCCh.clear();
                TDCTS.clear();
                TDCCh.insert(TDCCh.end(),olddata.TDCCh->begin(),olddata.TDCCh->end());
                TDCTS.insert(TDCTS.end(),olddata.TDCTS->begin(),olddata.TDCTS->end());

                lastEvent = olddata.iEvent;
            }
        }
        newRAWDataTree->Fill();

        newRAWDataTree->Write();
        newRunParameters->Write();
        ID->Write();
        Triggers->Write();
        Thrs->Write();
        output->Close();

        input->Close();
    }
}
