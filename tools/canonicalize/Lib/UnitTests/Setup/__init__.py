import sys,os.path

# print 'from setup package: ',sys.path[0]

mypath = sys.path[0]

libpath = os.path.normpath(os.path.join(sys.path[0],'..'))

# print 'new path to add: ',libpath

sys.path.insert(0,libpath)

# print 'new sys.path = ', sys.path
