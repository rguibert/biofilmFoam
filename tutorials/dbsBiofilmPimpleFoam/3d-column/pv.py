import sys
import math
if sys.version_info<(3,5,0):
  sys.stderr.write("You need python 3.0 or later!\n")
  exit(1)

rc = 50*1.89e-6
rs = 40*1.89e-6
h = 280*1.89e-6
  
pv = math.pi*rc*rc*h-3*4/3*math.pi*rs*rs*rs
n_pvh = 10
q = n_pvh*pv/3600

print(q)
