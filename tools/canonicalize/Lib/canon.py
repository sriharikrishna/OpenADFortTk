'''
canonicalization routines
'''

import fortStmts as fs
import fortExp  as fe
from intrinsic import is_intrinsic

__tmp_prefix = 'ad_ctmp'
__call_prefix = '_ad_s_'

def new_call(a,v):
    '''from an app term, and a new var v,
    generate a call to a related subroutine, with v as the last var
    '''
    return fs.CallStmt(__call_prefix + a.head,
                       a.args + [v])
    
def gen_repl_fns(line):
    '''routine to generate closures that keep track of various
    function replacement ops
    '''

    line.ctxt._tcnt    = 0
    line.ctxt.new_vars = []

    def repl_fn(a):
        tvar = __tmp_prefix + str(line.ctxt._tcnt)

        line.ctxt._tcnt += 1
        line.ctxt.new_vars.append(tvar)
        line.ctxt.new_calls.append(new_call(a,tvar))

        return tvar

    def pat_fn(a):
        lookup = line.ctxt.lookup_var
        return isinstance(a,fe.App) and \
               not ( lookup(a.head).dims or \
                     lookup(a.head).lngth or \
                     is_intrinsic(a.head) )

    return (pat_fn,repl_fn)

fn2sub = fe.subst

def canon1(e,fn_pat,fn_exp):
    '''First canon of an exp: remove function calls and repl
    with subroutine calls.
    canon1 of an expression => ([contexted-stmts],new_exp)
    '''
    e1  = fe.subst(e,fn_pat,fn_repl)
    pre = []
    for l in fn_repl.stmts:
        pre.extend([ll for ll in l.canon()])

    return (pre,e1)

def canon_call(self):
    '''
    Canonicalize a call statement by replacing function calls with
    subroutine calls, and replacing all arguments that are not
    a simple variable or a constant with new temporaries
    '''
    newargs = []
    self.ctxt.new_calls   = []


    new_assigns = []
    for a in self.args:
        a1           = fn2sub(a,self.ctxt.fn_pat,self.ctxt.fn_repl)
        (a1,assigns) = nontriv(a1,self)
        new_assigns.extend(assigns)
#        print '->back from nontriv, new assgns =',new_assigns
        newargs.append(a1)

    new_call = self.same(fs.CallStmt(self.head,newargs))
    pre = []
    for c in self.ctxt.new_calls:
        pre.extend([l for l in self.same(c).map()])
    
    pre.extend(new_assigns)
    pre.append(new_call)

    return pre

def canon_assign(self):
    '''
    Canonicalize an assigment statement by removing function
    calls from the rhs
    '''

    self.ctxt.new_calls   = []

    rhs = fn2sub(self.rhs,self.ctxt.fn_pat,self.ctxt.fn_repl)
    pre = []
    for c in self.ctxt.new_calls:
        pre.extend([l for l in self.same(c).map()])
    
    new_assign = self.same(fs.AssignStmt(self.lhs,rhs))
    pre.append(new_assign)

    return pre

def canon_ifthen(self):
    '''
    Canonicalize if-then stmt by canonicalizing the test
    component of the if
    '''
    self.ctxt.new_calls   = []

    tst = fn2sub(self.test,self.ctxt.fn_pat,self.ctxt.fn_repl)
    pre = []
    for c in self.ctxt.new_calls:
        pre.extend([l for l in self.same(c).map()])
    
    new_if = self.same(fs.IfThenStmt(tst))
    pre.append(new_if)

    return pre

def canon_PUstart(self):

    (fn_pat,fn_repl)   = gen_repl_fns(self)

    self.ctxt.fn_pat   = fn_pat
    self.ctxt.fn_repl  = fn_repl

    return [self]
    
def nontriv(e,line):
    if isinstance(e,str):
        return (e,[])
    if isinstance(e,fe.App) and not line.ctxt.fn_pat(e):
        return (e,[])

    tvar = __tmp_prefix + str(line.ctxt._tcnt)
    line.ctxt._tcnt += 1
    a1 = line.same(fs.AssignStmt(tvar,e))
#    print 'appending new assign-->',repr(a1)
#    line.ctxt.new_assigns.append(a1)
#    print 'new assigns list =',[a1]
    return (tvar,[a1])

'''
def set_canon():
    
    fs.PUstart.map    = canon_PUstart
    fs.CallStmt.map   = canon_call
    fs.AssignStmt.map = canon_assign
    fs.IfThenStmt.map = canon_ifthen
'''
def set_canon():
    for (cls,meth) in canon_lexi:
        cls.map = meth

canon_lexi = [(fs.PUstart,    canon_PUstart),
              (fs.CallStmt,   canon_call),
              (fs.AssignStmt, canon_assign),
              (fs.IfThenStmt, canon_ifthen),
              ]
    
'''
Spikes

from fortScan import scan1
def scan(s): return scan1.scan(s)[0]

class Sym(object):
    pass

dummy_sym       = Sym()
dummy_sym.dims  = []
dummy_sym.lngth = False

class Context(object):
    def lookup_var(s,v):
        return dummy_sym

parse = fs.parse

def init():
    global s,pp,p0,pp1,s1,s2,pp2

    s0 = 'subroutine no()'
    p0 = parse(scan(s0))
    p0.basic_line()
    p0.ctxt = Context()
    canon_PUstart(p0)
    s  = 'call foo(bar(x,y()))'
    pp = parse(scan(s))
    p0.same(pp)
    s1 = 'call foo(x + bar(k),h(I(1,2)))'
    pp1 = p0.same(parse(scan(s1)))
    s2  = 'xxx = 1. + g(kk * 2.2,h(II,ll(x+5,iiii)))'
    pp2 = p0.same(parse(scan(s2)))
    set_canon()
'''
