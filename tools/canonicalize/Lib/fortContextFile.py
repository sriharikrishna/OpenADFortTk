'''
Turn a parsed line into a context line
'''

import fortParseFile as fpf
import fortStmts     as fs
import fortExp       as fe
import mapper
from   mapper    import _Map

'''
def _ident(self,*args,**kw):
    return [self]
'''

class Struct(object):
    '''
    Structural object: a dynamic scratchpad for adding
    whatever state is needed
    '''
    def __init__(self):
        pass

_sym_init = dict(typeof=None,
                 mod=(),
                 dims=(),
                 vclass='local',
                 lngth=None,
                 kw_str='????')

class SymEntry(object):
    def __init__(self,**kw):
        self.__dict__.update(_sym_init)
        self.__dict__.update(kw)

default_sym = SymEntry(typeof=None,
                       kw_str='????',
                       dims=(),
                       mod=None,
                       vclass=None,
                       lngth=None
                       )

class Context(object):
    'Line context structure'

    def __init__(self,toplev,hook=mapper.noop):
        self.toplev   = toplev
        self.uname    = '__dummy__'
        self.utype    = None
        self.vars     = dict()
        self._getnew  = False
        self.implicit = dict()
        hook(self)

    def lookup_var(self,v):
        if v in self.vars:
            return self.vars[v]
        return default_sym

#    def typeof(self,v):
#        if v in self.vars:
 
def nextunit(line,ctxtm):
    ctxt = ctxtm[0]
    ctxt._getnew = True
    if ctxt.utype == 'module':
        ctxt.toplev.modules[ctxt.uname] = ctxt
    return line

def newunit(line,ctxtm):
    ctxt = ctxtm[0]
    ctxt.utype = line.__class__.utype_name
    ctxt.uname = line.name
    ctxt.retntype = None
    return line

def fnunit(line,ctxtm):
    ctxt = ctxtm[0]
    ctxt.utype = 'function'
    ctxt.uname = line.name
    ctxt.retntype = line.ty
    return line

def typesep(d):
    '''return name and dimensions for a given decl entry
    a type declaration will either be a simple var (string)
    or an App expression
    '''
    return isinstance(d,str) and (d,()) or (d.head,tuple(d.args))

def typedecl(line,ctxtm):
    ctxt = ctxtm[0]

    typeof  = line.__class__
    kw_str  = line.kw_str
    mod     = line.mod
    lngth   = kw_str == 'character' and (mod and mod[0] or 1)
    for d in line.decls:
        (name,dims)     = typesep(d)
        if name in ctxt.vars:
            ctxt.vars[name].typeof = typeof
            ctxt.vars[name].mod    = mod
        else:
            ctxt.vars[name] = SymEntry(typeof=typeof,
                                       kw_str=kw_str,
                                       mod=mod,
                                       dims=dims,
                                       vclass='local',
                                       lngth=lngth)
    return line

def dimen(line,ctxtm):
    ctxt = ctxtm[0]

    for d in line.decls:
        (name,dims) = (d.head,d.args)
        if name in ctxt.vars:
            ctxt.vars[name].dims = dims
        else:
            (typeof,kw_str,mod) = ctxt.typeof(name)
            ctxt.vars[name] = SymEntry(typeof,kw_str,mod,dims)

    return line

def assgn(line,ctxtm):
    ctxt = ctxtm[0]
    lhs  = line.lhs
    look = ctxt.lookup_var
    if isinstance(lhs,fe.App) and not look(lhs.head).dims:
        ret = fs.StmtFnStmt(lhs.head,lhs.args,line.rhs)
        ret.rawline = line.rawline
        ret.lineno  = line.lineno
        ret.lead    = line.lead
        return ret

    return line

def use_module(line,ctxtm):
    from warnings import warn
    
    ctxt    = ctxtm[0]
    modules = ctxt.toplev.modules
    mod     = line.name
    if mod not in modules:
        warn('module %s not seen' % mod)
        return line

    modvars = modules[mod].vars
    ctxt.vars.update(modvars)
    vcstr = 'module:'+mod
    for v in modvars:
        ctxt.vars[v].vclass = vcstr
    
    return line

ctxt_lexi = [(fs.PUend,         nextunit),
             (fs.PUstart,       newunit),
             (fs.FunctionStmt,  fnunit),
             (fs.TypeDecl,      typedecl),
             (fs.DimensionStmt, dimen),
             (fs.AssignStmt,    assgn),
             (fs.UseStmt,       use_module),
             ]

class fortContext(_Map):
    '''create a list of contextLine objects:
    At the moment, this is just a list of parsed lines
    with an additional attribute called 'ctxt' has
    been added to the parseLine object
    '''

    def __init__(self,line_iter):
        'initialize by adding the lines, 1 at a time via iterator'
        self.lines = []
        for l in line_iter:
            self.lines.append(l)

    def rewrite(self,lexi,*args,**kws):
        return fortContext(self.map(lexi,*args,**kws))

    def printit(self,out=None):
        for l in self.lines:
            if out:
                print >> out,l.rawline,
            else:
                print l.rawline,

    def write(self,fname):
        ff = open(fname,'w')
        self.printit(ff)
        ff.close()


def _gen_context(parse_iter,hook=mapper.noop):
    '''
    The workhorse routine:
      from a list of un contexted but parsed lines, process each line,
      creating or modifying the context object according to
      the supplied lexi
    '''
    toplev         = Struct()
    toplev.units   = dict()
    toplev.modules = dict()

    ctxt         = Context(toplev,hook)

    ctxt_mutable = [ctxt]

    for l in parse_iter.map1(ctxt_lexi,ctxt_mutable):
        l.ctxt = ctxt_mutable[0]
        yield l
        if l.ctxt._getnew:
            _new = Context(toplev,hook)
            del l.ctxt._getnew
            ctxt_mutable[0] = _new

def fortContextFile(fname,hook=mapper.noop):
    'from a file name create a fortContext object'

    return fortContext(_gen_context(fpf.fortParseFileIter(fname),hook))

'''
Spikes

def fname_t(s): return s

def show(l):
    print 'testit %s %s COUNT = %d' % (l.ctxt.utype,
                                       l.ctxt.uname,
                                       l.ctxt.lcount)

def init_cnt(self):
    self.lcount = 0
    return self

def bump_cnt(l):
    l.ctxt.lcount += 1

lexi_show = [(fs.GenStmt,show)]

lexi_cnt  = [(fs.GenStmt,bump_cnt)]

def t():
    global fc1
    fc1 = fortContextFile(fname_t('fc1.f'))

#    for dc in fc1.mapc(lexi_cnt,init_cnt):pass

#    for dc in fc1.mapc(lexi_show): pass

'''
