import scala.io.Source

object Day23 extends App {
  val in = Source.fromFile("day23.in").getLines.toVector

  val di = Vector(-1, 0, 1, 0)
  val dj = Vector(0, 1, 0, -1)
  val slides = Map('^' -> 0, '>' -> 1, 'v' -> 2, '<' -> 3)

  type Pos = (Int, Int)

  val startPos = (0, 1)
  val endPos = (in.length - 1, in(0).length - 2)

  def validDirs(i: Int, j: Int, useSlides: Boolean): List[Int] = in(i)(j) match {
    case '#' => Nil
    case ch if useSlides && slides.contains(ch) => List(slides(ch))
    case ch => (0 to 3).toList
  }

  def buildGraph(useSlides: Boolean): Map[Pos, List[(Pos, Int)]] = {
    def followPath(i: Int, j: Int, d: Int, dist: Int = 1): Option[(Pos, Int)] = {
      if ((i, j) == endPos) Some(((i, j), dist))
      else if (i < 0 || i >= in.length) None
      else {
        val adjs = validDirs(i, j, useSlides)
          .map { d1 => (i + di(d1), j + dj(d1), d1) }
          .filter { (i1, j1, d1) => d1 != (d + 2) % 4 && i1 >= 0 && in(i1)(j1) != '#' }

        adjs match {
          case Nil => None
          case (i1, j1, d1) :: Nil => followPath(i1, j1, d1, dist + 1)
          case _ => Some(((i, j), dist))
        }
      }
    }
    def expand(p: Pos, graph: Map[Pos, List[(Pos, Int)]]): Map[Pos, List[(Pos, Int)]] = {
      if (graph.contains(p)) graph
      else {
        val adjs = (0 to 3).flatMap { d => followPath(p._1 + di(d), p._2 + dj(d), d) }
        val newGraph = graph + (p -> adjs.toList)
        adjs.foldRight(newGraph) { (adj, acc) => expand(adj._1, acc) }
      }
    }
    expand(startPos, Map.empty)
  }

  def longestDist(graph: Map[Pos, List[(Pos, Int)]]): Option[Int] = {
    def aux(p: Pos, dist: Int, visited: Set[Pos]): Option[Int] = {
      if (p == endPos) Some(dist)
      else if (visited(p)) None
      else graph(p).flatMap { case (p1, dist1) => aux(p1, dist + dist1, visited + p) }.maxOption
    }
    aux(startPos, 0, Set.empty)
  }

  println(longestDist(buildGraph(true)).get)
  println(longestDist(buildGraph(false)).get)
}
