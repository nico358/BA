class SerialStorage:
    """TODO."""

    # ommit self. creates local variable
    def __init__(self): 
        """TODO."""
        # refer to using object (fw = FileWriter(); fw.writer.write(...))
        self.writer = None

        # declared as private but still accessible 
        self._reader = None     

        # declared as private (concealed), but accessible by "fw._FileWriter__reader"
        self.__reader = None    
    
    #Create getter (use without preceeding _)
    @property
    def reader(self):
        """TODO."""
        return self._reader

    #Create setter
    @reader.setter
    def reader(self, value):
        """TODO."""
        self._reader = value

    #Create deleter
    @reader.deleter
    def reader(self):
        del self._reader


    def writeToNewFile(self, readings):
        """TODO."""
        writer = open("readings.txt","w+")
        writer.write(readings)
        writer.close()


    def rewriteToExistingFile(self, readings):
        """TODO."""
        writer = open("readings.txt", "a+")
        writer.write(readings)
        writer.close()

    def readFromFile(self, filename):
        """TODO."""
        reader = open("readings.txt", "r")
        if reader.mode == 'r':
            content = reader.read()
            print (content)

if __name__ == "__main__":
    """TODO."""
    filewriter = SerialStorage()
    filewriter.writeToNewFile("Here goes the reading\r")

        

# Mode 	Description
# 'r' 	This is the default mode. It Opens file for reading.
# 'w' 	This Mode Opens file for writing.
# If file does not exist, it creates a new file.
# If file exists it truncates the file.
# 'x' 	Creates a new file. If file already exists, the operation fails.
# 'a' 	Open file in append mode.
# If file does not exist, it creates a new file.
# 't' 	This is the default mode. It opens in text mode.
# 'b' 	This opens in binary mode.
# '+' 	This will open a file for reading and writing (updating)