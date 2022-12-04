import scala.io.Source

object Day04 extends App {
  val in = Source.fromFile("2022/day04.in").getLines
    .map(_.split(",").map(_.split("-").map(_.toInt))).toList

  println(in.count { case Array(Array(l0, l1), Array(r0, r1)) =>
    l0 <= r0 && l1 >= r1 || r0 <= l0 && r1 >= l1
  })
  println(in.count { case Array(Array(l0, l1), Array(r0, r1)) =>
    l1 >= r0 && r1 >= l0
  })
}
