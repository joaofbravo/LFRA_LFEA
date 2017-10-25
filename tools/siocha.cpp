//-- After ROOT installation and launching, this routine is executed   --//
//--      at the root line prompt:    root[0]  .x siocha.cpp             --//

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

//-- Definition of the fit function
Double_t fitfcn(Double_t *x, Double_t *par)
{
    Double_t fitval = par[0]/2.5066/par[2]*exp(-0.5*(x[0]-par[1])*(x[0]-par[1])/(par[2]*par[2]));
    return fitval;
}

//-- Main routine
void gama()
{
    const Int_t dim = 1024;
    Float_t xval[dim];
    Float_t yval[dim];
    Float_t exval[dim];
    Float_t eyval[dim];
    Float_t lwlim,uplim;

    //... codigo eventual ...
    //...
    //...

    for(int i=0; i<dim; i++){ exval[i] = 0.; }

    //... codigo eventual ...
    //...
    //...
    //-- Open the ASCII file:
    ifstream fp ("./cs137c_15.asc");  // nome do ficheiro ASCII

    string line, s1, s2;

    if (fp.is_open())
    {
        int i = 0;
        while (i < dim)
        {
            getline (fp,line);
            s1 = line.substr(0,4);         //canal
            s2 = line.substr(6,14);        //contagens
            xval[i] = atof(s1.c_str());
            yval[i] = atof(s2.c_str());

            eyval[i]  = sqrt( yval[i] );
            i++;    
        }

        TCanvas *c1 = new TCanvas("c1","Distrib. de Gamas", 1220,0,700,500);       // 55(esq) ou 1220(dir) - conforme ecran
        c1->SetFillColor(42); 
        c1->SetGrid(); 
        c1->GetFrame()->SetFillColor(21); 
        c1->GetFrame()->SetBorderSize(12); 

        TGraphErrors *graph = new TGraphErrors(dim,xval,yval,exval,eyval);

        graph->SetTitle("Distrib. de Gamas");
        graph->SetLineColor(5);
        graph->SetLineWidth(1);
        graph->SetMarkerColor(kYellow); //kBlue
        graph->SetMarkerStyle(21); 

        //   graph->SetMaximum(200);
        //   graph->SetMinimum(8);

        // Creates a ROOT function based on the user fit function:
        lwlim = 360.;   // lwlim < User fit region < uplim                     
        uplim = 420.;                          
        TF1 *func = new TF1("myfit",fitfcn,lwlim,uplim,3); // N. parametros de fit = 3
        //-- Sets initial values and parameter names:
        //func->SetParameter(0, 2.e04);           //Estimar par[0] 
        func->SetParameters(2000., 390., 30.);  //Se varios: par[0]...par[n]

        func->SetParNames("Amp", "Mean", "Sigma");
        //func->SetParLimits(2,-10,-4);          //SetParLimits(): -10<par[2]<-4
        //func->FixParameter(2,0.);              //FixParameter(2,0):  par[2]=0

        graph->Draw("AP");          //A=axis, P=defined marker
        graph->Fit("myfit","UR");   //U: com funçao User defined   R: fit region
        //graph->Fit("expo","Q");     //funçoes predefinidas: "polN", ou "expo" ou "gaus"

        // Writes the fit results into the par array
        //Double_t par[3];
        //func->GetParameters(par);
        //cout << par[0] <<' '<< par[1] << ' '<< par[2] << endl; 

        cout << "lwlim = " << lwlim <<"   uplim = "<< uplim << endl;

        fp.close();
    }

    else cout << "Unable to open file"; 
}