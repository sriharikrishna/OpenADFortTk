'''
Sample python script to illustrate context line processing +
trivial canonicalization
'''
import sys
import cPickle as cp

from Lib.fortContextFile import fortContextFile

from Lib.canon import canon_lexi,decl_lexi,_verbose

def hook1(self):
    if hasattr(self.toplev,'_scnt'):
        pass
    else:
        self.toplev._scnt = 0
        self.toplev.slice_undo = dict()

_verbose   = True

f1 = fortContextFile(sys.argv[1],hook1)

f1rw = f1.rewrite(canon_lexi).rewrite(decl_lexi)

slcf = open('reslice.dat','w')
pp = cp.Pickler(slcf)
pp.dump(f1rw.lines[0].ctxt.toplev.slice_undo)
slcf.close()

f1rw.printit()


