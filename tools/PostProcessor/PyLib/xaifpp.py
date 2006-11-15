'''
   Transformations:
      1. add the active_module
      2. convert type(OpenAD_type)  ...
         or type(OpenAD_type_init)  ... TO
         type(active) :: ...
      3. convert __value__($p) --> $p%v
      4. convert __deriv__($p) --> $p
'''
import fortStmts as fs
import fortExp   as fe

from mutable_tree import LexiMutator,mutate

def type_active_m(self,arg):
    '''convert type(OpenAD_type) to type(active)
    only applied to type declaration stmts
    '''
    if self.name.lower() in set(['openad_type','openad_type_init']):
        self.name = 'active'
        self.dblc = True
        self.reflow()
    arg.attach(self)

def val_deriv_m(self,top):
    'mutate __value__ and __deriv__ calls'
    if self.head == '__value__':
        nv = fe.Sel(self.args[0],'v')
        self.repl(nv)
        self.prune(True)
        top.reflow()
    if self.head == '__deriv__':
        nv = self.args[0]
        self.repl(nv)
        self.prune(True)
        top.reflow()

def add_active_module(self,arg):
    'add the active module'
    new_stmt = fs.UseStmt('active_module')
    new_stmt.clone_fmt(self)
    arg.attach(self,new_stmt)

def o_add_active_module(self):
    'add the active module'
    new_stmt = fs.comment_bl('use active module')
    return [self,new_stmt[0]]

def xUse(self):
    if (self.name == 'w2f__types'):
        return o_add_active_module(self)
    else:
        return [self]

xaif_lexi = [(fs.UseStmt,xUse),
             (fe.App,val_deriv_m),
             (fs.TypeDecl,type_active_m)
             ]
xaif_lexi_o = [(fs.UseStmt,xUse)
               ]

def xaifpp(ftn,real=False):
    return ftn.rewrite(xaif_lexi_o)
