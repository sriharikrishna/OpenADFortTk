'''
Turn a scanned line into a parsed line
'''
import fortScanFile as fsf
import fortStmts    as fs

def _ident(self,*args,**kws):
    return [self]

class _fortParseLine(object):
    'base class for parsed lines'

    parse =  fs.Skip()

    def __str__(self):
        return chomp(self.rawline)
    def __repr__(self):
        return '%s(%s)' % (self.__class__.__name__,repr(str(self)))

def fortParseComment(scanline):
    'parsed comments = scanned comments'

    return fs.Comments(scanline.rawline)

def fortParseLine(scanline):

    line         = fs.parse(scanline.scan)

    line.rawline = scanline.rawline
    line.lineno  = scanline.lineno
    line.lead    = scanline.lead
    line.rm      = scanline.rm

    return line

class _fortParse(object):
    'base class for fortParseIterator and fortParse'

    def map(self,lexi,*args,**kws):
        for (cls,meth) in lexi:
            cls.map = meth
        for l in self.lines:
            for v in l.map(*args,**kws):
                yield v
        for (cls,meth) in lexi:
            cls.map = _ident

class fortParseIter(_fortParse):
    'return an iterator for parseLine objects'

    def __init__(self,scan_iter):
        lexi = ((fsf.fortScanComment,lambda l: [fortParseComment(l)]),
                (fsf.fortScanLine,   lambda l: [fortParseLine(l)]))

        self.lines = scan_iter.map(lexi)

class fortParse(_fortParse):
    'create a list of parseLine objects'

    def __init__(self,scan_iter):
        self.lines = list(fortParseIter(scan_iter).lines)
        
def fortParseFile(fname):
    'from a file name create a fortParse object'

    return fortParse(fsf.fortScanFile(fname))

def fortParseFileIter(fname):
    'return an iterator for the parseLine objects'
    return fortParseIter(fsf.fortScanFile(fname))

