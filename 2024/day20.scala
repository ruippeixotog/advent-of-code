import scala.io.Source
import scala.collection.mutable

object Day20 extends App {
  val in = Source.fromFile("day20.in").getLines.toVector

  val di = Vector(-1, 0, 1, 0)
  val dj = Vector(0, 1, 0, -1)

  def isValid(i: Int, j: Int) = i >= 0 && j >= 0 && i < in.length && j < in(i).length

  val dists = Array.fill[Int](in.length, in(0).length)(Int.MaxValue)

  def bfs(i0: Int, j0: Int): Unit = {
    val q = mutable.Queue[(Int, Int, Int)]((0, i0, j0))
    val seen = mutable.Set[(Int, Int)]()

    while (!q.isEmpty) {
      val (dist, i, j) = q.dequeue()
      if (isValid(i, j) && in(i)(j) != '#' && !seen(i, j)) {
        seen += ((i, j))
        dists(i)(j) = dist
        (0 until 4).foreach { d => q += ((dist + 1, i + di(d), j + dj(d))) }
      }
    }
  }

  val (iEnd, jEnd) = in.indices.flatMap(i => in(i).indices.map((i, _))).find(in(_)(_) == 'E').get
  bfs(iEnd, jEnd)

  def cheatValue(i: Int, j: Int, i1: Int, j1: Int, limit: Int): Int = {
    val step = Math.abs(i - i1) + Math.abs(j - j1)
    if (step > limit) 0
    else if (dists(i)(j) < dists(i1)(j1)) dists(i1)(j1) - dists(i)(j) - step
    else dists(i)(j) - dists(i1)(j1) - step
  }

  val idxs = in.indices.flatMap(i => in(i).indices.map((i, _))).filter(in(_)(_) != '#')

  val cheats1 = for { (i, j) <- idxs.iterator; (i1, j1) <- idxs } yield cheatValue(i, j, i1, j1, 2)
  println(cheats1.count(_ >= 100) / 2)
  val cheats2 = for { (i, j) <- idxs.iterator; (i1, j1) <- idxs } yield cheatValue(i, j, i1, j1, 20)
  println(cheats2.count(_ >= 100) / 2)
}
