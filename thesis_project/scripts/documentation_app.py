#!/usr/bin/env python
"""TODO."""

import threaded_storage as ts
from timer               import Timer
from meas_processor      import MeasProcessor

if __name__ == "__main__":
    time_limit = 3.0
    folderpath = '/meas'
    filepath = 'dings'

    threads = [ts.SerialControllerMon(), ts.StorageController(filepath=filepath), ts.SerialControllerMcu()]

    ts.startThreads(threads)

    timer = Timer()
    while timer.get_elapsed_time() < time_limit:
        pass

    ts.stopThreads(threads)

    mp = MeasProcessor(filepath=filepath, meas_id="TEST_MEAS", meas_time=time_limit)
    mp.processFileByLine()