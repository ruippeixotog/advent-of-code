import scala.io.Source

object Day18 extends App {
  val in = Source.fromFile("2022/day18.in").getLines.map(_.split(",").map(_.toInt).toVector).toSet

  val dirs = (Vector(1, 0, 0).permutations ++ Vector(-1, 0, 0).permutations).toList

  val bound = in.flatten.min to in.flatten.max
  val faces = in.toList.flatMap { p => dirs.map(p.zip(_).map(_ + _)).filterNot(in) }

  var mem = Map[Vector[Int], Boolean]()

  def isUnbounded(curr: Vector[Int]): Boolean = {
    if (mem.contains(curr)) return mem(curr)
    var visited = Set[Vector[Int]]()

    def aux(curr: Vector[Int]): Boolean =
      if (curr.exists(!bound.contains(_))) true
      else if (in(curr) || visited(curr)) false
      else {
        visited = visited + curr
        dirs.exists { d => aux(curr.zip(d).map(_ + _)) }
      }

    val res = aux(curr)
    mem = mem ++ visited.map((_ -> res))
    res
  }

  println(faces.size)
  println(faces.filter(isUnbounded).size)
}
