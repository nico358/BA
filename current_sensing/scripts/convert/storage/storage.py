""" This module sequentially controls two MCUs on the Elastic Node and stores received data in a file.
    Therefore, serial connections are stablished and subsequently control signals are send to the MCUs.
    The controller MCU causes the FPGA on the Node to change its state while the monitor MCU sends
    readings of the current sensors to the host. The data send by the monitor MCU is stored in
    a file. A timer stops the monitoring after a desired time.
"""

from adapter.timer.timer            import Timer
from adapter.serial_adapter         import SerialAdapter
from adapter.exception_handler      import ExceptionHandler
from adapter.filestorage_adapter    import FileStorageAdapter

# Filepath for the data to be stored
FILEPATH            = 'meas/FPGA@400Hz20mV.txt'
# Serial connection parameters
PORT_MON            = '/dev/ttyS26' # Serial port for monitor MCU
PORT_MCU            = '/dev/ttyS22' # Serial port for controller MCU
BAUDRATE            = 115200
# Control signals to the monitor MCU
START_MON_CMD       = 'A'
PAUSE_MON_CMD       = 'p'
STOP_MON_CMD        = 'q'
# Control signals to the controller MCU
SUSPEND_FPGA_CMD    = 'S'
UNSUSPEND_FPGA_CMD  = 's'
RESET_FPGA_CMD      = 'R'
SHUT_ON_FPGA_CMD    = 'C'
SHUT_OFF_FPGA_CMD   = 'c'
TESTMODE_FPGA_CMD   = 'T'
LEDFLASH_FPGA_CMD   = 'L'


class StorageController:
    """ The class creates two instances of serial connection adapters and
        a file writer by calling the constructor. The storeSerialDataInFile
        method initializes a monitoring process that writes data, received
        by a serial connection, into a file.
    """

    # Adapter instances
    fileStorageAdapter      = None
    serialMonAdapter        = None
    serialMcuAdapter        = None
    # Timer instance
    timer                   = None


    def __init__(self):
        """ The constructor creates the adapter instances and establishes
            serial connections and an open file. A timer instance is created
            that stops the read/write process.
        """
        self.serialMonAdapter   = SerialAdapter(PORT_MON, BAUDRATE)
        self.serialMcuAdapter   = SerialAdapter(PORT_MCU, BAUDRATE)
        self.fileStorageAdapter = FileStorageAdapter()
        self.timer              = Timer()
        self.serialMonAdapter.openSerial()
        self.serialMcuAdapter.openSerial()
        self.fileStorageAdapter.openFile(FILEPATH)

    def storeSerialDataInFile(self, time_limit):
        """ This method executes the read/write process. The data
            is written to the controller MCU and then the monitoring
            process is awaked. The data send by the monitor MCU is
            alternating received and written to a file.
        """
        try:
            # Switch FPGA's state
            self.serialMcuAdapter.writeToSerial(TESTMODE_FPGA_CMD)
            self.serialMcuAdapter.serialSleep(0.01)
            # Start timer
            self.timer.reset_timer()
            # Start monitoring
            self.serialMonAdapter.writeToSerial(START_MON_CMD)
            # Cause FPGA to flash LEDs
            self.serialMcuAdapter.writeToSerial(LEDFLASH_FPGA_CMD)
            # Receive data and write it to open file, stop when time elapsed
            while self.timer.get_elapsed_time() < time_limit:
                t0 = self.timer.get_elapsed_time()
                self.fileStorageAdapter.writeToOpenFile(
                                                       self.serialMonAdapter.readFromSerialWithDelay()
                                                       )                             
        except KeyboardInterrupt:
            print("Keyboard interrupt in storage")
        finally:
            # Stop all
            self.serialMonAdapter.writeToSerial(PAUSE_MON_CMD)
            self.fileStorageAdapter.closeFile()
            self.serialMonAdapter.closeSerial()
            self.serialMcuAdapter.closeSerial()


if __name__ == "__main__":
    s = StorageController()
    s.storeSerialDataInFile(2.0)


