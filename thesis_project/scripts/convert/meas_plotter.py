#!/usr/bin/env python

""" This module uses the matplotlib in order to plot measurement results provided by the
    meas_processor module. The constructor takes two lists containing the measurements
    of the two sensor channels formatted by the meas_processor module. Basically the
    results can be plotted in two formats. The first plot method plots each quantity
    results in subplots and arrange them in a single frame. The second plot method draws
    each quantity in one plot and arrange the axes according to the ranges of the quantities.
"""

from __future__ import division
import matplotlib.pyplot as plt
from mpl_toolkits.axes_grid1 import make_axes_locatable
from storage.adapter.exception_handler import ExceptionHandler

# Line styles and graph colors
LINE_STYLE_DOT    = 'o'
LINE_STYLE_LN     = 'b-'
FIRST_COLOR       = 'tab:red' 
PLOT_COLORS       = ['g', 'b', 'c', 'm', 'y', 'k', 'r']
# Title fontsize and adjustment
FONTSIZE          = 10
ADJUST            = 0.88
# Label at the x-axes
XLABEL            = 'time (s)'
# Linewidth and markersize of first line
LINEWIDTH         = 0.8
MARKERSIZE        = 1
# Index  of first quantity in container list
INDEX_MEAS_NAME   = 0
INDEX_FIRST_MEAS  = 0

