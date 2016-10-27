#include "../include/MakeDIPFile.h"

#include "TFile.h"
#include "TH1D.h"
#include "TH1I.h"

using namespace std;

void MakeDIPFile(string fName){
	if(existFile(fName)){
		TFile* input = new TFile(fName.c_str(),"READ");

		string outputName = getFileName(fName,"DIP");
		TFile* output = new TFile(outputName.c_str(),"RECREATE");

		TH1I* Attenuators		= (TH1I*)input->Get("Attenuators");
		TH1D* Pressure			= (TH1D*)input->Get("Pressure");
		TH1D* Temperature		= (TH1D*)input->Get("Temperature");
		TH1D* Humidity			= (TH1D*)input->Get("Humidity");
		TH1D* C2H2F4			= (TH1D*)input->Get("C2H2F4");
		TH1D* C4H10				= (TH1D*)input->Get("C4H10");
		TH1D* SF6				= (TH1D*)input->Get("SF6");
		TH1D* RPC_MFC_Humidity	= (TH1D*)input->Get("RPC_MFC_Humidity");

		Pressure->SetNameTitle("P","Source sensor pressure");
		Temperature->SetNameTitle("TIN","Source sensor temperature");
		Humidity->SetNameTitle("RHIN","Source sensor relative humidity");

		TH1I* AttDA = new TH1I("AttDA","Downstream absorber A position",1,0,1);
		TH1I* AttDB = new TH1I("AttDB","Downstream absorber B position",1,0,1);
		TH1I* AttDC = new TH1I("AttDC","Downstream absorber C position",1,0,1);
		TH1D* AttDEff = new TH1D("AttDEff","Effective attenuation Downstream",1,0,1);
		TH1I* AttUA = new TH1I("AttUA","Downstream absorber A position",1,0,1);
		TH1I* AttUB = new TH1I("AttUB","Downstream absorber B position",1,0,1);
		TH1I* AttUC = new TH1I("AttUC","Downstream absorber C position",1,0,1);
		TH1D* AttUEff = new TH1D("AttUEff","Effective attenuation Upstream",1,0,1);

		AttDA->SetCanExtend(TH1::kAllAxes);
		AttDB->SetCanExtend(TH1::kAllAxes);
		AttDC->SetCanExtend(TH1::kAllAxes);
		AttDEff->SetCanExtend(TH1::kAllAxes);
		AttUA->SetCanExtend(TH1::kAllAxes);
		AttUB->SetCanExtend(TH1::kAllAxes);
		AttUC->SetCanExtend(TH1::kAllAxes);
		AttUEff->SetCanExtend(TH1::kAllAxes);

		float A[3] = {1.,10.,100.};
		float B[3] = {1.,1.468,100.};
		float C[3] = {1.,2.154,4.642};

		unsigned int ABSD = Attenuators->GetBinContent(1);
		unsigned int ABSU = Attenuators->GetBinContent(2);

		unsigned int DA = ABSD/100;
		unsigned int DB = (ABSD-DA*100)/10;
		unsigned int DC = ABSD-DA*100-DB*10;
		float DEff = A[DA-1]*B[DB-1]*C[DC-1];

		unsigned int UA = ABSU/100;
		unsigned int UB = (ABSU-UA*100)/10;
		unsigned int UC = ABSU-UA*100-UB*10;
		float UEff = A[UA-1]*B[UB-1]*C[UC-1];

		AttDA->Fill(DA);
		AttDB->Fill(DB);
		AttDC->Fill(DC);
		AttDEff->Fill(DEff);
		AttUA->Fill(UA);
		AttUB->Fill(UB);
		AttUC->Fill(UC);
		AttUEff->Fill(UEff);

		Pressure->Write();
		Temperature->Write();
		Humidity->Write();
		C2H2F4->Write();
		C4H10->Write();
		SF6->Write();
		RPC_MFC_Humidity->Write();
		AttDA->Write();
		AttDB->Write();
		AttDC->Write();
		AttDEff->Write();
		AttUA->Write();
		AttUB->Write();
		AttUC->Write();
		AttUEff->Write();

		output->Close();
		input->Close();
	}
}
