'''
Sample python script to use the new fortran processing library
'''
import sys

from Lib.fortScanFile import fortScanFile,fortScanLine,fortScanComment

def checkfn(l):
    from warnings import warn
    if l.rm:
        warn('line not completely scanned:\n%s------\n' % l.rawline)
    return [ l.scan[0] ]

fname = sys.argv[1]

f1 = fortScanFile(fname)
lex = ((fortScanComment,lambda l: []),
       (fortScanLine,   checkfn))

for l in f1.map(lex):
    print l


