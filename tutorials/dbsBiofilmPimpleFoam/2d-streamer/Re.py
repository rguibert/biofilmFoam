import sys
if sys.version_info<(3,5,0):
  sys.stderr.write("You need python 3.0 or later!\n")
  exit(1)

Re = 1
L = 64*1.89e-6
nu = 1e-6

u = nu*Re/L

print("Re : ", Re)
print("L  : ", L, "m")
print("nu : ", nu, "m2/s")
print("u  : ", u, " m/s")
