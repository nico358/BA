import os, sys

def setpath():
    # set current dir
    currDir = os.path.dirname(os.path.realpath(__file__))
    # set root dir (project dir)
    rootDir = os.path.abspath(os.path.join(currDir, '../../../'))
    # add root dir to paths
    if rootDir not in sys.path: 
        sys.path.append(rootDir)