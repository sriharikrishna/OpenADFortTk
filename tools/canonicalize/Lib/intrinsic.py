'''
Module to list the intrinsic functions, and
a predicate to test for a function being an intrinsic
Note that the following: 
   write, read, print, open, close, format 
are separatly recognized and therefore don't 
need to be listed here.  
'''
__intrinsics = (
    'abs',
    'atan',
    'atan2',
    'cos',
    'exp',
    'float',
    'int',
    'len',
    'mod',
    'nint',
    'sign',
    'sin',
    'sqrt',
    'tan',
    'tanh',
    )

def is_intrinsic(op):
    return op.lower() in __intrinsics
