import scala.io.Source

object Day15 extends App {
  val Array(gridStr, movesStr) = Source.fromFile("day15.in").mkString.split("\n\n")
  val gridP1 = gridStr.split("\n").map(_.toVector).toVector
  val moves = movesStr.replace("\n", "").toList

  val di = Map('^' -> -1, '>' -> 0, 'v' -> 1, '<' -> 0)
  val dj = Map('^' -> 0, '>' -> 1, 'v' -> 0, '<' -> -1)

  type Grid = Vector[Vector[Char]]

  extension (grid: Grid) {
    def isValid(i: Int, j: Int) = i >= 0 && j >= 0 && i < grid.length && j < grid(i).length
    def updated(i: Int, j: Int, ch: Char) = grid.updated(i, grid(i).updated(j, ch))

    def move(i0: Int, j0: Int, d: Char): Option[Grid] = {
      def auxFront(i: Int, j: Int) = grid(i + di(d))(j + dj(d)) match {
        case '#' => None
        case '.' => Some(grid.updated(i + di(d), j + dj(d), grid(i)(j)))
        case ch => aux(i + di(d), j + dj(d)).map(_.updated(i + di(d), j + dj(d), grid(i)(j)))
      }
      def aux(i: Int, j: Int): Option[Grid] = grid(i + di(d))(j + dj(d)) match {
        case '[' if di(d) != 0 => auxFront(i, j).flatMap(_.move(i + di(d), j + 1 + dj(d), d))
        case ']' if di(d) != 0 => auxFront(i, j).flatMap(_.move(i + di(d), j - 1 + dj(d), d))
        case ch => auxFront(i, j)
      }
      aux(i0, j0).map(_.updated(i0, j0, '.'))
    }
  }

  def solve(grid: Grid, moves: List[Char]): Grid = {
    val (i0, j0) =
      grid.indices.flatMap(i => grid(i).indices.map((i, _))).find(grid(_)(_) == '@').get

    moves.foldLeft((grid.updated(i0, j0, '.'), i0, j0)) { case ((acc, i, j), d) =>
      acc.move(i, j, d) match {
        case Some(acc1) => (acc1, i + di(d), j + dj(d))
        case None => (acc, i, j)
      }
    }._1
  }

  def coords(grid: Grid): Iterable[Int] = {
    for (i <- grid.indices; j <- grid(i).indices; if grid(i)(j) == 'O' || grid(i)(j) == '[')
      yield 100 * i + j
  }

  println(coords(solve(gridP1, moves)).sum)

  val gridP2 = gridP1.map { line =>
    line.flatMap {
      case '#' => "##"
      case 'O' => "[]"
      case '.' => ".."
      case '@' => "@."
    }
  }
  println(coords(solve(gridP2, moves)).sum)
}
