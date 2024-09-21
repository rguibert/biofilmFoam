Installation
============

How to install
--------------

First, verify that OpenFOAM is installed and operational on your computer. Then, load the OpenFOAM environment

.. prompt:: bash

   source /installation/path/OpenFOAM/etc/bashrc

Next, within the **biofilmFoam** directory:

.. prompt:: bash

   cd /path/biofilmFoam/
   ./allwmake -j

Upon compilation, dynamic libraries are stored in the designated OpenFOAM user directory, ``$FOAM_USER_LIBBIN``,
while executable solvers and utilities are placed in the corresponding OpenFOAM user directory ``$FOAM_USER_APPBIN``.

Each tutorial directory includes ``./run`` and ``./clean`` scripts, which facilitate the testing of the installation and validation of the solvers.


Compatibility
-------------

Note that if you want to use the latest version of **biofilmFoam**, it is necessary to have a sufficiently recent installation of OpenFOAM. The toolbox has been tested with v2206, v2306 and v2406. `OpenFOAM.org` and `foam-extend` versions are not supported.
