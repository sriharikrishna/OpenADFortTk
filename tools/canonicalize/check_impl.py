'''
Sample python script to illustrate parsed line processing
'''

import sys

from Lib.fortParseFile import fortParseFile,fortParseFileIter
import Lib.fortStmts as fs

fname = sys.argv[1]

f1 = fortParseFileIter(sys.argv[1])

def impl(l):
    'run for side effect only'
    print '**IMPLICIT ',' '.join(l.scan[1:])
    return []

for l in f1.map([(fs.GenStmt,lambda *l:[]),
                 (fs.ImplicitStmt,impl),]):
    pass
