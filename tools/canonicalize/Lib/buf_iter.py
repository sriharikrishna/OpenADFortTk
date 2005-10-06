'''
Buffered iterator -- try to avoid itertool.chain for backtracking,
as I think the closure captures the values
'''
class buf_iter(object):
    def __init__(self,iterable):
        self.iterable   = iter(iterable)
        self.lookahead  = []

    def putback(self,lst):
        self.lookahead[0:0] = lst
        return self

    def next(self):
        if not self.lookahead:
            return self.iterable.next()
        v = self.lookahead[0]
        self.lookahead = self.lookahead[1:]
        return v

    def __iter__(self):
        return self
