import scala.io.Source

object Day06 extends App {
  val in = Source.fromFile("day06.in").getLines.toVector

  val (i0, j0) = in.indices.flatMap(i => in(i).indices.map((i, _))).find(in(_)(_) == '^').get

  val di = Vector(-1, 0, 1, 0)
  val dj = Vector(0, 1, 0, -1)

  def isValid(grid: Vector[String], i: Int, j: Int) =
    i >= 0 && j >= 0 && i < grid.length && j < grid(i).length

  def walk(grid: Vector[String], i: Int, j: Int, d: Int, seen: Set[(Int, Int, Int)]): Option[Set[(Int, Int)]] = {
    if(!isValid(grid, i, j)) Some(seen.map(p => (p._1, p._2)))
    else if(seen.contains(i, j, d)) None
    else {
      val i1 = i + di(d)
      val j1 = j + dj(d)
      if(isValid(grid, i1, j1) && grid(i1)(j1) == '#') walk(grid, i, j, (d + 1) % 4, seen)
      else walk(grid, i1, j1, d, seen + ((i, j, d)))
    }
  }

  val walked = walk(in, i0, j0, 0, Set()).get
  println(walked.size)
  println {
    walked.count { (i, j) =>
      (i != i0 || j != j0) && walk(in.updated(i, in(i).updated(j, '#')), i0, j0, 0, Set()).isEmpty
    }
  }
}
