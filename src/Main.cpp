/*
 * Copyright (c) 2017
 *     Leonardo Baroncelli, Giancarlo Zollino (IASF-Bologna),
 *
 * Any information contained in this software
 * is property of the AGILE TEAM and is strictly
 * private and confidential.
*/
 
#include <iostream> 
#include <fstream>
#include <iomanip>
#include <string.h>
#include "AgileMap.h"
#include "ExpRatioEvaluator.h"
 
//#define DEBUG 1


using namespace std; 

const char* startString = {
"################################################################\n"
"###                   Task AG_expratio v1.0.0 -              ###"
};

const char* endString = {
"### Task AG_expratio exiting ............................... ###\n"
"################################################################"
};

int main()
{
    cout << startString << endl;
	
	//Mat image;
	
	const char *expFilePath = "exp.exp";
	double minTreshold = 9.5;
	double maxTreshold = 15;
	
	// caso rettangolo fuori	
	//double l = 81;
	//double b = 49;
	
	// caso buono
	//double l = 45;
	//double b = 31;

	// caso fuori range	
	double l = 26;
	double b = 39;	

	ExpRatioEvaluator exp(expFilePath,minTreshold,maxTreshold,l,b);
	double *output = exp.computeExpRatioValues();
	if(exp.isRectangleInside()) {
		for(int i=0; i<4; i++) {
			cout << output[i] << endl;
			}
		}
	cout << endString << endl;
	
	return 0;
}
