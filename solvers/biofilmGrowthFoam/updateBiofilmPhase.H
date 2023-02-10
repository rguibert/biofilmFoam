
forAll ( mesh.C(), celli) {
  if(M[celli] > SMALL) {
    biofilmPhase[celli] = 1.;
  }
}

dimensionedScalar biofilmVolume = sum(biofilmPhase*mesh.V())/sum(mesh.V());
Info << "Occupied volume = " << biofilmVolume.value() << endl;

if (biofilmVolume.value() > 0.95) {
  runTime.printExecutionTime(Info);
  break;
 }
