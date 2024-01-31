// --- reading

Info << "Reading field C\n" << endl;

volScalarField C
(
    IOobject
    (
	"C",
	runTime.timeName(),
	mesh,
	IOobject::MUST_READ,
	IOobject::AUTO_WRITE
    ),
    mesh
);

Info << "Reading field M\n" << endl;

dimensionedScalar ddtC("ddtC", dimensionSet(0,0,0,0,0), 0.);

volScalarField M
(
    IOobject
    (
	"M",
	runTime.timeName(),
	mesh,
	IOobject::MUST_READ,
	IOobject::AUTO_WRITE
    ),
    mesh
);

dimensionedScalar ddtM("ddtM", dimensionSet(0,0,0,0,0), 0.);

// --- transportProperties

Info << "Reading transportProperties\n" << endl;

IOdictionary transportProperties
(
    IOobject
    (
	"transportProperties",
	runTime.constant(),
	mesh,
	IOobject::MUST_READ_IF_MODIFIED,
	IOobject::NO_WRITE
    )
);

// dimemsions: kg | m | s | K | mol | A | cd

Info << "Reading parameter d1 \n" << endl;
dimensionedScalar d1 ("d1", dimensionSet(0, 2, -1, 0, 0, 0, 0), transportProperties);

Info << "Reading parameter mmax \n" << endl;
dimensionedScalar mmax ("mmax", dimensionSet(1, 3, 0, 0, 0, 0, 0), transportProperties);

Info << "Reading parameter c0 \n" << endl;
dimensionedScalar c0 ("c0", dimensionSet(1, 3, 0, 0, 0, 0, 0), transportProperties);

Info << "Reading parameter mum \n" << endl;
dimensionedScalar mum ("mum", dimensionSet(0, 0, -1, 0, 0, 0, 0), transportProperties);

Info << "Reading parameter Yxs \n" << endl;
dimensionedScalar Yxs ("Yxs", dimensionSet(0, 0, 0, 0, 0, 0, 0), transportProperties);

Info << "Reading parameter ms \n" << endl;
dimensionedScalar ms ("ms", dimensionSet(0, 0, -1, 0, 0, 0, 0), transportProperties);

Info << "Reading parameter Ks \n" << endl;
dimensionedScalar Ks ("Ks", dimensionSet(1, 3, 0, 0, 0, 0, 0), transportProperties);

Info << "Reading parameter eps \n" << endl;
dimensionedScalar eps ("eps", dimensionSet(0, 0, 0, 0, 0, 0, 0), transportProperties);

Info << "Reading parameter a \n" << endl;
dimensionedScalar a ("a", dimensionSet(0, 0, 0, 0, 0, 0, 0), transportProperties);

Info << "Reading parameter b \n" << endl;
dimensionedScalar b ("b", dimensionSet(0, 0, 0, 0, 0, 0, 0), transportProperties);

// --- calculating

Info << "Calculating parameters ki \n" << endl;
dimensionedScalar k1 = mum/Yxs+ms;
dimensionedScalar k2 = Ks;
dimensionedScalar k3 = Yxs/mmax;
dimensionedScalar k4 = ms*mmax;

Info << "Calculating parameters Ki \n" << endl;
dimensionedScalar K1 = mmax*k1/c0;
dimensionedScalar K2 = k2/c0;
dimensionedScalar K3 = mmax*k3*k1;
dimensionedScalar K4 = k3*k4;

// --- G

//Info << "G = l * l * G0" << endl;
//Info << "G0 = mum * mmax / (d1 * c0)" << endl;
//Info << "G0 = " << mum*mmax/(d1*c0) << endl;

// --- biofilm phase

volScalarField biofilmPhase
(
    IOobject
    (
	"biofilmPhase",
	runTime.timeName(),
	mesh,
	IOobject::NO_READ,
	IOobject::AUTO_WRITE
    ),
    mesh,
    dimensionedScalar ("biofilmPhase", dimensionSet(0,0,0,0,0), 0.),
    "zeroGradient"
);

forAll ( mesh.C(), celli) {
    if(M[celli] > SMALL) {
	biofilmPhase[celli] = 1.;
    }
}
