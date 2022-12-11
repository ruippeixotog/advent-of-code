import scala.io.Source

object Day08 extends App {
  val in = Source.fromFile("2022/day08.in").getLines.toVector

  def lines(i: Int, j: Int): Seq[Seq[Char]] = List(
    (0 until j).reverse.map(in(i)),
    ((j + 1) until in(i).length).map(in(i)),
    (0 until i).reverse.map(in(_)(j)),
    ((i + 1) until in.length).map(in(_)(j))
  )

  println {
    in.zipWithIndex.map { case (inRow, i) =>
      inRow.zipWithIndex.count { case (h, j) =>
        lines(i, j).exists(_.forall(_ < h))
      }
    }.sum
  }

  println {
    in.zipWithIndex.flatMap { case (inRow, i) =>
      inRow.zipWithIndex.map { case (h, j) =>
        lines(i, j).map { line => line.length.min(line.takeWhile(_ < h).length + 1) }.product
      }
    }.max
  }
}
