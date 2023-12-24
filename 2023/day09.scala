import scala.io.Source

object Day09 extends App {
  val in = Source.fromFile("day09.in").getLines.toList
    .map(_.split(" ").toList.map(_.toInt))

  def solve(xs: List[Int]): Int =
    if (xs.forall(_ == 0)) 0
    else xs.head + solve(xs.sliding(2).map(_.reduce(_ - _)).toList)

  println(in.map(_.reverse).map(solve).sum)
  println(in.map(solve).sum)
}
