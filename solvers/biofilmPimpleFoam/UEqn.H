// Solve the Momentum equation

MRF.correctBoundaryVelocity(U);

tmp<fvVectorMatrix> tUEqn
(
    (1./porosity+SMALL) * fvm::ddt(U)
    + fvm::div(phiByPorosity, U)
    - fvm::laplacian(laminarTransport.nu()/(porosity+SMALL), U)
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
