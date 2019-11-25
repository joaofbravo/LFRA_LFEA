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
#include "TH2F.h"
#include "TF1.h"
#include "TFormula.h"
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
    ifstream table("pet/data/xy.data");

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

    // TH2F
    TH2F *hist1 = new TH2F("hist1", "Hist2D 1", bins, xlow, xup, bins, ylow, yup);
    hist1->SetStats(kFALSE);
    hist1->SetTitle("Coincidencias vs. Posicao da fonte");
    
    // Fill Hist
    for (int i = 0; i < dim; ++i) {
        hist1->Fill(xval[i], yval[i], weight[i]);
    }

    // Axis
    hist1->GetXaxis()->SetTitle("X ('')");
    hist1->GetYaxis()->SetTitle("Y ('')");
    // hist1->GetXaxis()->SetRangeUser(0, 2);
    // hist1->GetYaxis()->SetRangeUser(0, 10);

    // Draw
    hist1->Draw("COLZ");

    // Vertical Lines - Shadow Region
    Double_t xlow3sigma = -1.23402;
    Double_t xup3sigma = 1.28289;

    TLine* line1 = new TLine(xlow3sigma, ylow, xlow3sigma, yup);
    TLine* line2 = new TLine(xup3sigma, ylow, xup3sigma, yup);
    line1->SetVertical(kTRUE);
    line2->SetVertical(kTRUE);
    line1->SetLineColor(kBlack);
    line2->SetLineColor(kBlack);
    line1->SetLineWidth(4);
    line2->SetLineWidth(4);
    line1->Draw();
    line2->Draw();

    c1->Modified();
    c1->Update();
    while(c1->WaitPrimitive()) gSystem->ProcessEvents();
    c1->Print("pet/results/histXYshadow.pdf");

    delete d1;
    delete c1;
}