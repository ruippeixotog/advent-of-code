import scala.io.Source

object Day20 extends App {
  val in = Source.fromFile("day20.in").getLines.map(_.toLong).toVector
  val decKey = 811589153L

  def mix(xs: Vector[(Long, Int)]): Vector[(Long, Int)] = {
    (0 until xs.length).foldLeft(xs) { (acc, id) =>
      val idx = acc.indexWhere(_._2 == id)
      val newIdx = Math.floorMod(idx + acc(idx)._1, acc.length - 1)
      (acc.slice(0, idx) ++ acc.slice(idx + 1, acc.length)).patch(newIdx, List(acc(idx)), 0)
    }
  }

  def groveCoords(xs: Vector[(Long, Int)]): Long = {
    val idx0 = xs.indexWhere(_._1 == 0)
    List(1000, 2000, 3000).map { i => xs(Math.floorMod(idx0 + i, xs.length))._1 }.sum
  }

  println(groveCoords(mix(in.zipWithIndex)))
  println(groveCoords(LazyList.iterate(in.map(_ * decKey).zipWithIndex)(mix)(10)))
}
