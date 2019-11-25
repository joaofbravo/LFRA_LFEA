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
#include "TGaxis.h"
#include "TGraph.h"
#include "TGraph.h"
#include "TGraphErrors.h"
#include "TAxis.h"
#include "TMathText.h"
#include "TAxis.h"
#include "TPaveStats.h"
#include "TF1.h"
#include "TMath.h"
#include "TLegend.h"
#include "TH1F.h"
#include "TRandom.h"
#include <ctime>
#include "TFrame.h"
#include <fstream>

double r0 = 2.82E-13;
double Z = 13.;
double a = 662./511.;
double exp(double* x, double* par){return TMath::Exp(par[0])*pow(x[0],par[1]);}
double linear(double *x, double* par){return (par[0]*x[0] + par[1]);}
double dsdoKN(double x){
    return Z*pow(r0,2)*pow(1/(1+a*(1-cos(x))),2)*((1+cos(x)*cos(x))/2)*(1+(a*a*pow(1-cos(x),2))/((1+cos(x)*cos(x))*(1+a*(1-cos(x)))));
}
double dsdoKNNormalized(double*x, double* par){
    return dsdoKN(x[0])/dsdoKN(20*TMath::Pi()/180);
}
double dsdoTH(double x){
    return r0*r0*Z*(1+cos(x)*cos(x))/2;
}
double dsdoTHNormalized(double* x, double* par){
    return dsdoTH(x[0])/dsdoTH(20*TMath::Pi()/180);
}

