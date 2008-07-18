'''
Sample python script to illustrate context line processing +
trivial canonicalization
'''
import sys
import cPickle as cp

from optparse import OptionParser

from Lib.fortContextFile import fortContextFile

from Lib.userFuncs import addUserFunc

from Lib.canon import canon_lexi,decl_lexi,_verbose

def hook1(self):
    if hasattr(self.toplev,'_scnt'):
        pass
    else:
        self.toplev._scnt = 0
        self.toplev.slice_undo = dict()

def main():
  _verbose   = True
  usage = '%prog [options] <input_file>'
  opt = OptionParser(usage=usage)
  opt.add_option('-u','--uDefFuncsFile',dest='uDefFuncsFile',
                 help="file containing names of user defined functions not to be canonicalized",
                 metavar="<file_name>")
  opts, args = opt.parse_args()
  try:
      if len(args) < 1:
          opt.error("expect input file argument")
      fn = args[0]
      if (opts.uDefFuncsFile) :
          uFuncsFile=open(opts.uDefFuncsFile,"r")
          for theLine in uFuncsFile:
              addUserFunc(theLine.lower().strip())
          uFuncsFile.close()    
      f1 = fortContextFile(fn,hook1)
      f1rw = f1.rewrite(canon_lexi).rewrite(decl_lexi)
      slcf = open('reslice.dat','w')
      pp = cp.Pickler(slcf)
      pp.dump(f1rw.lines[0].ctxt.toplev.slice_undo)
      slcf.close()
      f1rw.printit()
  except RuntimeError, e:
      print 'caught excetion: ',e
      return -1
  return 0

if __name__ == "__main__":
  sys.exit(main())
