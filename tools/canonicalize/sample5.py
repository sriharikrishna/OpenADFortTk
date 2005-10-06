'''
Sample python script to illustrate parsed line processing
'''

import sys

from Lib.fortParseFile import fortParseFile,fortParseFileIter
import Lib.fortStmts as fs

fname = sys.argv[1]

f1 = fortParseFileIter(sys.argv[1])

def countem(l,d):
    'run for side effect only'
    t = l.__class__.__name__
    v = d.get(t,0)
    d[t] = v+1
    if t == 'GenStmt':
        print '***GenStmt detected:',' '.join(l.scan)
    return []

count = dict()
for l in f1.map([(fs.GenStmt,countem)],count):
    pass

for stmt_type in count:
    print stmt_type

