import scala.collection.mutable
import scala.io.Source

object Day14 extends App {
  type Grid = Vector[Vector[Char]]

  val in = Source.fromFile("2023/day14.in").getLines.map(_.toVector).toVector

  def tiltW(grid: Grid) = grid.map { row =>
    (row :+ '#').foldLeft((0, Vector[Char]())) {
      case ((sp, acc), '#') => (0, acc ++ Vector.fill(sp)('.') :+ '#')
      case ((sp, acc), 'O') => (sp, acc :+ 'O')
      case ((sp, acc), _) => (sp + 1, acc)
    }._2.init
  }

  def tiltE(grid: Grid) = tiltW(grid.map(_.reverse)).map(_.reverse)
  def tiltN(grid: Grid) = tiltW(grid.transpose).transpose
  def tiltS(grid: Grid) = tiltE(grid.transpose).transpose
  
  def cycle(grid: Grid) = tiltE(tiltS(tiltW(tiltN(grid))))
  
  val mem = new mutable.HashMap[Grid, Int]()
  def cycleLoop(grid: Grid, n: Int): Grid = (n, mem.getOrElseUpdate(grid, n)) match {
    case (0, _) => grid
    case (_, oldN) if oldN == n || oldN - n > n => cycleLoop(cycle(grid), n - 1)
    case (_, oldN) => cycleLoop(grid, n - n / (oldN - n) * (oldN - n))
  }

  def getLoad(grid: Grid) = grid.reverse.zip(Iterator.from(1)).map(_.count(_ == 'O') * _).sum

  println(getLoad(tiltN(in)))
  println(getLoad(cycleLoop(in, 1000000000)))
}
