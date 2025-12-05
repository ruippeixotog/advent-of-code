import scala.io.Source

object Day05 extends App {
  val (ranges, ids) = {
    val Array(in1, in2) = Source.fromFile("day05.in").mkString.split("\n\n")
    val ranges = in1.split("\n").map { case s"${n1}-${n2}" => (n1.toLong, n2.toLong) }.toList
    val ids = in2.split("\n").map(_.toLong).toList
    (ranges, ids)
  }

  val mergedRanges = ranges.sorted.foldRight(List[(Long, Long)]()) {
    case ((n1, n2), (n3, n4) :: rest) if n2 >= n3 => (n1, n2.max(n4)) :: rest
    case ((n1, n2), acc) => (n1, n2) :: acc
  }

  println(ids.count { id => mergedRanges.exists(id >= _ && id <= _) })
  println(mergedRanges.map { (n1, n2) => n2 - n1 + 1 }.sum)
}
