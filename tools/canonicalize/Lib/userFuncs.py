'''
Module to have a list of user defined functions
specified on the command line 
'''
__userFuncs= []

def addUserFunc(aFunc): 
    __userFuncs.append(aFunc.lower())

def is_userFunc(op):
    return op.lower() in __userFuncs
