//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
//
/// \file field/field04/include/globalField.hh
/// \brief Definition of the globalField class
//

#ifndef globalField_hh
#define globalField_hh

#include <vector>

#include "G4FieldManager.hh"
#include "G4PropagatorInField.hh"
#include "G4MagIntegratorStepper.hh"
#include "G4ChordFinder.hh"

#include "G4MagneticField.hh"
#include "G4ElectroMagneticField.hh"

#include "G4Mag_EqRhs.hh"
#include "G4Mag_SpinEqRhs.hh"


#include "G4GenericMessenger.hh"



#include "G4EqMagElectricField.hh"
#include "G4EqEMFieldWithSpin.hh"

#include "elementField.hh"

#include "construction.hh"

//  globalField - handles the global ElectroMagnetic field
//
//  There is a single G04GlobalField object.
//
//  The field from each individual beamline element is given by a
//  ElementField object. Any number of overlapping ElementField
//  objects can be added to the global field. Any element that
//  represents an element with an EM field must add the appropriate
//  ElementField to the global GlobalField object.

typedef std::vector<elementField*> FieldList;

class globalField : public G4ElectroMagneticField {
//class globalField : public G4MagneticField {

private:

  //globalField(MyDetectorConstruction* const);

  globalField(const globalField&);

  globalField& operator=(const globalField&);

  void SetupArray();

public:
	globalField();
  virtual ~globalField();



  G4ChordFinder* getChordFinder();

  /// GetObject() returns the single globalField object.
  /// It is constructed, if necessary.
  //static globalField* GetObject(MyDetectorConstruction* const);
static globalField* GetObject();

  /// GetFieldValue() returns the field value at a given point[].
  /// field is really field[6]: Bx,By,Bz,Ex,Ey,Ez.
  /// point[] is in global coordinates: x,y,z,t.
  virtual void GetFieldValue(const G4double* point, G4double* field) const; // !!!!!

  /// DoesFieldChangeEnergy() returns true.
  virtual G4bool DoesFieldChangeEnergy() const { return true; }

  /// AddElementField() adds the ElementField object for a single
  /// element to the global field.
  void AddElementField(elementField* f)
  {
    if (fFields) fFields->push_back(f);
  }
  
  /// Clear() removes all ElementField-s from the global object,
  /// and destroys them. Used before the geometry is completely
  /// re-created.
  void Clear();

  /// constructs all field tracking objects
  void ConstructField();

  /// Set the Stepper types
  void SetStepperType( G4int i ) { fStepperType = i; }

  /// Set the Stepper
  void SetStepper();

  /// Set the minimum step length
  void SetMinStep(G4double stp) { fMinStep = stp; }

  /// Set the delta chord length
  void SetDeltaChord(G4double dcr) { fDeltaChord = dcr; }

  /// Set the delta one step length
  void SetDeltaOneStep(G4double stp) { fDeltaOneStep = stp; }

  /// Set the delta intersection length
  void SetDeltaIntersection(G4double its) { fDeltaIntersection = its; }

  /// Set the minimum eps length
  void SetEpsMin(G4double eps) { fEpsMin = eps; }

  /// Set the maximum eps length
  void SetEpsMax(G4double eps) { fEpsMax = eps; }

  /// Return the list of Element Fields
  FieldList* GetFields() { return fFields; }

protected:

  /// Get the global field manager
  G4FieldManager* GetGlobalFieldManager();

private:

  static G4ThreadLocal globalField* fObject;

  G4int fNfp;
  G4bool fFirst;

  FieldList* fFields;

  const elementField **fFp;

private:
	G4double scaleB = 1;

	G4GenericMessenger* fMessenger;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // code to use field from TAB file
	// The dimensions of the table
	G4int nx = 101, ny = 101, nz = 101;
	// The physical limits of the defined region
	double minx, maxx, miny, maxy, minz, maxz;
	// The physical extent of the defined region
	double dx, dy, dz;
	double fXoffset;

	std::vector< std::vector< std::vector< double > > > BxField;
	std::vector< std::vector< std::vector< double > > > ByField;
	std::vector< std::vector< std::vector< double > > > BzField;
	std::vector< std::vector< std::vector< double > > > ExField;
	std::vector< std::vector< std::vector< double > > > EyField;
	std::vector< std::vector< std::vector< double > > > EzField;



	void readField(G4String fieldType);
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// 
	// 
  // A. INVARIANTS: 
  // --------------
  // INVARIANT: an integer to indicate the type of RK integration method ('stepper') used
  G4int fStepperType;

  // INVARIANTS: Accuracy parameters of field propagation (and the integration it uses.)
  // 1. These values are lengths - initialised in src
  G4double fMinStep;
  G4double fDeltaChord;
  G4double fDeltaOneStep;
  G4double fDeltaIntersection;
  // 2. Dimensionless numbers - can initialise here
  G4double fEpsMin = 2.5e-7; // Relative accuracy of integration (minimum)
  G4double fEpsMax = 0.001;  // Relative accuracy of integration (maximum)

  // B. STATE: objects which carry out the propagation and are modified during tracking 
  // --------
//  G4Mag_EqRhs*            fEquation;
//  G4Mag_SpinEqRhs*        fEquation;

//  G4EqMagElectricField*   fEquation;
  G4EqEMFieldWithSpin*     fEquation        = nullptr;

  G4FieldManager*          fFieldManager    = nullptr;
  G4PropagatorInField*     fFieldPropagator = nullptr;
  G4MagIntegratorStepper*  fStepper         = nullptr;
  G4ChordFinder*           fChordFinder     = nullptr;

  // INVARIANTS during tracking: Auxiliary class & information - used for setup
  //F04FieldMessenger*       fFieldMessenger;
  //MyDetectorConstruction* fDetectorConstruction= nullptr;
};

#endif
