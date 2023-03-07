#include "magneticField.hh"

using namespace std;

MyMagneticField::MyMagneticField()
{

	double lenUnit = millimeter;
	double fieldUnit = tesla;

	ifstream file("magField.TAB"); // Open the file for reading.
	//char buffer[256];
	//file.getline(buffer, 256);

	//file >> nx >> ny >> nz; // Note dodgy order
	nx = 101;
	ny = 101;
	nz = 101;
	
	G4cout << "  [ Number of values x,y,z: "
		<< nx << " " << ny << " " << nz << " ] "
		<< G4endl;
	xField.resize(nx);
	yField.resize(nx);
	zField.resize(nx);
	int ix, iy, iz;
	for (ix = 0; ix < nx; ix++) {
		xField[ix].resize(ny);
		yField[ix].resize(ny);
		zField[ix].resize(ny);
		for (iy = 0; iy < ny; iy++) {
			xField[ix][iy].resize(nz);
			yField[ix][iy].resize(nz);
			zField[ix][iy].resize(nz);
		}
	}
	// Read in the data
	G4double xval = 0.;
	G4double yval = 0.;
	G4double zval = 0.;
	G4double bx = 0.;
	G4double by = 0.;
	G4double bz = 0.;
	for (ix = 0; ix < nx; ix++) {
		for (iy = 0; iy < ny; iy++) {
			for (iz = 0; iz < nz; iz++) {
				file >> xval >> yval >> zval >> bx >> by >> bz;
				//G4cout << "xval: " << xval << ", yval: " << yval << ", zval: " << zval << G4endl;

				xval *= 1000;
				yval *= 1000;
				zval *= 1000;
				//exit(0);
				/*
				if (isnan(xval))
				{
					xval = 0.0;
				}
				if (isnan(yval))
				{
					yval = 0.0;
				}
				if (isnan(zval))
				{
					zval = 0.0;
				}
				*/
				if (ix == 0 && iy == 0 && iz == 0) {
					minx = xval * lenUnit;
					miny = yval * lenUnit;
					minz = zval * lenUnit;
				}
				xField[ix][iy][iz] = bx * fieldUnit;
				yField[ix][iy][iz] = by * fieldUnit;
				zField[ix][iy][iz] = bz * fieldUnit;
			}
		}
	}
	file.close();
	maxx = xval * lenUnit;
	maxy = yval * lenUnit;
	maxz = zval * lenUnit;



	//
	G4cout << "\n ---> ... done reading " << G4endl;

	// G4cout << " Read values of field from file " << filename << G4endl;
	G4cout << " ---> assumed the order:  x, y, z, Bx, By, Bz "
		<< "\n ---> Min values x,y,z: "
		<< minx / mm << " " << miny / mm << " " << minz / mm << " mm "
		<< "\n ---> Max values x,y,z: "
		<< maxx / mm << " " << maxy / mm << " " << maxz / mm << " mm " << G4endl;

	// Should really check that the limits are not the wrong way around.
	//if (maxx < minx) { swap(maxx, minx); invertX = true; }
	//if (maxy < miny) { swap(maxy, miny); invertY = true; }
	//if (maxz < minz) { swap(maxz, minz); invertZ = true; }
	G4cout << "\nAfter reordering if neccesary"
		<< "\n ---> Min values x,y,z: "
		<< minx / mm << " " << miny / mm << " " << minz / mm << " mm "
		<< " \n ---> Max values x,y,z: "
		<< maxx / mm << " " << maxy / mm << " " << maxz / mm << " mm ";

	dx = maxx - minx;
	dy = maxy - miny;
	dz = maxz - minz;
	G4cout << "\n ---> Dif values x,y,z (range): "
		<< dx / m << " " << dy / m << " " << dz / m << " m in z "
		<< "\n-----------------------------------------------------------" << G4endl;

}

MyMagneticField::~MyMagneticField()
{}

