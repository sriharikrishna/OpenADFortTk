'''
Various Fortran statement types and Fortran parsing functions
'''

from fortExp     import *
from l_assembler import *
from fortLine    import flow_line
from mapper      import _Mappable

class _TypeMod(object):
    'modifier for type declaration'

    def __init__(self,e):
        self.mod = e

    def __repr__(self):
        return '%s(%s)' % (self.__class__.__name__,repr(self.mod),)

    def __str__(self):
        return self.pat % str(self.mod)

class _Star(object):
    'Utility modifier type for character data'
    def __init__(self):
        pass
    def __repr__(self):
        return '_Star()'
    def __str__(self):
        return '(*)'

class _F90Len(object):
    'Utility modifier for character data, F90 style'
    def __init__(self,len):
        self.len = len
    def __repr__(self):
        return '_F90Len(%s)' % repr(self.len)
    def __str__(self):
        return '(%s)' % str(self.len)

class _F77Len(object):
    'Utility modifier for character data, F77 style'
    def __init__(self,len):
        self.len = len
    def __repr__(self):
        return '_F77Len(%s)' % repr(self.len)
    def __str__(self):
        return '*%s' % str(self.len)

class _Prec(_TypeMod):
    pat = '*%s'

class _Kind(_TypeMod):
    pat = '(%s)'

class _ExplKind(_TypeMod):
    pat = '(kind = %s)'

prec = seq(lit('*'),Exp)
prec = treat(prec,lambda a:_Prec(a[1]))

kind = seq(lit('('),Exp,lit(')'))
kind = treat(kind,lambda a:_Kind(a[1]))

explKind = seq(lit('('),lit('kind'),lit('='),Exp,lit(')'))
explKind = treat(explKind,lambda a:_ExplKind(a[3]))

starmod  = seq(lit('('),lit('*'),lit(')'))
starmod  = treat(starmod,lambda l: _Star())

lenmod   = disj(Exp,starmod)
f77mod   = seq(lit('*'),lenmod)
f77mod   = treat(f77mod,lambda l: _F77Len(l[1]))

f90mod   = seq(lit('('),disj(lit('*'),Exp),lit(')'))
f90mod   = treat(f90mod,lambda l: _F90Len(l[1]))

id_l     = treat(id,str.lower)
_typeid  = disj(lit('real'),
                lit('integer'),
                lit('logical'),
                lit('complex'),
                lit('doubleprecision'),
                lit('doublecomplex'),
                )

_dblp2   = seq(lit('double'),lit('precision'))
_dblp2   = treat(_dblp2,lambda l:'doubleprecision')

_dblp1   = lit('doubleprecision')

_dblp    = disj(_dblp2,_dblp1)

pstd = seq(_typeid,
         zo1(disj(prec,kind,explKind)),
         )

pchar = seq(lit('character'),
         zo1(disj(f77mod,f90mod)),
         )

type_pat = disj(pchar,pstd)

def typestr(raw):
    (tyid,mod) = raw
    return kwtbl[tyid].kw_str + (mod and str(mod[0]) or '')

class GenStmt(_Mappable):

    def __init__(self,scan):
        self.scan = scan

    def __repr__(self):
        return '%s(args)' % self.__class__.__name__

    @classmethod
    def parse(cls,scan):
        return cls(scan)

class Skip(GenStmt):
    def __init__(self):
        self.scan = []

class Comments(GenStmt):
    def __init__(self,rawline):
        self.rawline = rawline

class NonComment(GenStmt):

    def flow(self):
        lineno = self.lineno
        if lineno:
            init = ' ' + ('%-4d' % lineno) + ' '
        else:
            init = ' ' * 6
        self.rawline = flow_line(init + self.lead + str(self))+'\n'
        return self

    def same_level(self,parsed):
        parsed.lineno  = False
        parsed.lead    = self.lead
        return parsed.flow()

    def indent(self,n):
        self.lead += ' ' * n
        return self.flow()

    def basic_line(self):
        self.lineno = False
        self.lead   = ''
        self.flow()
        return self

    def same(self,targ):
        self.same_level(targ)
        targ.ctxt = self.ctxt
        return targ

