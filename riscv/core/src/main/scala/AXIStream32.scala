import spinal.core._
import spinal.lib._

case class AXIStream32() extends Bundle with IMasterSlave{
  val data = Bits(32 bits)
  val valid = Bool
  val ready = Bool

  override def asMaster(): Unit = {
    out(data, valid)
    in(ready)
  }
}