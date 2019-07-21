#!/usr/bin/env python
"""TODO."""

import sys
import datetime
import meas_defines as d
from exception_handler import ExceptionHandler
from filestorage_adapter import FileStorageAdapter

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

    # def writeFormattedDataToBinFile(self):
    #     """TODO."""
    #     self.filewriter = FileStorageAdapter()
    #     self.filewriter.openFile("{}".format(self.filepath.replace('.txt', '')) + '_' + self.name_ch1 + '_' + "{}".format("{}".format("{}".format(str(self.meas_timestamp).replace(' ', '-')).replace(':', '-')).replace('.', '-')) + '.bin', 'w+b')
    #     for row in self.tmp_meas_ch2:
    #         for elem in row:
    #             self.filewriter.writeToOpenFile(bytearray(elem))
    #     self.filewriter.closeFile()

    # def readFormattedDataFromBinFile(self):
        # data = None
        # self.filewriter = FileStorageAdapter()
        # self.filewriter.openFile("meas/bin.bin", 'rb')
        # data = self.filewriter.readFromOpenFile()
        # self.filewriter.closeFile()
        # return data
 

    def processFileByLine(self):
        """TODO."""
        try:
            with open (self.filepath, "r") as reader:
                if reader.mode == 'r':
                    self.appendHead()
                    line = reader.readline()                   
                    while(line):
                        splinter = self.splitStr("{}".format(line.replace('\r\n', '')))
                        if len(self.tmp_meas_ch1[d.LIST_INDEX_META]) == 1:
                            self.name_ch1 = splinter[d.CH1_NAME_INDEX]
                            self.setMetaCh1()

                        if len(self.tmp_meas_ch2[d.LIST_INDEX_META]) == 1:
                            self.name_ch2 = splinter[d.CH2_NAME_INDEX]
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
        self.tmp_meas_ch1[d.LIST_INDEX_CURRENT].append(d.CNTR_DELIMIT + splinter[d.CNTR_INDEX] + d.CNTR_DELIMIT)
        self.tmp_meas_ch1[d.LIST_INDEX_CURRENT].append(float(splinter[d.CH1_CURRENT_INDEX]))
        self.tmp_meas_ch1[d.LIST_INDEX_VOLTAGE].append(d.CNTR_DELIMIT + splinter[d.CNTR_INDEX] + d.CNTR_DELIMIT)
        self.tmp_meas_ch1[d.LIST_INDEX_VOLTAGE].append(float(splinter[d.CH1_VOLTAGE_INDEX]))
        self.tmp_meas_ch1[d.LIST_INDEX_POWER].append(d.CNTR_DELIMIT + splinter[d.CNTR_INDEX] + d.CNTR_DELIMIT)
        self.tmp_meas_ch1[d.LIST_INDEX_POWER].append(float(splinter[d.CH1_POWER_INDEX]))

        self.tmp_meas_ch2[d.LIST_INDEX_CURRENT].append(d.CNTR_DELIMIT + splinter[d.CNTR_INDEX] + d.CNTR_DELIMIT)
        self.tmp_meas_ch2[d.LIST_INDEX_CURRENT].append(float(splinter[d.CH2_CURRENT_INDEX]))
        self.tmp_meas_ch2[d.LIST_INDEX_VOLTAGE].append(d.CNTR_DELIMIT + splinter[d.CNTR_INDEX] + d.CNTR_DELIMIT)
        self.tmp_meas_ch2[d.LIST_INDEX_VOLTAGE].append(float(splinter[d.CH2_VOLTAGE_INDEX]))
        self.tmp_meas_ch2[d.LIST_INDEX_POWER].append(d.CNTR_DELIMIT + splinter[d.CNTR_INDEX] + d.CNTR_DELIMIT)
        self.tmp_meas_ch2[d.LIST_INDEX_POWER].append(float(splinter[d.CH2_POWER_INDEX]))

    def setMetaCh1(self):
        """TODO."""
        self.tmp_meas_ch1[d.LIST_INDEX_META].append(self.name_ch1)
        self.tmp_meas_ch1[d.LIST_INDEX_META].append(d.SPACE)
        self.tmp_meas_ch1[d.LIST_INDEX_META].append(self.meas_id)
        self.tmp_meas_ch1[d.LIST_INDEX_META].append(d.SPACE)
        self.tmp_meas_ch1[d.LIST_INDEX_META].append(self.meas_timestamp)
        self.tmp_meas_ch1[d.LIST_INDEX_META].append(d.SPACE)
        self.tmp_meas_ch1[d.LIST_INDEX_META].append(d.MEAS_FORMAT)
        self.tmp_meas_ch1[d.LIST_INDEX_META].append(d.SPACE)

    def setMetaCh2(self):
        """TODO."""
        self.tmp_meas_ch2[d.LIST_INDEX_META].append(self.name_ch2)
        self.tmp_meas_ch2[d.LIST_INDEX_META].append(d.SPACE)
        self.tmp_meas_ch2[d.LIST_INDEX_META].append(self.meas_id)
        self.tmp_meas_ch2[d.LIST_INDEX_META].append(d.SPACE)
        self.tmp_meas_ch2[d.LIST_INDEX_META].append(self.meas_timestamp)
        self.tmp_meas_ch2[d.LIST_INDEX_META].append(d.SPACE)
        self.tmp_meas_ch2[d.LIST_INDEX_META].append(d.MEAS_FORMAT)
        self.tmp_meas_ch2[d.LIST_INDEX_META].append(d.SPACE)

    def appendHead(self):
        """TODO."""
        self.tmp_meas_ch1[d.LIST_INDEX_META].append(d.REC_BEGIN_DELIMIT)
        self.tmp_meas_ch2[d.LIST_INDEX_META].append(d.REC_BEGIN_DELIMIT)
        self.tmp_meas_ch1[d.LIST_INDEX_CURRENT].append('current' + d.VAL_BEGIN_DELIMIT)
        self.tmp_meas_ch1[d.LIST_INDEX_VOLTAGE].append('voltage' + d.VAL_BEGIN_DELIMIT)
        self.tmp_meas_ch1[d.LIST_INDEX_POWER].append('power' + d.VAL_BEGIN_DELIMIT)
        self.tmp_meas_ch2[d.LIST_INDEX_CURRENT].append('current' + d.VAL_BEGIN_DELIMIT)
        self.tmp_meas_ch2[d.LIST_INDEX_VOLTAGE].append('voltage' + d.VAL_BEGIN_DELIMIT)
        self.tmp_meas_ch2[d.LIST_INDEX_POWER].append('power' + d.VAL_BEGIN_DELIMIT)

    def appendFoot(self):
        """TODO."""
        self.tmp_meas_ch1[d.LIST_INDEX_CURRENT].append(d.VAL_END_DELIMIT)
        self.tmp_meas_ch1[d.LIST_INDEX_VOLTAGE].append(d.VAL_END_DELIMIT)
        self.tmp_meas_ch1[d.LIST_INDEX_POWER].append(d.VAL_END_DELIMIT)
        self.tmp_meas_ch2[d.LIST_INDEX_CURRENT].append(d.VAL_END_DELIMIT)
        self.tmp_meas_ch2[d.LIST_INDEX_VOLTAGE].append(d.VAL_END_DELIMIT)
        self.tmp_meas_ch2[d.LIST_INDEX_POWER].append(d.VAL_END_DELIMIT)
        self.tmp_meas_ch1[d.LIST_INDEX_POWER].append(d.REC_END_DELIMIT)
        self.tmp_meas_ch2[d.LIST_INDEX_POWER].append(d.REC_END_DELIMIT)


if __name__ == "__main__":
    mp = MeasProcessor('meas/test.txt', "TEST_MEAS")
    mp.processFileByLine()

    