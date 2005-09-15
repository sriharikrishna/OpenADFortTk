'''Various regular expressions for fortran tokens
to use these expressions, be sure to sre.compile with sre.X
'''

import sre

def __str_intern(s):
    template = r"""
         (?:            # body of quote is a collection of chars
            [^%s\\] |   #    non-quote or backslash OR
            %s%s    |   #    repeated quote         OR
            \\.         #    backslashed anything
         )*             # 0 or more
"""
    return template % (s,s,s)

def __closed_q(s):
    return s + __str_intern(s) + s

def __ro_q(s):
    prelude = r'''
    ^(?: [^%s] | (?: %s) )*'''

    return prelude % (s,__closed_q(s)) + s + __str_intern(s) + '$'

q_re     = __closed_q("'")
qq_re    = __closed_q('"')

ro_q_re  = __ro_q("'")
ro_qq_re = __ro_q('"')