class Marker(NonComment):
    def __init__(self):
        pass

class LastDecl(Marker):
    pass

class FirstExec(Marker):
    pass

class Decl(NonComment):
    pass

class TypeDecl(Decl):
    kw = '__unknown__'
    kw_str = kw
    mod = None
    decls = []

class PUstart(Decl):
    pass

class Exec(NonComment):
    pass

class Leaf(Exec):
    "special Exec that doesn't have components"
    def __init__(self,*dc):
        pass

    def __repr__(self):
        return '%s()' % self.__class__.__name__

    def __str__(self):
        return '%s' % self.__class__.kw

class PUend(Leaf):
    pass

class BlockdataStmt(PUstart):
    pass

class CommonStmt(Decl):
    pass

class DataStmt(Decl):
    pass

class ImplicitNone(Decl):
    def __init__(self,*dc):
        pass
    def __repr__(self):
        return 'ImplicitNone()'
    def __str__(self):
        return 'implicit none'

class ImplicitStmt(Decl):
    @staticmethod
    def parse(scan):
        p0 = seq(lit('implicit'),lit('none'))
        p0 = treat(p0,ImplicitNone)

        impelt = seq(type_pat,lit('('),ExpList_l,lit(')'))
        impelt = treat(impelt,lambda l: (l[0],l[2]))

        p1 = seq(lit('implicit'),
                 cslist(impelt))

        p1 = treat(p1,lambda l:ImplicitStmt(l[1]))

        (v,r) = disj(p0,p1)(scan)

        return v

    def __init__(self,lst):
        self.lst = lst

    def __repr__(self):
        return 'ImplicitStmt(%s)' % repr(self.lst)

    def __str__(self):

        def _helper(elt):
            (typ,explst) = elt
            return '%s (%s)' % (typestr(typ),
                                ','.join([str(l).replace(' ','') \
                                          for l in explst]))
            
        return 'implicit %s' % ', '.join([_helper(e) for e in self.lst])

class EquivalenceStmt(Decl):
    pass

class ParameterStmt(Decl):
    pass

class SaveStmt(Decl):
    pass

class StmtFnStmt(Decl):
    def __init__(self,name,args,body):
        self.name = name
        self.args = args
        self.body = body
    def __repr__(self):
        return 'StmtFnStmt(%s,%s,%s)' % (repr(self.name),
                                         repr(self.args),
                                         repr(self.body))
    def __str__(self):
        return '%s(%s) = %s' % (str(self.name),
                                ','.join([str(l) for l in self.args]),
                                str(self.body))

class ExternalStmt(Decl):
    pass

class CharacterStmt(TypeDecl):
    kw = 'character'
    kw_str = kw
    @staticmethod
    def parse(scan):
        starmod  = seq(lit('('),lit('*'),lit(')'))
        starmod  = treat(starmod,lambda l: _Star())

        lenmod   = disj(Exp,starmod)
        f77mod   = seq(lit('*'),lenmod)
        f77mod   = treat(f77mod,lambda l: _F77Len(l[1]))

        f90mod   = seq(lit('('),disj(lit('*'),Exp),lit(')'))
        f90mod   = treat(f90mod,lambda l: _F90Len(l[1]))
                
        p1 = seq(lit('character'),
                 zo1(disj(f77mod,f90mod)),
                 app_id_l)
        ((dc,mod,decls),rest) = p1(scan)

        return CharacterStmt(mod,decls)
    def __init__(self,mod,decls):
        self.mod   = mod
        self.decls = decls

    def __repr__(self):
        return 'CharacterStmt(%s,%s)' % (repr(self.mod),repr(self.decls))

    def __str__(self):
        modstr = ''
        if self.mod:
            modstr = str(self.mod[0])
        
        return 'character%s %s' % (modstr,
                                   ','.join([str(d) for d in self.decls]))

