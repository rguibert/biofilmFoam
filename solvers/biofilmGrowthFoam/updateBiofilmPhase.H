
forAll ( mesh.C(), celli) {
    if(M[celli] > SMALL) {
	biofilmPhase[celli] = 1.;
    }
}

dimensionedScalar biofilmVolume = sum(biofilmPhase*mesh.V())/sum(mesh.V());

// #include <iostream>
// #include <fstream>

// std::ofstream ofile;
// ofile.open ("biofilmPhase.dat", std::fstream::app);
// ofile << runTime.timeName() << " " << biofilmVolume.value() << "\n";
// ofile.close();

if (biofilmVolume.value() > 0.95) {
    runTime.printExecutionTime(Info);
    break;
}
