if (checkZmax)
{

    forAll (mesh.C(), celli) {
	if (biofilmPhase[celli] == 1.) {
	    if (mesh.C()[celli][2] > zlimit) {
		Info << "maximum biomass height reached!" << endl;
		FatalError << "End" << exit(FatalError);
	    }
	}
    }
    
}

