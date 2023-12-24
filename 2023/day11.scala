import scala.io.Source
import scala.math._

object Day11 extends App {
  val in = Source.fromFile("day11.in").getLines.toVector

  val emptyRows = in.zipWithIndex.collect { case (row, i) if !row.contains('#') => i }
  val emptyCols = in.transpose.zipWithIndex.collect { case (col, j) if !col.contains('#') => j }

  val galaxies = for {
    (row, i) <- in.zipWithIndex
    case ('#', j) <- row.zipWithIndex
  } yield (i, j)

  def between(p: Int, a1: Int, a2: Int): Boolean =
    p > min(a1, a2) && p < max(a1, a2)

  def dist(expFactor: Long)(pos1: (Int, Int), pos2: (Int, Int)): Long =
    abs(pos1._1 - pos2._1) + abs(pos1._2 - pos2._2) +
      emptyRows.count(i => between(i, pos1._1, pos2._1)) * (expFactor - 1) +
      emptyCols.count(j => between(j, pos1._2, pos2._2)) * (expFactor - 1)

  def allDistsSum(expFactor: Long) =
    galaxies.combinations(2).map { case Vector(pos1, pos2) => dist(expFactor)(pos1, pos2) }.sum

  println(allDistsSum(2))
  println(allDistsSum(1000000))
}
