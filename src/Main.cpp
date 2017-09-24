/*
 * Copyright (c) 2017
 *     Leonardo Baroncelli, Giancarlo Zollino (IASF-Bologna),
 *
 * Any information contained in this software
 * is property of the AGILE TEAM and is strictly
 * private and confidential.
 *
*/

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <iomanip> 
#include "ExpRatioEvaluator.h"

const char* startString = {
"################################################################\n"
"###                   Task AG_expratio v1.0.0 -               ###"
};

const char* endString = {
"### Task AG_expratio exiting .................................... ###\n"
"################################################################"
};


int main(int argc, char *argv[])
{ 	

	cout << startString << endl;

	if( argc > 6) 
	{
        const char * imagePath = argv[1];
        const char * outfile = argv[2];
		double minThreshold = atof(argv[3]);
		double maxThreshold = atof(argv[4]);
		double l = atof(argv[5]);
		double b = atof(argv[6]);

	   	ofstream resText(outfile);
	   	resText.setf(ios::fixed); 

		ExpRatioEvaluator exp(imagePath,minThreshold,maxThreshold,l,b);
		double *output = exp.computeExpRatioValues();

		resText << setprecision(5) << output[0] <<" "<< output[1] <<" "<< output[2] <<" "<< output[3];
	
		cout << "Created " <<outfile<< " log file."<<endl;
		resText.close();
	}
	else
	{
		printf("Expected 7 parameters:\n   - The .exp file path\n   - The name of the output file\n   - The minThreshold\n   - The maxThreshold\n   - The l coordinate\n    -The b coordinate");
	}
	
	cout << endString << endl;
    return 0;
}
