"""TODO."""

from timer                  import Timer
from serial_adapter         import SerialAdapter
from exception_handler      import ExceptionHandler
from filestorage_adapter    import FileStorageAdapter


FILEPATH            = 'readings.txt'
PORT_MON            = '/dev/ttyS26'
PORT_MCU            = '/dev/ttyS22'
BAUDRATE            = 115200
START_MON_CMD       = 'C'
PAUSE_MON_CMD       = 'p'
STOP_MON_CMD        = 'c'
SUSPEND_MCU_CMD     = 'S'
UNSUSPEND_MCU_CMD   = 's'
RESET_MCU_CMD       = 'R'
SHUT_ON_MCU_CMD     = 'C'
SHUT_OFF_MCU_CMD    = 'c'
LEDFLASH_MCU_CMD    = 'TL'


class StorageController:
    """TODO."""

    fileStorageAdapter      = None
    serialMonAdapter        = None
    serialMcuAdapter        = None
    timer                   = None


    def __init__(self):
        """TODO."""
        self.serialMonAdapter   = SerialAdapter(PORT_MON, BAUDRATE)
        self.serialMcuAdapter   = SerialAdapter(PORT_MCU, BAUDRATE)
        self.fileStorageAdapter = FileStorageAdapter()
        self.timer              = Timer()
        self.serialMonAdapter.openSerial()
        self.serialMcuAdapter.openSerial()
        self.fileStorageAdapter.openFile(FILEPATH)
    

    def storeSerialDataInFile(self, time_limit):
        """TODO."""
        try:
            self.serialMonAdapter.writeToSerial(START_MON_CMD)
            self.timer.reset_timer()
            self.serialMcuAdapter.writeToSerial(LEDFLASH_MCU_CMD)
            while self.timer.get_elapsed_time() < time_limit:
                # print("Elapsed: %f") % self.timer.get_elapsed_time()
                # print("Time to run: %f") % (time_limit - self.timer.get_elapsed_time())
                self.fileStorageAdapter.writeToOpenFile(
                                                       self.serialMonAdapter.readFromSerialWithDelay(0.0)
                                                       )
                #print( self.serialMonAdapter.readFromSerialWithDelay(0.0))
        except KeyboardInterrupt:
            print("Keyboard interrupt in controller")
        finally:
            self.serialMonAdapter.writeToSerial(PAUSE_MON_CMD)
            self.fileStorageAdapter.closeFile()
            self.serialMonAdapter.closeSerial()


if __name__ == "__main__":
    s = StorageController()
    s.storeSerialDataInFile(1.0)


