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
/// \file field/field04/src/globalField.cc
/// \brief Implementation of the globalField class
//

#include <time.h>

#include "Randomize.hh"
#include "G4TransportationManager.hh"

#include "G4ExplicitEuler.hh"
#include "G4ImplicitEuler.hh"
#include "G4SimpleRunge.hh"
#include "G4SimpleHeum.hh"
#include "G4ClassicalRK4.hh"
#include "G4CashKarpRKF45.hh"
#include "G4SystemOfUnits.hh"

#include "globalField.hh"


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4ThreadLocal globalField* globalField::fObject = 0;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
/**/
globalField::globalField(G4double argScaleBDipole, G4double argScaleBNeon, G4double argScaleBSolenoid, G4double argScaleBTarget, G4double argScaleE) 
	: G4ElectroMagneticField(),   //  old  : G4MagneticField(),
    fMinStep(0.01*mm), fDeltaChord(0.5*mm),
    fDeltaOneStep(0.01*mm), fDeltaIntersection(0.1*mm),
    fEpsMin(2.5e-7), fEpsMax(0.001),  // These are pure numbers -- relative values
    fEquation(0), fFieldManager(0),
    fFieldPropagator(0), fStepper(0), fChordFinder(0)
    //fDetectorConstruction(det)
{
	scaleBDipole = argScaleBDipole;
	scaleBNeon = argScaleBNeon;
	scaleBSolenoid = argScaleBSolenoid;
	scaleBTarget = argScaleBTarget;
	scaleE = argScaleE;



  //fFieldMessenger = new F04FieldMessenger(this,det);
  fFields = new FieldList();
  fStepperType = 4 ;       // ClassicalRK4 is default stepper
  //  set object
  fObject = this;
  fFirst = true;
  fNfp = 0;
  fFp = NULL;
  // resize fields -------------------------------
  /*
  G4cout << "  [ Number of values x,y,z: "
	  << nx << " " << ny << " " << nz << " ] "
	  << G4endl;
	  */
  BxField.resize(nx);
  ByField.resize(nx);
  BzField.resize(nx);
  int ix, iy, iz;
  for (ix = 0; ix < nx; ix++) {
	  BxField[ix].resize(ny);
	  ByField[ix].resize(ny);
	  BzField[ix].resize(ny);
	  for (iy = 0; iy < ny; iy++) {
		  BxField[ix][iy].resize(nz);
		  ByField[ix][iy].resize(nz);
		  BzField[ix][iy].resize(nz);
	  }
  }
  ExField.resize(nx);
  EyField.resize(nx);
  EzField.resize(nx);
  for (ix = 0; ix < nx; ix++) {
	  ExField[ix].resize(ny);
	  EyField[ix].resize(ny);
	  EzField[ix].resize(ny);
	  for (iy = 0; iy < ny; iy++) {
		  ExField[ix][iy].resize(nz);
		  EyField[ix][iy].resize(nz);
		  EzField[ix][iy].resize(nz);
	  }
  }
  // ------------------------------------
  // Read different components of field
	G4String fieldType;
    G4String origin[4] = { "Dipole", "Neon", "Solenoid", "Target" };
	G4double scale[5] = { scaleBDipole, scaleBNeon, scaleBSolenoid, scaleBTarget, scaleE};
    fieldType = "magField";
	// read magnetic field in a loop
    for (int i = 0; i < 4; ++i) {
    readField(fieldType, origin[i], scale[i]);
    }
	// electric field is only originating from one origin, therefore 0-th index by default
	fieldType = "elField";
	readField(fieldType, origin[0], scale[4]);

	ConstructField();
	fMessenger = new G4GenericMessenger(this, "/MagField/", "MagField Messenger");
}


