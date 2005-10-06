'''
Sample python script to illustrate parsed line processing
'''

import sys

from Lib.fortParseFile import fortParseFile
import Lib.fortStmts as fs

fname = sys.argv[1]

f1 = fortParseFile(sys.argv[1])

for l in f1.map([]):
    print repr(l)

