import scala.collection.mutable
import scala.io.Source

object Day17 extends App {
  val in = Source.fromFile("2023/day17.in").getLines.map(_.map(_ - '0')).toList

  val di = Vector(-1, 0, 1, 0)
  val dj = Vector(0, 1, 0, -1)

  def isValid(i: Int, j: Int) = i >= 0 && j >= 0 && i < in.length && j < in(0).length
  def rot(d: Int, turns: Int) = (d + turns + 4) % 4

  def dijkstra(is: Int, js: Int, ie: Int, je: Int, minW: Int, maxW: Int): Int = {
    var dists = Map[(Int, Int, Int, Int), Int]()
    val q = mutable.PriorityQueue[(Int, Int, Int, Int, Int)]()(Ordering.by(-_._1))
    q.enqueue((0 to 3).map((0, is, js, _, 0)): _*)

    while (!q.isEmpty) {
      val (dist, i, j, d, nd) = q.dequeue()
      if (!dists.contains((i, j, d, nd))) {
        dists = dists + ((i, j, d, nd) -> dist)
        for {
          d1 <- 0 to 3 if d1 != rot(d, 2) && (d1 == d || nd >= minW) && (d1 != d || nd < maxW)
          (i1, j1) = (i + di(d1), j + dj(d1)) if isValid(i1, j1)
        } q.enqueue((dist + in(i1)(j1), i1, j1, d1, if (d1 == d) nd + 1 else 1))
      }
    }
    dists.filterKeys { (i, j, _, nd) => i == ie && j == je && nd >= minW }.values.min
  }

  println(dijkstra(0, 0, in.length - 1, in(0).length - 1, 0, 3))
  println(dijkstra(0, 0, in.length - 1, in(0).length - 1, 4, 10))
}
