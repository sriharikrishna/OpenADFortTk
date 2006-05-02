from Setup     import *
from unittest  import *

from fortStmts import *

def scan(s):
    from fortScan import scan1

    return scan1.scan(s)[0]

class C1(TestCase):
    '''Test that appropriate instances are created for
    some simple statements
    '''

    def test1(self):
        'simple real stmt'
        ae = self.assertEquals
        a_ = self.assert_

        s  = 'real  x(10),y,z'
        a_(isinstance(parse(scan(s)),RealStmt))

    def test2(self):
        'simple if stmt'
        ae = self.assertEquals
        a_ = self.assert_

        s  = 'if (x(11).EQ.y.OR.x(12).lt.(floob*(i**k))) goto 10'
        a_(isinstance(parse(scan(s)),IfStmt))

    def test3(self):
        'endif stmt as "end if"'
        ae = self.assertEquals
        a_ = self.assert_

        s  = 'end if'
        a_(isinstance(parse(scan(s)),EndifStmt))

    def test4(self):
        'endif stmt as "endif"'
        ae = self.assertEquals
        a_ = self.assert_

        s  = 'endif'
        a_(isinstance(parse(scan(s)),EndifStmt))

    def test5(self):
        'simple subroutine stmt'
        ae = self.assertEquals
        a_ = self.assert_

        s  = 'subroutine foo(x,y,z)'
        a_(isinstance(parse(scan(s)),SubroutineStmt))

class C2(TestCase):
    '''assignment statement'''

    def test1(self):
        'simple assignment statement'

        ae = self.assertEquals
        a_ = self.assert_

        s  = 'foo(5,7) = x.lt.y'
        v = parse(scan(s))
        ae(repr(v),
           repr(AssignStmt(App('foo',['5','7']),Ops('.lt.','x','y')))
           )

    def test2(self):
        'assignment w kw "if" as var'
        ae = self.assertEquals
        a_ = self.assert_

        s  = 'if(ix,iy) = sin(x)'
        v = parse(scan(s))
        ae(repr(v),
           repr(AssignStmt(App('if',['ix','iy']),App('sin',['x'])))
           )

class C3(TestCase):
    '''derived type declarations'''

    def test1(self):
        'simple derived type declarations'

        ae = self.assertEquals
        a_ = self.assert_

        s = 'TYPE (OpenADTy_active) OpenAD_Symbol_3865'
        v = parse(scan(s))
        ae(repr(v),
           repr(DerivedTypeDecl('OpenADTy_active',['OpenAD_Symbol_3865'])))

    def test2(self):
        'simple derived type declarations with ::'

        ae = self.assertEquals
        a_ = self.assert_

        s = 'TYPE (OpenADTy_active) :: OpenAD_Symbol_3865'
        v = parse(scan(s))
        ae(repr(v),
           repr(DerivedTypeDecl('OpenADTy_active',['OpenAD_Symbol_3865'])))

    def test3(self):
        'simple derived type declarations with multiple vars'

        ae = self.assertEquals
        a_ = self.assert_

        s = 'TYPE (OpenADTy_active) :: OpenAD_Symbol_3865,vv(12),zz(is,ist)'
        v = parse(scan(s))
        ae(repr(v),
           repr(DerivedTypeDecl('OpenADTy_active',['OpenAD_Symbol_3865',
                                                   App('vv',['12']),
                                                   App('zz',['is', 'ist'])])))

class C4(TestCase):
    '''Test Jean's allocatable'''

    def test1(self):
        '''allocatable Stmt works'''

        ae = self.assertEquals
        a_ = self.assert_

        s = 'allocatable foo,bar,baz'
        ss = scan(s)
        v = parse(ss)
        ae(repr(v),
           repr(AllocatableStmt('args')))
        
s1    = makeSuite(C4)
suite = asuite(C1,C2,C3,C4)

if __name__ == '__main__':
    runit(suite)
