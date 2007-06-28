'''
Expression parser for fortran expressions:
  use rec decent
'''
from l_assembler import *
import fortScan  as fs

class _TypeMod(object):
    'modifier for type declaration'

    def __init__(self,e):
        self.mod = e

    def __repr__(self):
        return '%s(%s)' % (self.__class__.__name__,repr(self.mod),)

    def __str__(self):
        return self.pat % str(self.mod)

class fst_Kind(_TypeMod):
    pat = '(%s)'

import sre
from flatten import flatten
from op_prec import OpPrec

_id_re     = sre.compile(fs.id_re,sre.I | sre.X)
_flonum_re = sre.compile(fs.flonum_re,sre.I | sre.X)
_int_re    = sre.compile(fs.int_re,sre.I | sre.X)
_q_re      = sre.compile(fs.q_re,sre.I | sre.X)
_qq_re     = sre.compile(fs.qq_re,sre.I | sre.X)
_num_re    = sre.compile(fs.flonum_re + '|' + fs.int_re,sre.I | sre.X)

_quote_set   = set(['"',"'"])
_logicon_set = set(['.true.','.false.'])
_optbl       = (([':']    ,1),
                (['.or.'] ,2),
                (['.and.'],3),
                (['.le.',
                  '.lt.',
                  '.eq.',
                  '.ne.',
                  '.ge.',
                  '.gt.'] ,4),
                (['//']   ,5),
                (['+','-'],6),
                (['*','/'],7),
                (['**']   ,8),
                )

_unary_ops   = ['-',
                '+',
                '.not.',
                ]

def is_op(op):
    '''
    Check to see if op is in the _optbl

    This routine is only necessary for
    unit test to check if all ops are covered
    '''
    op_l = op.lower()
    for (lst,prec) in _optbl:
        if op_l in lst:
            return True
    return False

class _Exp(object):
    'base class for Expression trees'
    pass

class App(_Exp):
    'application expressions (ie f(x))'
    def __init__(self,head,args):
        self.head = head
        self.args = args

    def __repr__(self):
        return 'App(%s,%s)' % (repr(self.head),repr(self.args))

    def __str__(self):
        return '%s(%s)' % (str(self.head),
                           ','.join([str(l) for l in self.args]))
    def map(self,fn):
        return App(self.head,[fn(a) for a in self.args])

    def typeit(self,exptype,idchk,kw2type,lenfn,poly,typemerge):
        headtype = idchk(self.head)
        if poly(self.head):
            return typemerge([exptype(l,idchk,kw2type,lenfn,poly,typemerge) \
                              for l in self.args],
                             headtype)
        return headtype

class Unary(_Exp):
    def typeit(self,exptype,idchk,kw2type,lenfn,poly,typemerge):
        return exptype(self.exp,idchk,kw2type,lenfn,poly,typemerge)
    
class Umi(Unary):
    'unary minus'
    def __init__(self,exp):
        self.exp = exp

    def __repr__(self):
        return 'Umi(%s)' % (repr(self.exp),)

    def __str__(self):
        return '-%s' % (str(self.exp),)

    def map(self,fn):
        return Umi(fn(self.exp))

class Upl(Unary):
    'unary plus'
    def __init__(self,exp):
        self.exp = exp

    def __repr__(self):
        return 'Upl(%s)' % (repr(self.exp),)

    def __str__(self):
        return '+%s' % (str(self.exp),)

    def map(self,fn):
        return Upl(fn(self.exp))

class Not(Unary):
    'unary not'

    def __init__(self,exp):
        self.exp = exp

    def __repr__(self):
        return 'Not(%s)' % (repr(self.exp),)

    def __str__(self):
        return '.not. %s' % (str(self.exp),)

    def map(self,fn):
        return Not(fn(self.exp))

class ParenExp(Unary):
    'parenthesized expression'
    def __init__(self,exp):
        self.exp = exp

    def __repr__(self):
        return 'ParenExp(%s)' % (repr(self.exp),)

    def __str__(self):
        return '(%s)' % (str(self.exp),)

    def map(self,fn):
        return ParenExp(fn(self.exp))

