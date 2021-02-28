import spinal.core._
import spinal.lib._
import vexriscv.plugin.Plugin
import vexriscv.{Stageable, DecoderService, VexRiscv}
// import axiStream32._

class StreamwPlugin(streamCount: Int) extends Plugin[VexRiscv]{

  var streams : Vec[AXIStream32] = null
  
  //Define the concept of IS_STREAMW signals, which specify if the current instruction is destined for this plugin
  object IS_STREAMW extends Stageable(Bool)

  //Callback to setup the plugin and ask for different services
  override def setup(pipeline: VexRiscv): Unit = {
    import pipeline.config._

    //Retrieve the DecoderService instance
    val decoderService = pipeline.service(classOf[DecoderService])

    //Specify the IS_STREAMW default value when instructions are decoded
    decoderService.addDefault(IS_STREAMW, False)

    //Specify the instruction decoding which should be applied when the instruction matches the 'key' parttern
    decoderService.add(
      //Bit pattern of the new STREAMW instruction
      key = M"1111111----------000-----0001011",

      //Decoding specification when the 'key' pattern is recognized in the instruction
      List(
        IS_STREAMW               -> True,
        // BYPASSABLE_EXECUTE_STAGE -> True, //Notify the hazard management unit that the instruction result is already accessible in the EXECUTE stage (Bypass ready)
        BYPASSABLE_MEMORY_STAGE  -> True, //Same as above but for the memory stage
        RS1_USE                  -> True, //Notify the hazard management unit that this instruction uses the RS1 value
        RS2_USE                  -> True,  //Same than above but for RS2.
        SRC1_CTRL                -> Src1CtrlEnum.RS, // Input comes from register
        SRC2_CTRL                -> Src1CtrlEnum.RS
      )
    )
  }

  override def build(pipeline: VexRiscv): Unit = {
    import pipeline._
    import pipeline.config._

    // Create Streams
    streams = Vec(master(AXIStream32()), streamCount)

    //Add a new scope on the execute stage (used to give a name to signals)
    memory plug new Area {
      val rs1 = memory.input(RS1) // Value of the regfile[RS1]
      val rs2 = memory.input(RS2) // Value of the regfile[RS2]

      for(i <- 0 until streamCount) {
        val stream = streams(i)
        stream.setName("writeStream" + i)

        stream.valid := False
        stream.data := 0
        when(memory.arbitration.isValid && memory.input(IS_STREAMW) && rs1 === i) {
           stream.valid := True
           when(stream.ready) {
             stream.data := rs2
           }.otherwise {
             memory.arbitration.haltItself := True
           }
        }
      }
    }
  }
}