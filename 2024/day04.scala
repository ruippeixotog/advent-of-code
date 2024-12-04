import scala.io.Source

object Day04 extends App {
  val in = Source.fromFile("day04.in").getLines.toArray

  println {
    in.indices.iterator.map { i =>
      in(i).indices.iterator.map { j =>
        val hor =
          if (j + 4 > in(i).length) Nil
          else in(i).substring(j, j + 4).toSeq

        val ver =
          if (i + 4 > in.length) Nil
          else (0 until 4).map(k => in(i + k)(j))

        val diag1 =
          if (i + 4 > in.length || j + 4 > in(i).length) Nil
          else (0 until 4).map(k => in(i + k)(j + k))

        val diag2 =
          if (i + 4 > in.length || j < 3) Nil
          else (0 until 4).map(k => in(i + k)(j - k))

        Seq(hor, ver, diag1, diag2).flatMap(xs => List(xs, xs.reverse)).count(_ == "XMAS".toSeq)
      }.sum
    }.sum
  }

  println {
    (1 until in.length - 1).iterator.map { i =>
      (1 until in(i).length - 1).iterator.count { j =>
        in(i)(j) == 'A' &&
        Set(in(i - 1)(j + 1), in(i + 1)(j - 1)) == Set('M', 'S') &&
        Set(in(i - 1)(j - 1), in(i + 1)(j + 1)) == Set('M', 'S')
      }
    }.sum
  }
}
