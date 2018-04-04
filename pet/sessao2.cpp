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
	//Double_t fitval = par[0]*(2*par[1]*par[1]*TMath::ACos(TMath::Abs(15.6*0.3937*x[0]+2*par[2])*TMath::Pi()/(2*par[1]*180))-0.001*TMath::Abs(15.6*0.3937*x[0]+2*par[2])*TMath::Pi()/(2*180));//*TMath::Sqrt(4*par[1]*par[1]));//-TMath::Abs(15.6*0.3937*x[0]+2*par[2])*TMath::Pi()/(180)*TMath::Abs(15.6*0.3937*x[0]+2*par[2])*TMath::Pi()/(180)));
    Double_t fitval = par[0]*TMath::Gaus(x[0],par[1],par[2]);;
	return fitval;
}


// Main routine
int main()
{
    // Create TGraphErrors from file
    string FILE1 = "pet/sessao2_data_32.data";
    vector<TGraphErrors*> DataSaver;
    DataSaver.push_back(new TGraphErrors(FILE1.c_str(),"%lg %lg %lg %lg",""));


    string FILE2 = "pet/sessao2_data_16.data";
    vector<TGraphErrors*> DataSaver2;
    DataSaver2.push_back(new TGraphErrors(FILE2.c_str(),"%lg %lg %lg %lg",""));


    string FILE3 = "pet/sessao2_data_0.data";
    vector<TGraphErrors*> DataSaver3;
    DataSaver3.push_back(new TGraphErrors(FILE3.c_str(),"%lg %lg %lg %lg",""));


    string FILE4 = "pet/sessao2_data_min16.data";
    vector<TGraphErrors*> DataSaver4;
    DataSaver4.push_back(new TGraphErrors(FILE4.c_str(),"%lg %lg %lg %lg",""));

    
    string FILE5 = "pet/sessao2_data_24.data";
    vector<TGraphErrors*> DataSaver5;
    DataSaver5.push_back(new TGraphErrors(FILE5.c_str(),"%lg %lg %lg %lg",""));

    string FILE6 = "pet/sessao2_data_08.data";
    vector<TGraphErrors*> DataSaver6;
    DataSaver6.push_back(new TGraphErrors(FILE6.c_str(),"%lg %lg %lg %lg",""));

    string FILE7 = "pet/sessao2_data_min08.data";
    vector<TGraphErrors*> DataSaver7;
    DataSaver7.push_back(new TGraphErrors(FILE7.c_str(),"%lg %lg %lg %lg",""));

    string FILE8 = "pet/sessao2_data_min24.data";
    vector<TGraphErrors*> DataSaver8;
    DataSaver8.push_back(new TGraphErrors(FILE8.c_str(),"%lg %lg %lg %lg",""));


    string FILE9 = "pet/sessao2_data_min32.data";
    vector<TGraphErrors*> DataSaver9;
    DataSaver9.push_back(new TGraphErrors(FILE9.c_str(),"%lg %lg %lg %lg",""));

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


    DataSaver5[0]->SetLineColor(kViolet+2);
    DataSaver5[0]->SetLineWidth(2);
    DataSaver5[0]->SetMarkerStyle(1);
    DataSaver5[0]->SetMarkerColor(0);
    DataSaver5[0]->SetFillColor(0);
    DataSaver5[0]->SetTitle("");

    DataSaver6[0]->SetLineColor(kGray+2);
    DataSaver6[0]->SetLineWidth(2);
    DataSaver6[0]->SetMarkerStyle(1);
    DataSaver6[0]->SetMarkerColor(0);
    DataSaver6[0]->SetFillColor(0);
    DataSaver6[0]->SetTitle("");


    DataSaver7[0]->SetLineColor(kYellow+2);
    DataSaver7[0]->SetLineWidth(2);
    DataSaver7[0]->SetMarkerStyle(1);
    DataSaver7[0]->SetMarkerColor(0);
    DataSaver7[0]->SetFillColor(0);
    DataSaver7[0]->SetTitle("");

    DataSaver8[0]->SetLineColor(kGray+2);
    DataSaver8[0]->SetLineWidth(2);
    DataSaver8[0]->SetMarkerStyle(1);
    DataSaver8[0]->SetMarkerColor(0);
    DataSaver8[0]->SetFillColor(0);
    DataSaver8[0]->SetTitle("");

    DataSaver9[0]->SetLineColor(kGray+2);
    DataSaver9[0]->SetLineWidth(2);
    DataSaver9[0]->SetMarkerStyle(1);
    DataSaver9[0]->SetMarkerColor(0);
    DataSaver9[0]->SetFillColor(0);
    DataSaver9[0]->SetTitle("");


    // Axis
    DataSaver3[0]->GetXaxis()->SetTitle("#theta (#º)");
    DataSaver3[0]->GetYaxis()->SetTitle("R_c (cts/s)");

    DataSaver3[0]->GetXaxis()->SetRangeUser(-50.,50);
    DataSaver3[0]->GetYaxis()->SetRangeUser(0, 430);

    // User fit region
    Double_t lwlim = -40;
    Double_t uplim = 40;
    Int_t Npar = 3;

    // Fit Function
    TF1 *func1 = new TF1("myfit", fitFunc, lwlim, uplim, Npar);
    func1->SetLineColor(kRed+1);
    func1->SetLineWidth(2);

    TF1 *func2 = new TF1("myfit2", fitFunc, lwlim, uplim, Npar);
    func2->SetLineColor(kBlue);
    func2->SetLineWidth(2);

    TF1 *func3 = new TF1("myfit3", fitFunc, lwlim, uplim, Npar);
    func3->SetLineColor(kGreen);
    func3->SetLineWidth(2);

    TF1 *func4 = new TF1("myfit4", fitFunc, lwlim, uplim, Npar);
    func4->SetLineColor(kOrange);
    func4->SetLineWidth(2);

    TF1 *func5 = new TF1("myfit5", fitFunc, lwlim, uplim, Npar);
    func5->SetLineColor(kViolet);
    func5->SetLineWidth(2);

    TF1 *func6 = new TF1("myfit6", fitFunc, lwlim, uplim, Npar);
    func6->SetLineColor(kGray);
    func6->SetLineWidth(2);


    TF1 *func7 = new TF1("myfit7", fitFunc, lwlim, uplim, Npar);
    func7->SetLineColor(kYellow);
    func7->SetLineWidth(2);


    TF1 *func8 = new TF1("myfit8", fitFunc, lwlim, uplim, Npar);
    func8->SetLineColor(kGray);
    func8->SetLineWidth(2);

    TF1 *func9 = new TF1("myfit9", fitFunc, lwlim, uplim, Npar);
    func9->SetLineColor(kGray);
    func9->SetLineWidth(2);

    //Set initial values and parameter names
    func1->SetParameter(0,400);
    
    func1->SetParameter(1, 20);
    //func1->SetParameter(1, 1.01);
    
    func1->SetParameter(2, 2.5);
    

    func2->SetParameter(0,400.2);
    func2->SetParameter(1, 15);
    func2->SetParameter(2, 5);
    
    func3->SetParameter(0,400.2);
    func3->SetParameter(1, 0);
    func3->SetParameter(2, 5);

    func4->SetParameter(0,400);
    func4->SetParameter(1, -15);
    func4->SetParameter(2, 5);

    func5->SetParameter(0,400);
    func5->SetParameter(1, 17.5);
    func5->SetParameter(2, 5);


    func6->SetParameter(0,400);
    func6->SetParameter(1, 5);
    func6->SetParameter(2, 5);

    func7->SetParameter(0,400);
    func7->SetParameter(1, -5);
    func7->SetParameter(2, 5);

    func8->SetParameter(0,400);
    func8->SetParameter(1, -17.5);
    func8->SetParameter(2, 5);

    func9->SetParameter(0,400);
    func9->SetParameter(1, -20);
    func9->SetParameter(2, 5);

    //func1->SetParNames("A","B","C");
    //func1->SetParLimits(2, -10, -4);
    //func1->FixParameter(0, 1.186e-1);

    // Draw
    DataSaver[0]->Draw("AP");
    DataSaver[0]->Fit("myfit","UR");


    DataSaver[0]->Draw("P");
    DataSaver[0]->Fit("myfit","UR");



    DataSaver2[0]->Draw("P");
    DataSaver2[0]->Fit("myfit2","UR");


  


    DataSaver4[0]->Draw("P");
    DataSaver4[0]->Fit("myfit4","UR");


    DataSaver5[0]->Draw("P");
    DataSaver5[0]->Fit("myfit5","UR");


    

    DataSaver6[0]->Draw("P");
    DataSaver6[0]->Fit("myfit6","UR");




    DataSaver7[0]->Draw("P");
    DataSaver7[0]->Fit("myfit7","UR");


    


    DataSaver8[0]->Draw("P");
    DataSaver8[0]->Fit("myfit8","UR");



    DataSaver9[0]->Draw("P");
    DataSaver9[0]->Fit("myfit9","UR");

    
    Double_t chi2 = func1->GetChisquare();
    Double_t ndf = func1->GetNDF();
    cout << "\n Chi2: " << chi2 << endl;
    cout << " ndf: " << ndf << endl;    
    cout << " Chi2/ndf: " << chi2/ndf << endl << endl;

    Double_t func5chi2 = func5->GetChisquare();
    Double_t func5ndf = func5->GetNDF();
    cout << "\n Chi2: " << func5chi2  << endl;
    cout << " ndf: " << func5ndf  << endl;    
    cout << " Chi2/ndf: " << func5chi2/func5ndf  << endl << endl;


    Double_t func2chi2 = func2->GetChisquare();
    Double_t func2ndf = func2->GetNDF();
    cout << "\n Chi2: " << func2chi2  << endl;
    cout << " ndf: " << func2ndf  << endl;    
    cout << " Chi2/ndf: " << func2chi2/func2ndf  << endl << endl;

    Double_t func6chi2 = func6->GetChisquare();
    Double_t func6ndf = func6->GetNDF();
    cout << "\n Chi2: " << func6chi2  << endl;
    cout << " ndf: " << func6ndf  << endl;    
    cout << " Chi2/ndf: " << func6chi2/func6ndf  << endl << endl;

    Double_t func3chi2 = func3->GetChisquare();
    Double_t func3ndf = func3->GetNDF();
    cout << "\n Chi2: " << func3chi2  << endl;
    cout << " ndf: " << func3ndf  << endl;    
    cout << " Chi2/ndf: " << func3chi2/func3ndf  << endl << endl;


    Double_t func7chi2 = func7->GetChisquare();
    Double_t func7ndf = func7->GetNDF();
    cout << "\n Chi2: " << func7chi2  << endl;
    cout << " ndf: " << func7ndf  << endl;    
    cout << " Chi2/ndf: " << func7chi2/func7ndf  << endl << endl;


    Double_t func4chi2 = func4->GetChisquare();
    Double_t func4ndf = func4->GetNDF();
    cout << "\n Chi2: " << func4chi2  << endl;
    cout << " ndf: " << func4ndf  << endl;    
    cout << " Chi2/ndf: " << func4chi2/func4ndf  << endl << endl;


    Double_t func8chi2 = func8->GetChisquare();
    Double_t func8ndf = func8->GetNDF();
    cout << "\n Chi2: " << func8chi2  << endl;
    cout << " ndf: " << func8ndf  << endl;    
    cout << " Chi2/ndf: " << func8chi2/func8ndf  << endl << endl;


    Double_t func9chi2 = func9->GetChisquare();
    Double_t func9ndf = func9->GetNDF();
    cout << "\n Chi2: " << func9chi2  << endl;
    cout << " ndf: " << func9ndf  << endl;    
    cout << " Chi2/ndf: " << func9chi2/func9ndf  << endl << endl;

   


    c1->Modified();
    c1->Update();
    while(c1->WaitPrimitive()) gSystem->ProcessEvents();
    c1->Print("pet/sessao2_gaus.pdf");

    delete d1;
    delete c1;
}