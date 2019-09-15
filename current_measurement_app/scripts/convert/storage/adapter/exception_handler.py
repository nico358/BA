"""The Exception Handler module delegates exceptions from other modules."""

import sys

class ExceptionHandler:
    """ This class is a generic exception handler. An instance takes the exception
        passed to the constructor and maps the exception. According to the mapping
        a message is printed to the console and the program either is stopped by
        the class object or further executed.
    """

    # The exception object
    exception = None
    # The exception's origin
    origin = None
    # A name for the exception
    name = None  

    def __init__(self, exception, origin):
        """ The constructor assigns the passed exception to
            the class object and calls the mapping function.
            The 'origin' attribute is a string provided by the caller.
        """
        self.exception = exception
        self.origin = origin
        self.name = str(exception.__class__.__name__)
        self.exceptionMapping()

    def exceptionMapping(self):
        """ Known exceptions are mapped in this
            method and a handler is called.
        """
        if self.name == "SerialException":
            self.handleSerialException()
        elif self.name == "KeyboardInterrupt":
            self.handleKeyboardInterrupt()
        elif self.name == "SerialTimeoutException":
            self.handleSerialTimeoutException()
        else:
            self.defaultHandler()

    def handleKeyboardInterrupt(self):
        """This method handles a keyboard interrupt exception."""
        self.writeErrorAndExit("\n\'" + self.origin + "\' left by user\n")

    def handleSerialException(self):
        """This method handles an open connection  
            exception from the py_serial module.
        """
        errstr = None
        if self.origin == "openSerial":
            errstr = "Could not open port in "
        elif self.origin == "writeToSerial" or self.origin =="readFromSerial" or self.origin == "readFromSerialUntilExpect":
            errstr = "SerialException in "
        self.writeErrorAndExit(errstr + "\'" + self.origin + "\'\n")

    def handleSerialTimeoutException(self):
        """This method handles an read exception
            from the py_serial module.
        """
        errstr = None
        if self.origin == "readFromSerial" or self.origin == "readFromSerialUntilExpect":
            errstr += "Timeout while reading in "
        elif self.origin == "writeToSerial":
            errstr += "Timeout while writing to serial in "
        self.writeErrorAndExit(errstr + "\'" + self.origin + "\'\n")

    def defaultHandler(self):
        """This method handles exceptions
            unknown by this class.
        """
        sys.stderr.write("Exception \'" + self.name + "\' in \'" + str(self.origin) + "\' ...exit program\n")
        raise self.exception
        sys.exit(0)

    def writeErrorAndExit(self, msg):
        """This method prints the passed
            string and exits the program.
        """
        sys.stderr.write(msg)
        sys.exit(0)