'''
Simple program to re-introduce the slice operations that were
removed by the canonicalizer

NOTE: Currently, the reslice info is in a file named reslice.dat.
That will most likely be changed in the future to reflect
a multifile process.
'''

import sys
from Lib.reslice import reslice

reslice(sys.argv[1]).printit()

