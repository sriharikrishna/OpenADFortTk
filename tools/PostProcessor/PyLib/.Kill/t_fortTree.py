from Setup import *
from unittest import *
from useparse import *

from fortTree import *
from fortExp import _optbl


class C1(TestCase):
    def test1(self):
        "binary slice op ':' op has sons"
        ae = self.assertEquals
        a_ = self.assert_
        v = ep('xxx:yyy')
        a_(hasattr(v,'sons'))

class C2(TestCase):
    def test1(self):
        "transform one app name to another"
        ae = self.assertEquals
        a_ = self.assert_

def _mkt2fn(s):
    def __test(self):
        ae = self.assertEquals
        a_ = self.assert_
        v  = ep('xxx %s yyy' %s)
        a_(hasattr(v,'sons'))
    __test.__doc__ = "op '%s' has sons" % s

    return __test

__c = 2
for b in ([x for (o,p) in _optbl for x in o][1:]):
    setattr(C1,'test%d' % __c,_mkt2fn(b))
    __c += 1

s1 = makeSuite(C1)

suite = asuite(C1)

if __name__ == "__main__":
    runit(suite)
