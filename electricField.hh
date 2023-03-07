#ifndef ELFIELD_HH
#define ELFIELD_HH

#include "G4ElectricField.hh"
#include "G4SystemOfUnits.hh"

#include <fstream>
#include <vector>
#include <cmath>


class MyElectricField : public G4ElectricField
{
public:
	MyElectricField();
	~MyElectricField();
	void GetFieldValue(const G4double point[4], G4double* Bfield) const;
private:
	// The dimensions of the table
	G4int nx, ny, nz;
	// The physical limits of the defined region
	double minx, maxx, miny, maxy, minz, maxz;
	// The physical extent of the defined region
	double dx, dy, dz;
	double fXoffset;
	bool invertX, invertY, invertZ;

	std::vector< std::vector< std::vector< double > > > xField;
	std::vector< std::vector< std::vector< double > > > yField;
	std::vector< std::vector< std::vector< double > > > zField;
	
};

#endif
