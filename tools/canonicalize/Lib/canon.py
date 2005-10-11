'''
canonicalization routines
'''

import fortStmts as fs
import fortExp  as fe
from   fortContextFile import SymEntry
from intrinsic import is_intrinsic

__tmp_prefix   = 'ad_ctmp'
__call_prefix  = 'ad_s_'
__slice_prefix = 'ad_slc'

def new_call(a,v,polyfix=''):
    '''from an app term, and a new var v,
    generate a call to a related subroutine, with v as the last var
    '''
    return fs.CallStmt(__call_prefix + a.head + polyfix,
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
        ty = line.ctxt.ety(a)

        line.ctxt.new_vars.append((ty,tvar),)
        post_tag = ''
        if fs.poly(a.head):
            post_tag = '_' + ty[0].kw.lower()[0]
        line.ctxt.new_calls.append(new_call(a,tvar,post_tag))

        return tvar

    def pat_fn(a):
        lookup = line.ctxt.lookup_var
        return isinstance(a,fe.App) and \
               not ( lookup(a.head).dims or \
                     lookup(a.head).lngth or \
                     is_intrinsic(a.head) )

    def ety(e):
        ety1 = fe.exptype
        return ety1(e,
                    line.ctxt.lookup_type,
                    fs.kw2type,
                    fs.lenfn,
                    fs.poly,
                    fs.typemerge)

    def slice_subst(a):

        tvar = __slice_prefix + str(line.ctxt.toplev._scnt)
        line.ctxt.toplev._scnt += 1
        line.ctxt.new_vars.append(((fs.IntegerStmt,[]),tvar),)
        line.ctxt.toplev.slice_undo[tvar] = a

        return tvar

    return (pat_fn,repl_fn,ety,slice_subst)

fn2sub = fe.subst
def slice_pat(e):
    return isinstance(e,fe.Ops) and e.op == ':'

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
    slice_subst = self.ctxt.slice_subst
    for a in self.args:
        a0           = fe.subst(a,slice_pat,slice_subst)
        a1           = fn2sub(a0,self.ctxt.fn_pat,self.ctxt.fn_repl)
        (a1,assigns) = nontriv(a1,self)
        new_assigns.extend(assigns)
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

    slice_subst = self.ctxt.slice_subst
    rhs1 = fe.subst(self.rhs,slice_pat,slice_subst)
#    rhs = fn2sub(self.rhs,self.ctxt.fn_pat,self.ctxt.fn_repl)
    rhs = fn2sub(rhs1,self.ctxt.fn_pat,self.ctxt.fn_repl)
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

    slice_subst = self.ctxt.slice_subst
    tst1 = fe.subst(self.test,slice_pat,slice_subst)
#    tst = fn2sub(self.test,self.ctxt.fn_pat,self.ctxt.fn_repl)
    tst = fn2sub(tst1,self.ctxt.fn_pat,self.ctxt.fn_repl)
    pre = []
    for c in self.ctxt.new_calls:
        pre.extend([l for l in self.same(c).map()])
    
    new_if = self.same(fs.IfThenStmt(tst))
    pre.append(new_if)

    return pre

_verbose = False

def canon_PUstart(self):

    import sys
    (fn_pat,fn_repl,ety,slice_subst)   = gen_repl_fns(self)

    self.ctxt.fn_pat      = fn_pat
    self.ctxt.fn_repl     = fn_repl
    self.ctxt.ety         = ety
    self.ctxt.slice_subst = slice_subst  

    if _verbose:
        print >> sys.stderr, 'working on program unit ',self.ctxt.uname

    return [self]
    
def nontriv(e,line):
    if isinstance(e,str):
        return (e,[])

    lookup_dims   = line.ctxt.lookup_dims
    lookup_lngth  = line.ctxt.lookup_lngth

    if isinstance(e,fe.App) and ( lookup_dims(e.head) or \
                                  lookup_lngth(e.head) ):
        return (e,[])

    tvar = __tmp_prefix + str(line.ctxt._tcnt)
    line.ctxt._tcnt += 1
    line.ctxt.new_vars.append((line.ctxt.ety(e),tvar),)
    a1 = line.same(fs.AssignStmt(tvar,e))
    return (tvar,[a1])

def declare_tmpvars(line):
    '''Declare all temporary variables generated by
    canonicalization phase.
    This routine should be called at the decls marker
    '''
    rv = []
    for (ty,tvar) in line.ctxt.new_vars:
        (cls,mod) = ty
#        decl = cls(mod,[fe.App(tvar,[])])
        decl = cls(mod,[tvar])
        decl.lineno = False
        decl.lead   = line.lead
        decl.ctxt   = line.ctxt
        decl.ctxt.vars[tvar] = SymEntry(typeof=ty)
        decl.flow()
        rv.append(decl)

    rv.append(line)
    return rv

canon_lexi = [(fs.PUstart,    canon_PUstart),
              (fs.CallStmt,   canon_call),
              (fs.AssignStmt, canon_assign),
              (fs.IfThenStmt, canon_ifthen),
              ]

decl_lexi  = [(fs.LastDecl,   declare_tmpvars),
              ]
    
'''
Spikes

def fname_t(n): return n
def hook1(self):
    if hasattr(self.toplev,'_scnt'):
        pass
    else:
        self.toplev._scnt = 0
        self.toplev.slice_undo = dict()


from fortContextFile import fortContextFile

fc  = fortContextFile(fname_t('fc3.f'),hook1)
fcc = fc.rewrite(canon_lexi)
fcd = fcc.rewrite(decl_lexi)
'''
