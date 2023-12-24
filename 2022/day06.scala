import scala.io.Source

object Day06 extends App {
  val in = Source.fromFile("day06.in").mkString

  println(in.sliding(4).indexWhere(_.toSet.size == 4) + 4)
  println(in.sliding(14).indexWhere(_.toSet.size == 14) + 14)
}
