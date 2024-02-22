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

    std::ofstream bfile;
    bfile.open ("biomass.dat");
    
    Foam::timeSelector::addOptions();  
    Foam::argList args(argc,argv); 

    #include "createTime.H"
    Foam::instantList timeDirs = Foam::timeSelector::select0(runTime, args);

    // int last = timeDirs.size()-1;
    // runTime.setTime(timeDirs[last], last);
    
    forAll(timeDirs, timei)
    {
      
	runTime.setTime(timeDirs[timei], timei);
    
	#include "createMesh.H"

	Info << "Reading M" << endl;
	volScalarField M
	(
	    IOobject
	    (
		"M",
		runTime.timeName(),
		mesh,
		IOobject::MUST_READ,
		IOobject::AUTO_WRITE
	    ),
	    mesh
	);

	// volume

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

	dimensionedScalar domainVolume = gSum(cellVolume);
	Info << domainVolume << endl;

	// biomass

	dimensionedScalar biomassVolume = 0.*domainVolume;

	forAll(M, celli) {
	    if(M[celli] > SMALL) {
		biomassVolume += cellVolume.ref()[celli];
	    }
	}

	biomassVolume = biomassVolume/domainVolume;

	// write

	bfile << runTime.timeName() << " " << biomassVolume.value() << "\n";
	
    }
	
    Info << nl << "ExecutionTime = " << runTime.elapsedCpuTime() << " s"
	<< "  ClockTime = " << runTime.elapsedClockTime() << " s"
	<< nl << endl;

    Info << "End\n" << endl;

    return 0;
    
}


// ************************************************************************* //
