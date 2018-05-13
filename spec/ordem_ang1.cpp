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
    Double_t fitval = par[0]*sqrt(par[1]-x[0]*x[0]);
    return fitval;
}


// Main routine
int main()
{
    // Lines - Constants
    const Int_t dim = 5;

    // Variables
    double xval[dim], exval[dim];
    double yval[dim], eyval[dim];
    double X, Y, eX, eY;

    // Open the file
    ifstream table("spec/data/ordem_ang1.data");

    if (table.is_open())
    {
        for(int i=0; i<dim; i++)
        {
            table >> X >> Y >> eX >> eY;

            // Data Treatment:
            xval[i] = sin(TMath::Pi()/2 - X*TMath::Pi()/180);
            exval[i] = eX*TMath::Pi()/180 * cos(TMath::Pi()/2 - X*TMath::Pi()/180);

            yval[i] = Y;
            eyval[i] = eY;
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

    // TGraphErrors
    TGraphErrors *graph1 = new TGraphErrors(dim, xval, yval, exval, eyval);
    graph1->SetLineColor(kRed);
    graph1->SetLineWidth(2);
    graph1->SetMarkerStyle(8);
    graph1->SetMarkerColor(0); // kPink
    graph1->SetMarkerSize(2);
    graph1->SetFillColor(0);
    graph1->SetTitle("");

    // Axis
    graph1->GetXaxis()->SetTitle("sin(#theta)");
    graph1->GetYaxis()->SetTitle("m");
    // graph1->GetXaxis()->SetRangeUser(0, 2);
    // graph1->GetYaxis()->SetRangeUser(0, 10);
    graph1->GetYaxis()->SetNdivisions(5,0,0);

    // User fit region
    Double_t lwlim = 0.5;
    Double_t uplim = 2.;
    Int_t Npar = 2;

    // Fit Function
    TF1 *func1 = new TF1("myfit", fitFunc, lwlim, uplim, Npar);
    func1->SetLineColor(kBlue);
    func1->SetLineWidth(2);

    // Set initial values and parameter names
    func1->SetParameter(0, 11500.);
    func1->SetParameter(1, 1.45);

    // func1->SetParNames("A","B");
    // func1->SetParLimits(1, -10, 4);
    // func1->FixParameter(0, 1.1);

    // Draw
    graph1->Draw("AP");
    graph1->Fit("myfit","UR");

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
    c1->Print("spec/results/ordem_ang1.pdf");

    delete d1;
    delete c1;
}