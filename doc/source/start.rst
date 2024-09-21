Getting started
===============

Introduction
------------

**biofilmFoam** is an open-source toolbox designed for the simulation of biofilm growth at the micro-scale, coupledwith surrounding hydrodynamics. Built on the OpenFOAM environment, it leverages numerous features such as pre- and post-processing tools and parallel computing efficiency.

The current version of biofilmFoam is based on Eberl's deterministic biofilm growth model. However, the toolbox is flexible and can also accommodate more recent biofilm models.

Source code
-----------

As a reminder, the source code can be found `here <https://github.com/rguibert/biofilmFoam>`_.

The source code is organized in a classical OpenFOAM structure:

  - The ``doc/`` directory contains the sources for the documentation.

  - The ``libraries/`` directory contains the specific source code for timestep management.

  - The ``solvers/`` directory contains the specific solvers.

  - The ``tutorials/`` directory contains test and validation cases.

  - The ``utilities/`` directory contains specific post-processing tools.

  - The ``allwclean`` script cleans (or purges) the binary directories.

  - The ``allwmake`` script compiles all elements of the package.
    
  - The ``changelog`` file describes information about successive versions.

  - The ``license`` file describes the GPL-3.0 license.

  - The ``readme.rst`` file contains essential information about the toolbox.
