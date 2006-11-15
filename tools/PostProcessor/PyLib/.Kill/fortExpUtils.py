'''
Utilities to manipulate expressions, particularly tree replacement
and generation
'''

import fortExp as fe

# app node
if self.name == '__deriv__':
    self.repl(Sel(self.getson(0),'d'))
    self.prune()
if self.name == '__value__':
    self.repl(Sel(self.getson(0),'v'))
    self.prune()

def walk(self,vizlexi):
    Exp.setup(vizlexi)
    for n in self.wklst():
        n.visit()
        self.wklst_upd(n)
    Exp.restore(vizlexi)
