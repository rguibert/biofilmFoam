Utilities
=========

biomass
-------

This post-processing tool enables the evaluation of the proportion of volume occupied by the biofilm phase. It generates a ``biomass.dat`` file that includes times and the corresponding percentages of volume occupied by the biofilm. Once the calculations are finished, type:

.. prompt:: bash

   biomass

inoculumGenerator
-----------------

This utility allows you to inoculate a surface with biomass. It randomly selects ``NBCELLS`` cells with a minimum of one side in contact with the ``PATCH`` surface. The utility is used with the following command 

.. prompt:: bash

   inoculumGenerator -patch PATCH -nbcells NBCELLS

It generates the file ``system/topoSetDict`` and the native OpenFOAM ``topoSet`` function creates the ``inoculum`` cells set. The biomass value (0.8 by default in all tutorials) is set in the ``0/M`` file by the native OpenFOAM function ``setFields``, via the associated dictionary ``setFieldsDict``. Its use is therefore tracked by orders

.. prompt:: bash

   topoSet
   setFields

The tool also has optional arguments that allow you to define a spatial window from which to draw cells at random. An example can be found in ``tutorials/biofilmFoam/3d-A``. For further information, type

.. prompt:: bash

   inoculumGenerator -help

permeability
------------

As with the ``biomass`` utility, this post-processing tool enables to evaluate the permeability of the domain by volume averaging. The biomass present is taken into account as a porous medium, with the effective permeability given in the ``0/K`` file. It generates a ``permeability.dat`` file that includes times and the evaluated permeability. Once the calculations are finished, type:

.. prompt:: bash

   permeability
