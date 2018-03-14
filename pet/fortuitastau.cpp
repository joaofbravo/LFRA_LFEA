#include "FCtools.h"
#include "Spline3Interpolator.h"
#include "cFCgraphics.h"
#include "TPad.h"
#include "TGraphErrors.h"
#include "TFitResult.h"
#include "TF1.h"
#include "TMath.h"
#include <cmath>
#include <vector>
#include <cstring>



using namespace std;

int main()
{
	FCtools tools;
	cFCgraphics Gtau;


	string tabname[] = {"angequim0_8.data", "angequim1_6.data", "angequim2_4.data", "angequim3_2.data", "angequip0_0.data", "angequip0_8.data", "angequip1_6.data", "angequip2_4.data", "angequip3_2.data"}

	string dir = "experimentaldata/LFEA/LFEAPet/";
	FCmatrixFull datatau = tools.ReadFileToMatrix("experimentaldata/LFEA/LFEAPet/fortuitastau.data");
		
	double * tau= new double[datatau.size()];
	double * nfort= new double[datatau.size()];
	double * etau= new double[datatau.size()];
	double * enfort= new double[datatau.size()];

	for (int i = 0; i < datatau.size(); ++i)
	{
		tau[i] = datatau[i][0];
		nfort[i] = datatau[i][1];
		etau[i] = 1;
		enfort[i] = sqrt(nfort[i]);
	}



	TGraphErrors graphtau(datatau.size(),tau,nfort,etau,enfort);

	TF1 fittau("fittau","[0] + [1]*x",0,5640
	);
	//fittau.SetParameters(20000,0,4);
	graphtau.Fit("fittau");

	graphtau.SetTitle("Coincidencias;\\tau(ns);N_{fort.}");
	graphtau.SetMarkerStyle(20);
	graphtau.SetMarkerSize(.05);


	TPad* padtau = Gtau.CreatePad("padtau");

	Gtau.AddObject(&graphtau,"padtau","AP");

	Gtau.AddObject(padtau);

	Gtau.Draw();
	Gtau.Print("plots/LFEA/PET/fortvtau.pdf");

	cout <<"\n Chi^2/Ndf=	" <<fittau.GetChisquare()/fittau.GetNDF()  <<endl<<endl<<endl;
	
	return 0;
}