#include <stdio.h>
#include <cmath>
#include <cstdio>
#include <vector>
#include "TFormula.h"
#include "TROOT.h"
#include "TStyle.h"
#include "TApplication.h"
#include "TCanvas.h"
#include "TSystem.h"
#include "TGraph.h"
#include "TGraph.h"
#include "TGraphErrors.h"
#include "TAxis.h"
#include "TF1.h"
#include "TLegend.h"
#include "TH1F.h"
#include "TRandom.h"
#include <ctime>
#include "TFrame.h"


double fitfcn(double *x, double *par)
{
    double fitval = par[0]*x[0] + par[1];
    return fitval;
}

using namespace std;
int main(){
    string FILE1 = "geigermuller/RateNaoCorrigido.data";
    vector<TGraphErrors*> DataSaver;
    DataSaver.push_back(new TGraphErrors(FILE1.c_str(),"%lg %lg %lg",""));
    
    TApplication* theApp = new TApplication("App", 0, 0);
    TCanvas* c = new TCanvas("c", "SOLUTION", 1400, 1000);
    c->SetFillColor(42);
    c->SetGrid();
    c->GetFrame()->SetFillColor(21);
    c->GetFrame()->SetBorderSize(12);
    TPad* d1 = new TPad("Draw","Pad1",0,0,1,1,0,1);
    d1->Draw();
    d1->cd();

    DataSaver[0]->SetLineWidth(2);
    DataSaver[0]->SetLineColor(2);
    DataSaver[0]->SetMarkerColor(20);
    DataSaver[0]->GetXaxis()->SetTitle("Tensao [V]");
    DataSaver[0]->GetYaxis()->SetTitle("R_{m} / R_{o} []");
    DataSaver[0]->SetTitle("");
    DataSaver[0]->SetFillColor(6);
    DataSaver[0]->Draw("ap");
    
    TF1 *func = new TF1("myfit",fitfcn,700,2000,2);
    func->SetLineColor(4);
    func->SetLineWidth(2);
    DataSaver[0]->Fit("myfit", "U", "N");
    
    double chi2 = func->GetChisquare();
    double ndf = func->GetNDF();
    cout << "Chi2: " << chi2 << endl;
    cout << "ndf: " << ndf << endl;    
    cout << "Chi2/ndf: " << chi2/ndf << endl;
    
    c->Modified();
    c->Update();
    while(c->WaitPrimitive()) gSystem->ProcessEvents();
    c->Print("geigermuller/RateNaoCorrigido.pdf");
    
    delete d1;
    delete c;
}