class IntrinsicStmt(Decl):
    pass

class IncludeStmt(Decl):
    pass

class BasicTypeDecl(TypeDecl):
    @classmethod
    def parse(cls,scan):
        prec = seq(lit('*'),Exp)
        prec = treat(prec,lambda a:_Prec(a[1]))

        kind = seq(lit('('),Exp,lit(')'))
        kind = treat(kind,lambda a:_Kind(a[1]))

        explKind = seq(lit('('),lit('kind'),lit('='),Exp,lit(')'))
        explKind = treat(explKind,lambda a:_ExplKind(a[3]))

        p1 = seq(lit(cls.kw),
                 star(disj(prec,kind,explKind)),
                 star(lit('::')),
                 app_id_l)

        ((dc,mod,dc1,decls),rest) = p1(scan)
        return cls(mod,decls)

    def __init__(self,mod,decls):
        self.mod   = mod
        self.decls = decls

    def __repr__(self):
        return '%s(%s,%s)' % (self.__class__.__name__,
                              repr(self.mod),
                              repr(self.decls))
    def __str__(self):
        modtype = self.kw

        if self.mod:
            modtype += str(self.mod[0])

        return '%s %s' %(modtype,
                         ','.join([str(d).replace('()','') \
                                   for d in self.decls]))

class RealStmt(BasicTypeDecl):
    kw = 'real'
    kw_str = kw

class ComplexStmt(BasicTypeDecl):
    kw = 'complex'
    kw_str = kw

class IntegerStmt(BasicTypeDecl):
    kw = 'integer'
    kw_str = kw

class LogicalStmt(BasicTypeDecl):
    kw = 'logical'
    kw_str = kw

class F77Type(TypeDecl):
    '''
    These types do not have kinds or modifiers
    '''
    @classmethod
    def parse(cls,scan):
        p1 = seq(lit(cls.kw),
                 star(lit('::')),
                 app_id_l)

        ((dc,dc1,decls),rest) = p1(scan)
        return cls([],decls)

    def __init__(self,mod,decls):
        'same interface as other type decls, but mod is always empty'
        self.mod   = []
        self.decls = decls

    def __repr__(self):
        return '%s(%s)' % (self.__class__.__name__,
                           repr(self.decls))

    def __str__(self):
        return '%s  %s' % (self.__class__.kw_str,
                           ','.join([str(d) for d in self.decls]))

class DoubleStmt(F77Type):
    kw     = 'doubleprecision'
    kw_str = 'double precision'

class DoubleCplexStmt(F77Type):
    kw     = 'doublecomplex'
    kw_str = 'double complex'

class DimensionStmt(BasicTypeDecl):
    @staticmethod
    def parse(scan):
        p1 = seq(lit('dimension'),
                 cslist(app))
        ((dc,lst),rest) = p1(scan)
        return DimensionStmt(lst)

    def __init__(self,lst):
        self.lst = lst

    def __repr__(self):
        return 'dimension(%s)' % repr(self.lst)

    def __str__(self):
        return 'dimension %s' % ','.join([str(l) for l in self.lst])

class NamelistStmt(Decl):
    pass

class SubroutineStmt(PUstart):
    utype_name = 'subroutine'
    @staticmethod
    def parse(scan):
        p1 = seq(lit('subroutine'),
                 id,
                 zo1(seq(lit('('),cslist(id),lit(')')))
                 )
        ((dc,name,args),rst) = p1(scan)
        if args:
            (dc,args,dc1) = args[0]

        return SubroutineStmt(name,args)

    def __init__(self,name,args):
        self.name = name
        self.args = args

    def __repr__(self):
        return '%s(%s,%s)' % (self.__class__.__name__,
                              repr(self.name),
                              repr(self.args))
    def __str__(self):
        return 'subroutine %s(%s)' % (self.name,
                                      ','.join([str(d) for d in self.args]))

