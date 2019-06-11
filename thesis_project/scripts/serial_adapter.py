"""TODO."""
import os
import sys
import time
import serial
from serial.tools import list_ports
from exception_handler import ExceptionHandler


class SerialAdapter:
    """TODO."""

    connection = None

    def __init__(self, port='/dev/ttyUSB', baudrate=9600, readTimeout=0.5, writeTimeout=0.5):
        """TODO."""
        self.connection = serial.Serial()
        self.setConnectionReadTimeout(readTimeout)
        self.setConnectionWriteTimeout(writeTimeout)
        if not self.setUserDefinedConnection():
            self.connection.port = self.checkSerialPortAvailable(port)
            self.connection.baudrate = int(baudrate)


    def openSerial(self):
        """TODO."""
        attempts = 0
        while not self.connection.is_open and attempts < 10:
            try:
                self.connection.open()
            except serial.SerialException:
                sys.stdout.write("Try to open port\n")
                attempts += 1
                try:
                    time.sleep(1)
                    if attempts == 10:
                        raise serial.SerialException
                except (KeyboardInterrupt, serial.SerialException) as e:
                    ExceptionHandler(e,"openSerial")
            except (ValueError, KeyboardInterrupt) as e:
                ExceptionHandler(e,"openSerial")
        self.resetConnectionBuffers()


    def closeSerial(self):
        """TODO."""
        if self.connection.is_open:
            self.connection.close()


    def writeToSerial(self, data):
        """TODO."""
        writtenBytes = None
        if self.connection.is_open:
            try:
                writtenBytes = self.connection.write(data)
            except (KeyboardInterrupt, serial.SerialTimeoutException, serial.SerialException) as e:
                ExceptionHandler(e,"writeToSerial")
            finally:
                self.flushWriteBuffer()
        return writtenBytes



    def readFromSerialWithDelay(self, secondsDelay=0.1):
        """TODO."""
        data = None
        if self.connection.is_open: 
            try:
                self.serialSleep(secondsDelay)
                data = self.connection.read(self.getBytesInWaiting())
            except (KeyboardInterrupt, serial.SerialTimeoutException, serial.SerialException) as e:
                ExceptionHandler(e,"readFromSerial")
        return data


    def readFromSerialUntilExpectWithDelay(self, expectedEnd='LF' , expectedBytes=None, secondsDelay=0.1):
        """TODO."""
        data = None
        if self.connection.is_open: 
            try:
                self.serialSleep(secondsDelay)
                data = self.connection.read_until(expectedEnd, expectedBytes)
            except (KeyboardInterrupt, serial.SerialTimeoutException, serial.SerialException) as e:
                ExceptionHandler(e,"readFromSerialUntilExpect")
        return data


    def checkSerialPortAvailable(self, port):
        """TODO."""
        availablePorts = list(list_ports.grep(port))
        if len(availablePorts) == 0:
            sys.stderr.write("No available ports for \'" + str(port) + "\' ...exit\n")
            sys.exit(0)
        if len(availablePorts) == 1:
            availablePort = availablePorts[0][0]
            sys.stdout.write("Found port: " + str(availablePort) + "\n")
            return availablePort
        else:
            sys.stderr.write("Found too many available ports for \'" + str(port) + "\' ...exit\n")
            sys.exit(0)


    def setUserDefinedConnection(self):
        """TODO."""
        if self.connection != None:
            try:
                self.connection.port = self.checkSerialPortAvailable(sys.argv[1])
                self.connection.baudrate = int(sys.argv[2])
            except Exception:
                return False
            return True


    def resetConnectionBuffers(self):
        """TODO."""
        if self.connection.is_open:
            self.connection.reset_input_buffer()
            self.connection.reset_output_buffer()


    def flushWriteBuffer(self):
        """TODO."""
        self.connection.flush()


    def setConnectionReadTimeout(self, seconds):
        """TODO."""
        if self.connection != None:
            self.connection.timeout = seconds
    

    def setConnectionWriteTimeout(self, seconds):
        """TODO."""
        if self.connection != None:
            self.connection.write_timeout = seconds


    def getBytesInWaiting(self):
        """TODO."""
        return self.connection.in_waiting


    def serialSleep(self, seconds):
        """TODO."""
        if seconds != None:
            time.sleep(seconds)



if __name__ == "__main__":
    """TODO."""
    s = SerialAdapter('/dev/ttyS26', 9600)
    s.openSerial()
    s.writeToSerial("C")
    data = s.readFromSerialWithDelay()
    s.closeSerial()
    print(data)
    