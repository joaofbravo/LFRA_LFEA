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
	cFCgraphics G;


	FCmatrixFull data = tools.ReadFileToMatrix("experimentaldata/LFEA/LFEAPet/distAng2_Mar.data");
	
	TF1 fittime("fittime","[0] + [1]*x",0,5640
	);
	
	fittime.SetParameters(-2.599,0.9173);
	double efit[] = {2.113,0.04113};
		
	double * x= new double[data.size()];
	double * y= new double[data.size()];
	double * ex= new double[data.size()];
	double * ey= new double[data.size()];
	
	for (int i = 0; i < data.size(); ++i)
	{
		x[i] = data[i][0];
		y[i] = data[i][2]-fittime.Eval(data[i][1])/data[i][1];
		ex[i] = 0.1;
		ey[i] = sqrt(data[i][3]*data[i][3] + efit[0]*efit[0]/data[i][1]/data[i][1] + efit[1]*efit[1]);
	}



	TGraphErrors graph(data.size(),x,y,ex,ey);

	TF1 fit("fit","[0]/[2]*exp(-(x-[1])*(x-[1])/2/[2]/[2])",-30,30);
	fit.SetParameters(20000,0,4);
	graph.Fit("fit");

	graph.SetTitle("Coincidencias;Angulo(º);Rate(N/s)");
	graph.SetMarkerStyle(20);
	graph.SetMarkerSize(.05);


	TPad* pad = G.CreatePad("pad");

	G.AddObject(&graph,"pad","AP");

	G.AddObject(pad);

	G.Draw();
	G.Print("plots/LFEA/PET/distAng2_Mar.pdf");

	cout <<"\n\n\nA =	" <<fit.GetParameter(0) << " +- "<<fit.GetParError(0)<<endl;
	cout <<"mu =	" <<fit.GetParameter(1) << " +- "<<fit.GetParError(1)<<endl;
	cout <<"sigma =	" <<fit.GetParameter(2) << " +- "<<fit.GetParError(2)<<endl;
	//cout <<"fundo =	" <<fit.GetParameter(3) << " +- "<<fit.GetParError(3)<<endl;
	cout <<"\n Chi^2/Ndf=	" <<fit.GetChisquare()/fit.GetNDF()  <<endl<<endl<<endl;


	
	return 0;
}