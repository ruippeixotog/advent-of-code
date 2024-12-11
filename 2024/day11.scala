import scala.io.Source
import scala.collection.mutable

object Day11 extends App {
  val in = Source.fromFile("day11.in").mkString.trim.split(" ").map(_.toLong).toList

  def numDigits(x: Long) = Math.log10(x).toInt + 1
  def powMult(digits: Int) = Math.pow(10, digits / 2).toLong

  def blink(x: Long): List[Long] =
    if (x == 0) List(1)
    else if (numDigits(x) % 2 == 0) List(x / powMult(numDigits(x)), x % powMult(numDigits(x)))
    else List(x * 2024)

  val memo = mutable.Map[(Long, Int), Long]()

  def expand(xs: List[Long], n: Int): Long =
    if (n == 0) xs.length
    else xs.map { x => memo.getOrElseUpdate((x, n), expand(blink(x), n - 1)) }.sum

  println(expand(in, 25))
  println(expand(in, 75))
}
