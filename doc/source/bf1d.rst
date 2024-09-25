1D validation case
==================

The configuration presented in this tutorial is located in the folder ``tutorials/biofilmFoam/1d-A/``
and corresponds to the first 1D validation test case from the original work by Eberl et al.

This 1D configuration focuses on biofilm growth from a surface. The domain consists of 64 cells,
with the biomass inoculum deposited at one end and the nutrient supplied by pure diffusion at the other end.

For all the test cases supplied, we use the dimensions and parameter values specified in the original work. 
The mesh is described in this file ``system/blockMeshDict``, and each cell is 1.6 microns

.. literalinclude:: bf1d-1
   :language: text

Model parameters are entered in the ``constant/transportProperties`` file

.. literalinclude:: bf1d-2
   :language: text

To run this case, the procedure is as follows 

.. prompt:: bash

   cd tutorials/biofilmFoam/1d-A/
   blockMesh
   setFields
   biofilmFoam
   postProcess -func sample

All steps are also specified in the ``tutorials/biofilmFoam/1d-A/run`` script.
Then, the script ``tutorials/biofilmFoam/1d-plot.py`` reproduces the figure illustrating the evolution of biofilm growth over time

.. prompt:: bash

   ln -s ../1d-plot.py
   python3 1d-plot.py

The obtained image, reported below, illustrates time trends in nutrient concentration C and biomass M.
   
.. figure:: img/biofilmFoam-tutorial-1d-a.png
   :scale: 75 %
   :alt: biofilmFoam-tutorial-1d-a.png
   :align: center

|br|

The other 1D test cases of this type (1d-B, 1d-C and 1d-D) available in the toolbox,  can be used to handle elementary behaviours, namely
the biofilm growth under non-symmetric, the biofilm growth under symmetric conditions and the merging of two colonies.

.. |br| raw:: html

  <br/>
