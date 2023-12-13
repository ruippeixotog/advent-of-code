import scala.io.Source

object Day06 extends App {
  val patt = """(?s)Time: +([0-9].+)\nDistance: +([0-9].+)\n""".r

  def getIntVec(str: String): List[Long] = str.trim.split(" +").map(_.toLong).toList
  def getSpacedInt(str: String): Long = str.replace(" ", "").toLong

  val in1 = Source.fromFile("2023/day06.in").mkString match {
    case patt(timesStr, distsStr) =>
      getIntVec(timesStr).zip(getIntVec(distsStr))
  }
  val in2 = Source.fromFile("2023/day06.in").mkString match {
    case patt(timesStr, distsStr) =>
      List(getSpacedInt(timesStr) -> getSpacedInt(distsStr))
  }

  def strictCeil(x: Double): Long =
    if (x == x.toLong) x.toLong + 1 else Math.ceil(x).toLong

  def strictFloor(x: Double): Long =
    if (x == x.toLong) x.toLong - 1 else Math.floor(x).toLong

  def numWays(t: Long, d: Long): Long = {
    val low = strictCeil((t - Math.sqrt(t * t - 4 * d)) / 2)
    val high = strictFloor((t + Math.sqrt(t * t - 4 * d)) / 2)
    high - low + 1
  }

  println(in1.map(numWays).product)
  println(in2.map(numWays).product)
}