void globalField::readField(G4String fieldType, G4String origin, G4double scale) {
	double lenUnit = millimeter;
	double fieldUnit;
	G4String fileName;
	int ix, iy, iz;
	if (fieldType == "magField") {	
		G4cout << "Reading magnetic field" << G4endl;
		fileName = fieldType + origin + ".txt";
		fieldUnit = tesla;
		std::ifstream file(fileName);
		// Read in the data
		G4double xval = 0.;
		G4double yval = 0.;
		G4double zval = 0.;
		G4double bx = 0.;
		G4double by = 0.;
		G4double bz = 0.;
		for (iz = 0; iz < nz; iz++) {
			for (iy = 0; iy < ny; iy++) {
				for (ix = 0; ix < nx; ix++) {
					file >> xval >> yval >> zval >> bx >> by >> bz;
					// scale to get from meter to millimeter
					xval *= 1000;
					yval *= 1000;
					zval *= 1000;
					if (ix == 0 && iy == 0 && iz == 0) {
						minx = xval * lenUnit;
						miny = yval * lenUnit;
						minz = zval * lenUnit;
					}
					BxField[ix][iy][iz] += bx * tesla * scale;
					ByField[ix][iy][iz] += by * tesla * scale;
					BzField[ix][iy][iz] += bz * tesla * scale;
				}
			}
		}
		file.close();
		maxx = xval * lenUnit;
		maxy = yval * lenUnit;
		maxz = zval * lenUnit;
		dx = maxx - minx;
		dy = maxy - miny;
		dz = maxz - minz;
	}
	else if (fieldType == "elField") {
		G4cout << "Reading electric field" << G4endl;
		fileName = "elField.TAB";
		fieldUnit = volt / meter;
		std::ifstream file(fileName); // Open the file for reading.
		// Read in the data
		G4double xval = 0.;
		G4double yval = 0.;
		G4double zval = 0.;
		G4double ex = 0.;
		G4double ey = 0.;
		G4double ez = 0.;
		for (iz = 0; iz < nz; iz++) {
			for (iy = 0; iy < ny; iy++) {
				for (ix = 0; ix < nx; ix++) {
					file >> xval >> yval >> zval >> ex >> ey >> ez;
					// scale from m -> mm
					xval *= 1000;
					yval *= 1000;
					zval *= 1000;
					if (ix == 0 && iy == 0 && iz == 0) {
						minx = xval * lenUnit;
						miny = yval * lenUnit;
						minz = zval * lenUnit;
					}
					ExField[ix][iy][iz] += ex * fieldUnit * scale;
					EyField[ix][iy][iz] += ey * fieldUnit * scale;
					EzField[ix][iy][iz] += ez * fieldUnit * scale;

				}
			}
		}
		file.close();
		maxx = xval * lenUnit;
		maxy = yval * lenUnit;
		maxz = zval * lenUnit;

		dx = maxx - minx;
		dy = maxy - miny;
		dz = maxz - minz;

	}
	else {
		G4cerr << "Unclear which field should be called!";
		exit(1);
	}
}



//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

globalField::~globalField()
{
  Clear();

  delete fFields;

 // delete fFieldMessenger;

  if (fEquation)        delete fEquation;
  if (fStepper)         delete fStepper;
  if (fChordFinder)     delete fChordFinder;
}

G4ChordFinder* globalField::getChordFinder() {
	return this->fChordFinder;
}

