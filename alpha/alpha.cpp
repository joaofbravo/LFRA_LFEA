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
#include "TSpline.h"
#include "TMath.h"
#include "TLegend.h"
#include "TH1F.h"
#include "TRandom.h"
#include <ctime>
#include "TFrame.h"
#include <fstream>

double linear1(double *x, double* par){return (par[0]*x[0] + par[1]);}
double Secante(TSpline* T, double eps, double x0, double x1, double EF){
    int n = 0;
    while(fabs(x1-x0)>=eps && n<500){
        n++;
        double aux =x1-((T->Eval(x1)-EF)*(x1-x0))/((T->Eval(x1)-EF)-(T->Eval(x0)-EF));
        x0=x1;
        x1=aux;
    }
    return x1;
}
double deltaEtrocos(TSpline* T,double E0,double z,double density, int n){
    double deltaz = z/n;
    double Ei = 0;
    for(int i=0;i<n;++i){
        double Ej = Ei + T->Eval(E0-Ei)*density*deltaz;
        Ei = Ej;
    }
    return Ei;
}

using namespace std;
int main(){
    
    string FILE0 = "alpha/calibracao1.data";
    string FILE1 = "alpha/calibracao2.data";
    vector<TGraphErrors*> DataSaver;
    DataSaver.push_back(new TGraphErrors(FILE0.c_str(),"%lg %lg %lg %lg",""));
    DataSaver.push_back(new TGraphErrors(FILE1.c_str(),"%lg %lg %lg %lg",""));
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
    DataSaver[0]->GetYaxis()->SetTitle("Tensao[V]");
    DataSaver[0]->SetTitle("");
    DataSaver[0]->SetFillColor(6);
    DataSaver[0]->Draw("ap");
    
    TF1* func1 = new TF1("myfit1",linear1,0,1000,2);
    func1->SetLineColor(4);
    func1->SetLineWidth(2);
    DataSaver[0]->Fit(func1,"U", 0,1000);
    
    cout << "Chi^2/ngl do primeiro fit : " << func1->GetChisquare()/func1->GetNDF() << "\n\n" <<endl;

    c1->Modified();
    c1->Update();
    while(c1->WaitPrimitive()) gSystem->ProcessEvents();
    c1->Print("alpha/Calibracao1.pdf");
    
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
    DataSaver[1]->GetXaxis()->SetTitle("Canal");
    DataSaver[1]->GetYaxis()->SetTitle("Tensao[V]");
    DataSaver[1]->SetTitle("");
    DataSaver[1]->SetFillColor(6);
    DataSaver[1]->Draw("ap");
    
    TF1* func2 = new TF1("myfit1",linear1,0,1000,2);
    func2->SetLineColor(4);
    func2->SetLineWidth(2);
    DataSaver[1]->Fit(func2,"U", 0,1000);
    
    cout << "Chi^2/ngl do segundo fit : " << func2->GetChisquare()/func2
    ->GetNDF() << "\n\n" <<endl;
    
    c2->Modified();
    c2->Update();
    while(c2->WaitPrimitive()) gSystem->ProcessEvents();
    c2->Print("alpha/Calibracao2.pdf");
    
    ///////////////////////////////////////////////////////////
    TCanvas* c3 = new TCanvas("c3", "SOLUTION1", 1400, 1000);
    TPad* d3 = new TPad("Draw","Pad1",0,0,1,1,0,1);
    d3->Draw();
    d3->cd();
    d3->SetGrid();
    double energy[18] = {0.05,0.08,0.128,0.201,0.4,0.5,0.64,0.8,1,1.6,2,2.401,2.8,3.2,4,5,6.4,8};
    double range[18] = {0.1248,0.1722,0.235,0.3156,0.4946,0.568,0.66,0.7566,0.8704,1.2036,1.441,1.7026,1.9978,2.33,3.1086,4.2776,6.2486,8.9362};
    TGraph* rangeData = new TGraph(18,energy,range);
    rangeData->SetMarkerStyle(3);
    rangeData->SetMarkerColor(4);
    rangeData->SetMarkerSize(2);
    rangeData->GetXaxis()->SetTitle("Energy (MeV)");
    rangeData->GetYaxis()->SetTitle("Range (mg/cm^2)");
    rangeData->SetTitle("");
    rangeData->Draw("ap");
    TSpline3* rangefunction = new TSpline3("RANGE", energy, range, 18);
    rangefunction->Draw("same");
    double deltaz[7] = {0.95,1.35,1.75,2.15,2.55,2.95,3.35};
    double E0 = 5.305; //MeV
    double RangeFinalE[7];
    double density = 1.2041; //mg/cm^3
    cout << endl;
    cout << "Método do Alcance:" << endl;
    for(int i=0; i<7;++i){
        double Range0 = rangefunction->Eval(E0) - density*deltaz[i];
        RangeFinalE[i] = Secante(rangefunction, 0.001,5.305, 2, Range0);
        cout << "prateleria = "<< i+2 << " ----- DeltaE = " << E0 - RangeFinalE[i] << endl;
    }
    c3->Modified();
    c3->Update();
    while(c3->WaitPrimitive()) gSystem->ProcessEvents();
    c3->Print("alpha/rangeSpline.pdf");
    
    ///////////////////////////////////////////////////////////
    TCanvas* c4 = new TCanvas("c4", "SOLUTION1", 1400, 1000);
    TPad* d4 = new TPad("Draw","Pad1",0,0,1,1,0,1);
    d4->Draw();
    d4->cd();
    d4->SetGrid();
    double loss[18] = {0.5572,0.676,0.809,0.9508,1.2948,1.4314,1.5924,1.7202,1.8024,1.7584,1.6242,1.4434,1.279,1.1412,0.9392,0.7848,0.6492,0.5508};
    TGraph* lossData = new TGraph(18,energy,loss);
    lossData->SetMarkerStyle(3);
    lossData->SetMarkerColor(4);
    lossData->SetMarkerSize(2);
    lossData->GetXaxis()->SetTitle("Energy (MeV)");
    lossData->GetYaxis()->SetTitle("#frac{dE}{dx} (MeV/mg/cm^2)");
    lossData->SetTitle("");
    lossData->Draw("ap");
    TSpline3* lossfunction = new TSpline3("RANGE", energy, loss, 18);
    lossfunction->Draw("same");
    double MeasuredFinalE[7] = {4.28890452,3.872291624,3.42879062,2.942742241,2.393827633,1.738659168,0.905891695};
    double dEdxFinalE[7];
    cout << endl;
    cout << "Método do dE/dx Médio:" << endl;
    for(int i=0; i<7;++i){
        double dEdxAv = (lossfunction->Eval(E0)+lossfunction->Eval(MeasuredFinalE[i]))/2;
        cout << "prateleria = "<< i+2 << " ----- DeltaE = " << dEdxAv*deltaz[i]*density << endl;
    }
    cout << endl;
    cout << "Método do dE/dx por troços:" << endl;
    for(int i=0; i<7;++i){
        cout << "prateleria = "<< i+2 << " ----- DeltaE = " << deltaEtrocos(lossfunction,E0, deltaz[i],density,5000) << endl;
    }
    
    c4->Modified();
    c4->Update();
    while(c4->WaitPrimitive()) gSystem->ProcessEvents();
    c4->Print("alpha/dEdxSpline.pdf");
    
    ///////////////////////////////////////////////////////////
    
    delete func1;
    delete d1;
    delete c1;
    
    delete func2;
    delete d2;
    delete c2;
    
    delete rangefunction;
    delete rangeData;
    delete d3;
    delete c3;
    
    delete lossfunction;
    delete lossData;
    delete d4;
    delete c4;
    
}
