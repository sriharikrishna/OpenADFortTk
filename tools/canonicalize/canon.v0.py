'''
Sample python script to illustrate context line processing +
trivial canonicalization
'''
import sys

from Lib.fortContextFile import fortContextFile
import Lib.fortStmts as fs
from Lib.canon import canon_lexi

f1 = fortContextFile(sys.argv[1])

f1.rewrite(canon_lexi).printit()

