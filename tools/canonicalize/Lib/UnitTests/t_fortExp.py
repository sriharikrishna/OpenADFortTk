from Setup    import *
from unittest import *

from fortScan import scan1
from fortExp  import *

def scan(s):
    (v,rst) = scan1.scan(s)
    return v

class C1(TestCase):
    def test1(self):
        'simple function app'

        ae = self.assertEquals
        a_ = self.assert_

        l1  = scan('f(x)')
        (e1,dc)  = Exp(l1)
        ae(repr(e1),repr(App('f',['x'])))

    def test2(self):
        'function app with embedded function app'

        ae = self.assertEquals
        a_ = self.assert_
        l1  = scan('h(x,zzz(a,bbb),c)')
        (e1,dc)  = Exp(l1)
        ae(repr(e1),repr(App('h',['x',App('zzz',['a','bbb']),'c'])))

    def test3(self):
        'simple constant'

        ae = self.assertEquals
        a_ = self.assert_
        l1  = scan('3.')
        (e1,dc)  = Exp(l1)
        ae(e1,'3.')

    def test4(self):
        'simple variable'

        ae = self.assertEquals
        a_ = self.assert_
        l1  = scan('x')
        (e1,dc)  = Exp(l1)
        ae(e1,'x')

    def test5(self):
        'simple no arg app'

        ae = self.assertEquals
        a_ = self.assert_
        l1  = scan('hfffhfhg_kk()')
        (e1,dc)  = Exp(l1)
        ae(repr(e1),repr(App('hfffhfhg_kk',[])))

    def test6(self):
        'embedded apps, string constants, and no arg apps'

        ae = self.assertEquals
        a_ = self.assert_
        l1  = scan('g(hh(x0,x1),"Str",kk(1,xx("aa")),3,f())')
        (e1,dc)  = Exp(l1)
        ae(repr(e1),
           repr(App('g',[App('hh',['x0', 'x1']),
                         '"Str"',
                         App('kk',['1',App('xx',['"aa"'])]),
                         '3',
                         App('f',[])]))
           )

    def test7(self):
        "embedded app leaves extra ')' at end"

        ae = self.assertEquals
        a_ = self.assert_
        l1  = scan('h(x,zzz(a,bbb),c))')
        (e1,dc)  = Exp(l1)
        ae(repr(e1),
           repr(App('h',['x',App('zzz',['a', 'bbb']), 'c']))
           )
        ae(dc,[')'])

    def test8(self):
        'simple unary minus inside app'

        ae = self.assertEquals
        a_ = self.assert_
        l1  = scan('h(-x,zzz)')
        (e1,dc)  = Exp(l1)
        ae(repr(e1),
           repr(App('h',[Umi('x'), 'zzz']))
           )

    def test9(self):
        'app w embedded parenthesized expressions'

        ae = self.assertEquals
        a_ = self.assert_
        l1  = scan('hhh((kkk),(h3(x,y)))')
        (e1,dc)  = Exp(l1)
        ae(repr(e1),
           repr(App('hhh',[ParenExp('kkk'),
                           ParenExp(App('h3',['x', 'y']))]))
           )

    def test10(self):
        'simple unary minus of a fp constant'

        ae = self.assertEquals
        a_ = self.assert_
        l1  = scan('-3.14')
        (e1,dc)  = Exp(l1)
        ae(repr(e1),
           repr(Umi('3.14'))
           )

    def test11(self):
        'nested paren expressions, unary minus'

        ae = self.assertEquals
        a_ = self.assert_
        l1  = scan('-(h6(xxx,-y,(-2.2)))')
        (e1,dc)  = Exp(l1)
        ae(repr(e1),
           repr(Umi(ParenExp(App('h6',['xxx',Umi('y'),
                                        ParenExp(Umi('2.2'))]))))
           )

    def test12(self):
        'constant w trailing - & paren'

        ae = self.assertEquals
        a_ = self.assert_
        l1  = scan('12.3-)')
        (e1,dc)  = Exp(l1)
        ae(e1,'12.3')
        ae(dc,['-',')'])

    def test13(self):
        'app w logical constant'

        ae = self.assertEquals
        a_ = self.assert_
        l1  = scan('f((.TRUE.),-5.2E22_w2f)')
        (e1,dc)  = Exp(l1)
        ae(repr(e1),
           repr(App('f',[ParenExp('.true.'),Umi('5.2E22_w2f')]))
           )

    def test14(self):
        'simple arithmetic ops'

        ae = self.assertEquals
        a_ = self.assert_
        l1  = scan('h(x,y,z)-kkk')
        (e1,dc)  = Exp(l1)
        ae(repr(e1),
           repr(Ops('-',App('h',['x', 'y', 'z']), 'kkk'))
           )

    def test15(self):
        'embedded arith ops as args to app'

        ae = self.assertEquals
        a_ = self.assert_
        l1  = scan('h(x*y,y:y+1,-zzz) * -hgh(2.1)')
        (e1,dc)  = Exp(l1)
        ae(repr(e1),
           repr(Ops('*',
                    App('h',[Ops('*','x','y'),
                             Ops(':','y',Ops('+','y','1')),
                             Umi('zzz')]),
                    Umi(App('hgh',['2.1']))))
           )

    def test16(self):
        'unary .not. handled'
        ae = self.assertEquals
        a_ = self.assert_

        l1      = scan('IF((K .GE. 2) .AND.(CALCADVECTION .AND.' + \
                       '(.NOT. IMPLICITADVECTION))) THEN')
        (e1,dc) = Exp(l1)
        ae(repr(e1),
           repr(App('IF',[Ops('.AND.',
                              ParenExp(Ops('.GE.','K','2')),
                              ParenExp(Ops('.AND.',
                                           'CALCADVECTION',
                                           ParenExp(Not('IMPLICITADVECTION'))
                                           ))
                              )]))
           )

    def test17(self):
        'unary + handled'
        ae = self.assertEquals
        a_ = self.assert_

        l1      = scan('+foo - bar * 3.14_w2f')
        (e1,dc) = Exp(l1)
        ae(repr(e1),
           repr(Ops('-',Upl('foo'),Ops('*','bar','3.14_w2f')))
           )

