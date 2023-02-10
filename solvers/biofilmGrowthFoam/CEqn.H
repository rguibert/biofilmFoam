fvScalarMatrix CEqn
(
   fvm::ddt(C)
 - fvm::laplacian(d1, C)
 == 
 - fvm::Sp(K1*M/(K2+C), C)
 );

solve(CEqn);

ddtC = gMax(mag(fvc::ddt(C)())())/(gMax(C)+SMALL);
