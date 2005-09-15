'''read Fortran Lines from sources into a Line object'''

from flatten import flatten
from assembler import *
from chomp import chomp
from fortScan import q_re,qq_re
import sre

class anyFortLine(object):
    '''generic line class for any fortran line'''
    pass

class fline(anyFortLine):
    '''a non-comment (semantic) class for a fortran line'''

    def __init__(self,dta):

        '''a true fortran line dta structure comes in as:
        [initial stmt [continuation_lines]]

        continuation_lines are structures as well:
        [[comments] continuation_line]
        '''

        self.rawline           = ''.join(flatten(dta))
        self.internal_comments = []

        (self.line,c)          = kill_bang_comment(chomp(dta[0]))
        if not c == '':
            self.internal_comments.append(chomp(c))

        for cont in dta[1]:
            self.internal_comments.extend([ chomp(l) for l in cont[0]])
            (l,c) = kill_bang_comment(chomp(cont[1])[6:])
            if not c == '':
                self.internal_comments.append(chomp(c))
            self.line += l

class cline(anyFortLine):
    '''a comment (or blank) line'''
    def __init__(self,dta):
        self.rawline = ''.join(flatten(dta))

    def comment_list(self):
        return self.rawline.splitlines()

def comment_p(l):
    '''given a line l, return true if l is a comment (or blank) line'''
    comre   = sre.compile(r'''[^\d\s]''')
    blankre = sre.compile(r'''\s* $''',sre.X)
    shoutre = sre.compile(r''' \s* !''',sre.X)
    return comre.match(l) or blankre.match(l) or shoutre.match(l)

def cont_p(l):
    '''given a line l, return true if l is a continuation line'''
    contre = sre.compile(r'''\s{5} \S''',sre.X)
    return contre.match(l)

def stmt_p(l):
    '''given a line l, return true if l is a starting statement'''
    return not (comment_p(l) or cont_p(l))

def flow_line(l,cont='+'):
    '''given a long line, write it out as a series of continued lines'''
    l1 = chomp(l)
    if comment_p(l) or (len(l1) <= 72):
        return l

    rv = l1[0:72] + '\n'
    rem = l1[72:]
    while len(rem) > 66:
        tmp  = rem[0:66]
        rv  += ' ' * 5 + cont + tmp + '\n'
        rem  = rem[66:]
    if len(rem) > 0:
        rv  += ' ' * 5 + cont + rem + '\n'
    return rv

_no_bang_re = r'''^((?: [^'"!] | (?: %s ) | (?: %s) )*) (! .*)$'''
_no_bang_re = _no_bang_re % (q_re,qq_re)
_no_bang_re = sre.compile(_no_bang_re,sre.X)

def kill_bang_comment(l):
    '''kill bang comments from end of line'''
    mm = _no_bang_re.match(l)
    if not mm:
        return(l,'')
    else:
        return(mm.group(1),mm.group(2))

strt   = pred(stmt_p)
comm   = pred(comment_p)
cont   = pred(cont_p)

cblk   = treat(plus(comm),cline)
stmt   = treat(seq(strt,star(seq(star(comm),cont))),fline)

a_line = disj(cblk,stmt)
