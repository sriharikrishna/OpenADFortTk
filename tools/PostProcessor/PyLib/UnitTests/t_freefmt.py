'''
unit tests for free format line iterator
'''
from Setup    import *
from unittest import *
from freefmt import *
from kill_bang import kill_bang_comment

class C1(TestCase):
    l1 = ' a = sin(x)'
    l2 = 'a = sin(x & ! a commmented cont line'
    l3 = '    ! this is a comment line     '
    l4 = ''
    l5 = '		\n'
    l6 = '\n'
    l7 = '     \n'
    globals().update(locals())

    def test1(self):
        'non comment/non continued simple statement'
        ae = self.assertEquals
        a_ = self.assert_
        a_(not is_comm(l1))
        a_(not is_cont(l1))

    def test2(self):
        'continued line with embedded comment'
        ae = self.assertEquals
        a_ = self.assert_

        a_(not is_comm(l2))
#        (l2r,r) = kill_bang_comment(l2)
#        a_(is_cont(l2r))
        a_(is_cont(l2))

    def test3(self):
        'simple comment line'
        ae = self.assertEquals
        a_ = self.assert_
        a_(is_comm(l3))

    def test4(self):
        'null line = comment'
        ae = self.assertEquals
        a_ = self.assert_
        a_(is_comm(l4))

    def test5(self):
        'ordinary comment line'
        ae = self.assertEquals
        a_ = self.assert_
        a_(is_comm(l5))

    def test6(self):
        'line with only a carriage return'
        ae = self.assertEquals
        a_ = self.assert_

        a_(is_comm(l6))

    def test6(self):
        'line with blanks followed by carriage return'
        ae = self.assertEquals
        a_ = self.assert_

        a_(is_comm(l7))

s = asuite(C1)

if __name__ == '__main__':
    runit(s)

