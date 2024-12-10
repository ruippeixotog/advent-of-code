import scala.io.Source

object Day10 extends App {
  val in = Source.fromFile("day10.in").getLines.toVector

  val di = Vector(-1, 0, 1, 0)
  val dj = Vector(0, 1, 0, -1)

  def isValid(i: Int, j: Int) =
    i >= 0 && j >= 0 && i < in.length && j < in(i).length

  def trails(i: Int, j: Int, h: Int = 0): (Set[(Int, Int)], Int) = {
    if (!isValid(i, j) || in(i)(j).asDigit != h) (Set(), 0)
    else if (h == 9) (Set((i, j)), 1)
    else
      (0 until 4).map { d => trails(i + di(d), j + dj(d), h + 1) }
        .reduce { case ((s1, c1), (s2, c2)) => (s1 ++ s2, c1 + c2) }
  }

  val (tops, counts) = (
    for (i <- in.indices; j <- in(i).indices; if in(i)(j) == '0')
      yield trails(i, j)
  ).unzip

  println(tops.map(_.size).sum)
  println(counts.sum)
}
