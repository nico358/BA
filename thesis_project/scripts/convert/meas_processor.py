#!/usr/bin/env python
"""TODO."""

import sys
from datetime import datetime
from meas_plotter import MeasPlotter
from storage.adapter.filestorage_adapter import FileStorageAdapter
from storage.adapter.exception_handler import ExceptionHandler


LIST_INDEX_META    = 0
LIST_INDEX_CURRENT = 1
LIST_INDEX_VOLTAGE = 2
LIST_INDEX_POWER   = 3
MEAS_FORMAT        = 'float'

CNTR_DELIMIT        = '\''
REC_BEGIN_DELIMIT   = '{'
REC_END_DELIMIT     = '}'
VAL_BEGIN_DELIMIT   = '['
VAL_END_DELIMIT     = ']'
SPACE               = ' '

CNTR_INDEX          = 0
CH1_NAME_INDEX      = 1
CH1_CURRENT_INDEX   = 2
CH1_VOLTAGE_INDEX   = 3
CH1_POWER_INDEX     = 4
CH2_NAME_INDEX      = 5
CH2_CURRENT_INDEX   = 6
CH2_VOLTAGE_INDEX   = 7
CH2_POWER_INDEX     = 8

class MeasProcessor:
    """TODO."""

    meas_id         = None#
    meas_time       = None#
    meas_timestamp  = None#
    tmp_meas_ch1    = None#
    tmp_meas_ch2    = None#
    name_ch1        = None#
    name_ch2        = None#
    folderpath      = None
    filepath        = None#
    overlay         = None
    show            = None


    def __init__(self, folderpath='meas/', filepath=None, meas_id=None, meas_time=None, plotoverlay=False, showplot=False):
        """TODO."""
        self.tmp_meas_ch1 = [[], [], [], []]
        self.tmp_meas_ch2 = [[], [], [], []]
        self.meas_id = meas_id
        self.meas_time = meas_time
        self.meas_timestamp = datetime.now().strftime("%m-%d-%Y-%H-%M-%S")
        self.filepath = filepath
        self.folderpath = folderpath
        self.overlay = plotoverlay
        self.show = showplot

    def plotFormattedDataToPngFile(self, overlay):
        """TODO."""
        filepath_ch1 = self.formatFilepath(self.name_ch1)
        filepath_ch2 = self.formatFilepath(self.name_ch2)
        plotter = MeasPlotter(meas_ch1=self.tmp_meas_ch1, meas_ch2=self.tmp_meas_ch2, folderpath=self.folderpath, filepath1=filepath_ch1, filepath2=filepath_ch2, show=self.show, meas_time=self.meas_time)
        plotter.plotAll(overlay)

    def writeFormattedDataToTxtFile(self, tmp_meas_ch, ch_name):
        """TODO."""
        filewriter = FileStorageAdapter()
        filepath_ch = self.folderpath + self.formatFilepath(ch_name) + '.txt'
        filewriter.openFile(filepath_ch, 'w+')
        for row in tmp_meas_ch:
            for elem in row:
                filewriter.writeToOpenFile(str(elem))
        filewriter.closeFile()

    def formatFilepath(self, ch_name):
        """TODO."""
        pathstr = self.filepath + '_'
        pathstr += ch_name + '_'
        pathstr += self.meas_timestamp
        return pathstr

    def processFileByLine(self):
        """TODO."""
        if not self.filepath is None:
            # Assemble measurement location
            path = self.folderpath + self.filepath + '.txt'
            try:
                # Readin of multiple sensor measurements from one file not supported
                with open (path, "r") as reader:
                    if reader.mode == 'r':
                        # Set matadata and measurement header
                        self.appendHead()
                        reader.readline()
                        line = reader.readline()
                        while(line):
                            # Split incoming line
                            splinter = self.splitStr("{}".format(line.replace('\r\n', '')))
                            # Set metadata ch1 at first loop
                            if len(self.tmp_meas_ch1[LIST_INDEX_META]) == 1:
                                self.name_ch1 = splinter[CH1_NAME_INDEX]
                                self.setMetaCh1()
                            # Set metadata ch2 at first loop
                            if len(self.tmp_meas_ch2[LIST_INDEX_META]) == 1:
                                self.name_ch2 = splinter[CH2_NAME_INDEX]
                                self.setMetaCh2()
                            # Append measurements, must be 9 values, drop incomplete 
                            if len(splinter) == 9:
                                self.setListValues(splinter)
                            # Read next incoming line
                            line = reader.readline()
                        # Set matadata and measurement footer
                        self.appendFoot()
            except (ValueError, OSError, IOError) as e:
                ExceptionHandler(e, "processFileByLine")
            # Finally store formatted data
            self.writeFormattedDataToTxtFile(self.tmp_meas_ch1, self.name_ch1)
            self.writeFormattedDataToTxtFile(self.tmp_meas_ch2, self.name_ch2)
            # Plot formatted data
            self.plotFormattedDataToPngFile(self.overlay)

    def splitStr(self, strg):
        """TODO."""
        return strg.split(' ')

    def setListValues(self, splinter):
        """TODO."""
        self.tmp_meas_ch1[LIST_INDEX_CURRENT].append(CNTR_DELIMIT + splinter[CNTR_INDEX] + CNTR_DELIMIT)
        self.tmp_meas_ch1[LIST_INDEX_CURRENT].append(float(splinter[CH1_CURRENT_INDEX]))
        self.tmp_meas_ch1[LIST_INDEX_VOLTAGE].append(CNTR_DELIMIT + splinter[CNTR_INDEX] + CNTR_DELIMIT)
        self.tmp_meas_ch1[LIST_INDEX_VOLTAGE].append(float(splinter[CH1_VOLTAGE_INDEX]))
        self.tmp_meas_ch1[LIST_INDEX_POWER].append(CNTR_DELIMIT + splinter[CNTR_INDEX] + CNTR_DELIMIT)
        self.tmp_meas_ch1[LIST_INDEX_POWER].append(float(splinter[CH1_POWER_INDEX]))

        self.tmp_meas_ch2[LIST_INDEX_CURRENT].append(CNTR_DELIMIT + splinter[CNTR_INDEX] + CNTR_DELIMIT)
        self.tmp_meas_ch2[LIST_INDEX_CURRENT].append(float(splinter[CH2_CURRENT_INDEX]))
        self.tmp_meas_ch2[LIST_INDEX_VOLTAGE].append(CNTR_DELIMIT + splinter[CNTR_INDEX] + CNTR_DELIMIT)
        self.tmp_meas_ch2[LIST_INDEX_VOLTAGE].append(float(splinter[CH2_VOLTAGE_INDEX]))
        self.tmp_meas_ch2[LIST_INDEX_POWER].append(CNTR_DELIMIT + splinter[CNTR_INDEX] + CNTR_DELIMIT)
        self.tmp_meas_ch2[LIST_INDEX_POWER].append(float(splinter[CH2_POWER_INDEX]))

    def setMetaCh1(self):
        """TODO."""
        self.tmp_meas_ch1[LIST_INDEX_META].append(self.name_ch1)
        self.tmp_meas_ch1[LIST_INDEX_META].append(SPACE)
        self.tmp_meas_ch1[LIST_INDEX_META].append(self.meas_id)
        self.tmp_meas_ch1[LIST_INDEX_META].append(SPACE)
        self.tmp_meas_ch1[LIST_INDEX_META].append(self.meas_timestamp)
        self.tmp_meas_ch1[LIST_INDEX_META].append(SPACE)
        self.tmp_meas_ch1[LIST_INDEX_META].append(MEAS_FORMAT)
        self.tmp_meas_ch1[LIST_INDEX_META].append(SPACE)

    def setMetaCh2(self):
        """TODO."""
        self.tmp_meas_ch2[LIST_INDEX_META].append(self.name_ch2)
        self.tmp_meas_ch2[LIST_INDEX_META].append(SPACE)
        self.tmp_meas_ch2[LIST_INDEX_META].append(self.meas_id)
        self.tmp_meas_ch2[LIST_INDEX_META].append(SPACE)
        self.tmp_meas_ch2[LIST_INDEX_META].append(self.meas_timestamp)
        self.tmp_meas_ch2[LIST_INDEX_META].append(SPACE)
        self.tmp_meas_ch2[LIST_INDEX_META].append(MEAS_FORMAT)
        self.tmp_meas_ch2[LIST_INDEX_META].append(SPACE)

    def appendHead(self):
        """TODO."""
        # Append record header
        self.tmp_meas_ch1[LIST_INDEX_META].append(REC_BEGIN_DELIMIT)
        self.tmp_meas_ch2[LIST_INDEX_META].append(REC_BEGIN_DELIMIT)
        # Append ch1 meas header
        self.tmp_meas_ch1[LIST_INDEX_CURRENT].append('current')
        self.tmp_meas_ch1[LIST_INDEX_CURRENT].append(VAL_BEGIN_DELIMIT)
        self.tmp_meas_ch1[LIST_INDEX_VOLTAGE].append('voltage')
        self.tmp_meas_ch1[LIST_INDEX_VOLTAGE].append(VAL_BEGIN_DELIMIT)
        self.tmp_meas_ch1[LIST_INDEX_POWER].append('power')
        self.tmp_meas_ch1[LIST_INDEX_POWER].append(VAL_BEGIN_DELIMIT)
        # Append ch2 meas header
        self.tmp_meas_ch2[LIST_INDEX_CURRENT].append('current')
        self.tmp_meas_ch2[LIST_INDEX_CURRENT].append(VAL_BEGIN_DELIMIT)
        self.tmp_meas_ch2[LIST_INDEX_VOLTAGE].append('voltage')
        self.tmp_meas_ch2[LIST_INDEX_VOLTAGE].append(VAL_BEGIN_DELIMIT)
        self.tmp_meas_ch2[LIST_INDEX_POWER].append('power')
        self.tmp_meas_ch2[LIST_INDEX_POWER].append(VAL_BEGIN_DELIMIT)

    def appendFoot(self):
        """TODO."""
        # Append meas footer
        self.tmp_meas_ch1[LIST_INDEX_CURRENT].append(VAL_END_DELIMIT)
        self.tmp_meas_ch1[LIST_INDEX_VOLTAGE].append(VAL_END_DELIMIT)
        self.tmp_meas_ch1[LIST_INDEX_POWER].append(VAL_END_DELIMIT)
        self.tmp_meas_ch2[LIST_INDEX_CURRENT].append(VAL_END_DELIMIT)
        self.tmp_meas_ch2[LIST_INDEX_VOLTAGE].append(VAL_END_DELIMIT)
        self.tmp_meas_ch2[LIST_INDEX_POWER].append(VAL_END_DELIMIT)
        # Append record footer
        self.tmp_meas_ch1[LIST_INDEX_POWER].append(REC_END_DELIMIT)
        self.tmp_meas_ch2[LIST_INDEX_POWER].append(REC_END_DELIMIT)




if __name__ == "__main__":
    mp = MeasProcessor(filepath='test', meas_id="TEST_MEAS", meas_time=3, overlay=False)
    mp.processFileByLine()

    