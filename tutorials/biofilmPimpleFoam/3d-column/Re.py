import sys
import math
if sys.version_info<(3,5,0):
  sys.stderr.write("You need python 3.0 or later!\n")
  exit(1)

Re = 1e-3
  
rho = 1e3
mu = 1e-3
  
rcyl = 50*1.89e-6
rsph = 40*1.89e-6
h = 240*1.89e-6

cyl_are = math.pi*rcyl*rcyl
cyl_vol = math.pi*rcyl*rcyl*h
sph_vol = 3*4/3*math.pi*rsph*rsph*rsph

eps = (cyl_vol-sph_vol)/cyl_vol

# Re = rho*q*rsph*2/(mu*cyl_are*eps)

q = Re*mu*cyl_are*eps/(rho*rsph*2)

print('porosity = ', eps)

pv = cyl_vol-sph_vol

print('Reynolds = ', Re)

print('flowrate = ', q, '(m3/s)')
print('flowrate = ', q*3.6e9, '(mL/h)')

