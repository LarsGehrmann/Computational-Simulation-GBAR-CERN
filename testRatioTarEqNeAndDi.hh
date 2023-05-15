#ifndef TESTRATIOTAREQNEANDDI_HH
#define TESTRATIOTAREQNEANDDI_HH
#include "ConstructionParameters.hh"
#include "RunParameters.hh"
#include "construction.hh"
#include "G4RunManager.hh"
#include "action.hh"


void testRatioTarEqNeAndDi(ConstructionParameters *constructionParameters,  RunParameters * runParameters, G4RunManager* runMan, double TarStart, 
	double TarStep, double ratioStart, double ratioStep, int noTar, int noDi);
#endif
