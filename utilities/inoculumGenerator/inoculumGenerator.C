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

    argList::addOption("xmin","float","xmin");
    argList::addOption("xmax","float","xmax");
    argList::addOption("ymin","float","ymin");
    argList::addOption("ymax","float","ymax");
    argList::addOption("zmin","float","zmin");
    argList::addOption("zmax","float","zmax");
    
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

    float xmin;
    if (args.found("xmin"))
    {
	xmin = stof(args.opt("xmin"));
    }
    else
    {
	xmin = -VGREAT;
    }

    float xmax;
    if (args.found("xmax"))
    {
	xmax = stof(args.opt("xmax"));
    }
    else
    {
	xmax = VGREAT;
    }

    float ymin;
    if (args.found("ymin"))
    {
	ymin = stof(args.opt("ymin"));
    }
    else
    {
	ymin = -VGREAT;
    }

    float ymax;
    if (args.found("ymax"))
    {
	ymax = stof(args.opt("ymax"));
    }
    else
    {
	ymax = VGREAT;
    }

    float zmin;
    if (args.found("zmin"))
    {
	zmin = stof(args.opt("zmin"));
    }
    else
    {
	zmin = -VGREAT;
    }

    float zmax;
    if (args.found("zmax"))
    {
	zmax = stof(args.opt("zmax"));
    }
    else
    {
	zmax = VGREAT;
    }
    
    Info << endl;

    cout << "box: [" << xmin << "," << xmax << "] [" << ymin << "," << ymax << "] [" << zmin << "," << zmax << "]\n\n";
    
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

	if ( (mesh.C()[cellid][0]<xmin) || (mesh.C()[cellid][0]>xmax) ||
       	     (mesh.C()[cellid][1]<ymin) || (mesh.C()[cellid][1]>ymax) ||
	     (mesh.C()[cellid][2]<zmin) || (mesh.C()[cellid][2]>zmax) ) {
	    test = false;
	}
	
	if (test == true) {
	    tabCells[i] = cellid;
	    topoFile << "      " << cellid << "\n";
	    Info << cellid << endl;
	}
	else {
	    i--;
	}
	
    }

    topoFile << "      );\n";  
    topoFile << " }\n";
    topoFile << " );\n";  

    topoFile.close();

    Info << "\n" << args.get<int>("nbcells") << " cells inoculated in system/topoSetDict" << endl;
  
    Info << "\nEnd\n" << endl;

    return 0;
    
}


// ************************************************************************* //
