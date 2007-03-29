'''
specific exceptions that we may want to catch 
at the top level rather than the system exceptions
which should continue to produce a stack trace.
'''

class UserError(Exception):
    '''exception for errors caused by the user'''
    def __init__(self,msg):
        self.msg  = msg


class ScanError(Exception):
    '''
	exception for errors detected in the scanner caused either by 
	faulty code or by incomplete handling in the scanner
    '''
    def __init__(self,lineNumber,aFortLine,scanned,rest):
        self.lineNumber=lineNumber
        self.aFortLine=aFortLine
	self.scanned=scanned
	self.rest=rest