class ProgramStmt(PUstart):
    utype_name = 'program'

    @staticmethod
    def parse(scan):
        p1 = seq(lit('program'),
                 id)
        ((dc,name),rest) = p1(scan)
        return ProgramStmt(name)

    def __init__(self,name):
        self.name = name

    def __repr__(self):
        return '%s(%s,%s)' % (self.__class__.__name__,
                              repr(self.name))
    def __str__(self):
        return 'program %s' % self.name

class FunctionStmt(PUstart):
    utype_name = 'function'

    @staticmethod
    def parse(scan):
        p1 = seq(zo1(type_pat),
                 lit('function'),
                 id,
                 lit('('),cslist(id),lit(')'),
             )

        ((ty,dc,name,dc1,args,dc2),rest) = p1(scan)
        return FunctionStmt(ty,name,args)

    def __init__(self,ty,name,args):
        self.ty   = ty
        self.name = name
        self.args = args

    def __repr__(self):
        return 'FunctionStmt(%s,%s,%s)' % (repr(self.name),
                                           repr(self.ty),
                                           repr(self.args))
    def __str__(self):
        ty = self.ty
        typeprefix = ty and (typestr(ty[0])+' ') or ''
        return '%sfunction %s(%s)' % (typeprefix,
                                      str(self.name),
                                      ','.join([str(l) for l in self.args]))

class ModuleStmt(PUstart):
    utype_name = 'module'
    @staticmethod
    def parse(scan):
        p1 = seq(lit('module'),
                 id)
        ((dc,name),rest) = p1(scan)
        return ModuleStmt(name)

    def __init__(self,name):
        self.name = name

    def __repr__(self):
        return '%s(%s)' % (self.__class__.__name__,
                              repr(self.name))
    def __str__(self):
        return 'module %s' % self.name

    pass

class UseStmt(Decl):
    @staticmethod
    def parse(scan):
        p1 = seq(lit('use'),id)
        ((dc,name),rest) = p1(scan)

        return UseStmt(name)

    def __init__(self,name):
        self.name = name

    def __repr__(self):
        return 'UseStmt(%s)' % repr(self.name)

    def __str__(self):
        return 'use %s' % str(self.name)

class FormatStmt(Decl):
    pass

class EntryStmt(Decl):
    pass

class CallStmt(Exec):
    @staticmethod
    def parse(scan):
        prefix = seq(lit('call'),disj(app,id))
        ((dc,a),rst) = prefix(scan)
        if (isinstance(a,App)):
            return CallStmt(a.head,a.args)
        else:
            return CallStmt(a,[])

    def __init__(self,head,args):
        self.head = head
        self.args = args

    def __repr__(self):
        return 'CallStmt(%s,%s)' % (repr(self.head),
                                    repr(self.args),)

    def __str__(self):
        return 'call %s(%s)' % (str(self.head),
                                ','.join([str(l) for l in self.args]))

class AssignStmt(Exec):

    @staticmethod
    def parse(scan):
        lhs     = disj(app,id)
        assign  = seq(lhs,lit('='),Exp)
        ((l,dc,r),rst) = assign(scan)
        return AssignStmt(l,r)

    def __init__(self,lhs,rhs):
        self.lhs = lhs
        self.rhs = rhs

    def __repr__(self):
        return 'AssignStmt(%s,%s)' % (repr(self.lhs),repr(self.rhs))

    def __str__(self):
        return '%s = %s' % (str(self.lhs),str(self.rhs))

class OpenStmt(Exec):
    pass

class CloseStmt(Exec):
    pass

class ReadStmt(Exec):
    pass

class WriteStmt(Exec):
    pass

class PrintStmt(Exec):
    pass

class StopStmt(Exec):
    pass

class ReturnStmt(Leaf):
    kw = 'return'

