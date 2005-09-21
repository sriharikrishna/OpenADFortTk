'''
Module for creating partially processed Fortran files that have
a token list, line number representation as well as a rawline
'''
from chomp import chomp
import sre
_lineno_re = sre.compile(r'(\d+)')
_lead_re   = sre.compile(r'(\s*)')

def _ident(self):
    return [self]

class _fortScanLine(object):
    'base class for scanned lines'

    map = _ident

    def __str__(self):
        return chomp(self.rawline)
    def __repr__(self):
        return '%s(%s)' % (self.__class__.__name__,repr(str(self)))

class fortScanComment(_fortScanLine):
    'scanned comments == comments'

    def __init__(self,cline):

        self.rawline = cline.rawline
        self.rm      = ''

class fortScanLine(_fortScanLine):
    'non comment fortran lines'

    def __init__(self,fline):

        from fortScan import scan1

        self.rawline         = fline.rawline
        line                 = fline.line
        m                    = _lineno_re.search(line[:6])
        self.lineno          = m and int(m.group(1))
        self.lead            = _lead_re.match(line[6:]).group(1)
        (self.scan,self.rm)  = scan1.scan(line[6:])

    def __repr__(self):
        return '%s(%s)' % ('fortScanLine',self.scan)

class fortScanFile(object):
    'scan File object should have a generator for scanned lines'

    def __init__(self,fname):
        from fortFile import Ffile
        import fortLine as fl

        lexi = ((fl.cline,lambda l: [fortScanComment(l)]),
                (fl.fline,lambda l: [fortScanLine(l)]))

        self.scanlines = Ffile.file(fname).map(lexi)

    def map(self,lexi):
        for (cls,meth) in lexi:
            cls.map = meth
        for l in self.scanlines:
            for v in l.map():
                yield v
        for (cls,meth) in lexi:
            cls.map = _ident

class T(object):

    def test1(self):

        global p1

        p1 = fortScanFile('__tmp.f')

