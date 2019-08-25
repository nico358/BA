#!/usr/bin/env python
""" This module processes measurements stored in a file. It opens the provided filepath and
    reads the data line by line. A specific format for the stored data has to be respected in
    order to allow correct processing. Basically, four lists are used to store measurements
    temporary and to capture the meta data of the measurement [[metadata], [current], [voltage], [power]].
    The temporary data are written into another file then and the plotter module is called in order
    to visualize the measurements.
"""

import sys
from datetime import datetime
from meas_plotter import MeasPlotter
from storage.adapter.exception_handler import ExceptionHandler
from storage.adapter.filestorage_adapter import FileStorageAdapter

# The list indexes within its container list
LIST_INDEX_META    = 0
LIST_INDEX_TIME    = 1
LIST_INDEX_CURRENT = 2
LIST_INDEX_VOLTAGE = 3
LIST_INDEX_POWER   = 4

# Format of single measurement
MEAS_FORMAT        = 'float'
# Definition of delimiters in file
CNTR_DELIMIT        = '\''
REC_BEGIN_DELIMIT   = '{'
REC_END_DELIMIT     = '}'
VAL_BEGIN_DELIMIT   = '['
VAL_END_DELIMIT     = ']'
SPACE               = ' '
# Indexes of entities in a measurement 
TIME_INDEX          = 0
CNTR_INDEX          = 1
CH1_NAME_INDEX      = 2
CH1_CURRENT_INDEX   = 3
CH1_VOLTAGE_INDEX   = 4
CH1_POWER_INDEX     = 5
CH2_NAME_INDEX      = 6
CH2_CURRENT_INDEX   = 7
CH2_VOLTAGE_INDEX   = 8
CH2_POWER_INDEX     = 9

