import scala.io.Source

object Day08 extends App {
  val in = Source.fromFile("day08.in").getLines.toVector

  val nodesByFreq = (
    for (i <- in.indices; j <- in(i).indices; if in(i)(j) != '.')
      yield in(i)(j) -> ((i, j))
  ).groupMap(_._1)(_._2)

  def gcd(a: Int, b: Int): Int = if (b == 0) a else gcd(b, a % b)

  def isValid(i: Int, j: Int) =
    i >= 0 && j >= 0 && i < in.length && j < in(i).length

  val antinodes = nodesByFreq.foldLeft(Set[(Int, Int)]()) { case (acc, (freq, locs)) =>
    locs.combinations(2).foldLeft(acc) { case (acc, Seq((i0, j0), (i1, j1))) =>
      acc ++ List(
        (i0 - (i1 - i0), j0 - (j1 - j0)),
        (i1 + (i1 - i0), j1 + (j1 - j0))
      ).filter(isValid)
    }
  }

  val antinodes2 = nodesByFreq.foldLeft(Set[(Int, Int)]()) { case (acc, (freq, locs)) =>
    locs.combinations(2).foldLeft(acc) { case (acc, Seq((i0, j0), (i1, j1))) =>
      val div = gcd(i1 - i0, j1 - j0)
      val (di, dj) = ((i1 - i0) / div, (j1 - j0) / div)

      val lefts = Iterator.from(0).map { k => (i0 + k * di, j0 + k * dj) }.takeWhile(isValid)
      val rights = Iterator.from(0).map { k => (i0 - k * di, j0 - k * dj) }.takeWhile(isValid)
      acc ++ lefts ++ rights
    }
  }

  println(antinodes.size)
  println(antinodes2.size)
}