class MeasPlotter:
    """ The plotter class. Instantiate an object by calling the constructor.
        Provide the list(s) of formatted results to the constructor in order
        to plot them by calling the plot_all method.
    """

    # The formatted measurement results of a single channel
    # [[METADATA], [CURRENT], [VOLTAGE], [POWER], [TIME]] 
    tmp_meas_ch1  = None
    tmp_meas_ch2  = None
    # The path where the plots will be stored
    path_ch1      = None
    path_ch2      = None
    # Shows plot after drawing
    show          = None
    # X-Axes
    meas_time     = None

    def __init__(self, meas_ch1=None, meas_ch2=None, folderpath=None, filepath1=None, filepath2=None, show=False, meas_time=None):
        """ The constructor requires references to one or two lists of measurements. These must be
            formatted as the meas_plotter module does. The folderpath is the directory where the plots
            will be stored within an extra folder 'plot'. The files will be identified by the respective
            filepath provided by the caller. If a filepath is 'None' nothing will be stored. The 'show' 
            attribute determines if the plot will be shown after drawing. The meas_time attribute is the
            basis for the x-axis of the whole plot.
        """
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
        """ This method plots all provided lists of results."""
        if not self.meas_time is None:
            if not self.tmp_meas_ch1 is None:
                self.plotMeasurement(self.tmp_meas_ch1, overlay, self.path_ch1)
            if not self.tmp_meas_ch2 is None:
                self.plotMeasurement(self.tmp_meas_ch2, overlay, self.path_ch2)

    def plotMeasurement(self, tmp_meas_ch, overlay, path):
        """ This method takes a list of measurements and filters floating
            point numbers and names. The filtered values are stored temporary
            in order to provide them to the matplotlib interface. 'path' is
            the location where the plot will be stored. 'overlay' determines
            the format of the plot. 
        """
        try:
            # Set up temporary lists
            if len(tmp_meas_ch) > 1:
                tmp_meas_names = []
                tmp_meas_lists = []
                # Get lists of measurement values and names from container
                # Discard first two lists in container (metadata + time)
                for i in range(len(tmp_meas_ch) -2):
                    # Temporary list of results
                    tmp = tmp_meas_ch[i+2]
                    # Filter name and append to list of names
                    tmp_meas_names.append(tmp[INDEX_MEAS_NAME])
                    # Filter floats and append to list of results
                    tmp_meas_lists.append(self.filterListByFloat(tmp))
                # Get metadata
                title = self.getTitle(tmp_meas_ch)
                # Get interval by division of meas time by meas number
                # xax = self.getXaxis(tmp_meas_lists)
                xax = tmp_meas_ch[1]
                # Call a plot method according to the 'overlay' attribute
                if overlay == 1:
                    self.plotAllOverlay(tmp_meas_names, tmp_meas_lists, title, xax, path)
                elif overlay == 2:
                    self.plotAllBeside(tmp_meas_names, tmp_meas_lists, title, xax, path)
                else:
                    self.plotAllOverlay(tmp_meas_names, tmp_meas_lists, title, xax, path)
                    self.plotAllBeside(tmp_meas_names, tmp_meas_lists, title, xax, path)
        except (KeyboardInterrupt, ValueError, AssertionError) as e:
             ExceptionHandler(e, "plotMeasurement")

    def plotAllBeside(self, tmp_meas_names, tmp_meas_lists, title, xax, path):
        """ This method plots each result quantity in an own subplot and arrange
            the subplots in a single frame.
        """
        try:
            # Get frame and list of 3 axes
            fig, axs = plt.subplots(3, sharex=True, sharey=False, figsize=(10, 5))
            # Set marker style of graphs
            marker = LINE_STYLE_DOT
            # Loop over temporary lists and draw a graph for each list
            for i in range(len(tmp_meas_lists)):
                # The color of the graph is set sequentially by looping over the color list
                axs[i].plot(xax, tmp_meas_lists[i], color=PLOT_COLORS[(i % len(PLOT_COLORS)) -1], marker=marker, linewidth=LINEWIDTH, markersize=MARKERSIZE)
                # The label for the y-axis of the subplot
                axs[i].set_ylabel(tmp_meas_names[i])
                # axs[i].set_yticks(tmp_meas_lists[i])
                # Draw grid lines
                axs[i].grid(axis='both')
                # Set x ticks according to time list
                k = 0
                for tick in axs[i].xaxis.get_major_ticks():
                    if k % 2 == 0:
                        tick.label.set_visible(False)
                    k += 1
                    tick.label.set_fontsize(5)
                    tick.label.set_rotation('vertical')
                plt.xticks(xax)
                

            # Set the XLABEL for x-axis of each plot
            axs[len(tmp_meas_lists) -1].set_xlabel(XLABEL)
            # Format frame layout
            plt.tight_layout()
            # Set frame title
            fig.suptitle(title, fontsize=FONTSIZE)
            plt.subplots_adjust(top=ADJUST)

            # Save figure
            if not path is None:
                plt.savefig(path + 'beside.png')
            # If show = True: show
            if self.show:
                plt.show()
        except (KeyboardInterrupt, ValueError, AssertionError) as e:
             ExceptionHandler(e, "plotAllBeside")

    def plotAllOverlay(self, tmp_meas_names, tmp_meas_lists, title, xax, path):
        """ This method plots all results in one frame and arranges
            the axes according to the results.
        """  
        try:
            # Get frame and basis plot
            fig, host = plt.subplots()
            fig.subplots_adjust(right=0.75)
            # Get subplots
            par1 = host.twinx()
            par2 = host.twinx()
            # Offset the right spine of par2.  The ticks and label have already been
            # placed on the right by twinx above.
            par2.spines["right"].set_position(("axes", 1.2))
            # Having been created by twinx, par2 has its frame off, so the line of its
            # detached spine is invisible.  First, activate the frame but make the patch
            # and spines invisible.
            self.makePatchSpinesInvisible(par2)
            # Second, show the right spine.
            par2.spines["right"].set_visible(True)
            # Set color and markerstyle of first graph
            color = FIRST_COLOR
            marker = LINE_STYLE_DOT
            # Plot first graph with provided x-axis as base, make linewidth and markerwidth bold
            p1, = host.plot(xax, tmp_meas_lists[INDEX_FIRST_MEAS], color=color, marker=marker, linewidth=LINEWIDTH+1, markersize=MARKERSIZE+1)
            # Set new color and plot 2nd graph, decrease linewidth and markerwidth
            color = PLOT_COLORS[0]
            p2, = par1.plot(xax, tmp_meas_lists[1], color=color, marker=marker, linewidth=LINEWIDTH/(2), markersize=MARKERSIZE/(2))
            # Set new color and plot 3rd graph, decrease linewidth and markerwidth again
            color = PLOT_COLORS[2]
            p3, = par2.plot(xax, tmp_meas_lists[2], color=color, marker=marker, linewidth=LINEWIDTH/(3), markersize=MARKERSIZE/(3))
            # Set the label for the x-axis
            host.set_xlabel(XLABEL)
            # Set labels for different axes
            host.set_ylabel(tmp_meas_names[0])
            par1.set_ylabel(tmp_meas_names[1])
            par2.set_ylabel(tmp_meas_names[2])
            # Set different colors for axes
            host.yaxis.label.set_color(FIRST_COLOR)
            par1.yaxis.label.set_color(color = PLOT_COLORS[0])
            par2.yaxis.label.set_color(color = PLOT_COLORS[2])
            # Tick colors for axes according to the graphs
            tkw = dict(size=4, width=1.5)
            host.tick_params(axis='y', colors=p1.get_color(), **tkw)
            par1.tick_params(axis='y', colors=p2.get_color(), **tkw)
            par2.tick_params(axis='y', colors=p3.get_color(), **tkw)
            host.tick_params(axis='x', **tkw)
            # Plot figure
            fig.tight_layout()
            plt.title(title, fontsize=FONTSIZE, y=1.03)
            plt.subplots_adjust(top=ADJUST)

            # Set x ticks according to time list
            k = 0
            for tick in host.xaxis.get_major_ticks():
                if k % 2 == 0:
                    tick.label.set_visible(False)
                k += 1
                tick.label.set_fontsize(5) 
                tick.label.set_rotation('vertical')
            plt.xticks(xax)

            # Save figure if filepath was != None
            if not path is None:
                plt.savefig(path  + 'ovelay.png')
            # If show = True: show plot
            if self.show:
                plt.show()
        except (KeyboardInterrupt, ValueError) as e:
             ExceptionHandler(e, "plotAllOverlay")

    def makePatchSpinesInvisible(self, ax):
        """ This helper method constructs invisible spines
            that helps to align several axes in a single plot.
        """
        ax.set_frame_on(True)
        ax.patch.set_visible(False)
        for sp in ax.spines.values():
            sp.set_visible(False)

    def getXaxis(self, tmp_meas_lists):
        """This helper method builds a list of values from the
            meas_time attribute. The list represents the
            x-axis in general and shows the measurement
            time in ms.
        """
        # Determine how many values the plot method requires for the x-axis
        # List size must be equal to size of measurements
        period = self.meas_time / len(tmp_meas_lists[INDEX_FIRST_MEAS])
        interval = []
        # Fill list with values of milliseconds
        for i in range(len(tmp_meas_lists[INDEX_FIRST_MEAS])):
            interval.append(i * period * 1000)
        return interval

    def getTitle(self, tmp_meas_ch):
        """This helper method gets the measurement identifier (i.e. names) 
            from the metadata lists.
        """
        tmp_metadata = tmp_meas_ch[INDEX_FIRST_MEAS]
        title = ''
        for i in range(len(tmp_metadata) -1):
            title += str(tmp_metadata[i+1])
            title += ' '
        return title

    def filterListByFloat(self, lst):
        """This helper method filters a list of mixed values by
            floating point numbers and returns a list
            containing only measurement results.
        """
        return list(filter(lambda elem : isinstance(elem, float), lst))


if __name__ == "__main__":

    l = [['af ae', 'df'], ['current', '[', '01', -0.1, '02', -0.2, '03', -0.3, '04', -0.686844, ']'], ['voltage', '[', '01', 1.2, '02', 2.12, '03', 2.3, '04', 2.686844, ']'], ['power', '[', '01', 0.133, '02', 0.2123, '03', 0.311, '04', 0.486844, ']']]
    l2 = [['{', 'FPGA_VCCAUX_MON TEST_MEAS', '2019-07-21 18:59:02.965000', 'float'], ['current', '[', '1', 0.006349, '2', 0.006349, '3', 0.006349, '4', 0.006349, '5', 0.006349, '6', 0.006349, ']'] , ['voltage', '[', '1', 1.09375, '2', 1.09375, '3', 1.09375, '4', 1.09375, '5', 1.09375, '6', 1.09375, ']'], ['power', '[', '1', 0.006809, '2', 0.006809, '3', 0.006809, '4', 0.006809, '5', 0.006809, '6', 0.006809, ']', '}']]
    mp = MeasPlotter(meas_ch1=l2, filepath1='test', filepath2='test', meas_time=1, show=True)
    mp.plotAll()
