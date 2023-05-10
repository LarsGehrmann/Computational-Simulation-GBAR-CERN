#ifndef TESTRATIO_HH
#define TESTRATIO_HH
#include "ConstructionParameters.hh"
#include "RunParameters.hh"
#include "construction.hh"
#include "G4RunManager.hh"
#include "action.hh"


void testRatio(ConstructionParameters *constructionParameters,  RunParameters * runParameters, G4RunManager* runMan, double TarNeStart, 
	double TarNeStep, double ratioStart, double ratioStep, int noTarNe, int noDi);
#endif
