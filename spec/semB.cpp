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
// #include "TGraph.h"
#include "TGraphErrors.h"
#include "TF1.h"
// #include "TFormula.h"
#include "TMath.h"
#include "TRandom.h"
#include "TLine.h"
#include "TLegend.h"

using namespace std;


// Fit Function
Double_t fitFunc(Double_t *x, Double_t *par)
{
	Double_t fitval = par[0]*sqrt(x[0]-par[1]);
	return fitval;
}


// Main routine
int main()
{
    // Create TGraphErrors from file
    string FILE1 = "spec/data/semB.data";
    vector<TGraphErrors*> DataSaver;
    DataSaver.push_back(new TGraphErrors(FILE1.c_str(),"%lg %lg %lg","")); // X,Y,eY

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
    DataSaver[0]->SetMarkerSize(2);
    DataSaver[0]->SetFillColor(0);
    DataSaver[0]->SetTitle("");

    // Axis
    DataSaver[0]->GetXaxis()->SetTitle("q");
    DataSaver[0]->GetYaxis()->SetTitle("#chi_{q} (#circ)");
    // DataSaver[0]->GetXaxis()->SetRangeUser(0, 2);
    // DataSaver[0]->GetYaxis()->SetRangeUser(0, 10);

    // User fit region
    Double_t lwlim = 0.4;
    Double_t uplim = 6;
    Int_t Npar = 2;

    // Fit Function
    TF1 *func1 = new TF1("myfit", fitFunc, lwlim, uplim, Npar);
    func1->SetLineColor(kBlue);
    func1->SetLineWidth(2);

    // Set initial values and parameter names
    func1->SetParameter(0, 0.74439);
    func1->SetParameter(1, 0.);
    // func1->SetParameter(2, 0.);

    // func1->SetParNames("A","B","C");
    // func1->SetParLimits(2, -10, -4);
    // func1->FixParameter(0, 1.186e-1);

    // Draw
    DataSaver[0]->Draw("AP");
    DataSaver[0]->Fit("myfit","UR");

    // Legend
    // TLegend *leg = new TLegend(0.68,0.82,0.88,0.88);
    // leg->SetFillColor(0);
    // leg->SetBorderSize(0);
    // leg->SetTextSize(0.05);
    // leg->AddEntry(func1,"Func do crl","lp");
    // leg->Draw();

    // Statistics
    Double_t chi2 = func1->GetChisquare();
    Double_t ndf = func1->GetNDF();
    cout << "\n Chi2: " << chi2 << endl;
    cout << " ndf: " << ndf << endl;
    cout << " Chi2/ndf: " << chi2/ndf << endl << endl;

    c1->Modified();
    c1->Update();
    while(c1->WaitPrimitive()) gSystem->ProcessEvents();
    c1->Print("spec/results/semB.pdf");

    delete d1;
    delete c1;
}