import scala.io.Source

object Day01 extends App {
  val in = Source.fromFile("2023/day01.in").getLines.toList

  val spellings = List("one", "two", "three", "four", "five", "six", "seven", "eight", "nine")

  def getDigit1(str: String): Option[Int] =
    str.headOption.filter(_.isDigit).map(_ - '0')

  def getDigit2(str: String): Option[Int] =
    spellings.zipWithIndex
      .collectFirst { case (sp, i) if str.startsWith(sp) => i + 1 }
      .orElse(getDigit1(str))

  def calibrationValue(getDigit: String => Option[Int])(str: String) =
    10 * str.tails.flatMap(getDigit).next + str.tails.toSeq.reverse.flatMap(getDigit).head

  println(in.map(calibrationValue(getDigit1)).sum)
  println(in.map(calibrationValue(getDigit2)).sum)
}
