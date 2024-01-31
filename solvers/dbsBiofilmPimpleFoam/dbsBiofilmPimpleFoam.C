/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | www.openfoam.com
     \\/     M anipulation  |
-------------------------------------------------------------------------------
    Copyright (C) 2011-2017 OpenFOAM Foundation
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
    dbsBiofilmPimpleFoam

\*---------------------------------------------------------------------------*/

#include "fvCFD.H"
#include "dynamicFvMesh.H"
#include "singlePhaseTransportModel.H"
#include "turbulentTransportModel.H"
#include "pimpleControl.H"
//#include "CorrectPhi.H"
#include "cfdTools/general/CorrectPhi/CorrectPhi.H"
#include "fvOptions.H"
#include "timestepManager.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

int main(int argc, char *argv[])
{
    #include "postProcess.H"

    #include "addCheckCaseOptions.H"
    #include "setRootCaseLists.H"
    #include "createTime.H"
    #include "createDynamicFvMesh.H"
    #include "initContinuityErrs.H"
    #include "createDyMControls.H"
    #include "createFields.H"
    #include "createUfIfPresent.H"
    #include "CourantNo.H"
    #include "setInitialDeltaT.H"
    #include "readTimeControls.H"
    
    turbulence->validate();

    // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
  
    Info << "\nStarting time loop\n" << endl;

    while (runTime.run())
    {
      
	//#include "CourantNo.H"
	#include "setDeltaT.H"
      
	++runTime;

	Info << "Time = " << runTime.timeName() << nl << endl;

	dtManagerC.updateDerivatives();
	dtManagerM.updateDerivatives();
      
	#include "updateFields.H"      
	#include "pimple.H"

	#include "CEqn.H"
	#include "updateDiffusion.H"
	#include "MEqn.H"
	#include "updateBiofilmPhase.H"
	
        Info << "C in [" << gMin(C) << ", " << gMax(C) << "]" << endl;
        Info << "M in [" << gMin(M) << ", " << gMax(M) << "]" << endl;

	// if ( (gMax(C)>1.+SMALL) || (gMin(C)<-SMALL) ) {
	//     Info << ">>> Check min/max concentrations! <<<" << endl;
	//     if (runTime.value() > 3600) {
	// 	FatalErrorIn("dbsBiofilmPimpleFoam.H") << nl << "Error conservation!" << nl << abort(FatalError);
	//     }
	// }
      
	runTime.write();

	runTime.printExecutionTime(Info);
    }

    Info << "End\n" << endl;

    return 0;
}


// ************************************************************************* //
