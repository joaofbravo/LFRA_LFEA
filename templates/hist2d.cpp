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
// #include "TH1F.h"
#include "TH2F.h"
// #include "TF1.h"
// #include "TFormula.h"
#include "TMath.h"
#include "TRandom.h"
#include "TLine.h"
#include "TLegend.h"

using namespace std;


// Main routine
int main()
{
    // Lines - Bins - Constants
    const Int_t dim = 36*4;
    const Int_t bins = 99;
    const Double_t xlow = -2.1;
    const Double_t xup = 2.1;
    const Double_t ylow = -2.1;
    const Double_t yup = 2.1;

    // Variables
    double xval[dim], yval[dim], weight[dim];
    double X, Y, Weight;

    // Open the file
    ifstream table("tools/data/hist2D.data");

    if (table.is_open())
    {
        for(int i=0; i<dim; i++)
        {
            table >> X >> Y >> Weight;

            // Data Treatment:
            xval[i] = X;
            yval[i] = Y;
            weight[i] = Weight;
        }

        table.close();
    }
    else cout << "Unable to open file!" << endl << endl;

    // Canvas
    TApplication *theApp = new TApplication("App", 0, 0);
    TCanvas *c1 = new TCanvas("c1", "Fit Solution", 0, 0, 700, 500);
    c1->SetFillColor(kWhite);
    c1->SetGrid();
    c1->GetFrame()->SetFillColor(21);
    c1->GetFrame()->SetBorderSize(12);

    // Pad
    TPad *p1 = new TPad("p1", "Pad1", 0, 0, 1, 1, kWhite);
    // p1->SetLogy();
    p1->SetGrid();
    p1->Draw();
    p1->cd();

    // TH2F
    TH2F *hist1 = new TH2F("hist1", "Hist2D 1", bins, xlow, xup, bins, ylow, yup);
    // hist1->SetLineColor(kBlue);
    // hist1->SetFillColor(0);
    // hist1->SetMarkerStyle(1);
    // hist1->SetMarkerColor(kRed);
    // hist1->SetMarkerSize(2);
    hist1->SetStats(kFALSE);
    hist1->SetTitle("Coincidencias");
    
    // Fill Hist
    for (int i = 0; i < dim; ++i) {
        hist1->Fill(xval[i], yval[i], weight[i]);
    }

    // Axis
    hist1->GetXaxis()->SetTitle("X (pol)");
    hist1->GetYaxis()->SetTitle("Y (pol)");
    // hist1->GetXaxis()->SetRangeUser(0, 2);
    // hist1->GetYaxis()->SetRangeUser(0, 10);

    // Draw
    hist1->Draw("COLZ");

    // Legend
    // TLegend *leg = new TLegend(0.68,0.82,0.88,0.88);
    // leg->SetFillColor(0);
    // leg->SetBorderSize(0);
    // leg->SetTextSize(0.05);
    // leg->AddEntry(func1,"Func do crl","lp");
    // leg->Draw();

    c1->Modified();
    c1->Update();
    while(c1->WaitPrimitive()) gSystem->ProcessEvents();
    c1->Print("tools/results/hist2D.pdf");

    delete p1;
    delete c1;
}