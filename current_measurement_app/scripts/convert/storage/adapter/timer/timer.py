"""The timer module provides a timer and a delay functionality."""

import os
import time

class Timer:
    """ The Timer class object stores the initial time
        when instantiated and returns the elapsed
        time by a call of the relevant method.
    """

    # Initial time
    initial_time = None

    def __init__(self):
        """ The initial time is saved by
            the class object when the
            constructor is called.
        """
        # Reset initial time variable
        self.initial_time = time.time()

    def reset_timer(self):
        """This method resets the initial time."""
        # Reset initial time variable
        self.initial_time = time.time()

    def get_elapsed_time(self):
        """ This method returns the time elapsed
            since instantiating.
        """
        # measure wall time
        return time.time() - self.initial_time

    def getNowTime(self):
        """This method returns the current time."""
        return time.time()

    def timerSleep(self, sec):
        """ This method causes the calling
            process to sleep for the specified time."""
        try:
            time.sleep(sec)
        except(InterruptedError):
            print("Sleep interrupted in timer")

if __name__ == "__main__":
    t = Timer()
    print("Time since instanciation: %2.6f") % t.get_elapsed_time()
    time.sleep(0.001000)
    print("Time after sleep: %2.6f") % t.get_elapsed_time()
    t.reset_timer()
    print("Time since reset: %2.6f") % t.get_elapsed_time() 
