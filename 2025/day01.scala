import scala.io.Source

object Day01 extends App {
  val in = Source.fromFile("day01.in").getLines.map { str => (str.head, str.tail.toInt) }.toList

  val processed = in.scanLeft((0, 50)) {
    case ((_, x), ('R', n)) => ((x + n) / 100, (x + n) % 100)
    case ((_, x), (_, n)) =>
      (if (x == 0) (x - n) / -100 else (x - n - 100) / -100, (x - n + 1000) % 100)
  }

  println(processed.count(_._2 == 0))
  println(processed.map(_._1).sum)
}
