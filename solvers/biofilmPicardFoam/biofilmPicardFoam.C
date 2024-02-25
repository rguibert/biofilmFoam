/*---------------------------------------------------------------------------* \
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
    biofilmPicardFoam

\*---------------------------------------------------------------------------*/

#include "fvCFD.H"
#include "pimpleControl.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

int main(int argc, char *argv[])
{
  
    #include "setRootCase.H"
    #include "createTime.H"
    #include "createMesh.H"
    #include "createFields.H"
    #include "readPicardControls.H"
    
    pimpleControl pimple(mesh);

    // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

    Info << "\nStarting time loop\n" << endl;

    while (runTime.run())
    {

	#include "readTimeControls.H"
	#include "setDeltaT.H"
	
	runTime++;
      
	Info << "Time = " << runTime.timeName() << nl << endl;
      
	#include "CEqn.H"

	scalar resPicard = GREAT;
	scalar iterPicard = 0;
	
        while ((resPicard > tolPicard) && (iterPicard != maxIterPicard))
        {
            iterPicard++;
	    #include "updateDiffusion.H"
	    #include "MEqn.H"
	    resPicard = gMax((mag(M-M.prevIter()))->internalField());
	    Info << "Picard iteration " << iterPicard << ": residual = " << resPicard << endl;
        }

	if (resPicard > tolPicard)
        {
	    FatalErrorIn("biofilmPicardFoam.C") << "Picard not converged!" << abort(FatalError);
	}
	
	#include "updateBiofilmPhase.H"
      
	runTime.write();

	runTime.printExecutionTime(Info);
      
    }

    Info << "End\n" << endl;

    return 0;
    
}


// ************************************************************************* //
