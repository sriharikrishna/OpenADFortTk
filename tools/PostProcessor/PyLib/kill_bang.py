'''
Routine to kill bang(= !) comments fromt the end of the line
'''
from fortScan import q_re,qq_re
# import sre
import re

_no_bang_re = r'''^((?: [^'"!] | (?: %s ) | (?: %s) )*) (! .*)$'''
_no_bang_re = _no_bang_re % (q_re,qq_re)
_no_bang_re = re.compile(_no_bang_re,re.X)

def kill_bang_comment(l):
    '''kill bang comments from end of line'''
    mm = _no_bang_re.match(l)
    if not mm:
        return(l,'')
    else:
        return(mm.group(1),mm.group(2))

"""
Spikes

from Devel import *

def t():
    l1 = preclip(r'''
    str1 = 'This is a string'
''')
    l2 = preclip(r'''
    str1 = 'This is a string & !it has something in it'
''')
    l3 = preclip(r'''
          str1 = 'This is a string with & ! stuff &
''')
    l4 = preclip(r'''
       str1 = 'This is a string with & ! stuff &' &
''')
    l5 = preclip(r'''
       str1 = 'This is a string with & ! stuff &' & ! this is a comment
''')
    globals().update(locals())
"""
