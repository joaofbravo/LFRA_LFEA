#include "FCtools.h"
#include "Spline3Interpolator.h"
#include "cFCgraphics.h"
#include "TPad.h"
#include "TGraphErrors.h"
#include "TFitResult.h"
#include "TF1.h"
#include "TMath.h"
#include "TAxis.h"
#include "TROOT.h"
#include "TSystem.h"
#include "TStyle.h"
#include "TApplication.h"
#include "TCanvas.h"
#include "TFrame.h"
#include "TMath.h"
#include "TRandom.h"
#include "TLegend.h"

#include <cmath>
#include <vector>
#include <cstring>



using namespace std;

int main()
{
	FCtools tools;
	//cFCgraphics G;

	int ndata = 9;


	string fname[] = {"angequim0_8", "angequim1_6", "angequim2_4", "angequim3_2", "angequip0_0", "angequip0_8", "angequip1_6", "angequip2_4", "angequip3_2"};

	string datastr = ".data";
	string dir = "experimentaldata/LFEA/LFEAPet/";
	FCmatrixFull* data = new FCmatrixFull[ndata];
	
	for (int i = 0; i < ndata; ++i)
		data[i] = tools.ReadFileToMatrix(dir + fname[i] + datastr);
		
	double ** ang= new double*[ndata];
	double ** ncoic= new double*[ndata];
	double ** eang= new double*[ndata];
	double ** encoic= new double*[ndata];

	for (int i = 0; i < ndata; ++i)
	{
		ang[i] = new double[data[i].size()];
		ncoic[i] = new double[data[i].size()];
		eang[i] = new double[data[i].size()];
		encoic[i] = new double[data[i].size()];
	}


	TF1 fittime("fittime","[0] + [1]*x",0,5640
	);
	
	fittime.SetParameters(-2.599,0.9173);
	double efit[] = {2.113,0.04113};


	for (int j = 0; j < ndata; ++j)
	{
		for (int i = 0; i < data[j].size(); ++i)
		{
			ang[j][i] = data[j][i][0];
			ncoic[j][i] = data[j][i][2]-fittime.Eval(data[j][i][1])/data[j][i][1];
			eang[j][i] = 0.1;
			encoic[j][i] = sqrt(data[j][i][3]*data[j][i][3] + efit[0]*efit[0]/data[j][i][1]/data[j][i][1] + efit[1]*efit[1]);
		}
	}


	TGraphErrors **  graphang = new TGraphErrors*[ndata];
	for (int i = 0; i < ndata; ++i)
		graphang[i] = new TGraphErrors(data[i].size(),ang[i],ncoic[i],eang[i],encoic[i]);
	

	string strfitang = "fit";
	
	TF1 ** fitang = new TF1*[ndata];
	for (int i = 0; i < ndata; ++i)
	{
		fitang[i] = new TF1((strfitang + fname[i]).c_str() ,"[0]/[2]*exp(-(x-[1])*(x-[1])/2/[2]/[2])",-100,100);
		fitang[i]->SetParameters(1000,0,10);
	}

	fitang[1]->SetParameters(1000,-10,10);
	fitang[5]->SetParameters(1000,10,10);

	fitang[3]->SetParameters(1000,-20,10);
	fitang[8]->SetParameters(1000,20,10);
	
	

	for (int i = 0; i < ndata; ++i)
	{
		graphang[i]->SetMarkerStyle(20);
		graphang[i]->SetMarkerSize(0);
	}
	

	// Canvas
    TApplication* theApp = new TApplication("App", 0, 0);
	TCanvas* c1 = new TCanvas("c1", "Plot", 0, 0, 1400, 1000);
    c1->SetFillColor(kWhite);
    c1->SetGrid();
    c1->GetFrame()->SetFillColor(21);
    c1->GetFrame()->SetBorderSize(12);
    c1->DrawFrame(-40,0,40,600);

    

    // Pad
    TPad* d1 = new TPad("Draw", "Pad1", 0,0, 1, 1, kWhite);
    d1->SetGrid();
    d1->Draw();
    d1->cd();

    graphang[0]->SetMarkerColor(kRed);
    graphang[0]->SetLineColor(kRed);
    fitang[0]->SetLineColor(kRed);

    graphang[1]->SetMarkerColor(kOrange);
    graphang[1]->SetLineColor(kOrange);
    fitang[1]->SetLineColor(kOrange);

    graphang[2]->SetMarkerColor(kYellow+2);
    graphang[2]->SetLineColor(kYellow+2);
    fitang[2]->SetLineColor(kYellow+2);

    graphang[3]->SetMarkerColor(kGreen);
    graphang[3]->SetLineColor(kGreen);
    fitang[3]->SetLineColor(kGreen);

    graphang[4]->SetMarkerColor(kBlue);
    graphang[4]->SetLineColor(kBlue);
    fitang[4]->SetLineColor(kBlue);

    graphang[5]->SetMarkerColor(kViolet);
    graphang[5]->SetLineColor(kViolet);
    fitang[5]->SetLineColor(kViolet);

    graphang[6]->SetMarkerColor(kPink);
    graphang[6]->SetLineColor(kPink);
    fitang[6]->SetLineColor(kPink);

    graphang[7]->SetMarkerColor(kGray+2);
    graphang[7]->SetLineColor(kGray+2);
    fitang[7]->SetLineColor(kGray+2);

    graphang[8]->SetMarkerColor(kBlack);
    graphang[8]->SetLineColor(kBlack);
    fitang[8]->SetLineColor(kBlack);


    for (int i = 0; i < ndata; ++i)
		graphang[i]->Fit((strfitang + fname[i]).c_str());


	graphang[0]->SetTitle("Coincidencias;Angulo;N_{coic.}");
	graphang[0]->GetXaxis()->SetLimits(-40,40);
    graphang[0]->Draw("AP");


    for (int i = 1; i < ndata; ++i)
		graphang[i]->Draw("P");


    c1->Modified();
    c1->Update();
    while(c1->WaitPrimitive()) 
    	gSystem->ProcessEvents();

    c1->Print("plots/LFEA/PET/coicvangequi.pdf");

	
	cout <<"\n\n A	err	mu	err	sigma	err	chi^2/Ndf" <<endl;

	cout <<setprecision(5);

	for (int i = 0; i < ndata; ++i)
	{	
		for (int j = 0; j < 3; ++j)
			cout <<fitang[i]->GetParameter(j)<<"	"<<fitang[i]->GetParError(j)<< "	";

		cout << fitang[i]->GetChisquare()/fitang[i]->GetNDF()  <<endl;
	}

	delete[] data;

	for (int i = 0; i < ndata; ++i)
	{
		delete[] ang[i];
		delete[] ncoic[i];
		delete[] eang[i];
		delete[] encoic[i];
		delete fitang[i];
		delete graphang[i];
	}
	

	delete[] ang;
	delete[] ncoic;
	delete[] eang;
	delete[] encoic;
	delete[] fitang;
	delete[] graphang;
	
	delete c1;
    delete theApp;
	
	return 0;
}