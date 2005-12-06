import fortStmts as fs
import fortExp   as fe
from fortContextFile import fortContextFile

def reslice_assign(l,pat,subst):
#    print 'reslice assign called:',l
    rhs = fe.subst(l.rhs,pat,subst)
    new_l = l.same(fs.AssignStmt(l.lhs,rhs))
#    print 'after reslice:',new_l
    return [new_l]

def reslice_call(l,pat,subst):
#    print 'reslice call called:',l
    args = [fe.subst(a,pat,subst) for a in l.args]
    new_l = l.same(fs.CallStmt(l.head,args))
#    print 'after reslice:',new_l
    return [new_l]

def reslice_ifthen(l,pat,subst):
#    print 'reslice ifthen called:',l
    test = fe.subst(l.test,pat,subst)
    new_l = l.same(fs.IfThenStmt(test))
#    print 'after reslice:',new_l
    return [new_l]

def gen_reslice_fns(undo_dict):
    def pat(e):
        return isinstance(e,str) and e.lower() in undo_dict

    def subst(e):
        return undo_dict[e.lower()]

    return (pat,subst)

reslice_lexi = [(fs.AssignStmt,reslice_assign),
                (fs.CallStmt,reslice_call),
                (fs.IfThenStmt,reslice_ifthen)]

def reslice(f):
    '''Given a filename f, re-introduce the slicing operations
    removed by the canonicalization process
    '''

    import cPickle as cp

    upf       = open('reslice.dat')
    reslc_up  = cp.Unpickler(upf)
    reslice_d = reslc_up.load()
    upf.close()

    fns  = gen_reslice_fns(reslice_d)
    fcr  = fortContextFile(f)
    
    fcr2 = fcr.rewrite(reslice_lexi,*fns)
    return fcr2

'''
Spikes
def t():
    global resl
    resl = reslice('fc3.canon.mod.f')
'''
