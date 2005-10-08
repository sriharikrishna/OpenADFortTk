'''
Module to list the intrinsic functions, and
a predicate to test for a function being an intrinsic
'''
__intrinsics = ('sin',
                'cos',
                'tan',
                'atan2',
                )

def is_intrinsic(op):
    return op.lower() in __intrinsics
