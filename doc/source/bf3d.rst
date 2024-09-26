3D validation case
==================

The 3D cases of biofilm growth without fluid coupling were also derived from the work of Eberl et al.
These cases demonstrate the model's ability to produce different types of biofilm.

We present here the case provided in ``tutorials/biofilmFoam/3d-B/``.

This configuration involves growing biofilm on a 128 x 64 cell surface. On this surface,
821 cells (i.e., 10% of the surface) are randomly inoculated with biomass.
Nutrient supply is again provided by pure diffusion from the upper surface of the domain,
which is located 64 cells away from the inoculated bottom surface.
The physical dimensions are fixed in ``the system/blockMeshDict`` file

.. literalinclude:: bf3d-1
   :language: text

Below is a commented version of the ``run`` script used to launch the case:

.. literalinclude:: bf3d-2
   :language: text

``runApplication`` and ``runParallel`` are internal OpenFOAM functions that automatically manage log files and retrieve the necessary arguments, such as the number of processors for the second function. Once the calculation is complete, the results can be visualized using ParaView

.. prompt:: bash

   paraview 3d-A.foam

For the same inoculum at the bottom surface, different types of biofilm formation can be obtained, depending on the model parameters provided in the ``constant/transportProperties`` file, as illustrated below.

.. figure:: https://raw.githubusercontent.com/rguibert/public-images/refs/heads/main/biofilmFoam-tutorial-3d-b-1.png
   :width: 500px
   :alt: biofilmFoam-tutorial-3d-b-1.png
   :align: center

.. figure:: https://raw.githubusercontent.com/rguibert/public-images/refs/heads/main/biofilmFoam-tutorial-3d-b-2.png
   :width: 500px
   :alt: biofilmFoam-tutorial-3d-b-2.png
   :align: center	   

|br|	   
	      
The **biofilmFoam** solver can be launched with the additionnal `-zmax` option,
which automatically stops the solver when the biofilm phase reaches the specified height. 
This option is activated in particular for the illustrations above, with :math:`z_{max} = 0.3 h`, with :math:`h` the domain height.

.. |br| raw:: html

  <br/>
