M.storePrevIter();

fvScalarMatrix MEqn
(
      fvm::ddt(M)
    - fvm::laplacian(d2,M)
    == 
      fvm::Sp(K3*C/(K2+C), M)
    - fvm::Sp(K4, M)
);

solve(MEqn);

resPicard = gMax((mag(M-M.prevIter()))->internalField());
Info << "Picard iteration " << iterPicard << ": residual = " << resPicard << endl; 

ddtM = gMax(mag(fvc::ddt(M)())())/(gMax(M)+SMALL);
