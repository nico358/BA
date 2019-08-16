#!/usr/bin/env python

"""This module ."""

from __future__ import division
import matplotlib.pyplot as plt
from mpl_toolkits.axes_grid1 import make_axes_locatable

LINE_STYLE_DOT    = 'o'
LINE_STYLE_LN     = 'b-'
PLOT_COLORS       = ['g', 'b', 'c', 'm', 'y', 'k', 'r']
FONTSIZE          = 10
XLABEL            = 'time (ms)'
ADJUST            = 0.88
FIRST_COLOR       = 'tab:red' 
LINEWIDTH         = 0.8
MARKERSIZE        = 1
INDEX_MEAS_NAME   = 0
INDEX_FIRST_MEAS  = 0

class MeasPlotter:
    """TODO."""

    tmp_meas_ch1  = None
    tmp_meas_ch2  = None
    path_ch1      = None
    path_ch2      = None
    show          = None
    meas_time     = None

    def __init__(self, meas_ch1=None, meas_ch2=None, folderpath=None, filepath1=None, filepath2=None, show=False, meas_time=None):
        """TODO."""
        self.tmp_meas_ch1  = meas_ch1
        self.tmp_meas_ch2  = meas_ch2
        self.show          = show
        self.meas_time     = meas_time
        if not folderpath is None:
            if not filepath1 is None:
                self.path_ch1 = folderpath + 'plot/' + filepath1
            if not filepath2 is None:
                self.path_ch2 = folderpath + 'plot/' + filepath2

    def plotAll(self, overlay=4):
        """TODO."""
        if not self.meas_time is None:
            if not self.tmp_meas_ch1 is None:
                self.plotMeasurement(self.tmp_meas_ch1, overlay, self.path_ch1)
            if not self.tmp_meas_ch2 is None:
                self.plotMeasurement(self.tmp_meas_ch2, overlay, self.path_ch2)

    def plotMeasurement(self, tmp_meas_ch, overlay, path):
        """TODO."""
        # Get lists of temp measurement values and names from container
        if len(tmp_meas_ch) > 1:
            tmp_meas_names = []
            tmp_meas_lists = []
            # Discard first element in container (metadata)
            for i in range(len(tmp_meas_ch) -1):
                tmp = tmp_meas_ch[i+1]
                tmp_meas_names.append(tmp[INDEX_MEAS_NAME])
                # Filter out floats and append list to temp container
                tmp_meas_lists.append(self.filterListByFloat(tmp))
            # Get metadata
            title = self.getTitle(tmp_meas_ch)
            # Get interval by division of meas time by meas number
            yax = self.getYaxis(tmp_meas_lists)
            if overlay == 1:
                self.plotAllOverlay(tmp_meas_names, tmp_meas_lists, title, yax, path)
            elif overlay == 2:
                self.plotAllBeside(tmp_meas_names, tmp_meas_lists, title, yax, path)
            elif overlay == 3:
                self.plotAllNormal(tmp_meas_names, tmp_meas_lists, title, yax, path)
            else:
                self.plotAllOverlay(tmp_meas_names, tmp_meas_lists, title, yax, path)
                self.plotAllBeside(tmp_meas_names, tmp_meas_lists, title, yax, path)
                # self.plotAllNormal(tmp_meas_names, tmp_meas_lists, title, yax, path)

    def plotAllBeside(self, tmp_meas_names, tmp_meas_lists, title, yax, path):
        """TODO."""
        fig, axs = plt.subplots(3, sharex=True, sharey=False, figsize=(10, 5))
        marker = LINE_STYLE_DOT
        for i in range(len(tmp_meas_lists)):
            axs[i].plot(yax, tmp_meas_lists[i], color=PLOT_COLORS[(i % len(PLOT_COLORS)) -1], marker=marker, linewidth=LINEWIDTH, markersize=MARKERSIZE)
            axs[i].set_ylabel(tmp_meas_names[i])
            axs[i].grid(axis='both')
            
        axs[len(tmp_meas_lists) -1].set_xlabel(XLABEL)

        plt.tight_layout()
        fig.suptitle(title, fontsize=FONTSIZE)
        plt.subplots_adjust(top=ADJUST)
        # Save figure
        if not path is None:
            plt.savefig(path + 'beside.png')
        # If show = True: show
        if self.show:
            plt.show()


    def plotAllNormal(self, tmp_meas_names, tmp_meas_lists, title, yax, path):
        """TODO."""
        fig, ax1 = plt.subplots(figsize=(20, 10))
        marker = LINE_STYLE_DOT
        ax1.set_xlabel(XLABEL)
        plt.grid(axis='both')

        # Plot graphs
        lines = []
        for i in range(len(tmp_meas_lists)):
            lines.append(ax1.plot(yax, tmp_meas_lists[i], PLOT_COLORS[(i % len(PLOT_COLORS)) -1], marker=marker))

        # Add legend according to graphs
        if len(tmp_meas_names) == 3:
            ax1.legend([ tmp_meas_names[0], tmp_meas_names[1], tmp_meas_names[2] ])
            plt.setp(lines[0], linewidth=LINEWIDTH, markersize=MARKERSIZE)
            plt.setp(lines[1], linewidth=LINEWIDTH/2, markersize=MARKERSIZE/2)
            plt.setp(lines[2], linewidth=LINEWIDTH/4, markersize=MARKERSIZE/4)
        if len(tmp_meas_names) == 4:
            ax1.legend([ tmp_meas_names[0], tmp_meas_names[1], tmp_meas_names[2], tmp_meas_names[3] ]) 
            plt.setp(lines[0], linewidth=LINEWIDTH, markersize=MARKERSIZE)
            plt.setp(lines[1], linewidth=LINEWIDTH/2, markersize=MARKERSIZE/2)
            plt.setp(lines[2], linewidth=LINEWIDTH/4, markersize=MARKERSIZE/4)
            plt.setp(lines[3], linewidth=LINEWIDTH/8, markersize=MARKERSIZE/8)

        fig.tight_layout()
        plt.title(title, fontsize=FONTSIZE)
        plt.subplots_adjust(top=ADJUST)
        # Save figure if path is given
        if not path is None:
            plt.savefig(path + 'normal.png')
        # If show = True: show figure
        if self.show:
            plt.show()
            
    # def plotAllOverlay(self, tmp_meas_names, tmp_meas_lists, title, yax, path):
    #     """TODO."""
    #     fig, ax1 = plt.subplots(figsize=(30, 10))

    #     color = FIRST_COLOR
    #     marker = LINE_STYLE_DOT
    #     ax1.set_xlabel(XLABEL)
    #     # Set label and plot first graph
    #     ax1.set_ylabel(tmp_meas_names[INDEX_FIRST_MEAS], color=color)
    #     ax1.plot(yax, tmp_meas_lists[INDEX_FIRST_MEAS], color=color, marker=marker, linewidth=LINEWIDTH+1, markersize=MARKERSIZE+1)
    #     ax1.tick_params(axis='y', labelcolor=color)
    #     # Plot remaining measurements
    #     self.plotLoop(tmp_meas_names, tmp_meas_lists, ax1, yax)

    #     # Plot figure
    #     fig.tight_layout()
    #     plt.title(title, fontsize=FONTSIZE)
    #     plt.subplots_adjust(top=ADJUST)

    #     # Save figure
    #     if not path is None:
    #         plt.savefig(path  + 'ovelay.png')
    #     # If show = True: show
    #     if self.show:
    #         plt.show()

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
            ax2.plot(yax, tmp_meas_lists[i+1], color=color, marker=marker, linewidth=LINEWIDTH/(i+1), markersize=MARKERSIZE/(i+1))
            ax2.tick_params(axis='y', labelcolor=color)
            # fig.align_ylabels()

    def make_patch_spines_invisible(self, ax):
        ax.set_frame_on(True)
        ax.patch.set_visible(False)
        for sp in ax.spines.values():
            sp.set_visible(False)
            
    def plotAllOverlay(self, tmp_meas_names, tmp_meas_lists, title, yax, path):   
        fig, host = plt.subplots()
        fig.subplots_adjust(right=0.75)
            
        par1 = host.twinx()
        par2 = host.twinx()
            
        # Offset the right spine of par2.  The ticks and label have already been
        # placed on the right by twinx above.
        par2.spines["right"].set_position(("axes", 1.2))
        # Having been created by twinx, par2 has its frame off, so the line of its
        # detached spine is invisible.  First, activate the frame but make the patch
        # and spines invisible.
        self.make_patch_spines_invisible(par2)
        # Second, show the right spine.
        par2.spines["right"].set_visible(True)

        color = FIRST_COLOR
        marker = LINE_STYLE_DOT
        host.set_xlabel(XLABEL)
            
        color = FIRST_COLOR
        p1, = host.plot(yax, tmp_meas_lists[INDEX_FIRST_MEAS], color=color, marker=marker, linewidth=LINEWIDTH+1, markersize=MARKERSIZE+1)

        color = PLOT_COLORS[0]
        p2, = par1.plot(yax, tmp_meas_lists[1], color=color, marker=marker, linewidth=LINEWIDTH/(2), markersize=MARKERSIZE/(2))

        color = PLOT_COLORS[2]
        p3, = par2.plot(yax, tmp_meas_lists[2], color=color, marker=marker, linewidth=LINEWIDTH/(3), markersize=MARKERSIZE/(3))
            
            
        host.set_xlabel(XLABEL)
        host.set_ylabel(tmp_meas_names[0])
        par1.set_ylabel(tmp_meas_names[1])
        par2.set_ylabel(tmp_meas_names[2])
            
        host.yaxis.label.set_color(FIRST_COLOR)
        par1.yaxis.label.set_color(color = PLOT_COLORS[0])
        par2.yaxis.label.set_color(color = PLOT_COLORS[2])
            
        tkw = dict(size=4, width=1.5)
        host.tick_params(axis='y', colors=p1.get_color(), **tkw)
        par1.tick_params(axis='y', colors=p2.get_color(), **tkw)
        par2.tick_params(axis='y', colors=p3.get_color(), **tkw)
        host.tick_params(axis='x', **tkw)
            
         # Plot figure
        fig.tight_layout()
        plt.title(title, fontsize=FONTSIZE, y=1.03)
        plt.subplots_adjust(top=ADJUST)

        # Save figure
        if not path is None:
            plt.savefig(path  + 'ovelay.png')
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
        for i in range(len(tmp_metadata) -1):
            title += str(tmp_metadata[i+1])
            title += ' '
        return title

    def filterListByFloat(self, lst):
        """TODO."""
        return list(filter(lambda elem : isinstance(elem, float), lst))


if __name__ == "__main__":

    l = [['af ae', 'df'], ['current', '[', '01', -0.1, '02', -0.2, '03', -0.3, '04', -0.686844, ']'], ['voltage', '[', '01', 1.2, '02', 2.12, '03', 2.3, '04', 2.686844, ']'], ['power', '[', '01', 0.133, '02', 0.2123, '03', 0.311, '04', 0.486844, ']']]
    l2 = [['{', 'FPGA_VCCAUX_MON TEST_MEAS', '2019-07-21 18:59:02.965000', 'float'], ['current', '[', '1', 0.006349, '2', 0.006349, '3', 0.006349, '4', 0.006349, '5', 0.006349, '6', 0.006349, ']'] , ['voltage', '[', '1', 1.09375, '2', 1.09375, '3', 1.09375, '4', 1.09375, '5', 1.09375, '6', 1.09375, ']'], ['power', '[', '1', 0.006809, '2', 0.006809, '3', 0.006809, '4', 0.006809, '5', 0.006809, '6', 0.006809, ']', '}']]
    mp = MeasPlotter(meas_ch1=l2, filepath1='test', filepath2='test', meas_time=1, show=True)
    mp.plotAll()
