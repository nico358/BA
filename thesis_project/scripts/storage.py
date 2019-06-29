"""TODO."""

from serial_adapter import SerialAdapter
from exception_handler import ExceptionHandler
from filestorage_adapter import FileStorageAdapter


class StorageController:
    """TODO."""

    serialAdapter = None
    fileStorageAdapter = None


    def __init__(self, port, baudrate):
        """TODO."""
        self.serialAdapter = SerialAdapter(port, baudrate)
        self.fileStorageAdapter = FileStorageAdapter()
    

    def storeSerialDataInFile(self):
        """TODO."""
        self.serialAdapter.openSerial()
        self.fileStorageAdapter.openFile(path='readings.txt')
        try:

            while True:
                self.serialAdapter.writeToSerial('C')
                self.fileStorageAdapter.writeToOpenFile(
                                                        self.serialAdapter.readFromSerialWithDelay(0.1)
                                                        )
                # self.serialAdapter.serialSleep(0.5)
        except KeyboardInterrupt:
            self.serialAdapter.writeToSerial('p')
            print("Keyboard interrupt in controller")
        finally:
            self.serialAdapter.closeSerial()
            self.fileStorageAdapter.closeFile()

if __name__ == "__main__":
    s = StorageController(port='/dev/ttyS26', baudrate=9600)
    s.storeSerialDataInFile()


