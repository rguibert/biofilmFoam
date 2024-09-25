2D parallel plates
================== 

This 2D test case illustrates biofilm growth between two flat plates, with a nutrient-laden fluid flowing between them. This case is located in ``tutorials/biofilmPimpleFoam/2d-parallel/``.
	   
Plate length is in the order of millimeter, and the inter-plate distance/length ratio is 0.125.
A parabolic velocity profile is imposed at the inlet,
and just over 6% of each plate surface is randomly inoculated onto a cell. 

The coupling of biofilm growth with the surrounding fluid involves several specific features:

- boundary conditions need to be defined in the ``0/`` directory.

- Permeability and porosity associated with the biofilm phase (which limit fluid velocity) can be specified in the ``constant/transportProperties`` file.
  
- The PIMPLE method must be parameterized in ``system/fvSolution`` for solving velocity :math:`\bf u` and pressure :math:`p` fields.
  
For a given inoculated starting state, the configuration after 96 hours at a Reynolds number of 1 is illustrated below.

.. figure:: https://raw.githubusercontent.com/rguibert/public-images/refs/heads/main/biofilmPimpleFoam-tutorial-2d.png
   :width: 700px
   :alt: biofilmPimpleFoam-tutorial-2d.png
   :align: center

|br|
	   
.. |br| raw:: html

  <br/>
