darcyTerm = fvc::average(laminarTransport.nu()/K);

scalar foo = gMax(M);

forAll (biofilmPhase, celli) {
  if(M[celli] > SMALL) {
    biofilmPhase[celli] = 1.;
    porosity[celli] = 1-M[celli];
  }
  else {
    biofilmPhase[celli] = 0.;
    porosity[celli] = 1.;
    darcyTerm[celli] = 0;
  }
}

// forAll(darcyTerm, celli)
// {
//   if (porosity[celli] > (1-SMALL)) {
//     darcyTerm[celli] = 0;
//   }
// }

