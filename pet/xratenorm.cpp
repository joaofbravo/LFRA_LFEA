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
#include "TLine.h"
#include "TLegend.h"

using namespace std;


// Fit Function
Double_t fitFunc(Double_t *x, Double_t *par)
{
	Double_t fitval = par[0]/par[2]*exp(-(x[0]-par[1])*(x[0]-par[1])/2/par[2]/par[2]);
	return fitval;
}


// Main routine
int main()
{
    // Create TGraphErrors from file
    string FILE1 = "pet/data/xratenorm.data";
    vector<TGraphErrors*> DataSaver;
    DataSaver.push_back(new TGraphErrors(FILE1.c_str(),"%lg %lg %lg %lg",""));

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
    DataSaver[0]->SetLineWidth(1);
    DataSaver[0]->SetMarkerStyle(4);
    DataSaver[0]->SetMarkerSize(1);
    DataSaver[0]->SetMarkerColor(0);
    DataSaver[0]->SetFillColor(0);
    DataSaver[0]->SetTitle("Coincidencias vs. Posicao em x");

    // Axis
    DataSaver[0]->GetXaxis()->SetTitle("X ('')");
    DataSaver[0]->GetYaxis()->SetTitle("Rate (cts/s)");
    DataSaver[0]->GetXaxis()->SetRangeUser(-2.1, 2.1);
    // DataSaver[0]->GetYaxis()->SetRangeUser(0, 10);

    // User fit region
    Double_t lwlim = -2.1;
    Double_t uplim = 2.1;
    Int_t Npar = 3;

    // Fit Function
    TF1 *func1 = new TF1("myfit", fitFunc, lwlim, uplim, Npar);
    func1->SetLineColor(kBlue);
    func1->SetLineWidth(2);

    // Set initial values and parameter names
    func1->SetParameter(0, 0.5);
    func1->SetParameter(1, 0.);
    func1->SetParameter(2, 0.33);

    func1->SetParNames("A","mu","sigma");
    //func1->SetParLimits(2, -10, -4);
    //func1->FixParameter(0, 1.186e-1);

    // Draw
    DataSaver[0]->Draw("AP");
    DataSaver[0]->Fit("myfit","UR");

    // Vertical Lines - Shadow Region
    Double_t xlow3sigma = func1->GetParameter(1)-3*func1->GetParameter(2);
    Double_t xup3sigma = func1->GetParameter(1)+3*func1->GetParameter(2);

    TLine* line1 = new TLine(xlow3sigma, DataSaver[0]->GetYaxis()->GetXmin(), 
    	xlow3sigma, DataSaver[0]->GetYaxis()->GetXmax());
    TLine* line2 = new TLine(xup3sigma, DataSaver[0]->GetYaxis()->GetXmin(), 
    	xup3sigma, DataSaver[0]->GetYaxis()->GetXmax());
    line1->SetVertical(kTRUE);
    line2->SetVertical(kTRUE);
    line1->SetLineColor(kBlack);
    line2->SetLineColor(kBlack);
    line1->SetLineWidth(4);
    line2->SetLineWidth(4);
    line1->Draw();
    line2->Draw();

    // Statistics
    Double_t chi2 = func1->GetChisquare();
    Double_t ndf = func1->GetNDF();
    cout << "\n Chi2: " << chi2 << endl;
    cout << " ndf: " << ndf << endl;    
    cout << " Chi2/ndf: " << chi2/ndf << endl << endl;    
    cout << " mu+-3sigma: " << xlow3sigma << " ; " << xup3sigma << " ('')" << endl << endl;

    c1->Modified();
    c1->Update();
    while(c1->WaitPrimitive()) gSystem->ProcessEvents();
    c1->Print("pet/results/xratenorm.pdf");

    delete d1;
    delete c1;
}