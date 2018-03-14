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


// Main routine
int main()
{
    // Create TGraphErrors from file
    string FILE1 = "pet/data/xrate.data";
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
    DataSaver[0]->SetLineColor(kBlue);
    DataSaver[0]->SetLineWidth(1);
    DataSaver[0]->SetMarkerStyle(4);
    DataSaver[0]->SetMarkerSize(1);
    DataSaver[0]->SetMarkerColor(0);
    DataSaver[0]->SetFillColor(0);
    DataSaver[0]->SetTitle("Coincidencias vs. Posicao em x");

    // Axis
    DataSaver[0]->GetXaxis()->SetTitle("X (pol)");
    DataSaver[0]->GetYaxis()->SetTitle("Rate (cts/s)");
    DataSaver[0]->GetXaxis()->SetRangeUser(-2.1, 2.1);
    // DataSaver[0]->GetYaxis()->SetRangeUser(0, 10);

    // Draw
    DataSaver[0]->Draw("AP");

    c1->Modified();
    c1->Update();
    while(c1->WaitPrimitive()) gSystem->ProcessEvents();
    c1->Print("pet/results/xrate.pdf");

    delete d1;
    delete c1;
}