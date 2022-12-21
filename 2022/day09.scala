import scala.io.Source

object Day09 extends App {
  val in = Source.fromFile("2022/day09.in").getLines.toList
    .map(_.split(" ")).map { case Array(dir, n) => (dir.head, n.toInt) }

  val dirs = Map('U' -> (0, 1), 'D' -> (0, -1), 'L' -> (-1, 0), 'R' -> (1, 0))

  def nextT(h: (Int, Int), t: (Int, Int)): (Int, Int) = (h, t) match {
    case ((hx, hy), (tx, ty)) =>
      if ((hx - tx).abs <= 1 && (hy - ty).abs <= 1) t
      else (tx + (hx - tx).signum, ty + (hy - ty).signum)
  }

  def sim(sz: Int): List[List[(Int, Int)]] = {
    in.flatMap { (dir, n) => List.fill(n)(dirs(dir)) }
      .scanLeft((List.fill(sz)((0, 0)))) {
        case (Nil, _) => Nil
        case ((hx, hy) :: ts, (dx, dy)) => ts.scanLeft((hx + dx, hy + dy))(nextT)
      }
  }

  println(sim(2).map(_.last).toSet.size)
  println(sim(10).map(_.last).toSet.size)
}
