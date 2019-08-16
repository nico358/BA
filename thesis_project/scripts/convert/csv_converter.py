#!/usr/bin/env python
"""TODO."""

import sys
import matplotlib.pyplot as plt
from __future__ import division
from storage.adapter.exception_handler import ExceptionHandler

RESISTANCE = 0.82
PLOT_COLORS       = ['g', 'b', 'c', 'm', 'y', 'k', 'r']
INDEX_TIME    = 0
INDEX_CURRENT = 1
INDEX_VOLTAGE = 2
INDEX_AVG_VOLT = 3
INDEX_AVG_CURR = 4

class CsvPlotter:
    """TODO."""

    path = None
    folderpath = None
    filepath = None
    tmp_meas = None
    tmp_names = None
    avg_current = None
    avg_voltage = None

    def __init__(self, folderpath, filepath):
        """TODO."""
        self.tmp_meas = [[], [], [], [], []]
        self.tmp_names = ['seconds', 'current', 'diff_voltage', 'avg_diff_voltage', 'avg_current']
        self.folderpath = folderpath
        self.filepath = filepath
        self.path = folderpath + filepath + '.CSV'

    def processFileByLine(self):
        """TODO."""
        if not self.path is None:
            try:
                # Readin csv
                with open (self.path, "r") as reader:
                    if reader.mode == 'r':
                        # Drop first line
                        reader.readline()
                        line = reader.readline()
                        while(line):
                            # Split formatted line
                            splinter = self.splitStr(self.formatLine(line))
                            # 
                            self.tmp_meas[INDEX_TIME].append(self.formatNumber(splinter[0]))
                            self.tmp_meas[INDEX_VOLTAGE].append(self.formatNumber(splinter[1]))
                            # Read next incoming line
                            line = reader.readline()
            except (ValueError, OSError, IOError) as e:
                ExceptionHandler(e, "processFileByLine")

            self.calcCurrent()
            self.calcAverage()
            # Plot formatted data
            # self.plotAllBeside()
            self.plotAllNormal()

    def calcAverage(self):
        """TODO."""
        sumV = 0
        for num in self.tmp_meas[INDEX_VOLTAGE]:
            sumV += num
        self.avg_voltage = sumV / len(self.tmp_meas[INDEX_VOLTAGE])
        for i in range(len(self.tmp_meas[INDEX_VOLTAGE])):
            self.tmp_meas[INDEX_AVG_VOLT].append(self.avg_voltage)

        sumC = 0
        for num in self.tmp_meas[INDEX_CURRENT]:
            sumC += num
        self.avg_current = sumC / len(self.tmp_meas[INDEX_CURRENT])
        for i in range(len(self.tmp_meas[INDEX_CURRENT])):
            self.tmp_meas[INDEX_AVG_CURR].append(self.avg_current)
        

    def calcCurrent(self):
        """TODO."""
        for num in self.tmp_meas[INDEX_VOLTAGE]:
            self.tmp_meas[INDEX_CURRENT].append(num / RESISTANCE)

    
    def plotAllNormal(self):
        """TODO."""
        fig, ax1 = plt.subplots(figsize=(10, 5))
        marker = 'o'
        ax1.set_xlabel(self.tmp_names[INDEX_TIME])
        plt.grid(axis='both')

        # Plot graphs
        lines = []
        for i in range(len(self.tmp_meas) -1):
            lines.append(ax1.plot(self.tmp_meas[INDEX_TIME], self.tmp_meas[i+1], PLOT_COLORS[(i % len(PLOT_COLORS)) -1], marker=marker))

        # Add legend according to graphs
        ax1.legend([ self.tmp_names[INDEX_CURRENT], self.tmp_names[INDEX_VOLTAGE], self.tmp_names[INDEX_AVG_VOLT] + '=' + str(self.avg_voltage), self.tmp_names[INDEX_AVG_CURR] + '=' + str(self.avg_current) ])
        plt.setp(lines[0], linewidth=0.8, markersize=1)
        plt.setp(lines[1], linewidth=0.5, markersize=0.8)
        plt.setp(lines[2], linewidth=0.2, markersize=0.2)
        plt.setp(lines[3], linewidth=0.2, markersize=0.2)

        fig.tight_layout()
        plt.title(self.filepath + '.CSV', fontsize=15)
        plt.subplots_adjust(top=0.88)

        plt.savefig(self.folderpath + self.filepath + 'normal.png')
        plt.show()


    def formatNumber(self, num):
        """TODO."""
        split = num.split('E')
        mantissa = float(split[0])
        exp = int(split[1])
        return mantissa *10**exp

    def formatLine(self, line):
        """TODO."""
        return  "{}".format(line.replace('\n', ''))

    def splitStr(self, strg):
        """TODO."""
        return strg.split(',')



if __name__ == "__main__":
    cp = CsvPlotter('verify/resetFPGA/Osci/', 'WFM03')
    cp.processFileByLine()

    