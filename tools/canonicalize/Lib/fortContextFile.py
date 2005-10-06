'''
Turn a parsed line into a context line
'''

import fortParseFile as fpf
import fortStmts     as fs

def _ident(self,*args,**kw):
    return [self]

class Struct(object):
    '''
    Structural object: a dynamic scratchpad for adding
    whatever state is needed
    '''
    def __init__(self):
        pass

class SymEntry(object):
    def __init__(self):
        self.type = fs.RealStmt
        self.mod  = []
        self.dims = []
        self.lngth  = None

default_sym = SymEntry()

class Context(object):
    'Line context structure'

    def __init__(self,toplev):
        self.toplev  = toplev
        self.uname   = '__dummy__'
        self.utype   = None
        self.vars    = dict()
        self._getnew = False

    def lookup_var(self,v):
        return default_sym

def nextunit(line,ctxt):
    ctxt[0]._getnew = True
    return [line]

def newunit(line,ctxt):
    ctxt[0].utype = line.__class__.utype_name
    ctxt[0].uname = line.name
    return [line]

ctxt_lexi = [(fs.PUend,nextunit),
             (fs.PUstart,newunit),
             ]
class fortContext(object):
    'create a list of contextLine objects'

    def __init__(self,line_iter):
        self.lines = []
        for l in line_iter:
            self.lines.append(l)

        '''
        toplev       = Struct()
        toplev.units = dict()

        ctxt         = Context(toplev)

        ctxt_mutable = [ctxt]
        self.lines = []
        for l in parse_iter.map(ctxt_lexi,ctxt_mutable):
            l.ctxt = ctxt_mutable[0]
            self.lines.append(l)
            if l.ctxt._getnew:
                _new = Context(toplev)
                ctxt_mutable[0] = _new
        '''

    def map(self,lexi,*args,**kws):
        for (cls,meth) in lexi:
            cls.map = meth
        for l in self.lines:
            for v in l.map(*args,**kws):
                yield v
        for (cls,meth) in lexi:
            cls.map = _ident

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

def _add_context(parse_iter):
    toplev       = Struct()
    toplev.units = dict()

    ctxt         = Context(toplev)

    ctxt_mutable = [ctxt]

    for l in parse_iter.map(ctxt_lexi,ctxt_mutable):
        l.ctxt = ctxt_mutable[0]
        yield l
        if l.ctxt._getnew:
            _new = Context(toplev)
            ctxt_mutable[0] = _new

def fortContextFile(fname):
    'from a file name create a fortContext object'

    return fortContext(_add_context(fpf.fortParseFileIter(fname)))

'''
Spikes

def fname_t(s): return s

def show(l):
    print 'testit COUNT =',l.ctxt.lcount
    return []

fc1 = fortContextFile(fname_t('fc1.f'))

lexi_show = [(fs.GenStmt,show)]
'''

'''
def gen_con(line,ctxt):
    ctxt[0].lcount += 1
    return [line]

def unit(line,ctxt):
    ctxt[0].lcount += 1
    _new = Context()
    _new.lcount = 0
#    print '-->changing ctxt to ',_new
    ctxt[0] = _new
    
    return [line]

for i in fc1.map(lexi_show): pass
'''
