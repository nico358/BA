"""TODO."""

import threading
import Queue
from serial_adapter import SerialAdapter
from exception_handler import ExceptionHandler
from filestorage_adapter import FileStorageAdapter

BUF_SIZE = 128
queue = Queue.Queue(BUF_SIZE)

class SerialController(threading.Thread):
    """TODO."""

    serialAdapter = None
    data = None

    def __init__(self, group=None, target='SerialController', name='SerialThread', args=(), kwargs=None, verbose=None, port='/dev/ttyS26', baudrate=9600, data='M'):
        """TODO."""
        super(SerialController, self).__init__()
        self.target = target
        self.name = name
        self.serialAdapter = SerialAdapter(port=port, baudrate=baudrate)
        self.data = data


    def run(self):
        """TODO."""
        self.serialAdapter.openSerial()
        self.serialAdapter.writeToSerial(self.data)
        while True:
            if not queue.full():
                queue.put(self.serialAdapter.readFromSerialWithDelay(secondsDelay=0))
        #self.serialAdapter.closeSerial()


class StorageController(threading.Thread):
    """TODO."""

    fileStorageAdapter = None
    path = None
    
    def __init__(self, group=None, target='StorageController', name='StorageThread', args=(), kwargs=None, verbose=None, filepath='readings.txt'):
        """TODO."""
        super(StorageController, self).__init__()
        self.target = target
        self.name = name
        fileStorageAdapter = FileStorageAdapter()
        self.path = filepath


    def run(self):
        """TODO."""
        fileStorageAdapter.openFile(self.path)
        while True:
            if not queue.empty:
                self.fileStorageAdapter.writeToOpenFile(queue.get())
        #self.fileStorageAdapter.closeFile()


if __name__ == "__main__":
    """TODO."""
    sc = SerialController()
    stc = StorageController()
    sc.start()
    stc.start()

