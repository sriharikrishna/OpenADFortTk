'''
Combinator based assemblers for lists

In general, an assembler has this type:

list -> (val, list)

where list is the initial input list, and the result list
is the 'remainder' after the assembly

'''

from flatten import flatten

class AssemblerException(Exception):
    '''class for exception for failure to assemble'''
    def __init__(self,msg,rest):
        self.msg  = msg
        self.rest = rest

def pred(p):
    '''produce an assembler based on predicate p
    if p(s.next()), then return that value, otherwise AssemblerException
    '''
    def asm(s):
        if (len(s) == 0):
            raise AssemblerException("empty assembly",s)
        v = s[0]
        if p(v):
            return (v,s[1:])
        raise AssemblerException("predicate failure",s)

    return asm

any = pred(lambda x:True)

def star(a):
    '''assembler that repeatedly applies asm a to the stream

    NOTE: 0 applications is ok (still assembles)
    '''
    def asm(s):
        rv = []
        sloc = s
        try:
            while(True):
                v,sloc = a(sloc)
                rv.append(v)

        except AssemblerException,excp:
            return (rv,excp.rest)        

    return asm

def seq(*asms):
    '''assembler that produces a sequence of assemblies'''

    def asm(s):
        sloc = s
        rv = []
        try:
            for a in asms:
                v,sloc = a(sloc)
                rv.append(v)
            return (rv,sloc)

        except AssemblerException,excp:
            msg  = excp.msg + "->seq failure"
            rest = flatten(rv)+excp.rest
            raise AssemblerException(msg,rest)

    return asm

def disj(*asms):
    '''assembler that produces 1st valid assembly from a list of
    assemblers'''

    def asm(s):
        for a in asms:
            try:
                return a(s)

            except AssemblerException,excp:
                s = excp.rest

        raise AssemblerException('disj failure',s)

    return asm

def treat(a,f):
    '''Given an assembler a, and a function f, apply f to the
    assembler a return value, and return the value of the application
    as the return value of the treated assembler
    '''
    def asm(s):
        (rv,rst) = a(s)
        return(f(rv),rst)

    return asm

def plus(a):
    '''given an assembler a, return the Kleene '+' operation.
    Kleene '+' = seq(a,star(a)), but the return value should still
    be a list of values
    '''
    return treat(seq(a,star(a)),lambda x: [x[0]] + x[1])

def vgen(a,src):
    '''for a given assembler a, and source stream src
    vgen is a returns generator that yields a stream of a-assemblies
    from src, until src is exhausted
    '''
    rst = src
    while True:
        try:
            (v,rst) = a(rst)
            yield v
        except AssemblerException:
            break

