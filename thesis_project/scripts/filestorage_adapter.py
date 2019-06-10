"""TODO."""
import os
from os.path import join
from os.path import expanduser
from exception_handler import ExceptionHandler

class FileStorageAdapter: 
    """TODO."""

    file = None 

    def __init__(self, file=None):
        """TODO."""
        self.file = file

    
    def appendPathToHomeDIR(self, path):
        """TODO."""
        return os.path.join(expanduser("~"), path)


    def openFile(self, path=None, mode="w+"):
        """TODO."""
        if self.file == None and path != None:
            try:
                self.file = open(path, mode)
            except (ValueError, OSError, IOError) as e:
                ExceptionHandler(e, "openFile")
        

    def closeFile(self):
        """TODO."""
        if self.file != None:
            try:
                self.file.close()
            except (ValueError, OSError, IOError) as e:
                ExceptionHandler(e, "closeFile")


    def writeToOpenFile(self, data):
        """TODO."""
        if self.file != None:
            try:
                self.file.write(data)
            except (ValueError, OSError, IOError) as e:
                ExceptionHandler(e, "writeToOpenFile")


    def writeFileWithOpen(self, data, path='None', mode='w+'):
        """TODO."""
        try:
            with open (path, mode) as writer:
                writer.file.write(data)
        except (ValueError, OSError, IOError) as e:
            ExceptionHandler(e, "writeFileWithOpen")


    def readFileWithOpen(self, path):
        """TODO."""
        content = None
        try:
            with open (path, "r") as reader:
                if reader.mode == 'r':
                    content = reader.read()
        except (ValueError, OSError, IOError) as e:
             ExceptionHandler(e, "readFileWithOpen")
        return content


if __name__ == "__main__":
    """TODO."""
    filewriter = FileStorageAdapter()
    print(filewriter.appendPathToHomeDIR("Default"))
    filewriter.openFile(path="storage.txt")
    for i in range(1,10):
        filewriter.writeToOpenFile("test\n")
    filewriter.closeFile()
