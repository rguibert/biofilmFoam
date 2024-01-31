darcyTerm = fvc::average(laminarTransport.nu()/K);

forAll(darcyTerm, celli)
{
    if (porosity[celli] > (1-SMALL)) {
	darcyTerm[celli] = 0;
    }
}

