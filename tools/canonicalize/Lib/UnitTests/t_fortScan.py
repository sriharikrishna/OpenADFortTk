import Setup

from unittest import *
from fortScan import *

class qstrings(TestCase):
    def test1(self):
        'single quoted strings'

        re1 = sre.compile('(' + q_re +')',sre.X)
        s1  = "x4_ttxrebe = y5 + xy('foo bar bas gleem')"
        s2  = "xx(2:3) = 'this is a string with '' an embedded quote'"
        s3  = r"yzzy = 'this is a string with \n '' \' with stuff'"

        ae  = self.assertEquals

        mm  = re1.search(s1)
        ae(mm.group(1),"'foo bar bas gleem'")

        mm  = re1.search(s2)
        ae(mm.group(1),"'this is a string with '' an embedded quote'")

        mm  = re1.search(s3)
        ae(mm.group(1),r"'this is a string with \n '' \' with stuff'")

    def test2(self):
        'double quoted strings'

        re1 = sre.compile('(' + qq_re +')',sre.X)
        s1  = 'x4_ttxrebe = y5 + xy("foo bar bas gleem")'
        s2  = 'xx(2:3) = "this is a string with "" an embedded quote"'
        s3  = r'yzzy = "this is a string with \n "" \" with stuff"'

        ae  = self.assertEquals

        mm  = re1.search(s1)
        ae(mm.group(1),'"foo bar bas gleem"')

        mm  = re1.search(s2)
        ae(mm.group(1),'"this is a string with "" an embedded quote"')

        mm  = re1.search(s3)
        ae(mm.group(1),r'"this is a string with \n "" \" with stuff"')

class ro_qstrings(TestCase):
    def test1(self):
        'check for strings that are not closed at end of line'
        re1 = sre.compile(ro_q_re,sre.X)
        s1  = "x4_ttxrebe = y5 + xy('foo bar bas gleem"
        s2  = "xx(2:3) = 'this is a string with '' an embedded quote'"
        s3  = r"yzzy = 'this is a string with \n '' \' with stuff"
        aa  = self.assert_

        mm  = re1.match(s1)
        aa(mm)

        mm  = re1.match(s2)
        aa(not mm)

        mm  = re1.match(s3)
        aa(mm)

class qstrings2(TestCase):
    re1 = sre.compile(q_re)
    
    def test1(self):
        "q_re with internal 'x' flag"
        re1  = qstrings2.re1
        targ = r"x(3:4) = 'foo bar '''//'''baz'''"
        self.assertEquals(re1.findall(targ),["'foo bar '''",
                                             "'''baz'''"])
class scanit(TestCase):
    def test1(self):
        'scan quoted strings, int & float constants w kinds'
        self.assertEquals(scan1.scan(  \
            'f(3) = "foo bar" // "bazme""" // floob(3_iii ** 4.2e-2_w2f)'),
            (['f', '(', '3', ')', '=', '"foo bar"',
              '//', '"bazme"""', '//', 'floob',
              '(', '3_iii', '**', '4.2e-2_w2f', ')'], ''))

    def test2(self):
        'scan declarations, :: style'
        ae = self.assertEquals
        ae(scan1.scan('integer,dimension(10) :: xx,yy,zz'),
           (['integer', ',', 'dimension', '(', '10', ')',
             '::', 'xx', ',', 'yy', ',', 'zz'], ''))

    def test3(self):
        'new style int, float constants'
        ae         = self.assertEquals
        (scanin,r) = scan1.scan('3 3_2 4.2E-22 3.191D0_9 55_w2i .004_w2f')
        ae(scanin,['3', '3_2', '4.2E-22', '3.191D0_9', '55_w2i', '.004_w2f'])
        ae(r,'')

class C4(TestCase):
    def test1(self):
        'logicals and comparisons'
        ae         = self.assertEquals
        (scanin,r) = scan1.scan('IF (X .LT. 5) Y = 10.e0')
        ae(scanin,['IF','(','X','.LT.','5',')','Y','=','10.e0'])
        ae(r,'')

def s1():
    return makeSuite(C4)

def suite():
    rv = makeSuite(qstrings)
    rv.addTest(makeSuite(ro_qstrings))
    rv.addTest(makeSuite(qstrings2))
    rv.addTest(makeSuite(scanit))
    rv.addTest(makeSuite(C4))

    return rv

def runSuite(s):
    TextTestRunner(verbosity=2).run(s)

if __name__ == "__main__":
    runSuite(suite())

