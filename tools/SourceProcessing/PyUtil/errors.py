'''
specific exceptions that we may want to catch 
at the top level rather than the system exceptions
which should continue to produce a stack trace.
'''

class UserError(Exception):
    '''exception for errors caused by the user'''
    def __init__(self,msg):
        self.msg  = msg

