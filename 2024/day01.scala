import scala.io.Source

object Day01 extends App {
  val in = Source.fromFile("day01.in").getLines.map { line =>
    val Array(a, b) = line.split("\\s+").map(_.toInt)
    (a, b)
  }.toList

  val (in1, in2) = in.unzip()
  println(in1.sorted().zip(in2.sorted()).map(_ - _).map(Math.abs).sum)

  val in2Hist = in2.groupBy(identity).mapValues(_.length).toMap
  println(in1.map(x => x * in2Hist.getOrElse(x, 0)).sum)
}
