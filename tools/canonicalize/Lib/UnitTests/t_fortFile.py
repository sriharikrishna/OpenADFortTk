import Setup

from unittest import *
from fortFile import *

class file1(TestCase):
    def setUp(self):
        import os.path

        self.fname = os.path.join(Setup.mypath,'Tfiles','f1.f')

    def tearDown(self):
        pass

    def test1(self):
        '''Ffile string method returns the string rep of the file'''

        ff = file(self.fname)
        fff = Ffile.file(self.fname)

        self.assertEquals(Ffile.file(self.fname).str(),''.join(ff.readlines()))

        ff.close()

def s1():
    return makeSuite(file1)

def suite():
    rv = makeSuite(file1)

    return rv

def runSuite(s):
    TextTestRunner(verbosity=2).run(s)

if __name__ == '__main__':
    runSuite(suite())

