Solvers
=======

biofilmFoam
-----------

This solver allows the resolution of density-diffusion model of biofilm growth, as proposed by Eberl et al:

.. math::
   \frac{\partial c}{\partial t} = \nabla \cdot \left( d_1 \nabla c \right) - f(c,m)

.. math::
   \frac{\partial m}{\partial t} = \nabla \cdot \left( d_2(m) \nabla m \right) + g(c,m)

where :math:`c(t, {\bf x})` is the nutrient concentration, :math:`m(t,{\bf x})` is the biomass density,
:math:`d_i` (with :math:`i=1,2`) are diffusion coefficients,
:math:`f(c,m)` is the nutrient consumption rate and
:math:`g(c,m)` is the biomass production rate.

The code is written in a dimensionless form:

.. math::
   C(t, {\bf x}) = c(t, {\bf x}) / c_0

.. math::
   M(t, {\bf x}) = m(t, {\bf x}) / m_{max}
   
with  :math:`c_0` the initial nutrient concentration and :math:`m_{max}` the maximal biomass density.
   
biofilmPimpleFoam
-----------------

This solver allows to couple the previous density-diffusion biofilm model to the surrounding hydrodynamics, using a Darcy-Brinkman approach (see Soulaine et al):

.. math::
  \frac{1}{\phi} \left( \frac{\partial \rho {\bf u}}{\partial t}
  + \nabla \cdot \left( \frac{\rho}{\phi} {\bf u} {\bf u} \right) \right)
  = - \nabla p + \frac{\mu}{\phi} \nabla^2 {\bf u} - \frac{\mu}{k} {\bf u}

.. math::
  \nabla \cdot {\bf u} = 0

.. math::
   \frac{\partial c}{\partial t} + {\bf u} \cdot \nabla c = \nabla \cdot \left( d_1 \nabla c \right) - f(c,m)

.. math::
   \frac{\partial m}{\partial t} = \nabla \cdot \left( d_2(m) \nabla m \right) + g(c,m)   

