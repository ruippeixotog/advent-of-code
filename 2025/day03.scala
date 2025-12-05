import scala.io.Source

object Day03 extends App {
  val in = Source.fromFile("day03.in").getLines.map(_.map(_.asDigit).toVector).toVector

  def takeMax(bank: Vector[Int], left: Int, from: Int = 0, acc: Long = 0): (Int, Long) = {
    if (left == 0) (-1, acc)
    else {
      val maxIdx = Iterator.range(from, bank.length - left + 1).maxBy(bank)
      takeMax(bank, left - 1, maxIdx + 1, acc * 10 + bank(maxIdx))
    }
  }

  println(in.map(takeMax(_, 2)._2).sum)
  println(in.map(takeMax(_, 12)._2).sum)
}
