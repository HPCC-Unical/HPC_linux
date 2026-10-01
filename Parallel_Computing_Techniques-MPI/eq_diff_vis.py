import numpy as np
import matplotlib.pyplot as plt

# Reads the file of the parameters
finp = open( "parameters.data", "r" )
string = finp.readline()
dt = float( string )
string = finp.readline()
Tend = float( string )
string = finp.readline()
Tprint = float( string )
string = finp.readline()
cc = float( string )
string = finp.readline()
nu = float( string )
string = finp.readline()
kk = float( string )
string = finp.readline()
debug = int( string )
finp.close()

Nprints = int( Tend / Tprint ) + 1
for nout in range( Nprints ):
    xx, ff = np.loadtxt( "out-%d.dat" % ( nout ), unpack = True )
    plt.title( r"$f(x,t=%f)"%( Tprint * nout ) )
    plt.ylim( -1.0, +1.0 )
    plt.plot( xx, ff, 'r-' )
    plt.show()