class IfStmt(Exec):
    @staticmethod
    def parse(scan):
        prefix = seq(lit('if'),lit('('),Exp,lit(')'))
        ((dc,dc1,e,dc2),rest) = prefix(scan)
        if [l.lower() for l in rest] == ['then']:
            return IfThenStmt(e)
        else:
            return IfNonThenStmt(e,_kw_parse(rest))

class IfThenStmt(IfStmt):

    def __init__(self,e):
        self.test = e

    def __repr__(self):
        return 'IfThenStmt(%s)' % (repr(self.test),)

    def __str__(self):
        return 'if ( %s ) then' % (str(self.test),)

class IfNonThenStmt(IfStmt):

    def __init__(self,e,stmt):
        self.test = e
        self.stmt = stmt

    def __repr__(self):
        return 'IfNonThenStmt(%s,%s)' % (repr(self.test),
                                         repr(self.stmt))

    def __str__(self):
        return 'if ( %s ) %s' % (str(self.test),str(self.stmt))

class ElseifStmt(Exec):

    @staticmethod
    def parse(scan):
        prefix = seq(lit('elseif'),lit('('),Exp,lit(')'),lit('then'))

        ((dc0,dc1,e,dc2,dc3),rest) = prefix(scan)
        return ElseifStmt(e)

    def __init__(self,e):
        self.test = e

    def __repr__(self):
        return 'ElseifStmt(%s)' % (repr(self.test),)

    def __str__(self):
        return 'elseif (%s) then' % (repr(self.test),)
    
class ElseStmt(Leaf):
    kw = 'else'

class EndStmt(PUend):
    kw =  'end'

class EndifStmt(Leaf):
    kw = 'endif'

class DoStmt(Exec):
    pass

class EnddoStmt(Leaf):
    kw = 'enddo'

class ContinueStmt(Leaf):
    kw = 'continue'

class SelectStmt(Exec):
    pass

class WhileStmt(Exec):
    pass

class GotoStmt(Exec):
    pass

kwtbl = dict(blockdata       = BlockdataStmt,
             common          = CommonStmt,
             logical         = LogicalStmt,
             data            = DataStmt,
             doubleprecision = DoubleStmt,
             doublecomplex   = DoubleCplexStmt,
             implicit        = ImplicitStmt,
             equivalence     = EquivalenceStmt,
             parameter       = ParameterStmt,
             save            = SaveStmt,
             goto            = GotoStmt,
             external        = ExternalStmt,
             character       = CharacterStmt,
             intrinsic       = IntrinsicStmt,
             include         = IncludeStmt,
             real            = RealStmt,
             integer         = IntegerStmt,
             dimension       = DimensionStmt,
             complex         = ComplexStmt,
             subroutine      = SubroutineStmt,
             program         = ProgramStmt,
             function        = FunctionStmt,
             module          = ModuleStmt,
             use             = UseStmt,
             format          = FormatStmt,
             entry           = EntryStmt,
             call            = CallStmt,
             open            = OpenStmt,
             close           = CloseStmt,
             read            = ReadStmt,
             write           = WriteStmt,
             stop            = StopStmt,
             elseif          = ElseifStmt,
             endif           = EndifStmt,
             end             = EndStmt,
             endmodule       = EndStmt,
             endprogram      = EndStmt,
             endfunction     = EndStmt,
             endsubroutine   = EndStmt,
             endblockdata    = EndStmt,
             do              = DoStmt,
             enddo           = EnddoStmt,
             select          = SelectStmt,
             dowhile         = WhileStmt,
             )

for kw in ('if','continue','return','else','print'):
    kwtbl[kw] = globals()[kw.capitalize() + 'Stmt']
    
lhs    = disj(app,id)
assign = seq(lhs,lit('='),Exp)

def mkassign(a):
    'make an assignment statement object from a recognized scan'
    (lhs,dc,rhs) = a
    return AssignStmt(lhs,rhs)

import kw_multi

def sqz(n,mutable):
    'return the squeezed kw, and as a side effect, change the scan'

    rv = ''.join([l.lower() for l in mutable[0][0:n]])
    mutable[0][0:n] = [rv]
    return rv

