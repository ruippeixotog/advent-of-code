import scala.io.Source

object Day01 extends App {
  val in = Source.fromFile("day01.in").mkString.split("\n\n").map(_.split("\n").map(_.toInt))
  val cals = in.map(_.sum).sortBy(-_)
  println(cals.head)
  println(cals.take(3).sum)
}
