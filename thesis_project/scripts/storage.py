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
SUSPEND_FPGA_CMD    = 'S'
UNSUSPEND_FPGA_CMD  = 's'
RESET_FPGA_CMD      = 'R'
SHUT_ON_FPGA_CMD    = 'C'
SHUT_OFF_FPGA_CMD   = 'c'
TESTMODE_FPGA_CMD   = 'T'
LEDFLASH_FPGA_CMD   = 'L'


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
            self.serialMcuAdapter.writeToSerial(TESTMODE_FPGA_CMD)
            self.serialMcuAdapter.serialSleep(0.01)
            self.timer.reset_timer()
            self.serialMcuAdapter.writeToSerial(LEDFLASH_FPGA_CMD)
            
            while self.timer.get_elapsed_time() < time_limit:
                self.fileStorageAdapter.writeToOpenFile(
                                                       self.serialMonAdapter.readFromSerialWithDelay()
                                                       )
                if self.serialMcuAdapter.getBytesInWaiting() != 0:
                    print(self.serialMcuAdapter.readFromSerialWithDelay())
        except KeyboardInterrupt:
            print("Keyboard interrupt in controller")
        finally:
            self.serialMonAdapter.writeToSerial(PAUSE_MON_CMD)
            self.fileStorageAdapter.closeFile()
            self.serialMonAdapter.closeSerial()
            self.serialMcuAdapter.closeSerial()


if __name__ == "__main__":
    s = StorageController()
    s.storeSerialDataInFile(3.0)


