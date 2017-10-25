#include <iostream>
#include <fstream>
#include <string>
#include <cmath>

using namespace std;

// Main routine

void tableLatex()
{
	// Lines
	const int dim = 10;

	// Constants
	const double dt = 120;
	const double tau = 412.791819e-6, etau = 25.753701e-6;

	// Variables
	double x, y, z;
	double N1[dim], N2[dim], N[dim], R[dim], Rm[dim];
	double eN1[dim], eN2[dim], eN[dim], eR[dim], eRm[dim];

	// Open the file
	ifstream table("D05B.txt");

	if (table.is_open())
	{
		for(int i=0; i < dim; i++)
		{
			table >> x >> y >> z;

			// Data treatment
			N1[i] = y;
			eN1[i] = sqrt(y);
			N2[i] = z;
			eN2[i] = sqrt(z);
			N[i] = y + z;
			eN[i] = sqrt(y+z);

			Rm[i] = N[i]/dt;
			eRm[i] = eN[i]/dt;

			R[i] = Rm[i]/(1-Rm[i]*tau);
			eR[i] = (eRm[i]*eRm[i] + Rm[i]*Rm[i]*Rm[i]*Rm[i]*etau*etau)/pow((1-Rm[i]*tau),4);
		}
	}
	else cout << "Unable to open file" << endl << endl; 

	ofstream tableLatex;
	tableLatex.open("tableLatex.txt");

	if(tableLatex.is_open())
	{
		// Quantities
		tableLatex << "$N_1$ (1) & $N_2$ (1) & N (1) & $R_m$ ($^{-1}$) & $R_v$ ($^{-1}$) \\\\ \\midrule" << endl;
		
		for(int i=0; i < dim; i++)
		{
			// Data to Latex Table
			tableLatex <<          N1[i] << " $\\pm$ " << int(eN1[i] + 0.5)  
			<< " & " << N2[i] << " $\\pm$ " << int(eN2[i] + 0.5)
			<< " & " << N[i]  << " $\\pm$ " << int(eN[i] + 0.5) 
			<< " & " << Rm[ei] << " $\\pm$ " << eRm[i]
			<< " & " << R[i]  << " $\\pm$ " << eR[i]	    
			<< " \\\\" << endl;   
		}
	}
	else cout << "Unable to open file" << endl << endl;

	tableLatex.close();
}