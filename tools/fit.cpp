#include <iostream>
#include <fstream>
#include <string>
#include <cmath>

using namespace std;

// Fit Function
Double_t fitFunc(Double_t *x, Double_t *par)
{
    return par[1]*sin(par[0]*(x[0]-par[2])) / (par[0]*(x[0]-par[2])) + par[3];
}

// Main routine

void fit()
{
    // Lines
    const int dim = 10;

    // Constants
    const double alpha = 1.;

    // Variables
    double tau[dim], etau[dim];
    double K[dim], eK[dim];
    double ptau, petau, pK, peK;

    // Open the file
    ifstream table("D05B.txt");

    if (table.is_open())
    {
        for(int i=0; i<dim; i++)
        {
            table >> ptau >> pK >> petau >> peK;

            // Data treatment:
            tau[i] = ptau*1e9;
            etau[i] = petau*1e9;

            K[i] = pK;
            eK[i] = peK;
        }
    }
    else cout << "Unable to open file!" << endl << endl;

    // Canvas
    TCanvas *c1 = new TCanvas("c1", "LCET O CARALHO", 1220, 0, 700, 500);
    c1->SetFillColor(kWhite);
    c1->SetGrid();
    c1->GetFrame()->SetFillColor(21);
    c1->GetFrame()->SetBorderSize(12);

    // TGraph
    TGraphErrors *graph = new TGraphErrors(dim, tau, K, etau, eK);
    graph->SetTitle("");
    graph->SetLineColor(kBlack);
    graph->SetLineWidth(1);
    graph->SetMarkerColor(kBlack);
    graph->SetMarkerStyle(1); 

    // Axis Labels
    graph->GetXaxis()->SetTitle("#tau (ns)");
    // graph->GetXaxis()->SetRangeUser(0,2);
    graph->GetYaxis()->SetTitle("K (u.a.)");
    // graph->GetYaxis()->SetRangeUser(0.2,2.2);

    // User fit region
    double lwlim = 0.;
    double uplim = 4.;
    int Npar = 4;

    TF1 *func = new TF1("myfit", fitFunc, lwlim, uplim, Npar);
    func->SetLineColor(kRed);
    func->SetLineWidth(2);

    // Set initial values and parameter names
    func->SetParameter(0, 1.78512e+00);
    func->SetParameter(1, 6.89819e-01);
    func->SetParameter(2, 4.07951e-01);
    func->SetParameter(3, 6.49646e-01);

    func->SetParNames("dw/2","A","B","C");
    //func->SetParLimits(2, -10, -4);
    //func->FixParameter(0, 1.186e-1);
    //func->FixParameter(1, 8.5e-1);

    cout << endl;
    graph->Draw("AP");
    graph->Fit("myfit","UR");
    func->Draw("same");

    // Legend
    leg = new TLegend(0.1,0.7,0.3,0.8);
    leg->SetFillColor(0);
    leg->SetBorderSize(0);
    leg->SetTextSize(0.05);
    leg->AddEntry(func,"\\Delta x = \\frac{\\lambda}{sin \\theta}","lp");
    leg->Draw();

    Double_t chi2 = func->GetChisquare()/func->GetNDF();
    cout << "\nChi2/ndf value: " << chi2 << endl << endl;   
}