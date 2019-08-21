#!/usr/bin/env python
""" This module controls the communication with two MCUs on the Elastic Node and stores data
    that have been sent by the monitor MCU. Therefore, three classes extending the thrading
    module are contained. Each class is to be instantiated by its constructor and the run method of
    the class is to be called in order to execute a thread. The data is processed by the monitor and the
    storage thread according to producer-consumer-model. The monitor thread puts received data into
    a queue and the storage thread takes the data and stores it into a specified file. The folders
    for the stored data are created by the storage thread.
"""

import Queue
import threading
from adapter.timer.timer         import Timer
from adapter.serial_adapter      import SerialAdapter
from adapter.exception_handler   import ExceptionHandler
from adapter.filestorage_adapter import FileStorageAdapter

# Thread safe queue, globally visible
BUF_SIZE = 2048
queue = Queue.Queue(BUF_SIZE)

# Folder for data storage (will be created if not existing)
FOLDERPATH              = 'meas/'
# Serial communication settings
PORT_MON                = 'COM26' # serial port monitor MCU
PORT_MCU                = 'COM22' # serial port controller MCU
BAUDRATE                = 115200
# Delay time for subsequential commands
SLEEP_BETWEEN_MCU_CMDS  = 0.01
# Commands to the monitor MCU
START_MON_CMD           = 'A'
PAUSE_MON_CMD           = 'p'
STOP_MON_CMD            = 'q'
# Commands to the controller MCU
SUSPEND_FPGA_CMD        = 'S'
UNSUSPEND_FPGA_CMD      = 's'
RESET_FPGA_CMD          = 'R'
SHUT_ON_FPGA_CMD        = 'C'
SHUT_OFF_FPGA_CMD       = 'c'
TESTMODE_FPGA_CMD       = 'T'
LEDFLASH_FPGA_CMD       = 'L'



class SerialControllerMcu(threading.Thread):
    """ This class creates a thread by calling the constructor and executes it
        by calling the run method subsequently. The thread opens a serial port
        and sends the specified commands to the connection. On the Elastic Node this
        class is used to control the MCU that affects the FPGA's state.
    """

    # Serial connection adapter instance
    serialAdapter = None
    # Data to send
    data = None
    # Stop flag
    flag = None

    def __init__(self, group=None, target='SerialControllerMcu', name='SerialMcuThread', args=(), kwargs=None, verbose=None, port=PORT_MCU, baudrate=BAUDRATE, data=TESTMODE_FPGA_CMD):
        """ The constructor creates a thread object by calling the super constructor of the threading module.
            'name' and 'target' attributes are optional, the 'port', 'baudrate' and 'data' parameters have to
            be specified in order to send the data by the desired serial connection. An instance of
            the serialAdapter is created by the constructor that opens a serial connection.
        """
        super(SerialControllerMcu, self).__init__()
        self.target = target
        self.name = name
        self.serialAdapter = SerialAdapter(port=port, baudrate=baudrate)
        # Data could be either a single character or a list of characters
        self.data = data
        # Must be 'True' to start threads
        self.flag = True

    def run(self):
        """This method executes the thread. The data is sent to the
            serial connection and afterwards the incoming data is printed
            to the console.
        """
        try:
            # open serial connection
            self.serialAdapter.openSerial()
            # Check if data is a list and send data in loop if so
            if isinstance(self.data, list):
                for d in self.data:
                    # Delay between sending
                    self.serialAdapter.serialSleep(SLEEP_BETWEEN_MCU_CMDS)
                    self.serialAdapter.writeToSerial(d)
            else:
                self.serialAdapter.writeToSerial(self.data)
            # Print incoming data to console, stop if flag is set false
            while self.flag:
                if self.serialAdapter.getBytesInWaiting() != 0:
                    print(self.serialAdapter.readFromSerialWithDelay())
        except (KeyboardInterrupt, ValueError, RuntimeError) as e:
             ExceptionHandler(e, "runControllerThread")
        finally:
            # Close serial connection
            self.serialAdapter.closeSerial()

