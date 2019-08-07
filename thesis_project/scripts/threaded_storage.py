#!/usr/bin/env python
"""TODO."""""

import Queue
import threading
from timer               import Timer
from serial_adapter      import SerialAdapter
from exception_handler   import ExceptionHandler
from filestorage_adapter import FileStorageAdapter

BUF_SIZE = 2048
queue = Queue.Queue(BUF_SIZE)

FOLDERPATH              = 'meas/'
PORT_MON                = 'COM26' #'/dev/ttyS26'
PORT_MCU                = 'COM22' #'/dev/ttyS22'
BAUDRATE                = 115200
SLEEP_BETWEEN_MCU_CMDS  = 0.01
START_MON_CMD           = 'C'
PAUSE_MON_CMD           = 'p'
STOP_MON_CMD            = 'q'
SUSPEND_FPGA_CMD        = 'S'
UNSUSPEND_FPGA_CMD      = 's'
RESET_FPGA_CMD          = 'R'
SHUT_ON_FPGA_CMD        = 'C'
SHUT_OFF_FPGA_CMD       = 'c'
TESTMODE_FPGA_CMD       = 'T'
LEDFLASH_FPGA_CMD       = 'L'



class SerialControllerMcu(threading.Thread):
    """TODO."""

    serialAdapter = None
    data = None
    flag = None

    def __init__(self, group=None, target='SerialControllerMcu', name='SerialMcuThread', args=(), kwargs=None, verbose=None, port=PORT_MCU, baudrate=BAUDRATE, data=TESTMODE_FPGA_CMD):
        """TODO."""
        super(SerialControllerMcu, self).__init__()
        self.target = target
        self.name = name
        self.serialAdapter = SerialAdapter(port=port, baudrate=baudrate)
        self.data = data
        self.flag = True


    # Set data2 = None to transmit only one cmd
    def run(self):
        """TODO."""
        self.serialAdapter.openSerial()
        # Check if data is a list and send data in loop if
        if isinstance(self.data, list):
            for d in self.data:
                self.serialAdapter.serialSleep(SLEEP_BETWEEN_MCU_CMDS)
                self.serialAdapter.writeToSerial(d)
        else:
            self.serialAdapter.writeToSerial(self.data)
        # Print incoming data
        while self.flag:
            if self.serialAdapter.getBytesInWaiting() != 0:
                print(self.serialAdapter.readFromSerialWithDelay())
        self.serialAdapter.closeSerial()

class SerialControllerMon(threading.Thread):
    """TODO."""

    serialAdapterMon = None
    timer = None
    flag = None
    data = None

    def __init__(self, group=None, target='SerialControllerMon', name='SerialMonThread', args=(), kwargs=None, verbose=None, port=PORT_MON, baudrate=BAUDRATE, data=START_MON_CMD):
        """TODO."""
        super(SerialControllerMon, self).__init__()
        self.target = target
        self.name = name
        self.serialAdapterMon = SerialAdapter(port=port, baudrate=baudrate)
        self.flag = True
        self.data = data


    def run(self):
        """TODO."""
        self.serialAdapterMon.openSerial()
        # Check if data is a list and send data in loop if
        if isinstance(self.data, list):
            for d in self.data:
                self.serialAdapterMon.serialSleep(SLEEP_BETWEEN_MCU_CMDS)
                self.serialAdapterMon.writeToSerial(d)
        else:
            self.serialAdapterMon.writeToSerial(self.data)
        # Push incoming data to queue
        while self.flag:
            if not queue.full() & self.serialAdapterMon.getBytesInWaiting() != 0:
                queue.put(self.serialAdapterMon.readFromSerialWithDelay(None))
            else:
                print("Queue full or no bytes in waiting!")
        # Finally pause monitoring on platform
        self.serialAdapterMon.writeToSerial(PAUSE_MON_CMD)
        self.serialAdapterMon.closeSerial()


class StorageController(threading.Thread):
    """TODO."""

    fileStorageAdapter = None
    path = None
    flag = None

    
    def __init__(self, group=None, target='StorageController', name='StorageThread', args=(), kwargs=None, verbose=None, folderpath=FOLDERPATH, filepath=None):
        """TODO."""
        super(StorageController, self).__init__()
        self.target = target
        self.name = name
        self.fileStorageAdapter = FileStorageAdapter()
        self.fileStorageAdapter.createFolder(folderpath)
        self.fileStorageAdapter.createFolder(folderpath + '/plot')
        if not filepath is None:
            self.path = folderpath + filepath +'.txt'
        self.flag = True


    def run(self):
        """TODO."""
        if not self.path is None:
            self.fileStorageAdapter.openFile(self.path)
            while self.flag:
                if not queue.empty():
                    self.fileStorageAdapter.writeToOpenFile(queue.get())
            self.fileStorageAdapter.closeFile()

def startThreads(threadlst):
    """TODO."""
    for t in threadlst:
        t.start()

def stopThreads(threadlst):
    """TODO."""
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

