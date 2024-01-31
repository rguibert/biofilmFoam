// Solve the Momentum equation

MRF.correctBoundaryVelocity(U);

// tmp<fvVectorMatrix> tUEqn
// (
//    fvm::ddt(U) + fvm::div(phi, U)
//  + MRF.DDt(U)
//  + turbulence->divDevReff(U)
//  ==
//  fvOptions(U)
//  );

tmp<fvVectorMatrix> tUEqn
(
    (1./porosity) * fvm::ddt(U)
    + (1./porosity) * fvm::div(phiByPorosity, U)
    + (1./porosity) * MRF.DDt(U)
    + (1./porosity) * turbulence->divDevReff(U)
    + fvm::Sp(darcyTerm, U)
    ==
    fvOptions(U)
);
fvVectorMatrix& UEqn = tUEqn.ref();

UEqn.relax();

fvOptions.constrain(UEqn);

if (pimple.momentumPredictor())
{
    solve(UEqn == -fvc::grad(p));

    fvOptions.correct(U);
}
