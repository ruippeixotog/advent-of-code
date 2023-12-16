import scala.collection.mutable
import scala.io.Source

object Day16 extends App {
  val in = Source.fromFile("2023/day16.in").getLines.toVector

  val di = Vector(-1, 0, 1, 0)
  val dj = Vector(0, 1, 0, -1)

  def isValid(i: Int, j: Int) = i >= 0 && j >= 0 && i < in.length && j < in(0).length

  def newDirs(d: Int, ch: Char): List[Int] = ch match {
    case '.' => List(d)
    case '|' if d == 0 || d == 2 => List(d)
    case '|' => List(0, 2)
    case '-' if d == 1 || d == 3 => List(d)
    case '-' => List(1, 3)
    case '/' => List((if (d % 2 == 0) d + 1 else d + 3) % 4)
    case '\\' => List((if (d % 2 == 0) d + 3 else d + 1) % 4)
  }

  def step(beams: List[(Int, Int, Int)]): List[(Int, Int, Int)] = beams
    .flatMap { (i, j, d) => newDirs(d, in(i)(j)).map((i, j, _)) }
    .map { (i, j, d) => (i + di(d), j + dj(d), d) }
    .filter { (i, j, d) => isValid(i, j) }

  def sim(i0: Int, j0: Int, d: Int): Set[(Int, Int)] = {
    val visited = mutable.Set[(Int, Int, Int)]()

    def aux(beams: List[(Int, Int, Int)]): Set[(Int, Int)] =
      beams.filterNot(visited) match {
        case Nil => visited.map(_.init).toSet
        case beams1 =>
          visited ++= beams1
          aux(step(beams1))
      }
    aux(List((i0, j0, d)))
  }

  println(sim(0, 0, 1).size)

  val inits = in.indices.map((_, 0, 1)) ++ in.indices.map((_, in(0).length - 1, 3)) ++
    in(0).indices.map((0, _, 2)) ++ in(0).indices.map((in.length - 1, _, 0))

  println(inits.map(sim(_, _, _).size).max)
}
