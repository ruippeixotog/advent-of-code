import scala.io.Source

object Day14 extends App {
  val in = Source.fromFile("2022/day14.in").getLines
    .map(_.split(" -> ").map(_.split(",").map(_.toInt)))

  def points(x0: Int, y0: Int, x1: Int, y1: Int): Iterable[(Int, Int)] =
    for { x <- x0.min(x1) to x0.max(x1); y <- y0.min(y1) to y0.max(y1) } yield (x, y)

  val initialGrid = in.flatMap(_.sliding(2)).foldLeft(Set[(Int, Int)]()) {
    case (grid, Array(Array(x0, y0), Array(x1, y1))) => grid ++ points(x0, y0, x1, y1)
  }

  val bottomY = initialGrid.map(_._2).max + 1

  def dropSand(grid: Set[(Int, Int)], stack: List[(Int, Int)]): LazyList[(Int, Int)] = stack match {
    case Nil => LazyList()
    case (x, y) :: rest if y >= bottomY => (x, y) #:: dropSand(grid + ((x, y)), rest)
    case (x, y) :: rest =>
      List((x, y + 1), (x - 1, y + 1), (x + 1, y + 1)).filterNot(grid) match {
        case Nil => (x, y) #:: dropSand(grid + ((x, y)), rest)
        case cs => dropSand(grid, cs ++: (x, y) +: rest)
      }
  }

  val steps = dropSand(initialGrid, List((500, 0)))
  println(steps.indexWhere(_._2 == bottomY))
  println(steps.length)
}
