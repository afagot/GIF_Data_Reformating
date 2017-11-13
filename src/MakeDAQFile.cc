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
        olddata.TDCCh = new vector<int>;
        olddata.TDCTS = new vector<float>;
        olddata.TDCCh->clear();
        olddata.TDCTS->clear();

        oldRAWDataTree->SetBranchAddress("EventNumber",    &olddata.iEvent);
        oldRAWDataTree->SetBranchAddress("number_of_hits", &olddata.TDCNHits);
        oldRAWDataTree->SetBranchAddress("TDC_channel",    &olddata.TDCCh);
        oldRAWDataTree->SetBranchAddress("TDC_TimeStamp",  &olddata.TDCTS);

        TFile* output = new TFile(fName.c_str(),"RECREATE");

        TTree* newRAWDataTree = new TTree("RAWData","RAWData");

        int EventCount;
        int nHits;
        vector<int> *TDCCh = new vector<int>;
        vector<float> *TDCTS = new vector<float>;

        TDCCh->clear();
        TDCTS->clear();

        //Set the branches that will contain the previously defined variables
        newRAWDataTree->Branch("EventNumber",    &EventCount, "EventNumber/I");
        newRAWDataTree->Branch("number_of_hits", &nHits,      "number_of_hits/I");
        newRAWDataTree->Branch("TDC_channel",    &TDCCh);
        newRAWDataTree->Branch("TDC_TimeStamp",  &TDCTS);

        vector<int> EventCountList;
        vector<int> nHitsList;
        vector< vector<int> *> TDCChList;
        vector< vector<float> *> TDCTSList;

        EventCountList.clear();
        nHitsList.clear();
        TDCChList.clear();
        TDCTSList.clear();

        Uint nEntries = oldRAWDataTree->GetEntries();

        for(Uint i=0; i<nEntries; i++){
            oldRAWDataTree->GetEntry(i);

            if(olddata.iEvent > (int)EventCountList.size()){
                Uint Difference = olddata.iEvent - (int)EventCountList.size();
                for(Uint e = 1; e < Difference; e++){
                    EventCountList.push_back(olddata.iEvent-Difference+e);
                    nHitsList.push_back(0);
                    TDCChList.push_back(new vector<int>);
                    TDCTSList.push_back(new vector<float>);
                }

                EventCountList.push_back(olddata.iEvent);
                nHitsList.push_back(olddata.TDCNHits);
                TDCChList.push_back(olddata.TDCCh);
                TDCTSList.push_back(olddata.TDCTS);
            } else {
                Uint e = olddata.iEvent - 1;
                nHitsList.at(e) = nHitsList.at(e) + olddata.TDCNHits;
                TDCChList.at(e)->insert(TDCChList.at(e)->end(),olddata.TDCCh->begin(),olddata.TDCCh->end());
                TDCTSList.at(e)->insert(TDCTSList.at(e)->end(),olddata.TDCTS->begin(),olddata.TDCTS->end());
            }
        }

        for(Uint s = 0; s < EventCountList.size(); s++){
            EventCount = EventCountList.at(s);
            nHits = nHitsList.at(s);
            TDCCh = TDCChList.at(s);
            TDCTS = TDCTSList.at(s);

            newRAWDataTree->Fill();
        }

        newRAWDataTree->Write();
        newRunParameters->Write();
        ID->Write();
        Triggers->Write();
        Thrs->Write();
        output->Close();

        input->Close();
    }
}
