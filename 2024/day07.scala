import java.lang.Math._
import scala.io.Source

object Day07 extends App {
  val in = Source.fromFile("day07.in").getLines.map { line =>
    val Array(testStr, argsStr) = line.split(": ")
    (testStr.toLong, argsStr.split(" ").toList.map(_.toLong))
  }.toList

  def cat(x: Long, y: Long): Long = x * pow(10, floor(log10(y) + 1)).toLong + y

  def tryOps(tgt: Long, xs0: List[Long], useCat: Boolean): Boolean = {
    def aux(acc: Long, xs: List[Long]): Boolean = xs match {
      case Nil => tgt == acc
      case _ :: _ if acc > tgt => false
      case x :: xs1 => aux(acc + x, xs1) || aux(acc * x, xs1) || (useCat && aux(cat(acc, x), xs1))
    }
    aux(xs0.head, xs0.tail)
  }

  println(in.filter(tryOps(_, _, false)).map(_._1).sum)
  println(in.filter(tryOps(_, _, true)).map(_._1).sum)
}
