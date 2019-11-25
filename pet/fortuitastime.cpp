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




using namespace std;

int main()
{
	FCtools tools;
	cFCgraphics Gtime;


	FCmatrixFull datatime = tools.ReadFileToMatrix("experimentaldata/LFEA/LFEAPet/fortuitastime.data");
		
	double * time= new double[datatime.size()];
	double * nfort= new double[datatime.size()];
	double * etime= new double[datatime.size()];
	double * enfort= new double[datatime.size()];

	for (int i = 0; i < datatime.size(); ++i)
	{
		time[i] = datatime[i][0];
		nfort[i] = datatime[i][1];
		etime[i] = 0;
		enfort[i] = sqrt(nfort[i]);
	}



	TGraphErrors graphtime(datatime.size(),time,nfort,etime,enfort);

	TF1 fittime("fittime","[0] + [1]*x",0,5640
	);
	//fittime.SetParameters(20000,0,4);
	graphtime.Fit("fittime");

	graphtime.SetTitle("Coincidencias;t(s);N_{fort.}");
	graphtime.SetMarkerStyle(20);
	graphtime.SetMarkerSize(.05);


	TPad* padtime = Gtime.CreatePad("padtime");

	Gtime.AddObject(&graphtime,"padtime","AP");

	Gtime.AddObject(padtime);

	Gtime.Draw();
	Gtime.Print("plots/LFEA/PET/fortvtime.pdf");

	cout <<"\n Chi^2/Ndf=	" <<fittime.GetChisquare()/fittime.GetNDF()  <<endl<<endl<<endl;


	
	return 0;
}