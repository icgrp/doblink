# Streaming Instructions

| Instruction | for which | Description |
|---|---|---|
|  strmw rs1,rs2  | leaf | write value in rs2 to stream specified by r1, stalling processor if stream is full |
|  strmwi rs2,imm  | leaf | write value in rs2 to stream imm, stalling processor if stream is full |
|  strmr  rd,rs1  | leaf | read stream specified by rs1 and put results in rd, stalling processor if empy |
|  strmri  rd,imm  | leaf | read stream specified by imm and put results in rd, stalling processor if empty |
|  hstrmw rs1,rs2  | master | take value from rs2 and put in payload of stream packet; take value of rs1 and use as header of packet, talling if stream full -- works on single packet stream|
|---|---|---|
 

Useful to have leaf interfaces on master.  Maybe necessary in uniform
streaming case.

s - for pure data stream (only specifiying payload)

hs - for header+stream_payload 
