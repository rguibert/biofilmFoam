/*---------------------------------------------------------------------------*\


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

Global
    setDeltaT

\*---------------------------------------------------------------------------*/

if (adjustTimeStep)
  {
    
    scalar maxDeltaTFact = maxCo/(CoNum + SMALL);
    scalar deltaTFact = min(min(maxDeltaTFact, 1.0 + 0.1*maxDeltaTFact), 1.2);

    scalar dtForM = dtManagerM.computeTimestep();
    scalar dtForC = dtManagerC.computeTimestep();
    
    runTime.setDeltaT
    (
	min
	(
	    min(dtForM, dtForC),
	    min(deltaTFact*runTime.deltaTValue(), maxDeltaT)
        )
    );

    Info << "deltaT = " <<  runTime.deltaTValue() << endl;
}

// ************************************************************************* //
