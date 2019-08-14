"""TODO."""

import time

class Timer:
    """TODO."""

    # Initial time
    initial_time = None

    def __init__(self):
        """TODO."""
        # Reset initial time variable
        self.initial_time = time.time()

    def reset_timer(self):
        """TODO."""
        # Reset initial time variable
        self.initial_time = time.time()

    def get_elapsed_time(self):
        """TODO."""
        # measure wall time
        return time.time() - self.initial_time

    def getNowTime(self):
        """TODO."""
        return time.time()

    def timerSleep(self, sec):
        """TODO."""
        time.sleep(sec)

if __name__ == "__main__":
    t = Timer()
    print("Time since instanciation: %2.6f") % t.get_elapsed_time()
    time.sleep(0.001000)
    print("Time after sleep: %2.6f") % t.get_elapsed_time()
    t.reset_timer()
    print("Time since reset: %2.6f") % t.get_elapsed_time() 
