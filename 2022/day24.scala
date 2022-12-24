import scala.io.Source
import scala.collection.immutable.Queue

object Day24 extends App {
  val in = Source.fromFile("2022/day24.in").getLines.toVector

  val dirChars = Vector('^', 'v', '<', '>')
  val dirs = List((-1, 0), (1, 0), (0, -1), (0, 1))

  val blizs = in.flatten.map(dirChars.indexOf).zipWithIndex.filter(_._2 != -1)
    .map { (d, idx) => (idx / in(0).length, idx % in(0).length, d) }.toSet

  val (iEnd, jEnd) = (in.length - 1, in(0).length - 2)
  val phase = (in.length - 2) * (in(0).length - 2)

  def bfs(tFrom: Int, iFrom: Int, jFrom: Int, iTo: Int, jTo: Int): Int = {
    var visited = Set[(Int, Int, Int)]()

    def isBlocked(t: Int, i: Int, j: Int): Boolean = {
      i < 0 || i >= in.length || in(i)(j) == '#' || visited((i, j, t % phase)) ||
      (i > 0 && i < in.length - 1 && dirs.zipWithIndex.exists { case ((di, dj), d) =>
        val ib = Math.floorMod(i - 1 - t * di, in.length - 2) + 1
        val jb = Math.floorMod(j - 1 - t * dj, in(i).length - 2) + 1
        blizs((ib, jb, d))
      })
    }

    def aux(q: Queue[(Int, Int, Int)]): Int = q.dequeue match {
      case ((t, `iTo`, `jTo`), _) => t
      case ((t, i, j), qNext) if isBlocked(t, i, j) => aux(qNext)
      case ((t, i, j), qNext) =>
        visited = visited + ((i, j, t % phase))
        aux(qNext ++ ((0, 0) :: dirs).map { (di, dj) => (t + 1, i + di, j + dj) })
    }
    aux(Queue((tFrom, iFrom, jFrom)))
  }

  println(bfs(0, 0, 1, iEnd, jEnd))
  println {
    List((iEnd, jEnd), (0, 1), (iEnd, jEnd)).foldLeft((0, 0, 1)) { case ((ts, is, js), (ie, je)) =>
      (bfs(ts, is, js, ie, je), ie, je)
    }._1
  }
}
