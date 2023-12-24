import scala.io.Source
import scala.collection.mutable.PriorityQueue

object Day08 extends App {
  val patt = """(.+) = \((.+), (.+)\)""".r

  val (dirs, graph) = Source.fromFile("day08.in").mkString.split("\n\n").toList match {
    case List(dirs, rulesStr) =>
      val graph = rulesStr.split("\n")
        .collect { case patt(from, toL, toR) => from -> (toL, toR) }
        .toMap
      (dirs, graph)
  }

  def pathFrom(start: String): Iterator[String] =
    Iterator.continually(dirs).flatten
      .scanLeft(start) { (curr, d) => if (d == 'L') graph(curr)._1 else graph(curr)._2 }

  def gcd(a: Long, b: Long): Long = if (b == 0) a else gcd(b, a % b)
  def lcm(a: Long, b: Long): Long = a * b / gcd(a, b)

  println(pathFrom("AAA").takeWhile(_ != "ZZZ").length)

  println {
    graph.keys.filter(_.endsWith("A"))
      .map { st => pathFrom(st).takeWhile(!_.endsWith("Z")).length.toLong }
      .reduce(lcm)
  }
}
