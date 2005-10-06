'''
Sample python script to illustrate parsed line processing
'''

import sys

from Lib.fortParseFile import fortParseFile,fortParseFileIter
import Lib.fortStmts as fs

fname = sys.argv[1]

f1 = fortParseFileIter(sys.argv[1])

def fn(l):
    'run for side effect only'
    print '**FN ==>','  '.join(l.scan)
    return []

for l in f1.map([(fs.GenStmt,lambda *l:[]),
                 (fs.FunctionStmt,fn),]):
    pass
