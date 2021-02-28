import vexriscv.plugin._
import vexriscv.ip.{DataCacheConfig, InstructionCacheConfig}
import vexriscv.{plugin, VexRiscv, VexRiscvConfig}
import spinal.core._
import spinal.lib._

object VexRiscvStream extends App {
  def cpuOut() : VexRiscv = {
    val config = VexRiscvConfig(
      plugins = List(
        new PcManagerSimplePlugin(
          resetVector = 0x80000000l,
          relaxedPcCalculation = false
        ),
        new IBusCachedPlugin(
          prediction = DYNAMIC_TARGET,
          historyRamSizeLog2 = 8,
          config = InstructionCacheConfig(
            cacheSize = 4096*2,
            bytePerLine =32,
            wayCount = 1,
            addressWidth = 32,
            cpuDataWidth = 32,
            memDataWidth = 32,
            catchIllegalAccess = true,
            catchAccessFault = true,
            asyncTagMemory = false,
            twoCycleRam = false,
            twoCycleCache = true
          )
        ),
        new DBusCachedPlugin(
          config = new DataCacheConfig(
            cacheSize         = 4096*2,
            bytePerLine       = 32,
            wayCount          = 1,
            addressWidth      = 32,
            cpuDataWidth      = 32,
            memDataWidth      = 32,
            catchAccessError  = true,
            catchIllegal      = true,
            catchUnaligned    = true
          )
        ),
        new StaticMemoryTranslatorPlugin(
          ioRange      = _(31 downto 28) === 0xF
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
        new FullBarrelShifterPlugin(earlyInjection = true),
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
        new CsrPlugin(CsrPluginConfig.small),
        new ExternalInterruptArrayPlugin,
        // new DebugPlugin(ClockDomain.current.clone(reset = Bool().setName("debugReset"))),
        new BranchPlugin(
          earlyBranch = false,
          catchAddressMisaligned = true
        ),
        new YamlPlugin("output/VexRiscv.yaml"),
        new StreamrPlugin(streamCount = 1),
        new StreamwPlugin(streamCount = 1)
      )
    )

    val cpu = new VexRiscv(config)

    cpu.rework {
      for (plugin <- config.plugins) plugin match {
        case plugin: IBusSimplePlugin => {
          plugin.iBus.setAsDirectionLess() //Unset IO properties of iBus
          master(plugin.iBus.toWishbone()).setName("iBusWishbone")
        }
        case plugin: IBusCachedPlugin => {
          plugin.iBus.setAsDirectionLess()
          master(plugin.iBus.toWishbone()).setName("iBusWishbone")
        }
        case plugin: DBusSimplePlugin => {
          plugin.dBus.setAsDirectionLess()
          master(plugin.dBus.toWishbone()).setName("dBusWishbone")
        }
        case plugin: DBusCachedPlugin => {
          plugin.dBus.setAsDirectionLess()
          master(plugin.dBus.toWishbone()).setName("dBusWishbone")
        }
        case _ =>
      }
    }
    cpu
  }

  SpinalConfig(
    mode=Verilog,
    targetDirectory="output"
  ).generate(cpuOut())
}