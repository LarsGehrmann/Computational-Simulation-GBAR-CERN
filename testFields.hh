#ifndef TESTFIELDS_HH
#define TESTFIELDS_HH
#include "ConstructionParameters.hh"
#include "RunParameters.hh"
#include "construction.hh"
#include "G4RunManager.hh"
#include "action.hh"


void testFields(ConstructionParameters *constructionParameters,  RunParameters * runParameters, G4RunManager* runMan, 
	G4double minScale, G4double maxScale, G4double stepScale);
#endif