class SerialControllerMon(threading.Thread):
    """ This class creates a thread by calling the constructor and executes it
        by calling the run method subsequently. The thread opens a serial port
        and sends the specified commands to the connection. On the Elastic Node
        this class is used to control the MCU that monitors the current sensors.
    """

    # Serial connection adapter instance
    serialAdapterMon = None
    # Timer instance
    timer = None
    # Stops the thread
    flag = None
    # Data to send
    data = None

    def __init__(self, group=None, target='SerialControllerMon', name='SerialMonThread', args=(), kwargs=None, verbose=None, port=PORT_MON, baudrate=BAUDRATE, data=START_MON_CMD):
        """ The constructor creates a thread object by calling the super constructor of the threading module.
            'name' and 'target' attributes are optional, the 'port', 'baudrate' and 'data' parameters have to
            be specified in order to send the data by the desired serial connection. An instance of
            the serialAdapter is created by the constructor that opens a serial connection.
        """
        super(SerialControllerMon, self).__init__()
        self.target = target
        self.name = name
        self.serialAdapterMon = SerialAdapter(port=port, baudrate=baudrate)
        # Must be 'True' to start threads
        self.flag = True
        self.data = data


    def run(self):
        """This method executes the thread. The data is sent to the
            serial connection and afterwards the incoming data is put
            into the queue.
        """
        try: 
            # Open serial port
            self.serialAdapterMon.openSerial()
            # Check if data is a list and send data in loop if
            if isinstance(self.data, list):
                for d in self.data:
                    self.serialAdapterMon.serialSleep(SLEEP_BETWEEN_MCU_CMDS)
                    self.serialAdapterMon.writeToSerial(d)
            else:
                self.serialAdapterMon.writeToSerial(self.data)
            # Push incoming data to queue, stop if flag is set false
            while self.flag:
                if not queue.full() & self.serialAdapterMon.getBytesInWaiting() != 0:
                    queue.put(self.serialAdapterMon.readFromSerialWithDelay(None))
                else:
                    print("Queue full or no bytes in waiting!")
        except (KeyboardInterrupt, ValueError, RuntimeError) as e:
             ExceptionHandler(e, "runMonitorThread")
        finally:
            # Finally pause monitoring on platform
            self.serialAdapterMon.writeToSerial(PAUSE_MON_CMD)
            self.serialAdapterMon.closeSerial()


class StorageController(threading.Thread):
    """ This class creates a thread by calling the constructor and executes it
        by calling the run method subsequently. The thread opens a file and
        writes data from the queue into the file. On the Elastic Node this class
        is used to store the readings of the monitor MCU.
    """

    # File adapter instance
    fileStorageAdapter = None
    # Path of the file
    path = None
    # Stops the thread
    flag = None

    
    def __init__(self, group=None, target='StorageController', name='StorageThread', args=(), kwargs=None, verbose=None, folderpath=FOLDERPATH, filepath=None):
        """ The constructor creates a thread object by calling the super constructor of the threading module.
            'name' and 'target' attributes are optional, the 'folderpath' and 'filepath' parameters have to
            be specified in order to save the data at the desired location. An instance of
            the fileStorageAdapter is created by the constructor that controls the storage of the data.
        """
        super(StorageController, self).__init__()
        self.target = target
        self.name = name
        # Create file adapter instance
        self.fileStorageAdapter = FileStorageAdapter()
        # Creates a folder for the records
        self.fileStorageAdapter.createFolder(folderpath)
        # Creates a folder for plots
        self.fileStorageAdapter.createFolder(folderpath + '/plot')
        # Set filepath
        if not filepath is None:
            self.path = folderpath + filepath +'.txt'
        # Must be true in order to execute a thread
        self.flag = True


    def run(self):
        """ This method executes the thread. The data is popped
            from the queue and written to the file.
        """
        try:
            # Open file
            if not self.path is None:
                self.fileStorageAdapter.openFile(self.path)
                # Write data from queue to file, stop if flag is set false
                while self.flag:
                    if not queue.empty():
                        self.fileStorageAdapter.writeToOpenFile(queue.get())
        except (KeyboardInterrupt, ValueError, RuntimeError) as e:
             ExceptionHandler(e, "runStorageThread")
        finally:
            # Close file
            self.fileStorageAdapter.closeFile()

def startThreads(threadlst):
    """ This methods starts all thread from a list."""
    for t in threadlst:
        t.start()

def stopThreads(threadlst):
    """ This methods stops all thread from a list.
        The flag is set false in order to break
        the loop execution of the threads.
    """
    for t in threadlst:
        t.flag = False
        t.join()


if __name__ == "__main__":
    """TODO."""
    time_limit = 3.0

    threads = [SerialControllerMon(), StorageController(filepath='test'), SerialControllerMcu()]

    startThreads(threads)

    timer = Timer()
    while timer.get_elapsed_time() < time_limit:
        pass

    stopThreads(threads)

