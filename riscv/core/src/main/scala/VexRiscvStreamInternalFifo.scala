import vexriscv.plugin._
import vexriscv.ip.{DataCacheConfig, InstructionCacheConfig}
import vexriscv.{plugin, VexRiscv, VexRiscvConfig}
import spinal.core._
import spinal.lib._
import spinal.lib.bus.wishbone.{Wishbone, WishboneConfig}
import vexriscv.plugin.CsrAccess.WRITE_ONLY


case class FifoStream() extends Bundle with IMasterSlave {
  val valid = Bool
  val data = Bits(32 bits)
  val ready = Bool

  override def asMaster(): Unit = {
    out(valid, data)
    in(ready)
  }
}

class Fifo extends Component {
  val io = new Bundle {
    val push = slave(FifoStream())
    val pop = master(FifoStream())
  }
  val pushTo = Counter(32)
  val popFrom = Counter(32)
  val full = Reg(Bool) init(False)
  val data = Vec(Reg(Bits(32 bits)), 32)
      
  io.push.ready := pushTo.value =/= popFrom.value | (~full)
  io.pop.valid := pushTo.value =/= popFrom.value | full
  io.pop.data := data(popFrom.value)

  when(io.push.valid & io.push.ready) {
    data(pushTo.value) := io.push.data
    full := (pushTo.value + 1) === popFrom.value
    pushTo.increment()
  }
  when(io.pop.valid & io.pop.ready) {
    popFrom.increment()
    full := False
  }
}

class VexRiscvStreamWithFifo extends Component {
    val config = VexRiscvConfig(
      plugins = List(
        new IBusCachedPlugin(
            resetVector = null,
            relaxedPcCalculation = false,
            prediction = STATIC,
            compressedGen = false,
            config = InstructionCacheConfig(
              cacheSize = 4096,
              bytePerLine = 32,
              wayCount = 1,
              addressWidth = 32,
              cpuDataWidth = 32,
              memDataWidth = 32,
              catchIllegalAccess = true,
              catchAccessFault = true,
              asyncTagMemory = false,
              twoCycleRam = false,
              twoCycleCache = false
            )
          ),
        new DBusCachedPlugin(
            dBusCmdMasterPipe = true,
            dBusCmdSlavePipe = true,
            dBusRspSlavePipe = false,
            relaxedMemoryTranslationRegister = false,
            config = new DataCacheConfig(
              cacheSize = 4096,
              bytePerLine = 32,
              wayCount = 1,
              addressWidth = 32,
              cpuDataWidth = 32,
              memDataWidth = 32,
              catchAccessError = true,
              catchIllegal = true,
              catchUnaligned = true,
              withLrSc = false,
              withAmo = false,
              earlyWaysHits = true
            ),
            csrInfo = true
          ),
        new StaticMemoryTranslatorPlugin(
          ioRange      = _.msb
        ),
        new DecoderSimplePlugin(
          catchIllegalInstruction = true
        ),
        new RegFilePlugin(
          regFileReadyKind = plugin.SYNC,
          zeroBoot = false
        ),
        new IntAluPlugin,
        new SrcPlugin(
          separatedAddSub = false,
          executeInsertion = true
        ),
        new FullBarrelShifterPlugin,
        new HazardSimplePlugin(
          bypassExecute           = true,
          bypassMemory            = true,
          bypassWriteBack         = true,
          bypassWriteBackBuffer   = true,
          pessimisticUseSrc       = false,
          pessimisticWriteRegFile = false,
          pessimisticAddressMatch = false
        ),
        new MulPlugin,
        new DivPlugin,
        new CsrPlugin(CsrPluginConfig.small(mtvecInit = null).copy(mtvecAccess = WRITE_ONLY, ecallGen = true, wfiGenAsNop = true)),
        new ExternalInterruptArrayPlugin(
          machineMaskCsrId = 0xBC0,
          machinePendingsCsrId = 0xFC0,
          supervisorMaskCsrId = 0x9C0,
          supervisorPendingsCsrId = 0xDC0
        ),
        // new DebugPlugin(ClockDomain.current.clone(reset = Bool().setName("debugReset"))),
        new BranchPlugin(
          earlyBranch = false,
          catchAddressMisaligned = true
        ),
        new YamlPlugin("output/VexRiscvStreamWithFifo.yaml"),
        new StreamrPlugin(streamCount = 1),
        new StreamwPlugin(streamCount = 1)
      )
    )      

