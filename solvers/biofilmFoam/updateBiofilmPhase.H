
forAll (mesh.C(), celli) {
    if (M[celli] > SMALL) {
	biofilmPhase[celli] = 1.;
    }
    else {
	biofilmPhase[celli] = 0.;
    }
}

dimensionedScalar biofilmVolume = sum(biofilmPhase*mesh.V())/sum(mesh.V());
// bfile << runTime.timeName() << " " << biofilmVolume.value() << "\n";
    
if (biofilmVolume.value() > 0.95) {
    runTime.printExecutionTime(Info);
    break;
}
