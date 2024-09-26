3D sphere packing
=================

An interesting application of **biofilmFoam** is modeling bio-clogging in complex 3D media. This test case is based on an open dataset provided by Finney, which features a complex sphere packing. The case can be found in the ``tutorials/biofilmPimpleFoam/3d-packing/`` directory.

A cylinder with a height of 500 voxels and a diameter of 100 voxels was extracted from the binarized 3D image. The detailed extraction procedure is not provided. The constructed mesh, consisting of 1.3 million cells, is available in the ``constant/polyMesh.tgz`` compressed file. The mesh is rescaled just before using the solver.

.. literalinclude:: bpf3d-0
   :language: text

The flow is imposed from the upper surface, as specified in the ``0/U`` file.

.. literalinclude:: bpf3d-1
   :language: text

The normalized concentration is specified in the ``0/C`` file.

.. literalinclude:: bpf3d-2
   :language: text
	      
As with previous tutorials, the number of cells that are inoculated is fixed during pre-processing (see ``run`` script) before the resacling of the domain

.. prompt:: bash

   inoculumGenerator -patch solid -nbcells 5000 -zmin 50 -zmax 450
   topoSet
   setFields

For interested users, it is worth noting that the number of faces making up a surface can be found in the ``constant/polyMesh/boundary`` file.
This allows you to deduce the number of cells to be inoculated for the desired percentage.

The Reynolds number is estimated using sphere diameter and porosity. For a Reynolds equals to unity, the figure below illustrates the evolution of biofilm growth
to the clogging by step of 24 hours.
   
.. figure:: https://raw.githubusercontent.com/rguibert/public-images/refs/heads/main/biofilmPimpleFoam-tutorial-3d.png
   :width: 500px
   :alt: biofilmFoam-tutorial-3d-b-2.png
   :align: center

|br|
	   
.. |br| raw:: html

  <br/>
