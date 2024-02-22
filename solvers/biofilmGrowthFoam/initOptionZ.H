scalar zlimit;
bool checkZmax = false;

if (!args.found("zmax"))
{
    zlimit = 1.;
}
else
{

    zlimit = stof(args.opt("zmax"));
    checkZmax = true;

    if ((zlimit > 1) || (zlimit < 0))
    {
	FatalError << "invalid value for zmax (must be in [0, 1])" << exit(FatalError);
    }
	
}

point bMin = mesh.bounds().min();
point bMax = mesh.bounds().max();

scalar Z = bMax.component(2)-bMin.component(2);
zlimit = zlimit*Z;