class Ops(_Exp):
    'some sequence of binops'
    def __init__(self,op,a1,a2):
        self.op = op.lower()
        self.a1 = a1
        self.a2 = a2
    
    def __repr__(self):
        return 'Ops(%s,%s,%s)' % (repr(self.op),repr(self.a1),repr(self.a2),)

    def __str__(self):
        return '%s %s %s' % (str(self.a1),
                             str(self.op),
                             str(self.a2))
    def map(self,fn):
        return Ops(self.op,fn(self.a1),fn(self.a2))

    def typeit(self,exptype,idchk,kw2type,lenfn,poly,typemerge):
        return typemerge([exptype(self.a1,idchk,kw2type,lenfn,
                                  poly,typemerge),
                          exptype(self.a2,idchk,kw2type,lenfn,
                                  poly,typemerge)],'????')
class StarExp(_Exp):
    '* expression, as used for instance in array dimensions a(1:*)'
    def __init__(self,exp):
        self.exp = exp

    def __repr__(self):
        return 'StarExp(%s)' % (repr(self.exp),)

    def __str__(self):
        return '%s' % (str(self.exp),)

    def map(self,fn):
        return StarExp(fn(self.exp))


def is_id(t):
    return _id_re.match(t)

def is_const(t):
    t1 = t.lower()
    return t1[0] in _quote_set or t1 in _logicon_set or _num_re.match(t1)

def _lc_const(t):
    t1 = t.lower()
    if t1 in _logicon_set:
        return t1
    return t

def is_unary(t):
    t1 = t.lower()
    return t1 in _unary_ops

def _squeeze(exp_list):
    ''' turn an expression list into an actual list
    with no embedded commas or lists
    '''
    (e1,rest) = exp_list
    return [e1] + [e2 for (dc,e2) in rest]

def _mkapp1(a):
    '''turn a recognized app into an App object'''
    (h,dc1,el,dc2) = a
    return App(h,_squeeze(el))

def _mkapp0(a):
    '''turn a recognized app with empty arglist into an App object'''
    (h,dc1,dc2) = a
    return App(h,[])

def _mkumi(um):
    'turn a recognized unary minus into a Umi object'
    (dc,e) = um
    return Umi(e)

def _mkupl(um):
    'turn a recognized unary plus into a Upl object'
    (dc,e) = upl
    return Upl(e)

def _mkunot(unot):
    (dc,e) = unot
    return Not(e)

_unary_tbl = {'+'    : Upl,
              '-'    : Umi,
              '.not.': Not,
              }

def _mkunary(e):
    (op,ee) = e
    return _unary_tbl[op.lower()](ee)

def _mkparen(parn):
    'turn a recognized parenthesized expression into a paren object'
    (dc,e,dc2) = parn
    return ParenExp(e)

def _mkstar(star):
    'turn a recognized star expression into a StarExp object'
    return StarExp(star)

def _mkexp(e):
    'convert a recognized exp into an Ops object'
    (a,oplst) = e
    for (op,a2) in oplst:
        a = Ops(op,a,_mkexp(a2))
    return a

id      = pred(is_id)
const   = pred(is_const)
const   = treat(const,_lc_const)
unary   = pred(is_unary)


def atom(scan):
    '''eta expansion, since letrec unavail in python'''
    return disj(app,id,const,unaryExp,paren,starexp)(scan)

Exp = OpPrec(atom,_optbl,('**',))
Exp = treat(Exp,_mkexp)

ExpList   = seq(Exp,star(seq(lit(','),Exp)))
ExpList_l = treat(ExpList,_squeeze)

app1      = seq(id,lit('('),ExpList,lit(')'))
app1      = treat(app1,_mkapp1)

app0      = seq(id,lit('('),lit(')'))
app0      = treat(app0,_mkapp0)

app       = disj(app1,app0)

unaryExp  = seq(unary,atom)
unaryExp  = treat(unaryExp,_mkunary)

paren     = seq(lit('('),Exp,lit(')'))
paren     = treat(paren,_mkparen)

starexp   = lit('*')
starexp   = treat(starexp ,_mkstar)

# utility list
#
app_id    = disj(app,id)
app_id_l  = seq(app_id,star(seq(lit(','),app_id)))
app_id_l  = treat(app_id_l,_squeeze)

#
# simple subtree replacement function
#
def subst(a,pat,repl):
    if pat(a):
        return repl(a)
    elif isinstance(a,str):
        return a
    else:
        return a.map(lambda x:subst(x,pat,repl))