    val cpu = new VexRiscv(config)
    var iBus : Wishbone = null
    var dBus : Wishbone = null

    cpu.rework {
      for (plugin <- config.plugins) plugin match {
        // case plugin: IBusSimplePlugin => {
        //   plugin.iBus.setAsDirectionLess() //Unset IO properties of iBus
        //   master(plugin.iBus.toWishbone()).setName("iBusWishbone")
        // }
        case plugin: IBusCachedPlugin => {
          plugin.iBus.setAsDirectionLess()
          iBus = master(plugin.iBus.toWishbone())
        }
        // case plugin: DBusSimplePlugin => {
        //   plugin.dBus.setAsDirectionLess()
        //   master(plugin.dBus.toWishbone()).setName("dBusWishbone")
        // }
        case plugin: DBusCachedPlugin => {
          plugin.dBus.setAsDirectionLess()
          dBus = master(plugin.dBus.toWishbone())
        }
        case _ =>
      }
    }

    val fifo = new Fifo
    var iBusConfig : WishboneConfig = null
    var dBusConfig : WishboneConfig = null

    for(plugin <- config.plugins) plugin match{
      case plugin: StreamrPlugin => {
        val stream = plugin.streams(0)
        stream.valid := fifo.io.pop.valid
        stream.data := fifo.io.pop.data
        fifo.io.pop.ready := stream.ready
      }
      case plugin: StreamwPlugin => {
        val stream = plugin.streams(0)
        fifo.io.push.valid := stream.valid
        fifo.io.push.data := stream.data
        stream.ready := fifo.io.push.ready
      }
      case plugin: IBusCachedPlugin => {
        iBusConfig = plugin.config.getWishboneConfig()
      }
      case plugin: DBusCachedPlugin => {
        dBusConfig = plugin.config.getWishboneConfig()
      }
      case _ =>
    }

    val io = new Bundle {
      val iBusWishbone = master(Wishbone(iBusConfig))
      val dBusWishbone = master(Wishbone(dBusConfig))
      val timerInterrupt = in Bool
      val softwareInterrupt = in Bool
      val externalInterruptArray = in(Bits(32 bits))
      val externalResetVector = in(UInt(32 bits))
    }
    io.iBusWishbone.setName("iBusWishbone")
    io.dBusWishbone.setName("dBusWishbone")

    iBus >> io.iBusWishbone
    dBus >> io.dBusWishbone

    io.timerInterrupt.setName("timerInterrupt")
    io.softwareInterrupt.setName("softwareInterrupt")
    io.externalInterruptArray.setName("externalInterruptArray")
    io.externalResetVector.setName("externalResetVector")

    for(plugin <- config.plugins) plugin match{
      case plugin: CsrPlugin => {
        plugin.timerInterrupt := io.timerInterrupt
        plugin.softwareInterrupt := io.softwareInterrupt
      }
      case plugin: IBusCachedPlugin => {
        plugin.externalResetVector := io.externalResetVector
      }
      case plugin: ExternalInterruptArrayPlugin => {
        plugin.externalInterruptArray := io.externalInterruptArray
      }
      case _ =>
    }
}

