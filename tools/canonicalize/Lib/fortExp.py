'''
Expression parser for fortran expressions:
  use rec decent
'''
from l_assembler import *
import fortScan  as fs
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

class Umi(_Exp):
    'unary minus'
    def __init__(self,exp):
        self.exp = exp

    def __repr__(self):
        return 'Umi(%s)' % (repr(self.exp),)

    def __str__(self):
        return '-%s' % (str(self.exp),)

    def map(self,fn):
        return Umi(fn(self.exp))

class Upl(_Exp):
    'unary plus'
    def __init__(self,exp):
        self.exp = exp

    def __repr__(self):
        return 'Upl(%s)' % (repr(self.exp),)

    def __str__(self):
        return '+%s' % (str(self.exp),)

    def map(self,fn):
        return Upl(fn(self.exp))

class Not(_Exp):
    'unary not'

    def __init__(self,exp):
        self.exp = exp

    def __repr__(self):
        return 'Not(%s)' % (repr(self.exp),)

    def __str__(self):
        return '.not. %s' % (str(self.exp),)

    def map(self,fn):
        return Not(fn(self.exp))

class ParenExp(_Exp):
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
    return disj(app,id,const,unaryExp,paren)(scan)

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

'''
Spikes
'''

def scan(s):
    import fortScan as fs
    return fs.scan1.scan(s)[0]

def ee(s):
    return Exp(s)[0]

def p1(s):
    return isinstance(s,Ops) and s.op == '*'

def r1(s):
    return Ops('+',s.a1,s.a2)

ss = 'f(a *x + b, x**2)'

'''

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
