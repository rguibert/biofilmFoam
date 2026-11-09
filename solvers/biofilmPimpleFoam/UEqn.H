// Solve the Momentum equation

MRF.correctBoundaryVelocity(U);

tmp<fvVectorMatrix> tUEqn
(
    (1./porosity+SMALL) * ( fvm::ddt(U) + fvm::div(phiByPorosity, U) ) // K. Choudhary
    - fvm::laplacian(laminarTransport.nu()/(porosity+SMALL), U)
    + fvm::Sp(darcyTerm, U)
    + laminarTransport.nu()/porosity*(fvc::grad(porosity) & fvc::grad((1/porosity)*U)) // Machado et al, TiPM, 2025 
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
