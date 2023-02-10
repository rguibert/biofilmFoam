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

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

int main(int argc, char *argv[])
{
  
    #include "setRootCase.H"
    #include "createTime.H"
    #include "createMesh.H"
    #include "createFields.H"
  
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
	#include "updateDiffusion.H"
	#include "MEqn.H"
	#include "updateBiofilmPhase.H"
      
	runTime.write();

	runTime.printExecutionTime(Info);
      
    }

    Info << "End\n" << endl;

    return 0;
    
}


// ************************************************************************* //
