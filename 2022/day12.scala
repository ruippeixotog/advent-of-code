import scala.io.Source
import scala.collection.immutable.Queue

object Day12 extends App {
  val in = Source.fromFile("day12.in").getLines.toVector

  val indices = for (i <- 0 until in.length; j <- 0 until in(i).length) yield (i, j)
  val revIdx = indices.groupBy(in(_)(_))

  def elevation(i: Int, j: Int): Int = in(i)(j) match {
    case 'S' => 'a'
    case 'E' => 'z'
    case ch => ch
  }

  def bfs(from: (Int, Int)): Int = {
    def aux(q: Queue[((Int, Int), Int)], visited: Set[(Int, Int)]): Int = q.dequeueOption match {
      case None => Int.MaxValue
      case Some((((i, j), depth), _)) if in(i)(j) == 'E' => depth
      case Some((((i, j), depth), q)) =>
        val neighbors =
          List((i - 1, j), (i + 1, j), (i, j - 1), (i, j + 1))
            .filter { (i1, j1) => i1 >= 0 && i1 < in.length && j1 >= 0 && j1 < in(i1).length }
            .filter { (i1, j1) => elevation(i1, j1) - elevation(i, j) <= 1 }
            .filterNot(visited)

        aux(q ++ neighbors.map((_, depth + 1)), visited ++ neighbors)
    }
    aux(Queue((from, 0)), Set(from))
  }

  println(bfs(revIdx('S').head))
  println((revIdx('S') ++ revIdx('a')).map(bfs).min)
}
