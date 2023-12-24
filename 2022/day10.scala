import scala.io.Source

object Day10 extends App {
  val in = Source.fromFile("day10.in").getLines.map(_.split(" ")).toList

  val xs = in.flatMap {
    case Array("addx", n) => List(0, n.toInt)
    case Array("noop") => List(0)
  }.scanLeft(1)(_ + _).init

  println {
    xs.zip(Stream.from(1)).filter { (_, i) => (i - 20) % 40 == 0 }.map(_ * _).sum
  }

  println {
    xs.zip(Stream.continually(1 to 40).flatten)
      .map { (x, i) => if (x >= i - 2 && x <= i) '#' else '.' }
      .grouped(40)
      .map(_.mkString)
      .mkString("\n")
  }
}