void MyMagneticField::GetFieldValue(const G4double point[4], G4double* Bfield) const
{
	double x = point[0];
	double y = point[1];
	double z = point[2];

	// Position of given point within region, normalized to the range
	// [0,1]
	double xfraction = (x - minx) / dx;
	double yfraction = (y - miny) / dy;
	double zfraction = (z - minz) / dz;

	//if (invertX) { xfraction = 1 - xfraction; }
	//if (invertY) { yfraction = 1 - yfraction; }
	//if (invertZ) { zfraction = 1 - zfraction; }

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
		Bfield[0] = 0.0;
		Bfield[1] = 0.0;
		Bfield[2] = 0.0;
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

		// Full 3-dimensional version
		Bfield[0] =
			xField[xindex][yindex][zindex] * (1 - xlocal) * (1 - ylocal) * (1 - zlocal) +
			xField[xindex][yindex][zindex + 1] * (1 - xlocal) * (1 - ylocal) * zlocal +
			xField[xindex][yindex + 1][zindex] * (1 - xlocal) * ylocal * (1 - zlocal) +
			xField[xindex][yindex + 1][zindex + 1] * (1 - xlocal) * ylocal * zlocal +
			xField[xindex + 1][yindex][zindex] * xlocal * (1 - ylocal) * (1 - zlocal) +
			xField[xindex + 1][yindex][zindex + 1] * xlocal * (1 - ylocal) * zlocal +
			xField[xindex + 1][yindex + 1][zindex] * xlocal * ylocal * (1 - zlocal) +
			xField[xindex + 1][yindex + 1][zindex + 1] * xlocal * ylocal * zlocal;

		Bfield[1] =
			yField[xindex][yindex][zindex] * (1 - xlocal) * (1 - ylocal) * (1 - zlocal) +
			yField[xindex][yindex][zindex + 1] * (1 - xlocal) * (1 - ylocal) * zlocal +
			yField[xindex][yindex + 1][zindex] * (1 - xlocal) * ylocal * (1 - zlocal) +
			yField[xindex][yindex + 1][zindex + 1] * (1 - xlocal) * ylocal * zlocal +
			yField[xindex + 1][yindex][zindex] * xlocal * (1 - ylocal) * (1 - zlocal) +
			yField[xindex + 1][yindex][zindex + 1] * xlocal * (1 - ylocal) * zlocal +
			yField[xindex + 1][yindex + 1][zindex] * xlocal * ylocal * (1 - zlocal) +
			yField[xindex + 1][yindex + 1][zindex + 1] * xlocal * ylocal * zlocal;

		Bfield[2] =
			zField[xindex][yindex][zindex] * (1 - xlocal) * (1 - ylocal) * (1 - zlocal) +
			zField[xindex][yindex][zindex + 1] * (1 - xlocal) * (1 - ylocal) * zlocal +
			zField[xindex][yindex + 1][zindex] * (1 - xlocal) * ylocal * (1 - zlocal) +
			zField[xindex][yindex + 1][zindex + 1] * (1 - xlocal) * ylocal * zlocal +
			zField[xindex + 1][yindex][zindex] * xlocal * (1 - ylocal) * (1 - zlocal) +
			zField[xindex + 1][yindex][zindex + 1] * xlocal * (1 - ylocal) * zlocal +
			zField[xindex + 1][yindex + 1][zindex] * xlocal * ylocal * (1 - zlocal) +
			zField[xindex + 1][yindex + 1][zindex + 1] * xlocal * ylocal * zlocal;
	}

	//G4cout << "x: " << x << ", y: " << y << ", z: " << z << G4endl;
	//G4cout << "Bx: " << Bfield[0] << ", By: " << Bfield[1] << ", Bz: " << Bfield[2] <<  G4endl;
	/*
	if (Bfield[0] != 0) {
		G4cout << "Bx: " << Bfield[0] << G4endl;
	}

	if (Bfield[1] != 0) {
		G4cout << "By: " << Bfield[1] << G4endl;
	}

	if (Bfield[2] != 0) {
		G4cout << "Bz: " << Bfield[2] << G4endl;
	}
	*/

}
