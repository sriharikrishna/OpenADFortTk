import sys
import os
from optparse import OptionParser

from PyLib.fortParseFile import fortParseFile as fpf
from PyLib.prog1 import Prog1
import PyLib.lexi_visitor as lv
import PyLib.fortStmts as fs
import PyLib.fortExp   as fe
import PyLib.mutable_tree as mt
from PyLib.xaifpp import val_deriv_m as valm
from PyLib.xaifpp import type_active_m as actm
from PyLib.xaifpp import add_active_module as addm

def normal(self,arg):
    'attach self to prog repr'
    arg.attach(self)

def exec_s(self,arg):
    'mutate an executable statement, and attach'
    self.mutate(self)
    arg.attach(self)

def noop(self,*a):
    'do nothing'
    pass

opt = OptionParser()
opt.add_option('-f','--forward',dest='fwd',
               help="use forward mode postprocessing",
               action='store_true',default=False)
opt.add_option('-r','--real',dest='real',
               help='"old style" postprocessing:transform real vars',
               action='store_true',default=False)
opt.add_option('-t','--template',dest='tfile',
               default='ad_template.f',
               help='template file (default=ad_template.f)',metavar='FILE')
opt.add_option('-i','--inline',dest='ifile',
               default='ad_inline.f',
               help='inline definition file(default=ad_inline.f)',
               metavar='FILE')

exp1  = mt.LexiMutator([(fe._Exp,noop),
                       (fe.App,valm),
                       ])

vstr  = lv.LexiVisitor([(fs.GenStmt,normal),
                       (fs.Exec,exec_s),
                       (fs.DrvdTypeDecl,actm),
                       (fs.UseStmt,addm),
                       ],'build')

xaifv = lv.MultiLexiVisitor(vstr,exp1)

if __name__ == '__main__':
    config, args = opt.parse_args()
    fn         = args[0]
    (base,ext) = os.path.splitext(fn)
    newfn      = base + '.post' + ext

    Prog1(xaifv,fpf(fn).lines).writeit(newfn)
