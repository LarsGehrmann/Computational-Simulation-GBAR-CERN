#ifndef TESTDISTANCESTARGETORIGIN_HH
#define TESTDISTANCESTARGETORIGIN_HH
#include "ConstructionParameters.hh"
#include "RunParameters.hh"
#include "construction.hh"
#include "G4RunManager.hh"
#include "action.hh"


void testDistancesTargetOrigin(ConstructionParameters *constructionParameters,  RunParameters * runParameters, G4RunManager* runMan, 
	G4double minDist, G4double maxDist, G4double stepDist, G4int noDist);
#endif
