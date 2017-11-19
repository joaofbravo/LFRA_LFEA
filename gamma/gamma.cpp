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
#include "TPaveStats.h"
#include "TF1.h"
#include "TLegend.h"
#include "TH1F.h"
#include "TRandom.h"
#include <ctime>
#include "TFrame.h"
#include <fstream>

double linear(double *x, double *par){return (par[0]*x[0] + par[1]);}

using namespace std;
int main(){
    string FILE0 = "gamma/calibracao1.data";
    string FILE1 = "gamma/calibracao2.data";
    string FILE2 = "gamma/atenuacao.data";
    //gStyle->SetOptFit(1111);
    vector<TGraphErrors*> DataSaver;
    DataSaver.push_back(new TGraphErrors(FILE0.c_str(),"%lg %lg %lg %lg",""));
    DataSaver.push_back(new TGraphErrors(FILE1.c_str(),"%lg %lg %lg %lg",""));
    DataSaver.push_back(new TGraphErrors(FILE2.c_str(),"%lg %lg %lg",""));
    TApplication* theApp = new TApplication("App", 0, 0);

    TCanvas* c1 = new TCanvas("c1", "SOLUTION1", 1400, 1000);
    TPad* d1 = new TPad("Draw","Pad1",0,0,1,1,0,1);
    d1->Draw();
    d1->cd();
    d1->SetGrid();
    DataSaver[0]->SetLineWidth(3);
    DataSaver[0]->SetLineColor(2);
    DataSaver[0]->SetMarkerColor(2);
    DataSaver[0]->SetMarkerStyle(21);
    DataSaver[0]->GetXaxis()->SetTitle("Canal");
    DataSaver[0]->GetYaxis()->SetTitle("E[keV]");
    DataSaver[0]->SetTitle("");
    DataSaver[0]->SetFillColor(6);

    TF1* func1 = new TF1("myfit1",linear,0,1000,2);
    func1->SetLineColor(4);
    func1->SetLineWidth(2);
    DataSaver[0]->Fit(func1,"U", 0,1000);

    cout << "Chi^2/ngl do primeiro fit : " << func1->GetChisquare()/func1->GetNDF() << "\n\n" <<endl;

    DataSaver[0]->Draw("ap");
    c1->Modified();
    c1->Update();
    while(c1->WaitPrimitive()) gSystem->ProcessEvents();
    c1->Print("gamma/Calibracao1.pdf");

    //////////////////////////////////////////////////////////////////////////
    TCanvas* c2 = new TCanvas("c2", "SOLUTION2", 1400, 1000);
    TPad* d2 = new TPad("Draw","Pad2",0,0,1,1,0,1);
    d2->Draw();
    d2->cd();
    d2->SetGrid();
    DataSaver[1]->SetLineWidth(3);
    DataSaver[1]->SetLineColor(2);
    DataSaver[1]->SetMarkerColor(2);
    DataSaver[1]->SetMarkerStyle(21);
    DataSaver[1]->GetXaxis()->SetTitle("Canal");
    DataSaver[1]->GetYaxis()->SetTitle("E[keV]");
    DataSaver[1]->SetTitle("");
    DataSaver[1]->SetFillColor(6);

    TF1* func2 = new TF1("myfit2",linear,0,1000,2);
    func2->SetLineColor(4);
    func2->SetLineWidth(2);
    DataSaver[1]->Fit(func2,"U", 0,1000);

    cout << "Chi^2 do segundo fit : " << func2->GetChisquare()/func2->GetNDF() << "\n\n" <<endl;


    DataSaver[1]->Draw("ap");
    c2->Modified();
    c2->Update();
    while(c2->WaitPrimitive()) gSystem->ProcessEvents();
    c2->Print("gamma/Calibracao2.pdf");

    /////////////////////////////////////////////////////////////////////////
    TCanvas* c3 = new TCanvas("c3", "SOLUTION3", 1400, 1000);
    TPad* d3 = new TPad("Draw","Pad3",0,0,1,1,0,1);
    d3->Draw();
    d3->cd();
    d3->SetGrid();
    DataSaver[2]->SetMinimum(0);
    DataSaver[2]->SetLineWidth(3);
    DataSaver[2]->SetLineColor(2);
    DataSaver[2]->SetMarkerColor(2);
    DataSaver[2]->SetMarkerStyle(21);
    DataSaver[2]->GetXaxis()->SetTitle("x (g cm^-2)");
    DataSaver[2]->GetYaxis()->SetTitle("ln(I0/I)");
    DataSaver[2]->SetTitle("");
    DataSaver[2]->SetFillColor(6);

    TF1* func3 = new TF1("myfit3",linear,0,1000,2);
    func3->SetLineColor(4);
    func3->SetLineWidth(2);
    DataSaver[2]->Fit(func3,"U", 0,1000);

    cout << "Chi^2 do terceiro fit (ATENUAÇÂO): " << func3->GetChisquare()/func3->GetNDF() << "\n\n" <<endl;


    DataSaver[2]->Draw("ap");
    c3->Modified();
    c3->Update();
    while(c3->WaitPrimitive()) gSystem->ProcessEvents();
    c3->Print("gamma/atenuacao.pdf");

    /////////////////////////////////////////////////////////////////////////

    delete func1;
    delete func2;
    delete func3;
    delete d1;
    delete c1;
    delete d2;
    delete c2;
    delete d3;
    delete c3;
}