object VexRiscvStreamInternalFifo extends App {
  def cpuOut() : VexRiscvStreamWithFifo = {//VexRiscv = {
    val cpu = new VexRiscvStreamWithFifo
    // val config = VexRiscvConfig(
    //   plugins = List(
    //     new PcManagerSimplePlugin(
    //       resetVector = 0x80000000l,
    //       relaxedPcCalculation = false
    //     ),
    //     new IBusCachedPlugin(
    //       prediction = DYNAMIC_TARGET,
    //       historyRamSizeLog2 = 8,
    //       config = InstructionCacheConfig(
    //         cacheSize = 4096*2,
    //         bytePerLine =32,
    //         wayCount = 1,
    //         addressWidth = 32,
    //         cpuDataWidth = 32,
    //         memDataWidth = 32,
    //         catchIllegalAccess = true,
    //         catchAccessFault = true,
    //         asyncTagMemory = false,
    //         twoCycleRam = false,
    //         twoCycleCache = true
    //       )
    //     ),
    //     new DBusCachedPlugin(
    //       config = new DataCacheConfig(
    //         cacheSize         = 4096*2,
    //         bytePerLine       = 32,
    //         wayCount          = 1,
    //         addressWidth      = 32,
    //         cpuDataWidth      = 32,
    //         memDataWidth      = 32,
    //         catchAccessError  = true,
    //         catchIllegal      = true,
    //         catchUnaligned    = true
    //       )
    //     ),
    //     new StaticMemoryTranslatorPlugin(
    //       ioRange      = _(31 downto 28) === 0xF
    //     ),
    //     new DecoderSimplePlugin(
    //       catchIllegalInstruction = true
    //     ),
    //     new RegFilePlugin(
    //       regFileReadyKind = plugin.SYNC,
    //       zeroBoot = false
    //     ),
    //     new IntAluPlugin,
    //     new SrcPlugin(
    //       separatedAddSub = false,
    //       executeInsertion = true
    //     ),
    //     new FullBarrelShifterPlugin(earlyInjection = true),
    //     new HazardSimplePlugin(
    //       bypassExecute           = true,
    //       bypassMemory            = true,
    //       bypassWriteBack         = true,
    //       bypassWriteBackBuffer   = true,
    //       pessimisticUseSrc       = false,
    //       pessimisticWriteRegFile = false,
    //       pessimisticAddressMatch = false
    //     ),
    //     new MulPlugin,
    //     new DivPlugin,
    //     new CsrPlugin(CsrPluginConfig.small),
    //     // new DebugPlugin(ClockDomain.current.clone(reset = Bool().setName("debugReset"))),
    //     new BranchPlugin(
    //       earlyBranch = false,
    //       catchAddressMisaligned = true
    //     ),
    //     new YamlPlugin("output/VexRiscvInternalFifo.yaml"),
    //     new StreamrPlugin(streamCount = 1),
    //     new StreamwPlugin(streamCount = 1)
    //   )
    // )      

    // val cpu = new VexRiscv(config)

    // cpu.rework {
    //   for (plugin <- config.plugins) plugin match {
    //     case plugin: IBusSimplePlugin => {
    //       plugin.iBus.setAsDirectionLess() //Unset IO properties of iBus
    //       master(plugin.iBus.toWishbone()).setName("iBusWishbone")
    //     }
    //     case plugin: IBusCachedPlugin => {
    //       plugin.iBus.setAsDirectionLess()
    //       master(plugin.iBus.toWishbone()).setName("iBusWishbone")
    //     }
    //     case plugin: DBusSimplePlugin => {
    //       plugin.dBus.setAsDirectionLess()
    //       master(plugin.dBus.toWishbone()).setName("dBusWishbone")
    //     }
    //     case plugin: DBusCachedPlugin => {
    //       plugin.dBus.setAsDirectionLess()
    //       master(plugin.dBus.toWishbone()).setName("dBusWishbone")
    //     }
    //     case _ =>
    //   }
    // }

    // val fifo = new Fifo

    // for(plugin <- config.plugins) plugin match{
    //   case plugin: StreamrPlugin => {
    //     val stream = master(plugin.streams(0))
    //     stream.valid := fifo.pop.valid
    //     stream.data := fifo.pop.data
    //     fifo.pop.ready := stream.ready
    //   }
    //   case plugin: StreamwPlugin => {
    //     val stream = slave(plugin.streams(0))
    //     fifo.push.valid := stream.valid
    //     fifo.push.data := stream.data
    //     stream.ready := fifo.push.ready
    //   }
    //   case _ =>
    // }

    cpu
  }

  SpinalConfig(
    mode=Verilog,
    targetDirectory="output"
  ).generate(cpuOut())
}