import scala.io.Source

object Day13 extends App {
  val regex =
    "(?s).*Button A: X\\+(\\d+), Y\\+(\\d+)\nButton B: X\\+(\\d+), Y\\+(\\d+)\nPrize: X=(\\d+), Y=(\\d+).*".r

  val in = Source.fromFile("day13.in").mkString.split("\n\n").map {
    case regex(axStr, ayStr, bxStr, byStr, pxStr, pyStr) =>
      (axStr.toLong, ayStr.toLong, bxStr.toLong, byStr.toLong, pxStr.toLong, pyStr.toLong)
  }.toList

  def calcTokens(ax: Long, ay: Long, bx: Long, by: Long, px: Long, py: Long): Long = {
    val det = ax * by - bx * ay
    if (det == 0) 0
    else {
      val aNum = px * by - bx * py
      val bNum = ax * py - px * ay
      if (aNum % det == 0 && bNum % det == 0) 3 * aNum / det + bNum / det
      else 0
    }
  }

  println(in.map(calcTokens).sum)
  println {
    in.map { (ax, ay, bx, by, px, py) =>
      calcTokens(ax, ay, bx, by, 10000000000000L + px, 10000000000000L + py)
    }.sum
  }
}
