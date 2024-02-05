/*---------------------------------------------------------------------------* \

    ]3 | () /= | |_ |\/| /= () /\ |\/|

    Copyright 2023 Toulouse INP
    Romain Guibert

License
    This file is part of biofilmFoam, an extension of OpenFOAM.

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
    biofilmGrowthFoam

\*---------------------------------------------------------------------------*/

#include "fvCFD.H"
#include "pimpleControl.H"
#include "timestepManager.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //


int main(int argc, char *argv[])
{

    argList::addOption("zmax", "zmax");
    
    #include "setRootCase.H"
    #include "createTime.H"
    #include "createMesh.H"
    #include "createFields.H"
    #include "readTimeControls.H"
    
    pimpleControl pimple(mesh);

    // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

    Info << "\nStarting time loop\n" << endl;

    scalar zlimit;
    bool checkZmax = false;
    if (!args.found("zmax"))
    {
	zlimit = 1.;
    }
    else
    {
	zlimit = stof(args.opt("zmax"));
	checkZmax = true;
	if ((zlimit > 1) || (zlimit < 0))
	{
	    FatalError << "invalid value for zmax (must be in [0, 1])" << exit(FatalError);
	}
	
    }

    point bMin = mesh.bounds().min();
    point bMax = mesh.bounds().max();

    scalar Z = bMax.component(2)-bMin.component(2);
    zlimit = zlimit*Z;
    
    while (runTime.run())
    {
	
	#include "setDeltaT.H"
	
	runTime++;
      
	Info << "Time = " << runTime.timeName() << endl;

	dtManagerC.updateDerivatives();
	dtManagerM.updateDerivatives();
		
	#include "CEqn.H"
	#include "updateDiffusion.H"
	#include "MEqn.H"
	#include "updateBiofilmPhase.H"

	Info << "C in [" << gMin(C) << ";" << gMax(C) << "]" << endl;
	Info << "M in [" << gMin(M) << ";" << gMax(M) << "]" << endl;
	
	runTime.write();

	runTime.printExecutionTime(Info);

	#include "checkZmax.H"
      
    }

    Info << "End\n" << endl;

    return 0;
    
}


// ************************************************************************* //
