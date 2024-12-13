import scala.io.Source
import scala.collection.mutable

object Day12 extends App {
  val in = Source.fromFile("day12.in").getLines.toVector

  val di = Vector(-1, 0, 1, 0)
  val dj = Vector(0, 1, 0, -1)

  def isValid(i: Int, j: Int) = i >= 0 && j >= 0 && i < in.length && j < in(i).length
  def hasPlant(i: Int, j: Int, id: Char) = isValid(i, j) && in(i)(j) == id
  def isSide(i: Int, j: Int, dir: Int, id: Char) =
    hasPlant(i - di(dir), j - dj(dir), id) && !hasPlant(i, j, id)

  val seen = mutable.Set[(Int, Int)]()
  val seenSides = mutable.Set[(Int, Int, Int)]()

  def markSideAsSeen(i: Int, j: Int, dir: Int, id: Char): Int =
    if (seenSides((i, j, dir))) 0
    else {
      Iterator((dir + 1) % 4, (dir + 3) % 4).flatMap { d1 =>
        Iterator.from(0).map { k => ((i + k * di(d1), j + k * dj(d1))) }
          .takeWhile(isSide(_, _, dir, id))
      }.foreach { case (i1, j1) => seenSides += ((i1, j1, dir)) }
      1
    }

  def ffill(i: Int, j: Int, id: Char, prevDir: Int = -1): (Int, Int, Int) = {
    if (!hasPlant(i, j, id)) (0, 1, markSideAsSeen(i, j, prevDir, id))
    else if (seen((i, j))) (0, 0, 0)
    else {
      seen += ((i, j))
      (0 until 4).map { d => ffill(i + di(d), j + dj(d), id, d) }.foldLeft((1, 0, 0)) {
        case ((a1, p1, s1), (a2, p2, s2)) => (a1 + a2, p1 + p2, s1 + s2)
      }
    }
  }

  val res = in.indices.flatMap { i => in(i).indices.map { j => ffill(i, j, in(i)(j)) } }
  println(res.map { case (a, p, _) => a * p }.sum)
  println(res.map { case (a, _, s) => a * s }.sum)
}
