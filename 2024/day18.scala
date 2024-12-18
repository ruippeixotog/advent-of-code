import scala.io.Source
import scala.collection.mutable

object Day18 extends App {
  val in = Source.fromFile("day18.in").getLines.map { line =>
    val Array(x, y) = line.split(",")
    (x.toInt, y.toInt)
  }.toVector

  val gridSize = 71
  val dy = Vector(-1, 0, 1, 0)
  val dx = Vector(0, 1, 0, -1)

  def isValid(i: Int, j: Int) = i >= 0 && j >= 0 && i < gridSize && j < gridSize

  def bfs(walls: Set[(Int, Int)]): Option[Int] = {
    val q = mutable.Queue((0, 0, 0))
    val seen = mutable.Set[(Int, Int)]()

    while (!q.isEmpty) {
      val (dist, x, y) = q.dequeue()
      if (x == gridSize - 1 && y == gridSize - 1) return Some(dist)
      if (isValid(x, y) && !walls((x, y)) && !seen(x, y)) {
        seen += ((x, y))
        q.enqueueAll((0 until 4).map { d => (dist + 1, x + dx(d), y + dy(d)) })
      }
    }
    return None
  }

  def findCut(walls: Vector[(Int, Int)], low: Int, high: Int): (Int, Int) = {
    if (low >= high) walls(low - 1)
    else {
      val mid = (low + high) / 2
      bfs(walls.take(mid).toSet) match {
        case None => findCut(walls, low, mid)
        case _ => findCut(walls, mid + 1, high)
      }
    }
  }

  println(bfs(in.take(1024).toSet).get)
  println(findCut(in, 1025, in.length))
}
