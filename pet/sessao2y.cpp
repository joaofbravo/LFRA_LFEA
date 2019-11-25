#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include <ctime>

#include "TROOT.h"
#include "TSystem.h"
#include "TStyle.h"
#include "TApplication.h"
#include "TCanvas.h"
#include "TFrame.h"
#include "TAxis.h"
#include "TGraphErrors.h"
#include "TH1F.h"
#include "TF1.h"
#include "TFormula.h"
#include "TMath.h"
#include "TRandom.h"
#include "TLegend.h"

using namespace std;


// Fit Function
Double_t fitFunc(Double_t *x, Double_t *par)
{
	//Double_t fitval =  par[0]*par[1]*par[1]*TMath::Pi()/((15.6*0.3937+TMath::Abs(x[0]))*(15.6*0.3937+TMath::Abs(x[0]))); 
    Double_t fitval =  par[0]*par[1]*par[1]*(1/((par[2]*0.3937+TMath::Abs(x[0]))*(par[2]*0.3937+TMath::Abs(x[0])))); 
    //Double_t fitval = par[0]*TMath::Gaus(x[0],par[1],par[2])+par[3];;
	return fitval;
}


// Main routine
int main()
{
    // Create TGraphErrors from file
    string FILE1 = "pet/sessao2_data_y.data";
    vector<TGraphErrors*> DataSaver;
    DataSaver.push_back(new TGraphErrors(FILE1.c_str(),"%lg %lg %lg %lg",""));

    // Canvas

    // Canvas
    TApplication* theApp = new TApplication("App", 0, 0);
    TCanvas* c1 = new TCanvas("c1", "Fit Solution", 0, 0, 1400, 1000);
    c1->SetFillColor(kWhite);
    c1->SetGrid();
    c1->GetFrame()->SetFillColor(21);
    c1->GetFrame()->SetBorderSize(12);

    // Pad
    TPad* d1 = new TPad("Draw", "Pad1", 0, 0, 1, 1, kWhite);
    d1->SetGrid();
    d1->Draw();
    d1->cd();

    // TGraphErrors
    DataSaver[0]->SetLineColor(kRed);
    DataSaver[0]->SetLineWidth(2);
    DataSaver[0]->SetMarkerStyle(1);
    DataSaver[0]->SetMarkerColor(0);
    DataSaver[0]->SetFillColor(0);
    DataSaver[0]->SetTitle("");

    // Axis
    DataSaver[0]->GetXaxis()->SetTitle("#theta (#º)");
    DataSaver[0]->GetYaxis()->SetTitle("R_c (cts/s)");

    DataSaver[0]->GetXaxis()->SetRangeUser(-3,3);
    DataSaver[0]->GetYaxis()->SetRangeUser(0, 430);

    // User fit region
    Double_t lwlim = -2.5;
    Double_t uplim = 2.5;
    Int_t Npar = 3;

    // Fit Function
    TF1 *func1 = new TF1("myfit", fitFunc, lwlim, uplim, Npar);
    func1->SetLineColor(kRed+1);
    func1->SetLineWidth(2);

     //Set initial values and parameter names
    func1->SetParameter(0,200);
    func1->FixParameter(1, 1.02);    
    func1->FixParameter(2, 15.6);

    // func1->SetParNames("A","B","C");
    //func1->SetParLimits(2, -10, -4);
    //func1->FixParameter(0, 1.186e-1);

    // Draw
      
    DataSaver[0]->Draw("AP");
    DataSaver[0]->Fit("myfit","UR");


    Double_t funcchi2 = func1->GetChisquare();
    Double_t funcndf = func1->GetNDF();
    cout << "\n Chi2: " << funcchi2  << endl;
    cout << " ndf: " << funcndf  << endl;    
    cout << " Chi2/ndf: " << funcchi2/funcndf  << endl << endl;


    c1->Modified();
    c1->Update();
    while(c1->WaitPrimitive()) gSystem->ProcessEvents();
    c1->Print("pet/sessao2y_gaus.pdf");

    delete d1;
    delete c1;
}