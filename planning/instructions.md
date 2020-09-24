# Streaming Instructions

|----------|------|--------------------------------------------------------------|
| strmw r1,r2 | leaf | write value in r2 to stream specified by r1, stalling processor if stream is full |
| strmwi i1,r2 | leaf | write value in r2 to stream i1, stalling processor if stream is full |
| strmr  r1,r2 | leaf | read stream specified by r1 and put results in r2, stalling processor if full |
| strmri  r1,r2 | leaf | read stream specified by i1 and put results in r2, stalling processor if full |
| hstrmw r1,r2 | master | take value from r2 and put in payload of stream packet; take value of r1 and use as header of packet, talling if stream full -- works on single packet stream|
 |----------|--------------------------------------------------------------|
 
 TODO: check if registers and immediates correct place and notation

Useful to have leaf interfaces on master.  Maybe necessary in uniform
streaming case.






