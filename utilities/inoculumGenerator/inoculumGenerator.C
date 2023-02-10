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
    inoculumGenerator

\*---------------------------------------------------------------------------*/

#include "fvCFD.H"
#include <fstream>
#include <stdlib.h>
#include <time.h>


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

int main(int argc, char *argv[])
{

  argList::addOption("patch","word","specify the patch to inoculate");
  argList::addOption("nbcells","int","specify the number of cells to inoculate");
  
  Foam::timeSelector::addOptions();  
  Foam::argList args(argc,argv);

  if (!args.found("patch"))
    {
      FatalError << "no value specified" 
		 << nl << " use option -patch"
		 << exit(FatalError);
    }

  if (!args.found("nbcells"))
    {
      FatalError << "no value specified" 
  		 << nl << " use option -nbcells"
  		 << exit(FatalError);
    }  

  Info << endl;
  
  //Info << "nbcells: " << args.get<int>("nbcells") << endl;

  #include "createTime.H"  
  #include "createMesh.H"
  
  label patchID = mesh.boundaryMesh().findPatchID(args.get<word>("patch"));
  const polyPatch& cPatch = mesh.boundaryMesh()[patchID]; 

  Info << "Patch: " << args.get<word>("patch") << endl;
  Info << cPatch << endl;
  
  //Info << cPatch.start() << endl;
  //Info << cPatch.size() << endl;

  std::ofstream topoFile;
  topoFile.open("system/topoSetDict");

  topoFile << "FoamFile\n";
  topoFile << "{\n";
  topoFile << "    version     2.0;\n";
  topoFile << "    format      ascii;\n";
  topoFile << "    class       dictionary;\n";
  topoFile << "    location    \"system\";\n";
  topoFile << "    object      topoSetDict;\n";
  topoFile << "}\n";
  topoFile << "\n";
  topoFile << "actions\n";
  topoFile << "(\n";
  topoFile << " {\n";
  topoFile << "   name    inoculum;\n";
  topoFile << "   type    cellSet;\n";
  topoFile << "   action  new;\n";
  topoFile << "   source  labelToCell;\n";
  topoFile << "   value\n";
  topoFile << "     (\n";

  int tabCells[args.get<int>("nbcells")];

  srand(time(NULL)); // not pseudo-random
  
  for (int i=0; i<args.get<int>("nbcells"); ++i) {
    int v = rand() % cPatch.size();
    int faceid = cPatch.start() + v;
    int cellid = mesh.owner()[faceid];
    bool test = true;
    for (int j=0; j<i; ++j) {
      if (tabCells[j] == cellid) {
	test = false;
      }
    }
    if (test == true) {
      tabCells[i] = cellid;
      topoFile << "      " << cellid << "\n";
    }
    else {
      i--;
    }
  }

  topoFile << "      );\n";  
  topoFile << " }\n";
  topoFile << " );\n";  

  topoFile.close();

  Info << args.get<int>("nbcells") << " cells inoculated in system/topoSetDict" << endl;
  
  Info << "\nEnd\n" << endl;

  return 0;
    
}


// ************************************************************************* //
