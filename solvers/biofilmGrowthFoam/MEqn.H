fvScalarMatrix MEqn
(
   fvm::ddt(M)
 - fvm::laplacian(d2,M)
 == 
   //   fvm::Sp(K3*C/(K2+C), M)
   K3*C*M/(K2+C)
 - fvm::Sp(K4, M)
 );

solve(MEqn);

ddtM = gMax(mag(fvc::ddt(M)())())/(gMax(M)+SMALL);
