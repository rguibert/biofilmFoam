volScalarField d2 = (Foam::pow(eps/(1-M),a)*Foam::pow(M,b))();
d2.dimensions().reset(dimensionSet(0,2,-1,0,0));

surfaceScalarField d2f (fvc::interpolate(d2,"d2"));
