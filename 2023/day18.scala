import scala.io.Source

object Day18 extends App {
  val patt = """([UDLR]) ([0-9]+) \(#([a-f0-9]+)([a-f0-9])\)""".r
  val hexToDir = Map("0" -> 'R', "1" -> 'D', "2" -> 'L', "3" -> 'U')

  val (in1, in2) = Source.fromFile("day18.in").getLines.map {
    case patt(dStr, nStr, n2Hex, d2Hex) =>
      ((dStr(0), nStr.toInt), (hexToDir(d2Hex), Integer.parseInt(n2Hex, 16)))
  }.toList.unzip

  def baseArea(in: List[(Char, Int)]): Long =
    in.scanLeft((0L, 0L)) {
      case ((i, j), ('U', n)) => (i - n, j)
      case ((i, j), ('D', n)) => (i + n, j)
      case ((i, j), ('L', n)) => (i, j - n)
      case ((i, j), ('R', n)) => (i, j + n)
    }.sliding(2)
      .map { case List((i1, j1), (i2, j2)) => (i1 + i2) * (j1 - j2) }
      .sum / 2

  def discreteFix(in: List[(Char, Int)]): Long =
    in.map(_._2.toLong).sum / 2 + 1

  println(baseArea(in1) + discreteFix(in1))
  println(baseArea(in2) + discreteFix(in2))
}
