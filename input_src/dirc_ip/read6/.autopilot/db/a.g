#!/bin/sh
lli=${LLVMINTERP-lli}
exec $lli \
    /home/ylxiao/ws_183/F200703/dirc/read6/.autopilot/db/a.g.bc ${1+"$@"}
