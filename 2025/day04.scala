import scala.io.Source
import scala.collection.mutable

object Day04 extends App {
  val in = Source.fromFile("day04.in").getLines.map(_.toVector).toVector

  def isPaper(i: Int, j: Int): Boolean =
    i >= 0 && i < in.length && j >= 0 && j < in(i).length && in(i)(j) == '@'

  val di = Vector(-1, -1, 0, 1, 1, 1, 0, -1)
  val dj = Vector(0, 1, 1, 1, 0, -1, -1, -1)

  def paperAdjs(i: Int, j: Int): Seq[(Int, Int)] =
    di.zip(dj).map { (di, dj) => (i + di, j + dj) }.filter(isPaper)

  val paperAdjCount = in.indices.map { i =>
    in(i).indices.map { j => paperAdjs(i, j).length }.toArray
  }.toArray

  def solve(): Int = {
    var cnt = 0
    val q = mutable.Queue[(Int, Int)](
      (for (i <- in.indices; j <- in(i).indices; if in(i)(j) == '@' && paperAdjCount(i)(j) < 4)
        yield (i, j))*
    )

    println(q.size)

    while (!q.isEmpty) {
      val (i, j) = q.dequeue()
      cnt += 1

      paperAdjs(i, j).map { (i1, j1) =>
        if (paperAdjCount(i1)(j1) == 4) q += ((i1, j1))
        paperAdjCount(i1)(j1) -= 1
      }
    }
    cnt
  }

  println(solve())
}
