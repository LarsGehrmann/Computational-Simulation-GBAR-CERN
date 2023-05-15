#ifndef TESTRATIOTARNE_HH
#define TESTRATIOTARNE_HH
#include "ConstructionParameters.hh"
#include "RunParameters.hh"
#include "construction.hh"
#include "G4RunManager.hh"
#include "action.hh"


void testRatioTarNe(ConstructionParameters *constructionParameters,  RunParameters * runParameters, G4RunManager* runMan, double TarStart, 
	double TarStep, double ratioStart, double ratioStep, int noTar, int noNe);
#endif
