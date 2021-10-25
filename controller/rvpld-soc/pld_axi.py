from litex.soc.interconnect.axi import (AXIInterface, AXILiteInterface,
                                        AXIStreamInterface)


class PldAXILiteInterface(AXILiteInterface):
    def get_signals(self):
        signals = {}
        channels = [
            "aw",
            "w",
            "b",
            "ar",
            "r",
        ]
        for channel in channels:
            for name, width in [("valid", 1)] + getattr(
                self, channel
            ).description.payload_layout:
                sig = getattr(getattr(self, channel), name)
                signals[channel + name] = sig
            for name, width in [("ready", 1)]:
                sig = getattr(getattr(self, channel), name)
                signals[channel + name] = sig
        return signals


class PldAXIInterface(AXIInterface):
    def get_signals(self):
        signals = {}
        channels = [
            "aw",
            "w",
            "b",
            "ar",
            "r",
        ]
        for channel in channels:
            for name, width in [("valid", 1)] + getattr(
                self, channel
            ).description.payload_layout:
                sig = getattr(getattr(self, channel), name)
                signals[channel + name] = sig
            for name, width in [("ready", 1)]:
                sig = getattr(getattr(self, channel), name)
                signals[channel + name] = sig
        return signals


class PldAXIStreamInterface(AXIStreamInterface):
    def get_signals(self):
        signals = {}
        channels = [
            "valid",
            "ready",
            "first",
            "last",
            "payload",
            "param",
        ]
        for channel in channels:
            sig = getattr(self, channel)
            signals["t" + channel] = sig
        return signals
