'''
Combinator based assemblers for generators (streams)

In general, an assembler has this type:

stream -> (val, stream)

where stream is the initial input stream, and the result stream
is the 'remainder' after the assembly

'''

from itertools import chain
from flatten import flatten

class AssemblerException(Exception):
    '''base class for exception for failure to assemble'''
    pass

class PredicateFailure(AssemblerException):
    '''current selected stream item cannot be included in the assembly'''
    pass

class EmptyAssembly(AssemblerException):
    '''attempted to assemble from empty'''
    pass

class CompoundAssembly(AssemblerException):
    '''some compound object (ie seq) could not be completely assembled'''

class DisjAssembly(AssemblerException):
    '''no choice in a disjunction worked'''

def pred(p):
    '''produce an assembler based on predicate p
    if p(stream.next()), then return that value, otherwise AssemblerException
    '''
    def asm(s):
        try:
            v = s.next()
        except StopIteration:
            raise EmptyAssembly(iter([]))
        if p(v):
            return (v,s)
        raise PredicateFailure(v,s)

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

        except PredicateFailure,(v,s1):
            return (rv,chain(iter([v]),s1))

        except EmptyAssembly,s1:
            return (rv,iter([]))

        except CompoundAssembly,(lst,s1):
            return (rv,chain(iter(flatten(lst)),s1))

        except DisjAssembly,s1:
            return (rv,s1.args[0])


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
            return rv,sloc

        except EmptyAssembly,s1:
            raise CompoundAssembly(rv,iter([]))

        except PredicateFailure,(v,s1):
            rv.append(v)
            raise CompoundAssembly(rv,s1)

        except CompoundAssembly,(lst,s1):
            rv.extend(lst)
            raise CompoundAssembly(rv,s1)

        except DisjAssembly,s1:
            raise CompoundAssembly(rv,s1)

    return asm

def disj(*asms):
    '''assembler that produces 1st valid assembly from a list of
    assemblers'''

    def asm(s):
        for a in asms:
            try:
                return a(s)

            except EmptyAssembly,s1:
                s = iter([])

            except PredicateFailure,(v,s1):
                s = chain(iter([v]),s1)

            except CompoundAssembly,(lst,s1):
                s = chain(iter(flatten(lst)),s1)

            except DisjAssembly,s1:
                s = s1

        raise DisjAssembly(s)

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

