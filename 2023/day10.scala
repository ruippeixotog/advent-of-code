import scala.io.Source

object Day10 extends App {
  val in = Source.fromFile("2023/day10.in").getLines.toVector

  val di = Vector(-1, 0, 1, 0)
  val dj = Vector(0, 1, 0, -1)

  val shifts = Map(
    ('|', 0) -> 0,
    ('|', 2) -> 2,
    ('-', 1) -> 1,
    ('-', 3) -> 3,
    ('L', 2) -> 1,
    ('L', 3) -> 0,
    ('J', 1) -> 0,
    ('J', 2) -> 3,
    ('7', 0) -> 3,
    ('7', 1) -> 2,
    ('F', 0) -> 1,
    ('F', 3) -> 2
  )

  def move(pos: (Int, Int), d: Int) = (pos._1 + di(d), pos._2 + dj(d))

  def getSymbol(pos: (Int, Int)): Char =
    if (pos._1 < 0 || pos._2 < 0 || pos._1 >= in.length || pos._2 >= in(0).length) '.'
    else in(pos._1)(pos._2)

  val pos0 = in.zipWithIndex.map { case (row, i) => (i, row.indexOf('S')) }.find(_._2 != -1).get
  val d0s = (0 to 3).filter { d => shifts.contains(getSymbol(move(pos0, d)), d) }

  def path(pos0: (Int, Int), d0: Int): Iterator[((Int, Int), Int)] =
    Iterator.iterate((pos0, d0)) { (pos, d) =>
      (move(pos, d), shifts((getSymbol(move(pos, d)), d)))
    }.drop(1)

  println {
    path(pos0, d0s(0)).map(_._1).zip(path(pos0, d0s(1)).map(_._1)).indexWhere(_ == _) + 1
  }
}