using namespace std;
int main(){
    
    string FILE0 = "compton/calibracao1.data";
    string FILE1 = "compton/massaeletrao.data";
    string FILE2 = "compton/secaoeficaz.data";
    string FILE3 = "compton/eficiencia.data";
    vector<TGraphErrors*> DataSaver;
    DataSaver.push_back(new TGraphErrors(FILE0.c_str(),"%lg %lg %lg %lg",""));
    DataSaver.push_back(new TGraphErrors(FILE1.c_str(),"%lg %lg %lg %lg",""));
    DataSaver.push_back(new TGraphErrors(FILE2.c_str(),"%lg %lg %lg %lg",""));
    DataSaver.push_back(new TGraphErrors(FILE3.c_str(),"%lg %lg %lg %lg",""));
    TApplication* theApp = new TApplication("App", 0, 0);
    
    ///////////////////////////////////////////////////////////
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
    DataSaver[0]->Draw("ap");
    
    TF1* func1 = new TF1("myfit1",linear,0,1000,2);
    func1->SetLineColor(4);
    func1->SetLineWidth(2);
    DataSaver[0]->Fit(func1,"U", 0,1000);
    
    cout << "Chi^2/ngl do primeiro fit : " << func1->GetChisquare()/func1->GetNDF() << "\n\n" <<endl;
    
    c1->Modified();
    c1->Update();
    while(c1->WaitPrimitive()) gSystem->ProcessEvents();
    c1->Print("compton/Calibracao1.pdf");
    
    ///////////////////////////////////////////////////////////
    TCanvas* c2 = new TCanvas("c2", "SOLUTION1", 1400, 1000);
    TPad* d2 = new TPad("Draw","Pad1",0,0,1,1,0,1);
    d2->Draw();
    d2->cd();
    d2->SetGrid();
    
    DataSaver[1]->SetLineWidth(3);
    DataSaver[1]->SetLineColor(2);
    DataSaver[1]->SetMarkerColor(2);
    DataSaver[1]->SetMarkerStyle(21);
    DataSaver[1]->GetXaxis()->SetTitle("1 - cos(#theta) (rad)");
    DataSaver[1]->GetYaxis()->SetTitle("1/E_{#lambda}(1/keV)");
    DataSaver[1]->SetTitle("");
    DataSaver[1]->SetFillColor(6);
    TGaxis::SetMaxDigits(2);
    DataSaver[1]->Draw("ap");
    
    TF1* func2 = new TF1("myfit1",linear,0,1000,2);
    func2->SetLineColor(4);
    func2->SetLineWidth(2);
    func2->SetParameters(1/511.,1/662.);
    DataSaver[1]->Fit(func2,"U",0,1000);
    
    cout << "Chi^2/ngl do segundo fit : " << func2->GetChisquare()/func2->GetNDF() << "\n\n" <<endl;

    c2->Modified();
    c2->Update();
    while(c2->WaitPrimitive()) gSystem->ProcessEvents();
    c2->Print("compton/massaeletrao.pdf");
    
    ///////////////////////////////////////////////////////////
    TCanvas* c3 = new TCanvas("c3", "SOLUTION1", 1400, 1000);
    TPad* d3 = new TPad("Draw","Pad1",0,0,1,1,0,1);
    d3->Draw();
    d3->cd();
    d3->SetGrid();
    TGaxis::SetMaxDigits(3);
    
    DataSaver[2]->SetLineWidth(1);
    DataSaver[2]->SetLineColor(2);
    DataSaver[2]->SetMarkerColor(2);
    DataSaver[2]->SetMarkerStyle(21);
    DataSaver[2]->GetXaxis()->SetTitle("#theta (rad)");
    DataSaver[2]->GetYaxis()->SetTitle("(d#sigma/d#Omega)/(d#sigma/d#Omega)_{20^{#circ}}");
    //DataSaver[2]->GetYaxis()->SetRangeUser(0., 9.);
    DataSaver[2]->SetTitle("");
    DataSaver[2]->SetFillColor(6);
    DataSaver[2]->Draw("ap");
    
    TF1* funcdsdoKN = new TF1("dsdoKN",dsdoKNNormalized,0,2,0);
    TF1* funcdsdoTH = new TF1("dsdoKN",dsdoTHNormalized,0,2,0);
    funcdsdoKN->SetLineColor(4); //azul claro
    funcdsdoTH->SetLineColor(7); //azul escuro
    funcdsdoKN->Draw("same");
    funcdsdoTH->Draw("same");

    
    c3->Modified();
    c3->Update();
    while(c3->WaitPrimitive()) gSystem->ProcessEvents();
    c3->Print("compton/secaoeficaz.pdf");
    
    ///////////////////////////////////////////////////////////
    
    TCanvas* c4 = new TCanvas("c4", "SOLUTION1", 1400, 1000);
    TPad* d4 = new TPad("Draw","Pad1",0,0,1,1,0,1);
    d4->Draw();
    d4->cd();
    d4->SetGrid();
    DataSaver[3]->SetLineWidth(3);
    DataSaver[3]->SetLineColor(2);
    DataSaver[3]->SetMarkerColor(2);
    DataSaver[3]->SetMarkerStyle(21);
    DataSaver[3]->GetXaxis()->SetTitle("E(keV)");
    DataSaver[3]->GetYaxis()->SetTitle("#epsilon_{int}");
    DataSaver[3]->SetTitle("");
    DataSaver[3]->SetFillColor(6);
    DataSaver[3]->Draw("ap");
    
    TF1* func4 = new TF1("exp",exp,0,1000,2);
    func4->SetLineColor(4);
    func4->SetLineWidth(2);
    DataSaver[3]->Fit(func4,"U",0,1000);
    
    cout << "Chi^2/ngl do terceiro fit : " << func4->GetChisquare()/func4->GetNDF() << "\n\n" <<endl;
    
    c4->Modified();
    c4->Update();
    while(c4->WaitPrimitive()) gSystem->ProcessEvents();
    c4->Print("compton/eficiencia.pdf");
    
    ///////////////////////////////////////////////////////////
    
    delete func1;
    delete d1;
    delete c1;
    
    delete func2;
    delete d2;
    delete c2;
    
    delete funcdsdoTH;
    delete funcdsdoKN;
    delete d3;
    delete c3;
    
    delete func4;
    delete d4;
    delete c4;
    
}
