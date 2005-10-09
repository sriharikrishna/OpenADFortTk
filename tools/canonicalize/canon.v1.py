'''
Sample python script to illustrate context line processing +
trivial canonicalization
'''
import sys

from Lib.fortContextFile import fortContextFile

from Lib.canon import canon_lexi,decl_lexi,_verbose

# _verbose = True

f1 = fortContextFile(sys.argv[1])

f1.rewrite(canon_lexi).rewrite(decl_lexi).printit()