class MeasProcessor:
    """The class that processes the measurements and calls store module and plotter."""

    meas_id         = None # Some id, provided by caller 
    meas_time       = None # Period of measurement, used to determine x axes of plot
    meas_timestamp  = None # internal: places date and hour to the plot
    tmp_meas_ch1    = None # internal: List of mesurement provided by meas_processor module
    tmp_meas_ch2    = None # internal: List of mesurement provided by meas_processor module
    name_ch1        = None # internal: Name extracted form data
    name_ch2        = None # internal: Name extracted form data
    folderpath      = None # The folder where the data is stored
    filepath        = None # The file where the data is stored
    overlay         = None # Plot format
    show            = None # Plot is showed or not

    def __init__(self, folderpath='meas/', filepath=None, meas_id=None, meas_time=None, plotoverlay=False, showplot=False):
        """ Constructor: folderpath and filepath is required to load a file of measurement data, meas_time is required
            for plotting, showplot specifies whether the plot should be shown, plotoverlay specifies the plot format.
        """
        # Containers that are used to store the data temporary
        self.tmp_meas_ch1 = [[], [], [], [], []]
        self.tmp_meas_ch2 = [[], [], [], [], []]
        self.meas_id = meas_id
        self.meas_time = meas_time
        self.meas_timestamp = datetime.now().strftime("%m-%d-%Y-%H-%M-%S")
        self.filepath = filepath
        self.folderpath = folderpath
        self.overlay = plotoverlay
        self.show = showplot

    def plotFormattedDataToPngFile(self, overlay):
        """ This method instantiates the plot module and
            provides the temporary data to the plot.
        """
        filepath_ch1 = self.formatFilepath(self.name_ch1)
        filepath_ch2 = self.formatFilepath(self.name_ch2)
        plotter = MeasPlotter(meas_ch1=self.tmp_meas_ch1, meas_ch2=self.tmp_meas_ch2, folderpath=self.folderpath, filepath1=filepath_ch1, filepath2=filepath_ch2, show=self.show, meas_time=self.meas_time)
        plotter.plotAll(overlay)

    def writeFormattedDataToTxtFile(self, tmp_meas_ch, ch_name):
        """This method instantiates the store module and writes
           the processed data to a new file.
        """
        filewriter = FileStorageAdapter()
        # Assemble new file path from channel names
        filepath_ch = self.folderpath + self.formatFilepath(ch_name) + '.txt'
        filewriter.openFile(filepath_ch, 'w+')
        # Write file by line in temporary container
        for row in tmp_meas_ch:
            for elem in row:
                filewriter.writeToOpenFile(str(elem))
        filewriter.closeFile()

    def formatFilepath(self, ch_name):
        """Assemble new file path from provided paths and channel name."""
        pathstr = self.filepath + '_'
        pathstr += ch_name + '_'
        pathstr += self.meas_timestamp
        return pathstr

    def processFileByLine(self):
        """This method reads data from a file and formats the readings.
           The output is a continuous number of measurement results of a specific
           type such as current temporary stored in lists.
        """
        if not self.filepath is None:
            # Assemble measurement location
            path = self.folderpath + self.filepath + '.txt'
            try:
                # Readin of multiple sensor measurements from one file not supported
                with open (path, "r") as reader:
                    if reader.mode == 'r':
                        # Set matadata and measurement header
                        self.appendHead()
                        # Drop first line
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
                            if len(splinter) == 10:
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
        """ Helper method to split a string
            by whitespace.
        """
        return strg.split(' ')

    def setListValues(self, splinter):
        """ This method places the data read from a line in the specified list.
            Hereby 'splinter' contains a list of splitted data from a line (single measurement).
        """
        # Append measurement time 
        self.tmp_meas_ch1[LIST_INDEX_TIME].append(int(splinter[TIME_INDEX]))
        # Set the measurement counter in front of a value
        self.tmp_meas_ch1[LIST_INDEX_CURRENT].append(CNTR_DELIMIT + splinter[CNTR_INDEX] + CNTR_DELIMIT)
        # Append actual current value
        self.tmp_meas_ch1[LIST_INDEX_CURRENT].append(float(splinter[CH1_CURRENT_INDEX]))
        # Set the measurement counter in front of a value
        self.tmp_meas_ch1[LIST_INDEX_VOLTAGE].append(CNTR_DELIMIT + splinter[CNTR_INDEX] + CNTR_DELIMIT)
        # Append actual voltage value
        self.tmp_meas_ch1[LIST_INDEX_VOLTAGE].append(float(splinter[CH1_VOLTAGE_INDEX]))
        # Set the measurement counter in front of a value
        self.tmp_meas_ch1[LIST_INDEX_POWER].append(CNTR_DELIMIT + splinter[CNTR_INDEX] + CNTR_DELIMIT)
        # Append actual power value
        self.tmp_meas_ch1[LIST_INDEX_POWER].append(float(splinter[CH1_POWER_INDEX]))
        # Process the 2nd channel
        self.tmp_meas_ch2[LIST_INDEX_TIME].append(int(splinter[TIME_INDEX]))
        self.tmp_meas_ch2[LIST_INDEX_CURRENT].append(CNTR_DELIMIT + splinter[CNTR_INDEX] + CNTR_DELIMIT)
        self.tmp_meas_ch2[LIST_INDEX_CURRENT].append(float(splinter[CH2_CURRENT_INDEX]))
        self.tmp_meas_ch2[LIST_INDEX_VOLTAGE].append(CNTR_DELIMIT + splinter[CNTR_INDEX] + CNTR_DELIMIT)
        self.tmp_meas_ch2[LIST_INDEX_VOLTAGE].append(float(splinter[CH2_VOLTAGE_INDEX]))
        self.tmp_meas_ch2[LIST_INDEX_POWER].append(CNTR_DELIMIT + splinter[CNTR_INDEX] + CNTR_DELIMIT)
        self.tmp_meas_ch2[LIST_INDEX_POWER].append(float(splinter[CH2_POWER_INDEX]))

    def setMetaCh1(self):
        """This method sets metadata to a measurement from channel 1."""
        self.tmp_meas_ch1[LIST_INDEX_META].append(self.name_ch1)
        self.tmp_meas_ch1[LIST_INDEX_META].append(SPACE)
        self.tmp_meas_ch1[LIST_INDEX_META].append(self.meas_id)
        self.tmp_meas_ch1[LIST_INDEX_META].append(SPACE)
        self.tmp_meas_ch1[LIST_INDEX_META].append(self.meas_timestamp)
        self.tmp_meas_ch1[LIST_INDEX_META].append(SPACE)
        self.tmp_meas_ch1[LIST_INDEX_META].append(MEAS_FORMAT)
        self.tmp_meas_ch1[LIST_INDEX_META].append(SPACE)

    def setMetaCh2(self):
        """This method sets metadata to a measurement from channel 2."""
        self.tmp_meas_ch2[LIST_INDEX_META].append(self.name_ch2)
        self.tmp_meas_ch2[LIST_INDEX_META].append(SPACE)
        self.tmp_meas_ch2[LIST_INDEX_META].append(self.meas_id)
        self.tmp_meas_ch2[LIST_INDEX_META].append(SPACE)
        self.tmp_meas_ch2[LIST_INDEX_META].append(self.meas_timestamp)
        self.tmp_meas_ch2[LIST_INDEX_META].append(SPACE)
        self.tmp_meas_ch2[LIST_INDEX_META].append(MEAS_FORMAT)
        self.tmp_meas_ch2[LIST_INDEX_META].append(SPACE)

    def appendHead(self):
        """This method prepends delimiters and name of the
            seperated records to the data."""
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
        """This method appends delimiters to the data. """
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
    mp = MeasProcessor(filepath='test', meas_id="TEST_MEAS", meas_time=3, plotoverlay=False)
    mp.processFileByLine()

    