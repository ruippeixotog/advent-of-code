import scala.io.Source

object Day25 extends App {
  val in = Source.fromFile("2022/day25.in").getLines.toList

  def toBase10(num5: String): Long = num5.lastOption.fold(0L) {
    case '=' => 5 * toBase10(num5.init) - 2
    case '-' => 5 * toBase10(num5.init) - 1
    case d => 5 * toBase10(num5.init) + (d - '0')
  }

  def toBase5(num10: Long): String =
    if (num10 == 0) ""
    else
      num10 % 5 match {
        case 3 => toBase5(num10 / 5 + 1) + "="
        case 4 => toBase5(num10 / 5 + 1) + "-"
        case d => toBase5(num10 / 5) + d
      }

  println(toBase5(in.map(toBase10).sum))
}