void globalField::ConstructField()
{
  Clear();

  //  Construct equ. of motion of particles through B fields
//  fEquation = new G4Mag_EqRhs(this);
  //  Construct equ. of motion of particles through e.m. fields
//  fEquation = new G4EqMagElectricField(this);
  //  Construct equ. of motion of particles including spin through B fields
//  fEquation = new G4Mag_SpinEqRhs(this);
  //  Construct equ. of motion of particles including spin through e.m. fields
  fEquation = new G4EqEMFieldWithSpin(this);

  //  Get transportation, field, and propagator managers
  G4TransportationManager* transportManager =
         G4TransportationManager::GetTransportationManager();

  fFieldManager = GetGlobalFieldManager();

  fFieldPropagator = transportManager->GetPropagatorInField();

  //  Need to SetFieldChangesEnergy to account for a time varying electric
  //  field (r.f. fields)
  fFieldManager->SetFieldChangesEnergy(true);

  //  Set the field
  fFieldManager->SetDetectorField(this);

  //  Choose a stepper for integration of the equation of motion
  SetStepper();

  //  Create a cord finder providing the (global field, min step length,
  //  a pointer to the stepper)
  fChordFinder = new G4ChordFinder((G4MagneticField*)this,fMinStep,fStepper);

  // Set accuracy parameters
  fChordFinder->SetDeltaChord( fDeltaChord );

  fFieldManager->SetAccuraciesWithDeltaOneStep(fDeltaOneStep);

  fFieldManager->SetDeltaIntersection(fDeltaIntersection);

  fFieldPropagator->SetMinimumEpsilonStep(fEpsMin);
  fFieldPropagator->SetMaximumEpsilonStep(fEpsMax);
  /*
  G4cout << "Accuracy Parameters:" <<
            " MinStep=" << fMinStep <<
            " DeltaChord=" << fDeltaChord <<
            " DeltaOneStep=" << fDeltaOneStep << G4endl;
  G4cout << "                    " <<
            " DeltaIntersection=" << fDeltaIntersection <<
            " EpsMin=" << fEpsMin <<
            " EpsMax=" << fEpsMax <<  G4endl;
*/
  fFieldManager->SetChordFinder(fChordFinder);

  G4double l = 0.0;

  if (fFields) {
     if (fFields->size()>0) {
        FieldList::iterator i;
        for (i=fFields->begin(); i!=fFields->end(); ++i){
            (*i)->Construct();
        }
     }
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

globalField* globalField::GetObject()
{
 // if (!fObject) new globalField(scaleBDipole);
  return fObject;
}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
/*
globalField* globalField::GetObject()
{
  if (fObject) return fObject;
  return NULL;
}
*/
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void globalField::SetStepper()
{
  if(fStepper) delete fStepper;

  switch ( fStepperType )
  {
    case 0:
//      fStepper = new G4ExplicitEuler( fEquation, 8 ); // no spin tracking
      fStepper = new G4ExplicitEuler( fEquation, 12 ); // with spin tracking
      G4cout << "G4ExplicitEuler is called" << G4endl;
      break;
    case 1:
//      fStepper = new G4ImplicitEuler( fEquation, 8 ); // no spin tracking
      fStepper = new G4ImplicitEuler( fEquation, 12 ); // with spin tracking
      G4cout << "G4ImplicitEuler is called" << G4endl;
      break;
    case 2:
//      fStepper = new G4SimpleRunge( fEquation, 8 ); // no spin tracking
      fStepper = new G4SimpleRunge( fEquation, 12 ); // with spin tracking
      G4cout << "G4SimpleRunge is called" << G4endl;
      break;
    case 3:
//      fStepper = new G4SimpleHeum( fEquation, 8 ); // no spin tracking
      fStepper = new G4SimpleHeum( fEquation, 12 ); // with spin tracking
      G4cout << "G4SimpleHeum is called" << G4endl;
      break;
    case 4:
//      fStepper = new G4ClassicalRK4( fEquation, 8 ); // no spin tracking
      fStepper = new G4ClassicalRK4( fEquation, 12 ); // with spin tracking
      G4cout << "G4ClassicalRK4 (default) is called" << G4endl;
      break;
    case 5:
//      fStepper = new G4CashKarpRKF45( fEquation, 8 ); // no spin tracking
      fStepper = new G4CashKarpRKF45( fEquation, 12 ); // with spin tracking
      G4cout << "G4CashKarpRKF45 is called" << G4endl;
      break;
    default: fStepper = 0;
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4FieldManager* globalField::GetGlobalFieldManager()
{
  return G4TransportationManager::GetTransportationManager()
                                ->GetFieldManager();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void globalField::GetFieldValue(const G4double* point, G4double* field) const /////////////////////////////////////////////////////////////////////////////////////
{
	//G4cout << "In getFieldValue!!!" << G4endl;

	
	double x = point[0];
	double y = point[1];
	double z = point[2];

	// Position of given point within region, normalized to the range
	// [0,1]
	double xfraction = (x - minx) / dx;
	double yfraction = (y - miny) / dy;
	double zfraction = (z - minz) / dz;

	// Need addresses of these to pass to modf below.
	// modf uses its second argument as an OUTPUT argument.
	double xdindex, ydindex, zdindex;

	// Position of the point within the cuboid defined by the
	// nearest surrounding tabulated points
	double xlocal = (std::modf(xfraction * (nx - 1), &xdindex));
	double ylocal = (std::modf(yfraction * (ny - 1), &ydindex));
	double zlocal = (std::modf(zfraction * (nz - 1), &zdindex));

	// The indices of the nearest tabulated point whose coordinates
	// are all less than those of the given point
	int xindex = static_cast<int>(std::floor(xdindex));
	int yindex = static_cast<int>(std::floor(ydindex));
	int zindex = static_cast<int>(std::floor(zdindex));

	// Check that the point is within the defined region
	if ((xindex < 0) || (xindex >= nx - 1) ||
		(yindex < 0) || (yindex >= ny - 1) ||
		(zindex < 0) || (zindex >= nz - 1))
	{
		for (int i = 0; i < 5; ++i) {
		field[i] = 0.0;
		}
	}
	else
	{

#ifdef DEBUG_INTERPOLATING_FIELD
		G4cout << "Local x,y,z: " << xlocal << " " << ylocal << " " << zlocal << G4endl;
		G4cout << "Index x,y,z: " << xindex << " " << yindex << " " << zindex << G4endl;
		double valx0z0, mulx0z0, valx1z0, mulx1z0;
		double valx0z1, mulx0z1, valx1z1, mulx1z1;
		valx0z0 = table[xindex][0][zindex];  mulx0z0 = (1 - xlocal) * (1 - zlocal);
		valx1z0 = table[xindex + 1][0][zindex];  mulx1z0 = xlocal * (1 - zlocal);
		valx0z1 = table[xindex][0][zindex + 1]; mulx0z1 = (1 - xlocal) * zlocal;
		valx1z1 = table[xindex + 1][0][zindex + 1]; mulx1z1 = xlocal * zlocal;
#endif

		// Full 3(->6)-dimensional version
		// magnetic field
		field[0] =
			BxField[xindex][yindex][zindex] * (1 - xlocal) * (1 - ylocal) * (1 - zlocal) +
			BxField[xindex][yindex][zindex + 1] * (1 - xlocal) * (1 - ylocal) * zlocal +
			BxField[xindex][yindex + 1][zindex] * (1 - xlocal) * ylocal * (1 - zlocal) +
			BxField[xindex][yindex + 1][zindex + 1] * (1 - xlocal) * ylocal * zlocal +
			BxField[xindex + 1][yindex][zindex] * xlocal * (1 - ylocal) * (1 - zlocal) +
			BxField[xindex + 1][yindex][zindex + 1] * xlocal * (1 - ylocal) * zlocal +
			BxField[xindex + 1][yindex + 1][zindex] * xlocal * ylocal * (1 - zlocal) +
			BxField[xindex + 1][yindex + 1][zindex + 1] * xlocal * ylocal * zlocal;
		field[1] =
			ByField[xindex][yindex][zindex] * (1 - xlocal) * (1 - ylocal) * (1 - zlocal) +
			ByField[xindex][yindex][zindex + 1] * (1 - xlocal) * (1 - ylocal) * zlocal +
			ByField[xindex][yindex + 1][zindex] * (1 - xlocal) * ylocal * (1 - zlocal) +
			ByField[xindex][yindex + 1][zindex + 1] * (1 - xlocal) * ylocal * zlocal +
			ByField[xindex + 1][yindex][zindex] * xlocal * (1 - ylocal) * (1 - zlocal) +
			ByField[xindex + 1][yindex][zindex + 1] * xlocal * (1 - ylocal) * zlocal +
			ByField[xindex + 1][yindex + 1][zindex] * xlocal * ylocal * (1 - zlocal) +
			ByField[xindex + 1][yindex + 1][zindex + 1] * xlocal * ylocal * zlocal;
		field[2] =
			BzField[xindex][yindex][zindex] * (1 - xlocal) * (1 - ylocal) * (1 - zlocal) +
			BzField[xindex][yindex][zindex + 1] * (1 - xlocal) * (1 - ylocal) * zlocal +
			BzField[xindex][yindex + 1][zindex] * (1 - xlocal) * ylocal * (1 - zlocal) +
			BzField[xindex][yindex + 1][zindex + 1] * (1 - xlocal) * ylocal * zlocal +
			BzField[xindex + 1][yindex][zindex] * xlocal * (1 - ylocal) * (1 - zlocal) +
			BzField[xindex + 1][yindex][zindex + 1] * xlocal * (1 - ylocal) * zlocal +
			BzField[xindex + 1][yindex + 1][zindex] * xlocal * ylocal * (1 - zlocal) +
			BzField[xindex + 1][yindex + 1][zindex + 1] * xlocal * ylocal * zlocal;

		// electric field
		field[3] =
			ExField[xindex][yindex][zindex] * (1 - xlocal) * (1 - ylocal) * (1 - zlocal) +
			ExField[xindex][yindex][zindex + 1] * (1 - xlocal) * (1 - ylocal) * zlocal +
			ExField[xindex][yindex + 1][zindex] * (1 - xlocal) * ylocal * (1 - zlocal) +
			ExField[xindex][yindex + 1][zindex + 1] * (1 - xlocal) * ylocal * zlocal +
			ExField[xindex + 1][yindex][zindex] * xlocal * (1 - ylocal) * (1 - zlocal) +
			ExField[xindex + 1][yindex][zindex + 1] * xlocal * (1 - ylocal) * zlocal +
			ExField[xindex + 1][yindex + 1][zindex] * xlocal * ylocal * (1 - zlocal) +
			ExField[xindex + 1][yindex + 1][zindex + 1] * xlocal * ylocal * zlocal;
		field[4] =
			EyField[xindex][yindex][zindex] * (1 - xlocal) * (1 - ylocal) * (1 - zlocal) +
			EyField[xindex][yindex][zindex + 1] * (1 - xlocal) * (1 - ylocal) * zlocal +
			EyField[xindex][yindex + 1][zindex] * (1 - xlocal) * ylocal * (1 - zlocal) +
			EyField[xindex][yindex + 1][zindex + 1] * (1 - xlocal) * ylocal * zlocal +
			EyField[xindex + 1][yindex][zindex] * xlocal * (1 - ylocal) * (1 - zlocal) +
			EyField[xindex + 1][yindex][zindex + 1] * xlocal * (1 - ylocal) * zlocal +
			EyField[xindex + 1][yindex + 1][zindex] * xlocal * ylocal * (1 - zlocal) +
			EyField[xindex + 1][yindex + 1][zindex + 1] * xlocal * ylocal * zlocal;
		field[5] =
			EzField[xindex][yindex][zindex] * (1 - xlocal) * (1 - ylocal) * (1 - zlocal) +
			EzField[xindex][yindex][zindex + 1] * (1 - xlocal) * (1 - ylocal) * zlocal +
			EzField[xindex][yindex + 1][zindex] * (1 - xlocal) * ylocal * (1 - zlocal) +
			EzField[xindex][yindex + 1][zindex + 1] * (1 - xlocal) * ylocal * zlocal +
			EzField[xindex + 1][yindex][zindex] * xlocal * (1 - ylocal) * (1 - zlocal) +
			EzField[xindex + 1][yindex][zindex + 1] * xlocal * (1 - ylocal) * zlocal +
			EzField[xindex + 1][yindex + 1][zindex] * xlocal * ylocal * (1 - zlocal) +
			EzField[xindex + 1][yindex + 1][zindex + 1] * xlocal * ylocal * zlocal;
	}
}

void globalField::Clear()
{
  if (fFields) {
     if (fFields->size()>0) {
        FieldList::iterator i;
        for (i=fFields->begin(); i!=fFields->end(); ++i) delete *i;
        fFields->clear();
     }
  }

  if (fFp) { delete [] fFp; }
  fFirst = true;
  fNfp = 0;
  fFp = NULL;
}

void globalField::SetupArray()
{
  fFirst = false;
  fNfp = fFields->size();
  fFp = new const elementField* [fNfp+1]; // add 1 so it's never 0
  for (int i=0; i<fNfp; ++i) fFp[i] = (*fFields)[i];
}
