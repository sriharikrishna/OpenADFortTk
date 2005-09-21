'''
Sample python script to use the new fortran processing library
'''
import sys

from Lib.fortFile import Ffile

fname = sys.argv[1]

f1 = Ffile.file(fname)

for l in f1.iterlines():
    print l,