_types = ('real',
          'integer',
          'logical',
          'complex',
          'character',
          'doubleprecision',
          'doublecomplex',
          )
def parse(scan):
    try:
        return AssignStmt.parse(scan)

    except AssemblerException:
        lscan = tuple([ l.lower() for l in scan ])
        kw3g  = kw_multi.kw3.get
        kw2g  = kw_multi.kw2.get
#        print 'testing stmt ','|'.join(scan)
        kw = len(scan) >=3 and kw3g(lscan[0:3]) and sqz(3,[scan]) or \
             len(scan) >=2 and kw2g(lscan[0:2]) and sqz(2,[scan]) or \
             lscan[0]
        if kw in _types and 'function' in lscan:
            kw = 'function'
#        print 'scan =',scan,'==> kw =',kw

        cls = kwtbl.get(kw) or GenStmt
        return cls.parse(scan)
#
# alias so that stmts like if, etc can call the above routine
#
_kw_parse = parse

#
# Type helper routines
#

def kw2type(s): return(kwtbl[s.lower()])
def lenfn(n): return [_F77Len(str(n))]
def poly(s):
    return s.lower() in ('max',
                         'min',
                         )
def typecompare(t1,t2):
    mergeit = dict(character=0,
                   logical=1,
                   integer=2,
                   real=3,
                   complex=4,
                   doubleprecision=5,
                   doublecomplex=6,
                   )

    if t1[0] == t2[0]:
        return(t1[0],max(t1[1],t2[1]))

    if mergeit[t1[0].kw] > mergeit[t2[0].kw]: return t1

    return t2

def typemerge(lst,default):
    if not lst: return default
    if len(lst) == 1: return lst[0]
    t1 = typecompare(lst[0],lst[1])
    for l in lst[2:]:
        t1 = typecompare(t1,l)
    return t1

'''
Spikes

from fortScan import scan1
def scan(s):
    return scan1.scan(s)[0]

def p(s):
    return parse(scan(s))

ipl0  = 'implicit integer (e-f,k,l), real*4 (a-d,o-q,r)'
ipl1  = 'implicit none'
ipl2  = 'implicit complex (a,b,c,e-g)'


dm0   = 'dimension x(10)'
dm1   = 'dimension x(10),y(1,a:b,6 * STDLEN)'

ff0   = 'function foob(x,y,z)'
ff1   = 'real(kind=kind(1.0D0)) function ff(zy,zzy)'
ff2   = 'double complex function foo(xx,yy,zz,ww)'
ff3   = 'character*(ss+yy) function hhjhj(xx,yy)'


c0    = 'character x(10),y(1:2)'
c1    = 'Character*(AA*BB) zzz,bbb'
c2    = 'CHARACTER*(*) s,t,u'
c3    = 'CHARACTER(1)  x,y,zzz'
c4    = 'CHARACTER(*)  x,y,zzz'

i0    = 'integer*4 x(10),y,z(FOO*BAR,ikkk+3)'
i1    = 'integer(w2fkind_1) xxx,yyy,zzz(-4:10)'
i2    = 'INTEGER(KIND = ikkyk+4) lololo,hihi(ISZ,JSZ)'
i3    = 'INTEGER :: x(10),y(11),z'

r0    = 'real*4 x(10),y,z(FOO*BAR,ikkk+3)'
r1    = 'real(w2fkind_1) xxx,yyy,zzz(-4:10)'
r2    = 'REAL(KIND = ikkyk+4) lololo,hihi(ISZ,JSZ)'
r3    = 'REAL :: x(10),y(11),z'

s10   = 'real  x(10),y,z'
s11   = 'foo(5,7) = x.lt.y'
s12   = 'if (x(11).EQ.y.OR.x(12).lt.(floob*(i**k))) goto 10'
s13   = 'end if'
s13_1 = 'endif'
s14   = 'subroutine foo(x,y,z)'
'''