def const_type(e,kw2type,lenfn):
    kind_re = sre.compile(r'_(\w+)')
    if _flonum_re.match(e):
        sep_re = sre.compile(r'([^_]+)(_(\w+))?')
        v      = sep_re.match(e)
        ty     = 'd' in v.group(1).lower() and 'doubleprecision' or \
                 'real'
        ty     = kw2type(ty)
        kind   = v.group(2) and fst_Kind(v.group(3)) or []
        return (ty,kind)
    if _int_re.match(e):
        ty   = kw2type('integer')
        kind = kind_re.search(e)
        kind = kind and [ fst_Kind(kind.group(1)) ] or []
        return (ty,kind)
    if e.lower() in _logicon_set:
        return (kw2type('logical'),[])
    if e[0] in _quote_set:
        return (kw2type('character'),[lenfn(len(e)-2)])

def exptype(e,idchk,kw2type,lenfn,poly,typemerge):
    if isinstance(e,str) and is_const(e):
        return const_type(e,kw2type,lenfn)
    if isinstance(e,str) and _id_re.match(e):
        return idchk(e)
    return e.typeit(exptype,idchk,kw2type,lenfn,poly,typemerge)

'''
Spikes

def scan(s):
    import fortScan as fs
    return fs.scan1.scan(s)[0]

def ee(s):
    return Exp(scan(s))[0]

def p1(s):
    return isinstance(s,Ops) and s.op == '*'

def r1(s):
    return Ops('+',s.a1,s.a2)

def kw2type(s): return s
def lenfn(n): return str(n)
def poly(s) : return s.lower() == 'max'
mergeit = dict(character=0,
               logical=1,
               integer=2,
               real=3,
               complex=4,
               doubleprecision=5,
               doublecomplex=6,
               )

def typecompare(t1,t2):
    if t1[0] == t2[0]:
        return(t1[0],max(t1[1],t2[1]))
    if mergeit[t1[0]] > mergeit[t2[0]]: return t1
    return t2
    
def typemerge(lst,default):
    if not lst: return default
    if len(lst) == 1: return lst[0]
    if len(lst) == 2: return typecompare(lst[0],lst[1])
    t1 = typecompare(lst[0],lst[1])
    for l in lst[2:]:
        t1 = typecompare(t1,l)
    return t1
    
def idchk(s):
    kkk = dict(x=('real',[]),y=('doubleprecision',[]),
               ix=('integer',[]),hasit=('logical',[]))
    return kkk.get(s,('real',[]))

def t():
    global s1,s2,s3,s4,s5,s6,ety
    s1 = '(1)'
    s2 = '(.true.)'
    s3 = 'x(3.,sss * 7.7D0)'
    s4 = 'max(ix,7.7D0)'
    s5 = 'max("This is a string" // "more stuff",5)'
    s6 = 'hasit .or. .not. hasit'
    ety = lambda e:exptype(e,idchk,kw2type,lenfn,poly,typemerge)
    
def t0():
    global s1,s2,s3,s4,s5,s6,s7,s8,s9,s10,s11
    s1 = '3.1415D0'
    s2 = '3.1415'
    s3 = '3.1415_w2f_4'
    s4 = '3.1415_6'
    s5 = '31415'
    s6 = '31415_w2f_i2'
    s7 = '31415_2'
    s8 = '.TRUE.'
    s9 = '.False.'
    s10 = "'123456'"
    s11 = '"12345678"'

ss = 'f(a *x + b, x**2)'

s1 = 'IF((K .GE. 2) .AND.(CALCADVECTION .AND.(.NOT. IMPLICITADVECTION))) THEN'
s2 = 'DATA(A1(tmp0), tmp0 = 1, 5, 1) / 3.49999994039535522461D-01,' + \
     ' 6.00000023841857910156D-01, 1.0D00, 1.5D00, ' + \
     '1.39999997615814208984D00 /'
s3 = '+x * 59. + yy(zk)**(+ y)'
s4 = 'f(15,zzz) + 1d0 * y'
s5 = 'if (x.EQ.5.OR.y.LE.(i **j + 2_2)) goto 15'
s6 = 'if (x.EQ.5.)) goto 15'
s7 = 'if (x.EQ.5..OR.y.LE.i)) goto 15'

'''
