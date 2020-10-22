from litex.soc.interconnect.axi import AXILiteInterface

class PldAXILiteInterface(AXILiteInterface):
    def get_signals(self):
        signals = {}
        r = []
        channels = [
            "aw",
            "w",
            "b",
            "ar",
            "r",
        ]
        for channel in channels:
            for name, width in [("valid", 1)] + getattr(self, channel).description.payload_layout:
                sig  = getattr(getattr(self, channel), name)
                signals[channel + name] = sig
            for name, width in [("ready", 1)]:
                sig  = getattr(getattr(self, channel), name)
                signals[channel + name] = sig
        return signals
