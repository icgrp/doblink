import spinal.core._
import spinal.lib._
import vexriscv.plugin.Plugin
import vexriscv.{Stageable, DecoderService, VexRiscv}
// import axiStream32._

class StreamrPlugin(streamCount: Int) extends Plugin[VexRiscv]{

  var streams : Vec[AXIStream32] = null
  
  //Define the concept of IS_STREAMR signals, which specify if the current instruction is destined for this plugin
  object IS_STREAMR extends Stageable(Bool)

  //Callback to setup the plugin and ask for different services
  override def setup(pipeline: VexRiscv): Unit = {
    import pipeline.config._

    //Retrieve the DecoderService instance
    val decoderService = pipeline.service(classOf[DecoderService])

    //Specify the IS_STREAMR default value when instructions are decoded
    decoderService.addDefault(IS_STREAMR, False)

    //Specify the instruction decoding which should be applied when the instruction matches the 'key' parttern
    decoderService.add(
      //Bit pattern of the new STREAMR instruction
      key = M"1111111----------001-----0001011",

      //Decoding specification when the 'key' pattern is recognized in the instruction
      List(
        IS_STREAMR               -> True,
        REGFILE_WRITE_VALID      -> True, //Enable the register file write
        BYPASSABLE_EXECUTE_STAGE -> True, //Notify the hazard management unit that the instruction result is already accessible in the EXECUTE stage (Bypass ready)
        BYPASSABLE_MEMORY_STAGE  -> True, //Same as above but for the memory stage
        RS1_USE                  -> True, //Notify the hazard management unit that this instruction uses the RS1 value
        SRC1_CTRL                -> Src1CtrlEnum.RS // Input comes from register
      )
    )
  }

  override def build(pipeline: VexRiscv): Unit = {
    import pipeline._
    import pipeline.config._

    // Create Streams
    streams = Vec(slave(AXIStream32()), streamCount)

    //Add a new scope on the execute stage (used to give a name to signals)
    execute plug new Area {
      val rs1 = execute.input(RS1) // Value of the regfile[RS1]
      val rd = Bits(32 bits)

      rd := 0 // Default value
      for(i <- 0 until streamCount) {
        val stream = streams(i)
        stream.setName("readStream" + i)

        stream.ready := False
        when(execute.arbitration.isValid && execute.input(IS_STREAMR) && rs1 === i) {
           stream.ready := True
           when(stream.valid) {
             rd := stream.data
           }.otherwise {
             execute.arbitration.haltItself := True
           }
        }
      }

      // When the instruction is a STREAMR, write the result into the register file data path.
      when(execute.input(IS_STREAMR)) {
        execute.output(REGFILE_WRITE_DATA) := rd
      }
    }
  }
}