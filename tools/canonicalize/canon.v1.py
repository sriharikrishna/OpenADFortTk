'''
Sample python script to illustrate context line processing +
trivial canonicalization
'''
import sys
import cPickle as cp
from optparse import OptionParser

from Lib.fortContextFile import fortContextFile

import Lib.canon as lc 

def hook1(self):
    if hasattr(self.toplev,'_scnt'):
        pass
    else:
        self.toplev._scnt = 0
        self.toplev.slice_undo = dict()


def main():
  lc._verbose   = True
  usage = '%prog [options] <input_file>'
  opt = OptionParser(usage=usage)
  opt.add_option("","--r8",dest='r8',
                 help="set default size of REAL to 8 bytes",
                 action='store_true',default=False)
  options, args = opt.parse_args()
  if len(args) != 1:
     opt.error("expect input file argument")
  if options.r8 :
      lc._defaultPrec8=True
  f1 = fortContextFile(args[0],hook1)

  f1rw = f1.rewrite(lc.canon_lexi).rewrite(lc.decl_lexi)

  slcf = open('reslice.dat','w')
  pp = cp.Pickler(slcf)
  pp.dump(f1rw.lines[0].ctxt.toplev.slice_undo)
  slcf.close()

  f1rw.printit()
  return 0

if __name__ == "__main__":
  sys.exit(main())

