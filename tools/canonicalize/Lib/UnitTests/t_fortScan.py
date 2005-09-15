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
        ae(mm.group(0),"'foo bar bas gleem'")

        mm  = re1.search(s2)
        ae(mm.group(0),"'this is a string with '' an embedded quote'")

        mm  = re1.search(s3)
        ae(mm.group(0),r"'this is a string with \n '' \' with stuff'")

    def test2(self):
        'double quoted strings'

        re1 = sre.compile('(' + qq_re +')',sre.X)
        s1  = 'x4_ttxrebe = y5 + xy("foo bar bas gleem")'
        s2  = 'xx(2:3) = "this is a string with "" an embedded quote"'
        s3  = r'yzzy = "this is a string with \n "" \" with stuff"'

        ae  = self.assertEquals

        mm  = re1.search(s1)
        ae(mm.group(0),'"foo bar bas gleem"')

        mm  = re1.search(s2)
        ae(mm.group(0),'"this is a string with "" an embedded quote"')

        mm  = re1.search(s3)
        ae(mm.group(0),r'"this is a string with \n "" \" with stuff"')

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

def s1():
    return makeSuite(ro_qstrings)

def suite():
    rv = makeSuite(qstrings)
    rv.addTest(makeSuite(ro_qstrings))

    return rv

def runSuite(s):
    TextTestRunner(verbosity=2).run(s)

if __name__ == "__main__":
    runSuite(suite())
