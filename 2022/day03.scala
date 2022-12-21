import scala.io.Source

object Day03 extends App {
  val in = Source.fromFile("2022/day03.in").getLines.toList

  def prio(ch: Char): Int =
    if (ch >= 'a') ch - 'a' + 1 else ch - 'A' + 27

  println(
    in.map { line => line.splitAt(line.length / 2) }
      .map { (l, r) => prio((l.toSet & r.toSet).head) }
      .sum
  )
  println(in.map(_.toSet).grouped(3).map(_.reduce(_ & _).head).map(prio).sum)
}
