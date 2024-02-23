Info << "Reading field p\n" << endl;
volScalarField p
(
    IOobject
    (
	"p",
	runTime.timeName(),
	mesh,
	IOobject::MUST_READ,
	IOobject::AUTO_WRITE
    ),
    mesh
);

Info << "Reading field U\n" << endl;
volVectorField U
(
    IOobject
    (
	"U",
	runTime.timeName(),
	mesh,
	IOobject::MUST_READ,
	IOobject::AUTO_WRITE
    ),
    mesh
);

#include "createPhi.H"

label pRefCell = 0;
scalar pRefValue = 0.0;
setRefCell(p, pimple.dict(), pRefCell, pRefValue);
mesh.setFluxRequired(p.name());

singlePhaseTransportModel laminarTransport(U, phi);

autoPtr<incompressible::turbulenceModel> turbulence
(
    incompressible::turbulenceModel::New(U, phi, laminarTransport)
);

#include "createMRF.H"
#include "createFvOptions.H"

Info << "Reading field porosity\n" << endl;
volScalarField porosity
(
    IOobject
    (
	"porosity",
	runTime.timeName(),
	mesh,
	IOobject::MUST_READ,
	IOobject::AUTO_WRITE
    ),
    mesh
);

Info << "Reading field K\n" << endl;
volScalarField K
(
    IOobject
    (
	"K",
	runTime.timeName(),
	mesh,
	IOobject::MUST_READ,
	IOobject::AUTO_WRITE
    ),
    mesh
);

Info << "Creating averaged mass flux\n" << endl;
surfaceScalarField phiByPorosity
(
    IOobject
    (
	"phiByPorosity",
	runTime.timeName(),
	mesh,
	IOobject::READ_IF_PRESENT,
	IOobject::AUTO_WRITE
    ),
    phi*linearInterpolate(1./(porosity+SMALL))
);

dimensionedScalar nu ("nu", dimensionSet(0,2,-1,0,0), gMax(fvc::average( laminarTransport.nu() )()));

volScalarField darcyTerm ("darcyTerm", nu/K);