class C2(TestCase):
    'Test for all ops being covered'

    def test1(self):
        'all ops covered'
        ae = self.assertEquals
        a_ = self.assert_

        for op in list('+-*/:'):
            a_(is_op(op))

        for op in ('**','//',):
            a_(is_op(op))

        for op in [ '.' + t + '.' for t in ['and','or','lt','le',
                                            'gt','ge','eq','ne']]:
            a_(is_op(op))

    def test2(self):
        'all unary ops covered'
        ae = self.assertEquals
        a_ = self.assert_

        for op in ['+','-','.not.']:
            a_(is_unary(op))

class C3(TestCase):
    'check that Exp backtrack works correctly for data stmts'

    def test1(self):
        'data statement backtrack'
        ae = self.assertEquals
        a_ = self.assert_

        s = 'DATA(A1(tmp0), tmp0 = 1, 5, 1) / 3.49999994039535522461D-01,' + \
            ' 6.00000023841857910156D-01, 1.0D00, 1.5D00, ' + \
            '1.39999997615814208984D00 /'

        (e1,dc) = Exp(scan(s))
        ae(e1,'DATA')
        ae(dc,['(', 'A1', '(', 'tmp0', ')',
               ',', 'tmp0', '=', '1', ',', '5', ',', '1', ')',
               '/', '3.49999994039535522461D-01', ',',
               '6.00000023841857910156D-01', ',', '1.0D00', ',',
               '1.5D00', ',', '1.39999997615814208984D00', '/'])

s1 = makeSuite(C3)

suite = asuite(C1,C2,C3)

if __name__ == '__main__':
    runit(suite)
