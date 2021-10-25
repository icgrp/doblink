from migen import *

from litex.soc.interconnect.csr import *

from litex.build.generic_platform import Subsignal, Pins

class StartWriter(Module, AutoCSR):
    def __init__(self, signal):
        self.signal   = signal
        self._start   = CSRStorage(1, reset=0)
        self.comb += signal.eq(self._start.storage)

    def get_ios(self, bus_name='start'):
        subsignals = []
        subsignals.append(Subsignal('signal', Pins(1)))
        return [(bus_name, 0) + tuple(subsignals)]

    def connect_to_pads(self, pads):
        r = []
        r.append(pads.signal.eq(self.signal))

        return r
