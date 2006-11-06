'''
Manipulate the trees that make up the fortran program representation
'''

def is_leaf(v):
    '''a node is a leaf if:
       1) it is a token  OR
       2) it has an empty sons list
    '''
    return isinstance(v,str) or (hasattr(v,'sons') and not v.sons)

def ref_son(self,item):
    return getattr(self,self.sons[item])

