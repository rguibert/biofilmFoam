Librairies
==========

numericalMethods
----------------

Efficient time step management is crucial for modeling biofilm growth, as the characteristic time scales can vary by several orders of magnitude. This library implements an adaptive time step management system based on time truncation error estimates (see Horgue et al for more details).

The time step is computed to maintain a relative time truncation error (estimated using Taylor series) below a user-defined value :math:`\epsilon_{error}`.
The time-step computations for the available time schemes in the code are as follows:

- backward Euler: :math:`\Delta t = \sqrt{ \frac{ 2 \epsilon_{error} x_{max} }{ \left( \partial^2 x / \partial t^2 \right)_{max}  } }`

- 2nd order backward scheme: :math:`\Delta t = \sqrt[3]{ \frac{ 4 \epsilon_{error} x_{max} }{ \left( \partial^3 x / \partial t^3 \right)_{max}  } }`
  ​
- Crank-Nicolson: :math:`\Delta t = \sqrt[3]{ \frac{ 12 \epsilon_{error} x_{max} }{ \left( \partial^3 x / \partial t^3 \right)_{max}  } }`

where :math:`x_{max}` is the value of the variable at the cell where the maximal derivative has been computed.

A third-order time scheme had to be implemented in the toolbox (``EulerD3dt3Scheme``, using he current and three previous time-step values) to allow adaptive time step management for the available time schemes.

The timestep manager is configured within the file ``system/controlDict``

.. literalinclude:: lib-nm1
   :language: text
	      
and the time scheme is specified in the file ``system/fvSchemes``

.. literalinclude:: lib-nm2
   :language: text

parabolicVelocity
-----------------

In many configurations of relatively slow flows, it is interesting to impose a parabolic velocity profile directly,
rather than giving it the space it needs to establish itself. To do this, we use a dedicated library.

The option to impose a parabolic velocity profile is loaded within the file ``system/controlDict`` (when coupling biofilm growth with the fluid)

.. literalinclude:: parabolic-load
   :language: text

and the properties are specified in the file ``0/U``
	      
.. literalinclude:: parabolic
   :language: text

