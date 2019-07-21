"""TODO."""

import Queue
import threading
from timer               import Timer
from serial_adapter      import SerialAdapter
from meas_processor      import MeasProcessor
from exception_handler   import ExceptionHandler
from filestorage_adapter import FileStorageAdapter

BUF_SIZE = 2048
queue = Queue.Queue(BUF_SIZE)
flag = True

FILEPATH            = 'meas/FPGA@400Hz20mV.txt'
PORT_MON            = '/dev/ttyS26'
PORT_MCU            = '/dev/ttyS22'
BAUDRATE            = 115200
START_MON_CMD       = 'C'
PAUSE_MON_CMD       = 'p'
STOP_MON_CMD        = 'q'
SUSPEND_FPGA_CMD    = 'S'
UNSUSPEND_FPGA_CMD  = 's'
RESET_FPGA_CMD      = 'R'
SHUT_ON_FPGA_CMD    = 'C'
SHUT_OFF_FPGA_CMD   = 'c'
TESTMODE_FPGA_CMD   = 'T'
LEDFLASH_FPGA_CMD   = 'L'



class SerialControllerMcu(threading.Thread):
    """TODO."""

    serialAdapter = None
    data = None

    def __init__(self, group=None, target='SerialControllerMcu', name='SerialMcuThread', args=(), kwargs=None, verbose=None, port='/dev/ttyS22', baudrate=115200, data='T'):
        """TODO."""
        super(SerialControllerMcu, self).__init__()
        self.target = target
        self.name = name
        self.serialAdapter = SerialAdapter(port=port, baudrate=baudrate)
        self.data = data


    def run(self):
        """TODO."""
        self.serialAdapter.openSerial()
        self.serialAdapter.writeToSerial(TESTMODE_FPGA_CMD)
        self.serialAdapter.serialSleep(0.01)
        self.serialAdapter.writeToSerial(LEDFLASH_FPGA_CMD)
        while flag:
            if self.serialAdapter.getBytesInWaiting() != 0:
                print(self.serialAdapter.readFromSerialWithDelay())
        self.serialAdapter.closeSerial()

class SerialControllerMon(threading.Thread):
    """TODO."""

    serialAdapterMon = None
    data = None
    timer = None

    def __init__(self, group=None, target='SerialControllerMon', name='SerialMonThread', args=(), kwargs=None, verbose=None, port='/dev/ttyS26', baudrate=115200, data='C'):
        """TODO."""
        super(SerialControllerMon, self).__init__()
        self.target = target
        self.name = name
        self.serialAdapterMon = SerialAdapter(port=port, baudrate=baudrate)
        self.data = data


    def run(self):
        """TODO."""
        self.serialAdapterMon.openSerial()
        self.serialAdapterMon.writeToSerial(START_MON_CMD)
        while flag:
            if not queue.full() & self.serialAdapterMon.getBytesInWaiting() != 0:
                queue.put(self.serialAdapterMon.readFromSerialWithDelay(secondsDelay=0))
            else:
                print("Queue full!!!")
        self.serialAdapterMon.writeToSerial(PAUSE_MON_CMD)
        self.serialAdapterMon.closeSerial()


class StorageController(threading.Thread):
    """TODO."""

    fileStorageAdapter = None
    path = None
    
    def __init__(self, group=None, target='StorageController', name='StorageThread', args=(), kwargs=None, verbose=None, filepath='meas/FPGA@400Hz20mV.txt'):
        """TODO."""
        super(StorageController, self).__init__()
        self.target = target
        self.name = name
        self.fileStorageAdapter = FileStorageAdapter()
        self.path = filepath


    def run(self):
        """TODO."""
        self.fileStorageAdapter.openFile(FILEPATH)
        while flag:
            if not queue.empty():
                self.fileStorageAdapter.writeToOpenFile(queue.get())
        self.fileStorageAdapter.closeFile()


if __name__ == "__main__":
    """TODO."""
    time_limit = 3.0

    scmon = SerialControllerMon()
    stc = StorageController()
    scmcu = SerialControllerMcu()

    scmon.start()
    stc.start()
    scmcu.start()

    timer = Timer()
    while timer.get_elapsed_time() < time_limit:
        pass
    flag = False
    timer.timerSleep(0.01)

    scmon._Thread__stop()
    stc._Thread__stop()
    scmcu._Thread__stop()

    mp = MeasProcessor('meas/FPGA@400Hz20mV.txt', "TEST_MEAS")
    mp.processFileByLine()


