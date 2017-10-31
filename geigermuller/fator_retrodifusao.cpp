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
#include "TLegend.h"
#include "TRandom.h"

using namespace std;


// Fit Function
Double_t fitFunc(Double_t *x, Double_t *par)
{
    Double_t fitval = par[0]*x[0] + par[1];
    return fitval;
}


// Main routine
int main()
{
    // Create TGraphErrors from file
    string FILE1 = "geigermuller/fbksc.data";
    vector<TGraphErrors*> DataSaver;
    DataSaver.push_back(new TGraphErrors(FILE1.c_str(),"%lg %lg %lg",""));
    
    // Canvas
    TApplication* theApp = new TApplication("App", 0, 0);
    TCanvas* c1 = new TCanvas("c1", "Fit Solution", 0, 0, 1400, 1000);
    c1->SetFillColor(kWhite);
    c1->SetGrid();
    c1->GetFrame()->SetFillColor(21);
    c1->GetFrame()->SetBorderSize(12);
    
    // Pad
    TPad* d1 = new TPad("Draw", "Pad1", 0, 0, 1, 1, kWhite);
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
    DataSaver[0]->GetXaxis()->SetTitle("#sqrt{(Z+1)Z/M}");
    DataSaver[0]->GetYaxis()->SetTitle("f_{bksc}^{sat}");
    // DataSaver[0]->GetXaxis()->SetRangeUser(0, 1200);
    // DataSaver[0]->GetYaxis()->SetRangeUser(0, 10);

    // User fit region
    Double_t lwlim = 0.;
    Double_t uplim = 7.;
    Int_t Npar = 2;

    // Fit Function
    TF1 *func1 = new TF1("myfit", fitFunc, lwlim, uplim, Npar);
    func1->SetLineColor(kBlue);
    func1->SetLineWidth(2);

    // Draw
    DataSaver[0]->Draw("AP");
    DataSaver[0]->Fit("myfit", "UR");
    
    // Statistics
    Double_t chi2 = func1->GetChisquare();
    Double_t ndf = func1->GetNDF();
    cout << "\n Chi2: " << chi2 << endl;
    cout << " ndf: " << ndf << endl;    
    cout << " Chi2/ndf: " << chi2/ndf << endl << endl;
    
    c1->Modified();
    c1->Update();
    while(c1->WaitPrimitive()) gSystem->ProcessEvents();
    c1->Print("geigermuller/fator_retrodifusao.pdf");
    
    delete d1;
    delete c1;
}