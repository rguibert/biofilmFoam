const dictionary& picardDict = mesh.solutionDict().subDict("picard");
if (!picardDict.found("tolerance"))
{
    FatalErrorIn("readPicardControls.H")
    << "Missing keyword tolerance in system/fvSolution.Picard"
	<< abort(FatalError);
}

const scalar tolPicard = picardDict.lookupOrDefault<scalar>("tolerance", 1.);
if (!picardDict.found("maxIter"))
{
    FatalErrorIn("readPicardControls.H")
    << "Missing keyword maxIter in system/fvSolution.picard"
	<< abort(FatalError);
}

const label maxIterPicard = picardDict.lookupOrDefault<label>("maxIter",10);
