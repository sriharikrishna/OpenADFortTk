from Setup     import *
from unittest  import *

from fortStmts import *
from useparse  import *

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
    def test3(self):
        "selection(%) operator works on lhs"
        ae = self.assertEquals
        a_ = self.assert_

        s  = 'x%v = 5'
        v  = parse(scan(s))
        ae(repr(v),
           repr(AssignStmt(Sel('x','v'),'5')))
    def test4(self):
        "complicated exp including selection(%) works on lhs"
        ae = self.assertEquals
        a_ = self.assert_

        s  = 'x%v(1,2)%q(xx)%r = 5'
        v  = parse(scan(s))
        ae(repr(v),
           repr(AssignStmt(Sel(App(Sel(App(Sel('x','v'),['1', '2']),'q'),
                                   ['xx']),'r'),'5')))

class C3(TestCase):
    def test1(self):
        'create comment block'
        ae = self.assertEquals
        a_ = self.assert_
        c1 = comment_bl('This','is','a','comment')
        c2 = Comments('\n'.join(['c This','c is','c a','c comment'])+'\n')
        ae(c1.viz(),c2.viz())

class C4(TestCase):
    def test1(self):
        'assignment statement classes have have "_sons" attribute'
        ae = self.assertEquals
        a_ = self.assert_

        s  = 'if(ix,iy) = sin(x)'
        v = parse(scan(s))
        a_(hasattr(v,'_sons'))
        ae(v._sons,['lhs','rhs'])

    def test2(self):
        'if statement classes have have "_sons" attribute'
        ae = self.assertEquals
        a_ = self.assert_

        s  = 'if (x .eq. 5) goto 23'
        v = parse(scan(s))
        a_(hasattr(v,'_sons'))

class C5(TestCase):
    '''Test derived type
    '''
    def test1(self):
        'simple derived type declaration'
        ae = self.assertEquals
        a_ = self.assert_
        s = 'type(foo) :: x(10),y(len(kk),3),z,w'
        ps = pps(s)
        a_(isinstance(ps,DrvdTypeDecl))
        a_(not ps.attrs)
        ae(len(ps.decls),4)

    def test2(self):
        'simple derived type definition'
        ae = self.assertEquals
        a_ = self.assert_
        s = 'type bar'
        ps = pps(s)
        a_(isinstance(ps,DrvdTypeDefn))
        ae(ps.name,'bar')

    def test3(self):
        'derived type declaration with attributes'
        ae = self.assertEquals
        a_ = self.assert_
        s = 'type(foo),dimension(10),target :: x,y,z(30)'
        ps = pps(s)
        a_(isinstance(ps,DrvdTypeDecl),'instance check')
        ae(len(ps.attrs),2,'attr check')
        ae(len(ps.decls),3,'decls check')

    def test4(self):
        'empty interface definition'
        ae = self.assertEquals
        a_ = self.assert_
        s = 'interface'
        ps = pps(s)
        a_(isinstance(ps,InterfaceStmt),'instance check')
        ae(str(ps),s)

    def test5(self):
        'nonempty interface definition'
        ae = self.assertEquals
        a_ = self.assert_
        s = 'interface foo'
        ps = pps(s)
        a_(isinstance(ps,InterfaceStmt),'instance check')
        ae(str(ps),s)

s    = makeSuite(C5)
suite = asuite(C1,C2,C3,C4,C5)

if __name__ == '__main__':
    runit(suite)