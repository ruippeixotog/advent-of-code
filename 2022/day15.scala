import scala.io.Source

object Day15 extends App {
  val patt = """Sensor at x=(-?\d+), y=(-?\d+): closest beacon is at x=(-?\d+), y=(-?\d+)""".r

  val in = Source.fromFile("2022/day15.in").getLines.map { case patt(sx, sy, bx, by) =>
    (sx.toInt, sy.toInt, bx.toInt, by.toInt)
  }.toList

  def interval(y: Int)(sx: Int, sy: Int, bx: Int, by: Int): Option[(Int, Int)] = {
    val dist = (sx - bx).abs + (sy - by).abs
    val range = dist - (sy - y).abs
    if (range <= 0) None else Some((sx - range, sx + range))
  }

  extension (intervals: List[(Int, Int)]) {
    def normalized: List[(Int, Int)] =
      intervals.sorted.foldLeft(List[(Int, Int)]()) {
        case ((l0, l1) :: acc, (x0, x1)) if x0 <= l1 + 1 => (l0, x1 max l1) :: acc
        case (acc, (x0, x1)) => (x0, x1) :: acc
      }.reverse

    def remove(points: List[Int]): List[(Int, Int)] = (intervals, points) match {
      case (Nil, _) => Nil
      case (is, Nil) => is
      case ((x0, x1) :: is, p :: ps) if p < x0 => intervals.remove(ps)
      case ((x0, x1) :: is, p :: ps) if p > x1 => (x0, x1) :: is.remove(points)
      case ((x0, x1) :: is, p :: ps) => (x0, p - 1) :: (p + 1, x1) :: is.remove(ps)
    }
  }

  println {
    val yTarget = 2000000
    val bs = in.collect { case (_, _, bx, by) if by == yTarget => bx }.sorted

    in.flatMap(interval(yTarget).tupled).normalized.remove(bs)
      .map { case (from, to) => to - from + 1 }.sum
  }

  println {
    val window = 4000000
    val (x, y) = (0 to window).toIterator.flatMap { y =>
      in.flatMap(interval(y).tupled).normalized match {
        case (x0, _) :: _ if x0 > 0 => Some((x0 - 1, y))
        case (_, x1) :: _ if x1 < window => Some((x1 + 1, y))
        case _ => None
      }
    }.next()

    x.toLong * 4000000 + y
  }
}
