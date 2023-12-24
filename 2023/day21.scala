import scala.io.Source
import scala.collection.mutable

object Day21 extends App {
  val in = Source.fromFile("day21.in").getLines.toList
  val gridSize = in.length

  val di = Vector(-1, 0, 1, 0)
  val dj = Vector(0, 1, 0, -1)

  def isValid(i: Int, j: Int) = i >= 0 && j >= 0 && i < gridSize && j < gridSize

  def bfs(i0: Int, j0: Int, rem2: Int, maxDist: Int): Long = {
    var visited = Map[(Int, Int), Int]()
    val q = mutable.Queue[(Int, Int, Int)]()
    q += ((i0, j0, 0))

    while (!q.isEmpty && q.front._3 <= maxDist) {
      val (i, j, depth) = q.dequeue()
      if (isValid(i, j) && in(i)(j) != '#' && !visited.contains((i, j))) {
        visited = visited + ((i, j) -> depth)
        (0 to 3).foreach { d => q += ((i + di(d), j + dj(d), depth + 1)) }
      }
    }
    visited.filter { (_, dist) => dist % 2 == rem2 }.size.toLong
  }

  val (si, sj) =
    in.zipWithIndex.map { case (row, i) => (i, row.indexOf('S')) }.find(_._2 != -1).get

  println(bfs(si, sj, 0, 64))

  val n = 26501365
  val reps = (n - gridSize / 2) / gridSize // 202300
  
  val startFull = bfs(si, sj, 1, Int.MaxValue)
  val nonstartFull = bfs(si, sj, 0, Int.MaxValue)
  
  val topMid = bfs(gridSize - 1, sj, 1, gridSize - 1)
  val bottomMid = bfs(0, sj, 1, gridSize - 1)
  val leftMid = bfs(si, gridSize - 1, 1, gridSize - 1)
  val rightMid = bfs(si, 0, 1, gridSize - 1)
  
  val topLeftS = bfs(gridSize - 1, gridSize - 1, 0, gridSize / 2 - 1)
  val topLeftL = bfs(gridSize - 1, gridSize - 1, 1, 3 * gridSize / 2 - 1)
  val topRightS = bfs(gridSize - 1, 0, 0, gridSize / 2 - 1)
  val topRightL = bfs(gridSize - 1, 0, 1, 3 * gridSize / 2 - 1)
  val bottomLeftS = bfs(0, gridSize - 1, 0, gridSize / 2 - 1)
  val bottomLeftL = bfs(0, gridSize - 1, 1, 3 * gridSize / 2 - 1)
  val bottomRightS = bfs(0, 0, 0, gridSize / 2 - 1)
  val bottomRightL = bfs(0, 0, 1, 3 * gridSize / 2 - 1)

  println(
    topMid + bottomMid + leftMid + rightMid +
      (topLeftS + topRightS + bottomLeftS + bottomRightS) * reps +
      (topLeftL + topRightL + bottomLeftL + bottomRightL) * (reps - 1) +
      nonstartFull * reps * reps +
      startFull * (reps - 1) * (reps - 1)
  )
}
