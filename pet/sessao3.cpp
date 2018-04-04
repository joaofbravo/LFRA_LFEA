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
	//Double_t fitval = par[0]*(2*par[1]*par[1]*TMath::ACos(15.6*TMath::Abs(x[0]-par[2])*TMath::Pi()/(2*par[1]*180))-15.6*TMath::Abs(x[0]-par[2])*TMath::Pi()/(360)*TMath::Sqrt(4*par[1]*par[1]-15.6*15.6*(x[0]-par[2])*(x[0]-par[2])*TMath::Pi()*TMath::Pi()/(180*180)));
    Double_t fitval = par[0]*TMath::Gaus(x[0],par[1],par[2])+ par[3]*TMath::Gaus(x[0],par[4],par[5])+par[6];;
	return fitval;
}


// Main routine
int main()
{
    // Create TGraphErrors from file
    string FILE1 = "pet/sessao3_data_r05.data";
    vector<TGraphErrors*> DataSaver;
    DataSaver.push_back(new TGraphErrors(FILE1.c_str(),"%lg %lg %lg %lg",""));


    string FILE2 = "pet/sessao3_data_r1.data";
    vector<TGraphErrors*> DataSaver2;
    DataSaver2.push_back(new TGraphErrors(FILE2.c_str(),"%lg %lg %lg %lg",""));


    string FILE3 = "pet/sessao3_data_r15.data";
    vector<TGraphErrors*> DataSaver3;
    DataSaver3.push_back(new TGraphErrors(FILE3.c_str(),"%lg %lg %lg %lg",""));

    string FILE4 = "pet/sessao3_data_r2.data";
    vector<TGraphErrors*> DataSaver4;
    DataSaver4.push_back(new TGraphErrors(FILE4.c_str(),"%lg %lg %lg %lg",""));


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

    DataSaver2[0]->SetLineColor(kBlue-2);
    DataSaver2[0]->SetLineWidth(2);
    DataSaver2[0]->SetMarkerStyle(1);
    DataSaver2[0]->SetMarkerColor(0);
    DataSaver2[0]->SetFillColor(0);
    DataSaver2[0]->SetTitle("");

    DataSaver3[0]->SetLineColor(kGreen-2);
    DataSaver3[0]->SetLineWidth(2);
    DataSaver3[0]->SetMarkerStyle(1);
    DataSaver3[0]->SetMarkerColor(0);
    DataSaver3[0]->SetFillColor(0);
    DataSaver3[0]->SetTitle("");

    DataSaver4[0]->SetLineColor(kOrange+2);
    DataSaver4[0]->SetLineWidth(2);
    DataSaver4[0]->SetMarkerStyle(1);
    DataSaver4[0]->SetMarkerColor(0);
    DataSaver4[0]->SetFillColor(0);
    DataSaver4[0]->SetTitle("");


    // Axis
    DataSaver4[0]->GetXaxis()->SetTitle("#theta (#º)");
    DataSaver4[0]->GetYaxis()->SetTitle("R_c (cts/s)");

    DataSaver4[0]->GetXaxis()->SetRangeUser(0, 360);
    DataSaver4[0]->GetYaxis()->SetRangeUser(0, 500);

    // User fit region
    Double_t lwlim = -40;
    Double_t uplim = 400;
    Int_t Npar = 7;

    // Fit Function
    TF1 *func1 = new TF1("myfit", fitFunc, lwlim, uplim, Npar);
    func1->SetLineColor(kRed+1);
    func1->SetLineWidth(2);

    TF1 *func2 = new TF1("myfit2", fitFunc, lwlim, uplim, Npar-1);
    func2->SetLineColor(kBlue);
    func2->SetLineWidth(2);

    TF1 *func3 = new TF1("myfit3", fitFunc, lwlim, uplim, Npar);
    func3->SetLineColor(kGreen);
    func3->SetLineWidth(2);

    TF1 *func4 = new TF1("myfit4", fitFunc, lwlim, uplim, Npar);
    func4->SetLineColor(kOrange);
    func4->SetLineWidth(2);

    //Set initial values and parameter names
    func1->SetParameter(0,400.2);
    func1->SetParameter(1, 90);
    func1->SetParameter(2, 20);
    func1->SetParameter(3,400.2);
    func1->SetParameter(4, 270);
    func1->SetParameter(5, 20);
    func1->SetParameter(6, 150);

    func2->SetParameter(0,400.2);
    func2->SetParameter(1, 90);
    func2->SetParameter(2, 20);
    func2->SetParameter(3,400.2);
    func2->SetParameter(4, 270);
    func2->SetParameter(5, 20);

    func3->SetParameter(0,100.2);
    func3->SetParameter(1, 90);
    func3->SetParameter(2, 20);
    func3->SetParameter(3,100.2);
    func3->SetParameter(4, 270);
    func3->SetParameter(5, 20);
    func3->SetParameter(6, -2);
  
    func4->SetParameter(0,100.2);
    func4->SetParameter(1, 90);
    func4->SetParameter(2, 20);
    func4->SetParameter(3,100.2);
    func4->SetParameter(4, 270);
    func4->SetParameter(5, 20);
    func4->SetParameter(6, -2);
  

    // func1->SetParNames("A","B","C");
    //func1->SetParLimits(2, -10, -4);
    //func1->FixParameter(0, 1.186e-1);

    // Draw
    DataSaver4[0]->Draw("AP");
    DataSaver4[0]->Fit("myfit4","UR");


    Double_t func4chi2 = func4->GetChisquare();
    Double_t func4ndf = func4->GetNDF();
    cout << "\n Chi2: " << func4chi2  << endl;
    cout << " ndf: " << func4ndf  << endl;    
    cout << " Chi2/ndf: " << func4chi2/func4ndf  << endl << endl;

    DataSaver3[0]->Draw("P");
    DataSaver3[0]->Fit("myfit3","UR");


    Double_t func3chi2 = func3->GetChisquare();
    Double_t func3ndf = func3->GetNDF();
    cout << "\n Chi2: " << func3chi2  << endl;
    cout << " ndf: " << func3ndf  << endl;    
    cout << " Chi2/ndf: " << func3chi2/func3ndf  << endl << endl;

    DataSaver2[0]->Draw("P");
    DataSaver2[0]->Fit("myfit2","UR");


    Double_t func2chi2 = func2->GetChisquare();
    Double_t func2ndf = func2->GetNDF();
    cout << "\n Chi2: " << func2chi2  << endl;
    cout << " ndf: " << func2ndf  << endl;    
    cout << " Chi2/ndf: " << func2chi2/func2ndf  << endl << endl;

    DataSaver[0]->Draw("P");
    DataSaver[0]->Fit("myfit","UR");


    Double_t chi2 = func1->GetChisquare();
    Double_t ndf = func1->GetNDF();
    cout << "\n Chi2: " << chi2 << endl;
    cout << " ndf: " << ndf << endl;    
    cout << " Chi2/ndf: " << chi2/ndf << endl << endl;

    c1->Modified();
    c1->Update();
    while(c1->WaitPrimitive()) gSystem->ProcessEvents();
    c1->Print("pet/sessao3_gaus.pdf");

    delete d1;
    delete c1;
}