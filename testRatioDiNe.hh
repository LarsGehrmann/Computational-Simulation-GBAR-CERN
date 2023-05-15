#ifndef TESTRATIODINE_HH
#define TESTRATIODINE_HH
#include "ConstructionParameters.hh"
#include "RunParameters.hh"
#include "construction.hh"
#include "G4RunManager.hh"
#include "action.hh"


void testRatioDiNe(ConstructionParameters *constructionParameters,  RunParameters * runParameters, G4RunManager* runMan, double DiStart, 
	double DiStep, double ratioStart, double ratioStep, int noDi, int noNe);
#endif
