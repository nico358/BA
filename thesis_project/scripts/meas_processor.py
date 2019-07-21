#!/usr/bin/env python
"""TODO."""

import sys
import datetime
import meas_defines as d
from exception_handler import ExceptionHandler
from filestorage_adapter import FileStorageAdapter

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
    meas_timestamp  = None#
    tmp_meas_ch1    = None#
    tmp_meas_ch2    = None#
    name_ch1        = None#
    name_ch2        = None#
    filepath        = None#
    filewriter      = None#


    def __init__(self, filepath, meas_id):
        """TODO."""
        self.tmp_meas_ch1 = [[], [], [], []]
        self.tmp_meas_ch2 = [[], [], [], []]
        self.meas_id = meas_id
        self.filepath = filepath
        self.meas_timestamp = datetime.datetime.now()

    def writeFormattedDataToTxtFile(self):
        """TODO."""
        self.filewriter = FileStorageAdapter()
        self.filewriter.openFile("{}".format(self.filepath.replace('.txt', '')) + '_' + self.name_ch1 + '_' + "{}".format("{}".format("{}".format(str(self.meas_timestamp).replace(' ', '-')).replace(':', '-')).replace('.', '-')) + '.txt', 'w+')
        for row in self.tmp_meas_ch1:
            for elem in row:
                self.filewriter.writeToOpenFile(str(elem)) 
        self.filewriter.closeFile()

        self.filewriter = FileStorageAdapter()
        self.filewriter.openFile("{}".format(self.filepath.replace('.txt', '')) + '_' + self.name_ch2 + '_' + "{}".format("{}".format("{}".format(str(self.meas_timestamp).replace(' ', '-')).replace(':', '-')).replace('.', '-')) + '.txt', 'w+')
        for row in self.tmp_meas_ch2:
            for elem in row:
                self.filewriter.writeToOpenFile(str(elem))
        self.filewriter.closeFile()

    def processFileByLine(self):
        """TODO."""
        try:
            with open (self.filepath, "r") as reader:
                if reader.mode == 'r':
                    self.appendHead()
                    line = reader.readline()                   
                    while(line):
                        splinter = self.splitStr("{}".format(line.replace('\r\n', '')))
                        if len(self.tmp_meas_ch1[LIST_INDEX_META]) == 1:
                            self.name_ch1 = splinter[CH1_NAME_INDEX]
                            self.setMetaCh1()

                        if len(self.tmp_meas_ch2[LIST_INDEX_META]) == 1:
                            self.name_ch2 = splinter[CH2_NAME_INDEX]
                            self.setMetaCh2()

                        if len(splinter) == 9:
                            self.setListValues(splinter)
                        else:
                            raise ValueError

                        line = reader.readline()

                    self.appendFoot()
        except (ValueError, OSError, IOError) as e:
            ExceptionHandler(e, "processFileByLine")

        self.writeFormattedDataToTxtFile()

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
        self.tmp_meas_ch1[LIST_INDEX_META].append(REC_BEGIN_DELIMIT)
        self.tmp_meas_ch2[LIST_INDEX_META].append(REC_BEGIN_DELIMIT)
        self.tmp_meas_ch1[LIST_INDEX_CURRENT].append('current' + VAL_BEGIN_DELIMIT)
        self.tmp_meas_ch1[LIST_INDEX_VOLTAGE].append('voltage' + VAL_BEGIN_DELIMIT)
        self.tmp_meas_ch1[LIST_INDEX_POWER].append('power' + VAL_BEGIN_DELIMIT)
        self.tmp_meas_ch2[LIST_INDEX_CURRENT].append('current' + VAL_BEGIN_DELIMIT)
        self.tmp_meas_ch2[LIST_INDEX_VOLTAGE].append('voltage' + VAL_BEGIN_DELIMIT)
        self.tmp_meas_ch2[LIST_INDEX_POWER].append('power' + VAL_BEGIN_DELIMIT)

    def appendFoot(self):
        """TODO."""
        self.tmp_meas_ch1[LIST_INDEX_CURRENT].append(VAL_END_DELIMIT)
        self.tmp_meas_ch1[LIST_INDEX_VOLTAGE].append(VAL_END_DELIMIT)
        self.tmp_meas_ch1[LIST_INDEX_POWER].append(VAL_END_DELIMIT)
        self.tmp_meas_ch2[LIST_INDEX_CURRENT].append(VAL_END_DELIMIT)
        self.tmp_meas_ch2[LIST_INDEX_VOLTAGE].append(VAL_END_DELIMIT)
        self.tmp_meas_ch2[LIST_INDEX_POWER].append(VAL_END_DELIMIT)
        self.tmp_meas_ch1[LIST_INDEX_POWER].append(REC_END_DELIMIT)
        self.tmp_meas_ch2[LIST_INDEX_POWER].append(REC_END_DELIMIT)


if __name__ == "__main__":
    mp = MeasProcessor('meas/test.txt', "TEST_MEAS")
    mp.processFileByLine()

    