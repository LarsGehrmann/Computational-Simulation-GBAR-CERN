#ifndef EVENT_HH
#define EVENT_HH

#include "G4UserEventAction.hh"
#include "G4Event.hh"
#include "run.hh"


extern G4int noAnnihilationsStep;
extern G4int noPairProductionStep;
extern G4int noAnnihilationsSensDet;
extern G4int noPairProductionSensDet;



class MyEventAction : public G4UserEventAction
{
	public:
		MyEventAction(MyRunAction*);
		~MyEventAction();
		virtual void BeginOfEventAction(const G4Event*);
		virtual void EndOfEventAction(const G4Event*);
};

#endif
