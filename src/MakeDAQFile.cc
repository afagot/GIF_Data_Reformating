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
        oldRAWDataTree->SetBranchAddress("Quality_flag", &olddata.QFlag);
        oldRAWDataTree->SetBranchAddress("TDC_channel",    &olddata.TDCCh);
        oldRAWDataTree->SetBranchAddress("TDC_TimeStamp",  &olddata.TDCTS);

        TFile* output = new TFile(fName.c_str(),"RECREATE");

        TTree* newRAWDataTree = new TTree("RAWData","RAWData");

        int EventCount,nHits,qflag;
        vector<int> *TDCCh = new vector<int>;
        vector<float> *TDCTS = new vector<float>;

        TDCCh->clear();
        TDCTS->clear();

        //Set the branches that will contain the previously defined variables
        newRAWDataTree->Branch("EventNumber",    &EventCount, "EventNumber/I");
        newRAWDataTree->Branch("number_of_hits", &nHits,      "number_of_hits/I");
        newRAWDataTree->Branch("Quality_flag",   &qflag,      "Quality_flag/I");
        newRAWDataTree->Branch("TDC_channel",    &TDCCh);
        newRAWDataTree->Branch("TDC_TimeStamp",  &TDCTS);

        Uint nEntries = oldRAWDataTree->GetEntries();

        for(Uint i=0; i<nEntries; i++){
            oldRAWDataTree->GetEntry(i);

            EventCount = olddata.iEvent;
            nHits = olddata.TDCNHits;
            qflag = olddata.QFlag;
            TDCCh = olddata.TDCCh;
            TDCTS = olddata.TDCTS;

            cout << qflag << " -> ";

            int nDigits = 4;

            int tmpflag = qflag;
            while(nDigits != 0){
                int tdcflag = tmpflag/(int)pow(10,nDigits-1);

                if(tdcflag == 0) qflag = qflag + 2*(int)pow(10,nDigits-1);

                tmpflag = tmpflag%(int)pow(10,nDigits-1);
                nDigits--;
            }

            cout << qflag << endl;

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
