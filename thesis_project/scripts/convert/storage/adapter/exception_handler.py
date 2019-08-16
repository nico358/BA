"""TODO."""

import sys

class ExceptionHandler:
    """TODO."""

    exception = None
    origin = None
    name = None  

    def __init__(self, exception, origin):
        """TODO."""
        self.exception = exception
        self.origin = origin
        self.name = str(exception.__class__.__name__)
        self.exceptionMapping()

    def exceptionMapping(self):
        """TODO."""
        if self.name == "SerialException": 
            self.handleSerialException()
        elif self.name == "KeyboardInterrupt": 
            self.handleKeyboardInterrupt()
        elif self.name == "SerialTimeoutException":
            self.handleSerialTimeoutException()
        else:
            self.defaultHandler()

    def handleKeyboardInterrupt(self):
        """TODO."""
        self.writeErrorAndExit("\n\'" + self.origin + "\' left by user\n")

    def handleSerialException(self):
        """TODO."""
        errstr = None
        if self.origin == "openSerial":
            errstr = "Could not open port in "
        elif self.origin == "writeToSerial" or self.origin =="readFromSerial" or self.origin == "readFromSerialUntilExpect":
            errstr = "SerialException in "
        self.writeErrorAndExit(errstr + "\'" + self.origin + "\'\n")

    def handleSerialTimeoutException(self):
        """TODO."""
        errstr = None
        if self.origin == "readFromSerial" or self.origin == "readFromSerialUntilExpect":
            errstr += "Timeout while reading in "
        elif self.origin == "writeToSerial":
            errstr += "Timeout while writing to serial in "
        self.writeErrorAndExit(errstr + "\'" + self.origin + "\'\n")

    def defaultHandler(self):
        """TODO."""
        sys.stderr.write("Unknown exception \'" + self.name + "\' in \'" + str(self.origin) + "\' ...exit program\n")
        raise self.exception
        sys.exit(0)

    def writeErrorAndExit(self, msg):
        """TODO."""
        sys.stderr.write(msg)
        sys.exit(0)