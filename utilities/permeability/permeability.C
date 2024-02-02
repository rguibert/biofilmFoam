/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | www.openfoam.com
     \\/     M anipulation  |
-------------------------------------------------------------------------------
    Copyright (C) 2011-2016 OpenFOAM Foundation
    Copyright (C) 2019 OpenCFD Ltd.
-------------------------------------------------------------------------------
License
    This file is part of OpenFOAM.

    OpenFOAM is free software: you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    OpenFOAM is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
    for more details.

    You should have received a copy of the GNU General Public License
    along with OpenFOAM.  If not, see <http://www.gnu.org/licenses/>.

Application
    permeability

\*---------------------------------------------------------------------------*/

#include "fvCFD.H"
#include <iostream>
#include <fstream>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

int main(int argc, char *argv[])
{

    std::ofstream kfile;
    kfile.open ("permeability.dat");
    
    Foam::timeSelector::addOptions();  
    Foam::argList args(argc,argv); 

    #include "createTime.H"
    Foam::instantList timeDirs = Foam::timeSelector::select0(runTime, args);

    // int last = timeDirs.size()-1;
    // runTime.setTime(timeDirs[last], last);

    #include "createMesh.H"
    
    Info<< "Reading transportProperties\n" << endl;
    IOdictionary transportProperties
    (
	IOobject
	(
	    "transportProperties",
	    runTime.constant(),
	    mesh,
	    IOobject::MUST_READ,
	    IOobject::NO_WRITE
	)
    );

    dimensionedScalar nu ("nu", dimensionSet(0, 2, -1, 0, 0, 0, 0), transportProperties);
    
    forAll(timeDirs, timei)
    {
      
	runTime.setTime(timeDirs[timei], timei);
    
	#include "createMesh.H"

	Info << "Reading p" << endl;
	volScalarField p
	(
	    IOobject
	    (
		"p",
		runTime.timeName(),
		mesh,
		IOobject::MUST_READ,
		IOobject::AUTO_WRITE
	    ),
	    mesh
	);

	Info << "Reading U" << endl;
	volVectorField U
	(
	    IOobject
	    (
		"U",
		runTime.timeName(),
		mesh,
		IOobject::MUST_READ,
		IOobject::AUTO_WRITE
	    ),
	    mesh
	);

	// box

	point bMin = mesh.bounds().min();
	point bMax = mesh.bounds().max();
    
	dimensionedScalar domainVolume = (bMax.component(0)-bMin.component(0))
	* (bMax.component(1)-bMin.component(1))
	* (bMax.component(2)-bMin.component(2));

	domainVolume.dimensions().reset(dimensionSet(0,3,0,0,0));

	dimensionedVector Lv =  vector(bMax.component(0)-bMin.component(0),
	bMax.component(1)-bMin.component(1),
	bMax.component(2)-bMin.component(2));

	Lv.dimensions().reset(dimensionSet(0,1,0,0,0));

	volScalarField cellVolume
	(
	    IOobject
	    (
		"cellVolume",
		runTime.timeName(),
		mesh,
		IOobject::NO_READ,
		IOobject::AUTO_WRITE
	    ),
	    mesh,
	    dimensionedScalar("zero",dimVolume,0.0)
	);

	cellVolume.ref() = mesh.V();

	// patches

	const fvPatchList& patches = mesh.boundary();

	string s1 = "procBoundary";
	string s2 = "empty";

	// U
    
	volVectorField wtU((U*cellVolume)/domainVolume);
	dimensionedVector wtavgU = gSum(wtU);
	wtavgU.dimensions().reset(dimensionSet(0,1,-1,0,0));
    
	dimensionedVector tmp = wtavgU/mag(wtavgU);

	// flowDirection

	vector flowDirection = vector (0,0,0);

	if ( (tmp[0] > tmp[1]) && (tmp[0] > tmp[2]) ) {
	    flowDirection = vector (1,0,0);
	}
	if ( (tmp[1] > tmp[0]) && (tmp[1] > tmp[2]) ) {
	    flowDirection = vector (0,1,0);
	}
	if ( (tmp[2] > tmp[0]) && (tmp[2] > tmp[1]) ) {
	    flowDirection = vector (0,0,1);
	}

	Info << "flow direction: " << flowDirection << endl;

	// pressures

	scalar px0 = 0.;
	scalar px1 = 0.;
	scalar py0 = 0.;
	scalar py1 = 0.;
	scalar pz0 = 0.;
	scalar pz1 = 0.;
    
	forAll(patches, patchI) {
	    if (patches[patchI].name().find(s1) == std::string::npos) {
		if (patches[patchI].type().find(s2) == std::string::npos) {

		    scalar area = gSum(mesh.magSf().boundaryField()[patchI]);
		    scalar sumField = 0;
	
		    if (area > 0) {
			sumField = gSum(mesh.magSf().boundaryField()[patchI]*p.boundaryField()[patchI])/area;
		    }

		    // Info << "Pressure average over patch " << patches[patchI].name() << " = " << sumField << endl;	
		
		    vector test = gSum(mesh.Sf().boundaryField()[patchI])/gSum(mesh.magSf().boundaryField()[patchI]);

		    if (  ( fabs(test[0]+1.)<SMALL ) && ( fabs(test[1])<SMALL ) && ( fabs(test[2])<SMALL ) )
		    {
			px0 = sumField;
		    }
		    else if ( ( fabs(test[0]-1.)<SMALL ) && ( fabs(test[1])<SMALL ) && ( fabs(test[2])<SMALL ) )
		    {
			px1 = sumField;
		    }
		    else if ( ( fabs(test[0])<SMALL ) && ( fabs(test[1]+1.)<SMALL ) && ( fabs(test[2])<SMALL ) )
		    {
			py0 = sumField;
		    }
		    else if ( ( fabs(test[0])<SMALL ) && ( fabs(test[1]-1.)<SMALL ) && ( fabs(test[2])<SMALL ) )
		    {
			py1 = sumField;
		    }
		    else if ( ( fabs(test[0])<SMALL ) && ( fabs(test[1])<SMALL ) && ( fabs(test[2]+1.)<SMALL ) )
		    {
			pz0 = sumField;
		    }
		    else if ( ( fabs(test[0])<SMALL ) && ( fabs(test[1])<SMALL ) && ( fabs(test[2]-1.)<SMALL ) )
		    {
			pz1 = sumField;
		    }
		
		}
	    }
	}

	dimensionedVector deltaP ( "deltaP", dimensionSet(0,2,-2,0,0), vector(mag(px0-px1), mag(py0-py1), mag(pz0-pz1)) );
    
	// permeability

	dimensionedScalar L = Lv & flowDirection;
	dimensionedScalar deltaP_flowDirection = deltaP & flowDirection;
	dimensionedVector K = wtavgU / (deltaP_flowDirection/L) * nu;

	Info << K.value() << endl;

	if (runTime > runTime.startTime()) {
	    kfile << runTime.timeName() << " " << K[0].value() << " " << K[1].value() << " " << K[2].value() << "\n";
	}
	
	Info << " " << endl;
    
    }

    kfile.close();
    
    Info << nl << "ExecutionTime = " << runTime.elapsedCpuTime() << " s"
	<< "  ClockTime = " << runTime.elapsedClockTime() << " s"
	<< nl << endl;

    Info << "End\n" << endl;

    return 0;
    
}


// ************************************************************************* //
