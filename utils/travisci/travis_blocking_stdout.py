import fcntl, os
from sys import stdout, stderr

def to_blocking_mode(channel):
    flags = fcntl.fcntl(channel, fcntl.F_GETFL)
    if flags & os.O_NONBLOCK:
        fcntl.fcntl(channel, fcntl.F_SETFL, flags & ~os.O_NONBLOCK)
        return True
    return False

if to_blocking_mode(stderr):
    stderr.writelines(["Reset STDERR to blocking"])
if to_blocking_mode(stdout):
    stderr.writelines(["Reset STDOUT to blocking"])
