import scala.io.Source
import scala.collection.mutable

object Day10 extends App {
  val in = Source.fromFile("2023/day10.in").getLines.map(_.toVector).toVector

  val grid: Vector[Vector[Char]] = {
    val bordered =
      Vector.fill(in(0).length + 2)('.') +:
        in.map(row => '.' +: row :+ '.') :+
        Vector.fill(in(0).length + 2)('.')

    def expand(i: Int, j: Int): Vector[Vector[Char]] = bordered(i)(j) match {
      case '.' => Vector(Vector('.', '.', '.'), Vector('.', '.', '.'), Vector('.', '.', '.'))
      case '|' => Vector(Vector('.', 'X', '.'), Vector('.', 'X', '.'), Vector('.', 'X', '.'))
      case '-' => Vector(Vector('.', '.', '.'), Vector('X', 'X', 'X'), Vector('.', '.', '.'))
      case 'L' => Vector(Vector('.', 'X', '.'), Vector('.', 'X', 'X'), Vector('.', '.', '.'))
      case 'J' => Vector(Vector('.', 'X', '.'), Vector('X', 'X', '.'), Vector('.', '.', '.'))
      case '7' => Vector(Vector('.', '.', '.'), Vector('X', 'X', '.'), Vector('.', 'X', '.'))
      case 'F' => Vector(Vector('.', '.', '.'), Vector('.', 'X', 'X'), Vector('.', 'X', '.'))
      case 'S' =>
        Vector(
          Vector('.', expand(i - 1, j)(2)(1), '.'),
          Vector(expand(i, j - 1)(1)(2), 'S', expand(i, j + 1)(1)(0)),
          Vector('.', expand(i + 1, j)(0)(1), '.')
        )
    }

    bordered.indices
      .map { i => bordered(0).indices.map(expand(i, _)).reduce(_.zip(_).map(_ ++ _)) }
      .reduce(_ ++ _)
  }

  val di = Vector(-1, 0, 1, 0)
  val dj = Vector(0, 1, 0, -1)

  val (si, sj) =
    grid.zipWithIndex.map { case (row, i) => (i, row.indexOf('S')) }.find(_._2 != -1).get

  def isValid(i: Int, j: Int) = i >= 0 && j >= 0 && i < grid.length && j < grid(0).length

  def floodFill(i0: Int, j0: Int, fillFunc: (Int, Int) => Boolean): Map[(Int, Int), Int] = {
    var visited = Map[(Int, Int), Int]()
    val q = mutable.Queue[(Int, Int, Int)]()
    q.enqueue((i0, j0, 0))

    while (!q.isEmpty) {
      val (i, j, depth) = q.dequeue()
      if (isValid(i, j) && fillFunc(i, j) && !visited.contains((i, j))) {
        visited = visited + ((i, j) -> depth)
        (0 to 3).foreach { d => q.enqueue((i + di(d), j + dj(d), depth + 1)) }
      }
    }
    visited
  }

  val inPath = floodFill(si, sj, grid(_)(_) != '.')
  val outside = floodFill(0, 0, !inPath.contains(_, _)).keySet

  println(inPath.values.max / 3)
  println {
    (1 until grid.length by 3).map { i =>
      (1 until grid(0).length by 3).count { j =>
        !inPath.contains((i, j)) && !outside((i, j))
      }
    }.sum
  }
}
