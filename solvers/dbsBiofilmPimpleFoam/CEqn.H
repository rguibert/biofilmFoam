fvScalarMatrix CEqn
(
   fvm::ddt(porosity,C)
 + porosity * fvm::div(phiByPorosity, C)  
 - fvm::laplacian(d1*porosity, C)
 == 
 - fvm::Sp(K1*M/(K2+C), C)
);

solve(CEqn);

ddtC = gMax(mag(fvc::ddt(C)())())/(gMax(C)+SMALL);
