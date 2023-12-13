import scala.collection.mutable
import scala.io.Source

object Day03 extends App {
  val in = Source.fromFile("2023/day03.in").getLines.toVector

  val ids = mutable.Map[(Int, Int), Int]()
  var values = Vector[Int]()

  in.zipWithIndex.foreach { case (row, i) =>
    (row :+ '.').zipWithIndex.foldLeft[Option[(Int, Int)]](None) { case (curr, (c, j)) =>
      (c.isDigit, curr) match {
        case (true, None) => Some(j, c - '0')
        case (true, Some(j0, currN)) => Some(j0, currN * 10 + (c - '0'))
        case (false, None) => None
        case (false, Some(j0, currN)) =>
          ids ++= (j0 until j).map(jj => (i, jj) -> values.length)
          values = values :+ currN
          None
      }
    }
  }

  def adjs(i: Int, j: Int): Seq[(Int, Int)] =
    for (di <- -1 to 1; dj <- -1 to 1) yield (i + di, j + dj)

  val symbolIndex = for {
    i <- in.indices
    (ch, j) <- in(i).zipWithIndex
    if !ch.isDigit && ch != '.'
  } yield ch -> adjs(i, j).flatMap(ids.get).distinct

  println {
    symbolIndex.flatMap(_._2).distinct.map(values).sum
  }
  println {
    symbolIndex
      .filter { case (ch, pns) => ch == '*' && pns.length == 2 }
      .map(_._2.map(values).product).sum
  }
}
