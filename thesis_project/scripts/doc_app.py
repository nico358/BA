#!/usr/bin/env python

""" This module is the top of the current measurement documentation
    all other modules contained in the script folder are utilized here.
    The main method starts the threads that communicate with
    each MCU on the embedded board and save the received data.
    The scmcu thread controls the MCU, which causes the FPGA to switch
    its state. The scmon activates the measurement function
    on the monitor MCU and receives the data. The third thread saves this.
"""

import convert.storage.threaded_storage     as ts
from convert.storage.adapter.timer.timer    import Timer
from convert.meas_processor                 import MeasProcessor

# Define the path where the data is stored and the communication parameters.
FOLDERPATH              = 'meas/unsuspendFPGA/' # Folder to store the measurement
FILEPATH                = '400Hz40&10mV1s' # File to store the measurement
PORT_MON                =  'COM26' # COM port monitor MCU 'ttyS26' #
PORT_MCU                =  'COM22' # COM port controller MCU
BAUDRATE                = 115200
# The signals controlling the monitor MCU
START_MONITOR_ALL       = 'A'
START_MON_USB           = 'U'
START_MON_FPGA          = 'F'
START_MON_WIREL         = 'W'
PAUSE_MON_CMD           = 'p'
STOP_MON_CMD            = 'q'
# The signals to the MCU that controls the FPGA.
SUSPEND_FPGA_CMD        = 'S'
UNSUSPEND_FPGA_CMD      = 's'
RESET_FPGA_CMD          = 'R'
SHUT_ON_FPGA_CMD        = 'C'
SHUT_OFF_FPGA_CMD       = 'c'
TESTMODE_FPGA_CMD       = 'T'
LEDFLASH_FPGA_CMD       = 'L'
# Specifies the layout of the plot
PLOT_SUBPLOTS           = 2
PLOT_ALL_IN_ONE         = 1
PLOT_BOTH               = 3

def formatData():
    """ The stored data is processed within this method.
        The parameters affect the layout of the result.
        The paths and time limit are mandatory parameters
        as they tell the module where the data is to be
        stored and which time period underlies the plot.
    """
    # Instanciate class object, 'plotoverlay' can be assigned to 1 (three subplots in a single frame) 
    # and 2 (draw all graphs in one plot) or 3 (plot both layouts)
    mp = MeasProcessor(folderpath=FOLDERPATH, filepath=FILEPATH, meas_id='1', meas_time=time_limit, plotoverlay=PLOT_SUBPLOTS, showplot=False)
    # Execute data processing
    mp.processFileByLine()


if __name__ == "__main__":
    # Set time limit for monitoring
    time_limit = 2
    # Set desired control signal
    # mcu_data = [TESTMODE_FPGA_CMD, LEDFLASH_FPGA_CMD]
    mcu_data = UNSUSPEND_FPGA_CMD
    # mcu_data = SUSPEND_FPGA_CMD
    # mcu_data = RESET_FPGA_CMD
    # mcu_data = SHUT_ON_FPGA_CMD
    # mcu_data = SHUT_OFF_FPGA_CMD

    # Execute the process one ore more times
    for i in range(1):
        # Instanciate the threads and provide control signals
        scmcu = ts.SerialControllerMcu(port=PORT_MCU, baudrate=BAUDRATE, data=mcu_data)
        sc = ts.StorageController(folderpath=FOLDERPATH, filepath=FILEPATH)
        scmon = ts.SerialControllerMon(port=PORT_MON, baudrate=BAUDRATE, data=START_MON_FPGA)
        # List for thread start method
        # threads = [scmon, sc, scmcu]
        threads = [scmon, sc]
        # Start all threads
        ts.startThreads(threads)
        # Start timer
        timer = Timer()
        timer.timerSleep(0.2)
        scmcu.start()
        # Check if time limit is reached and stop threads
        while timer.get_elapsed_time() < time_limit:
            pass

        ts.stopThreads(threads)
        scmcu.flag = False
        scmcu.join()

        # Comment out the method call in order to just store the received data without formatting
        formatData()

        # Set sleep period between loops
        # timer.timerSleep(2)
