""" This module provides an interface for serial communication by wrapping the py_serial module."""
import os
import sys
import time
import serial
from serial.tools import list_ports
from exception_handler import ExceptionHandler


class SerialAdapter:
    """ This class provides methods for serial communication."""

    # The connection object
    connection = None

    def __init__(self, port='/dev/ttyUSB', baudrate=9600, readTimeout=0.5, writeTimeout=0.5):
        """ The constructor creates a serial connection object with the specified parameters.
            The 'port' attribute determines the serial COM port that is to be used for the
            communication, the communication's speed needs to be specified by 'baudrate'.
            'Timeout' parameters are optional.
        """
        # Create serial object
        self.connection = serial.Serial()
        # Set timeout
        self.setConnectionReadTimeout(readTimeout)
        self.setConnectionWriteTimeout(writeTimeout)
        # Check if 'port' and 'baudrate' are provided by call from console
        if not self.setUserDefinedConnection():
            # If no sys.argv parameters are provided set port and baudrate
            # according to parameters from constructor call
            self.connection.port = self.checkSerialPortAvailable(port)
            self.connection.baudrate = int(baudrate)


    def openSerial(self):
        """This method opens a connection on the current serial instance."""
        attempts = 0
        # Try open 10 times
        while not self.connection.is_open and attempts < 10:
            try:
                self.connection.open()
            except serial.SerialException:
                # Write attempts to console
                sys.stdout.write("Try to open port\n")
                attempts += 1
                try:
                    # Sleep between attempts and raise exception after 10 times
                    time.sleep(1)
                    if attempts == 10:
                        raise serial.SerialException
                # Catch exceptions
                except (KeyboardInterrupt, serial.SerialException) as e:
                    ExceptionHandler(e,"openSerial")
            except (ValueError, KeyboardInterrupt) as e:
                ExceptionHandler(e,"openSerial")
        # Reset buffers when connection is open
        self.resetConnectionBuffers()


    def closeSerial(self):
        """This method closes the actual connection."""
        if self.connection.is_open:
            self.resetConnectionBuffers()
            self.connection.close()


    def writeToSerial(self, data):
        """ This method writes the data to the open
            connection and returns the number of written bytes.
        """
        writtenBytes = None
        if self.connection.is_open:
            try:
                writtenBytes = self.connection.write(data)
            except (KeyboardInterrupt, serial.SerialTimeoutException, serial.SerialException) as e:
                ExceptionHandler(e,"writeToSerial")
            finally:
                self.flushWriteBuffer()
        return writtenBytes



    def readFromSerialWithDelay(self, secondsDelay=None):
        """This method returns read bytes from the connection with a
            specified delay between read attempts.
        """
        data = None
        if self.connection.is_open: 
            try:
                self.serialSleep(secondsDelay)
                data = self.connection.read(self.getBytesInWaiting())
            except (KeyboardInterrupt, serial.SerialTimeoutException, serial.SerialException) as e:
                ExceptionHandler(e,"readFromSerial")
        return data


    def readFromSerialUntilExpectWithDelay(self, expectedEnd='LF', expectedBytes=None, secondsDelay=0.1):
        """ This method returns read bytes. The reading stops at an expected point specified by
            'expectedEnd' or 'expectedBytes'. A delay between read attempts can be specified.
        """
        data = None
        if self.connection.is_open: 
            try:
                self.serialSleep(secondsDelay)
                data = self.connection.read_until(expectedEnd, expectedBytes)
            except (KeyboardInterrupt, serial.SerialTimeoutException, serial.SerialException) as e:
                ExceptionHandler(e,"readFromSerialUntilExpect")
        return data


    def checkSerialPortAvailable(self, port):
        """This method validates a provided path to a COM port by
            use of the py_serial.grep function.
        """
        # Get a list of available ports similar to the 'port' attribute
        availablePorts = list(list_ports.grep(port))
        # No matching port on system, exit
        if len(availablePorts) == 0:
            sys.stderr.write("No available ports for \'" + str(port) + "\' ...exit\n")
            sys.exit(0)
        # Found one match, print success and return port
        if len(availablePorts) == 1:
            availablePort = availablePorts[0][0]
            sys.stdout.write("Found port: " + str(availablePort) + "\n")
            return availablePort
        # Found too many ports, exit
        else:
            sys.stderr.write("Found too many available ports for \'" + str(port) + "\' ...exit\n")
            sys.exit(0)


    def setUserDefinedConnection(self):
        """ This method checks if 'port' and 'baudrate' parameters
            has been provided by a call from console and returns true if so.
        """
        if not self.connection is None:
            try:
                # First argument: port
                self.connection.port = self.checkSerialPortAvailable(sys.argv[1])
                # Second argument: baudrate
                self.connection.baudrate = int(sys.argv[2])
            except Exception:
                return False
            return True


    def resetConnectionBuffers(self):
        """This method resets all buffers."""
        if self.connection.is_open:
            self.connection.reset_input_buffer()
            self.connection.reset_output_buffer()


    def flushWriteBuffer(self):
        """This method flushes the connection."""
        self.connection.flush()


    def setConnectionReadTimeout(self, seconds):
        """This method sets a read timeout."""
        if not self.connection is None:
            self.connection.timeout = seconds
    

    def setConnectionWriteTimeout(self, seconds):
        """This method sets a write timeout."""
        if not self.connection is None:
            self.connection.write_timeout = seconds


    def getBytesInWaiting(self):
        """This method returns bytes that
            wait in the input buffer.
        """
        return self.connection.in_waiting


    def serialSleep(self, seconds):
        """This method causes a delay of the
            executing process.
        """
        if not seconds is None:
            time.sleep(seconds)



if __name__ == "__main__":
    """TODO."""
    s = SerialAdapter('/dev/ttyS26', 9600)
    s.openSerial()
    s.writeToSerial("C")
    data = s.readFromSerialWithDelay()
    s.closeSerial()
    print(data)
    