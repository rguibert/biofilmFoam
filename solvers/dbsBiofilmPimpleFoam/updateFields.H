forAll (mesh.C(), celli) {
    if (M[celli] > SMALL) {
	K[celli] = biofilmPermeability.value();
	porosity[celli] = biofilmPorosity.value();
	biofilmPhase[celli] = 1.;
        darcyTerm[celli] = nu.value()/K[celli];
    }
    else {
	K[celli] = 1.;
	porosity[celli] = 1.;
	biofilmPhase[celli] = 0.;
	darcyTerm[celli] = 0.;
    }
}
