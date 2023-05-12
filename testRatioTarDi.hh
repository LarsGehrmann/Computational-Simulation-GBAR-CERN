#ifndef TESTRATIOTARDI_HH
#define TESTRATIOTARDI_HH
#include "ConstructionParameters.hh"
#include "RunParameters.hh"
#include "construction.hh"
#include "G4RunManager.hh"
#include "action.hh"


void testRatioTarDi(ConstructionParameters *constructionParameters,  RunParameters * runParameters, G4RunManager* runMan, double TarStart, 
	double TarStep, double ratioStart, double ratioStep, int noTar, int noDi);
#endif
