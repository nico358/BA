#!/usr/bin/env python
"""TODO."""

from __future__ import division
import matplotlib.pyplot as plt


LINE_STYLE_DOT    = 'o'
LINE_STYLE_LN     = 'b-'
PLOT_COLORS       = ['g', 'b', 'c', 'm', 'y', 'k', 'r']
INDEX_MEAS_NAME   = 0
INDEX_FIRST_MEAS  = 0

class MeasPlotter:
    """TODO."""

    tmp_meas_ch1  = None
    tmp_meas_ch2  = None
    path          = None
    show          = None
    meas_time     = None

    def __init__(self, meas_ch1=None, meas_ch2=None, folderpath='plot/', filepath=None, show=True, meas_time=0):
        """TODO."""
        self.tmp_meas_ch1  = meas_ch1
        self.tmp_meas_ch2  = meas_ch2
        self.show          = show
        self.meas_time     = meas_time
        if not filepath is None:
            self.path = folderpath + filepath

    def plotAll(self, overlay=False):
        """TODO."""
        if not self.tmp_meas_ch1 is None:
            self.plotMeasurement(self.tmp_meas_ch1, overlay)
        if not self.tmp_meas_ch2 is None:
            self.plotMeasurement(self.tmp_meas_ch2, overlay)

    def plotMeasurement(self, tmp_meas_ch, overlay):
        """TODO."""
        # Get lists of temp measurement values and names from container
        if len(tmp_meas_ch) > 1:
            tmp_meas_names = []
            tmp_meas_lists = []
            # Discard first element in container (metadata)
            for i in range(len(tmp_meas_ch) -1):
                tmp = tmp_meas_ch[i+1]
                tmp_meas_names.append(tmp[INDEX_MEAS_NAME])
                tmp_meas_lists.append(self.filterListByFloat(tmp))
            # Get metadata
            title = self.getTitle(tmp_meas_ch)
            # Get interval by division of meas time by meas number
            yax = self.getYaxis(tmp_meas_lists)
            if overlay:
                self.plotAllOverlay(tmp_meas_names, tmp_meas_lists, title, yax)
            else:
                self.plotAllNormal(tmp_meas_names, tmp_meas_lists, title, yax)

    def plotAllNormal(self, tmp_meas_names, tmp_meas_lists, title, yax):
        """TODO."""
        fig, ax1 = plt.subplots()
        marker = LINE_STYLE_DOT
        ax1.set_xlabel('time (ms)')
        plt.grid(axis='both')
        # Plot graphs
        for i in range(len(tmp_meas_lists)):
            ax1.plot(yax, tmp_meas_lists[i], PLOT_COLORS[(i % len(PLOT_COLORS)) -1], marker=marker)
        fig.tight_layout()
        ax1.legend(['Current', 'Voltage', 'Power'])
        plt.title(title, fontsize=20)
        plt.subplots_adjust(top=0.88)
        # Save figure
        if not self.path is None:
            plt.savefig(self.path)
        # If show = True: show
        if self.show:
            plt.show()

    def getYaxis(self, tmp_meas_lists):
        """TODO."""
        period = self.meas_time / len(tmp_meas_lists[INDEX_FIRST_MEAS])
        interval = []
        for i in range(len(tmp_meas_lists[INDEX_FIRST_MEAS])):
            interval.append(i * period * 1000)
        return interval

    def getTitle(self, tmp_meas_ch):
        """TODO."""
        tmp_metadata = tmp_meas_ch[INDEX_FIRST_MEAS]
        title = ''
        for obj in tmp_metadata:
            title += obj
        return title
            
    def plotAllOverlay(self, tmp_meas_names, tmp_meas_lists, title, yax):
        """TODO."""
        fig, ax1 = plt.subplots()
        color = 'tab:red'
        marker = LINE_STYLE_DOT
        ax1.set_xlabel('time (ms)')
        # Set label and plot first graph
        ax1.set_ylabel(tmp_meas_names[INDEX_FIRST_MEAS], color=color)
        ax1.plot(yax, tmp_meas_lists[INDEX_FIRST_MEAS], color=color, marker=marker)
        ax1.tick_params(axis='y', labelcolor=color)
        # Plot remaining measurements
        self.plotLoop(tmp_meas_names, tmp_meas_lists, ax1, yax)
        # Plot figure
        fig.tight_layout()
        plt.title(title, fontsize=20)
        plt.subplots_adjust(top=0.88)
        # Save figure
        if not self.path is None:
            plt.savefig(self.path)
        # If show = True: show
        if self.show:
            plt.show()

    def plotLoop(self, tmp_meas_names, tmp_meas_lists, ax1, yax):
        """TODO."""
        for i in range(len(tmp_meas_lists) - 1):
            # First plot is base
            ax2 = ax1.twinx()
            # Choose color repetively
            color = PLOT_COLORS[i % len(PLOT_COLORS)]
            marker = LINE_STYLE_DOT
            # Set name and plot graph
            ax2.set_ylabel(tmp_meas_names[i+1], color=color)
            ax2.plot(yax, tmp_meas_lists[i+1], color=color, marker=marker)
            ax2.tick_params(axis='y', labelcolor=color)


    def filterListByFloat(self, lst):
        """TODO."""
        return list(filter(lambda elem : isinstance(elem, float), lst))


if __name__ == "__main__":

    l = [['af ae', 'df'], ['current[', '01', -0.1, '02', -0.2, '03', -0.3, '04', -0.686844, ']'], ['voltage[', '01', 1.2, '02', 2.12, '03', 2.3, '04', 2.686844, ']'], ['power[', '01', 0.133, '02', 0.2123, '03', 0.311, '04', 0.486844, ']']]
    mp = MeasPlotter(meas_ch1=l, filepath='test.png', meas_time=1)
    mp.plotAll()
