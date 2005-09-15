'''
Duplicate (most of) the functionality of perl Ffile.pm

In other words, read in a Fortran file, assembling the
line objects.
Provide mappers, rewriters, string conversion facilities
'''
from cStringIO import StringIO
from fortLine  import a_line
from assembler import vgen

class Ffile(object):
    def __init__(self,fobj):
        self.lines = list(vgen(a_line,fobj))
        fobj.close()

    @staticmethod
    def file(name):
        return Ffile(open(name))

    @staticmethod
    def here(str):
        return Ffile(StringIO(str))

    def str(self):
        return ''.join([l.rawline for l in self.lines])

def setup():
    global p1

    p1 = '''
      subroutine foo(x)
      x = x +
c
c embedded continuation lines
c
     &5 + 2 * x
c
c more embedded lines
c
     & + si
     &n(x+2.0)
      x = 5.0
      x
     & = 
     & 13.2
      end
'''
    p1 = p1[1:]
