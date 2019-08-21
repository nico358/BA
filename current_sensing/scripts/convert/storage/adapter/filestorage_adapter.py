""" This module provides an interface for file handling. Several methods are implemented in order to
    open a file and write data into it.
"""

import os
from os.path import join
from os.path import expanduser
from exception_handler import ExceptionHandler

class FileStorageAdapter: 
    """ This class provides methods for file handling."""

    file = None 

    def __init__(self, file=None):
        """ The constructor sets the specified path
            for the file to be handled.
        """
        self.file = file

    def fileIsOpen(self):
        """ This method returns true if the
            file handled by the object is open.
        """
        if self.file == None:
            return False
        if self.file.closed:
            return False
        return True

    
    def appendPathToHomeDIR(self, path):
        """ This method returns a specified
            path appended to $HOMEDIR$.
        """
        return os.path.join(expanduser("~"), path)


    def openFile(self, path=None, mode="w+"):
        """ This method opens a file at the
            specified path in write mode.
        """
        if self.file == None and path != None:
            try:
                self.file = open(path, mode)
            except (ValueError, OSError, IOError) as e:
                ExceptionHandler(e, "openFile")
        

    def closeFile(self):
        """ This method closes the actually
            handled file.
        """
        if self.file != None:
            try:
                self.file.close()
            except (ValueError, OSError, IOError) as e:
                ExceptionHandler(e, "closeFile")


    def writeToOpenFile(self, data):
        """ This method writes data to the actually
            handled file.
        """
        if self.file != None:
            try:
                self.file.write(data)
            except (ValueError, OSError, IOError) as e:
                ExceptionHandler(e, "writeToOpenFile")


    def writeFileWithOpen(self, data, path='None', mode='w+'):
        """ This method opens a file in write mode and writes
            the specified data into it.
        """
        try:
            with open (path, mode) as writer:
                writer.file.write(data)
        except (ValueError, OSError, IOError) as e:
            ExceptionHandler(e, "writeFileWithOpen")


    def readFileWithOpen(self, path):
        """ This method opens a file in read mode and returns
            the contained data.
        """
        content = None
        try:
            with open (path, "r") as reader:
                if reader.mode == 'r':
                    content = reader.read()
        except (ValueError, OSError, IOError) as e:
             ExceptionHandler(e, "readFileWithOpen")
        return content

    def readFromOpenFile(self):
        """ This method returns the data contained in an
            open file.
        """
        content = None
        if self.file != None:
            content = self.file.read()
        return content

    def createFolder(self, fname):
        """ This method creates a folder at the
            specified location."""
        if not os.path.exists(fname):
            os.makedirs(fname)

if __name__ == "__main__":
    """TODO."""
    filewriter = FileStorageAdapter()
    print(filewriter.appendPathToHomeDIR("Default"))
    filewriter.openFile(path="meas/test.txt")
    for i in range(1,100):
        filewriter.writeToOpenFile(str(i) + " FPGA_VCCINT_MON 0.014683 3.281250 0.047240 FPGA_VCCAUX_MON 0.006349 1.093750 0.006809\r\n")
    filewriter.closeFile()

