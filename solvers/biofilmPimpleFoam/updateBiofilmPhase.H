
forAll (mesh.C(), celli) {
    if (M[celli] > SMALL) {
	biofilmPhase[celli] = 1.;
	K[celli] = biofilmPermeability.value();
	porosity[celli] = biofilmPorosity.value();
        darcyTerm[celli] = nu.value()/K[celli];	
    }
    else {
	biofilmPhase[celli] = 0.;
	M[celli] = 0.;
	K[celli] = 1.;
	porosity[celli] = 1.;
	darcyTerm[celli] = 0.;
    }
}

dimensionedScalar biofilmVolume = sum(biofilmPhase*mesh.V())/sum(mesh.V());
// bfile << runTime.timeName() << " " << biofilmVolume.value() << "\n";
    
if (biofilmVolume.value() > 0.95) {
    runTime.printExecutionTime(Info);
    break;
}
