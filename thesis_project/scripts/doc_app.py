#!/usr/bin/env python
"""TODO."""

import threaded_storage  as ts
from timer               import Timer
from meas_processor      import MeasProcessor

FOLDERPATH              = 'meas/resetFPGA/'
FILEPATH                = '400Hz20mV3s'
PORT_MON                =  'COM26'#'/dev/ttyS26'#
PORT_MCU                =  'COM22'#'/dev/ttyS22'#
BAUDRATE                = 115200

START_MON_USB           = 'U' 
START_MON_FPGA          = 'F'
START_MON_WIREL         = 'W'
PAUSE_MON_CMD           = 'p'
STOP_MON_CMD            = 'q'

SUSPEND_FPGA_CMD        = 'S'
UNSUSPEND_FPGA_CMD      = 's'
RESET_FPGA_CMD          = 'R'
SHUT_ON_FPGA_CMD        = 'C'
SHUT_OFF_FPGA_CMD       = 'c'
TESTMODE_FPGA_CMD       = 'T'
LEDFLASH_FPGA_CMD       = 'L'


if __name__ == "__main__":
    time_limit = 3.0
    mcu_data = [TESTMODE_FPGA_CMD, LEDFLASH_FPGA_CMD]
    mcu_data = RESET_FPGA_CMD
    scmcu = ts.SerialControllerMcu(port=PORT_MCU, baudrate=BAUDRATE, data=mcu_data)
    sc = ts.StorageController(folderpath=FOLDERPATH, filepath=FILEPATH)
    scmon = ts.SerialControllerMon(port=PORT_MON, baudrate=BAUDRATE, data=START_MON_USB)

    threads = [scmon, sc, scmcu]
    # threads = [scmon, sc]
    ts.startThreads(threads)
    timer = Timer()
    while timer.get_elapsed_time() < time_limit:
        pass
    ts.stopThreads(threads)

    mp = MeasProcessor(folderpath=FOLDERPATH, filepath=FILEPATH, meas_id='1', meas_time=time_limit, plotoverlay=4, showplot=False)
    mp.processFileByLine()