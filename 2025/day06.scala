import scala.io.Source

object Day06 extends App {
  val in = Source.fromFile("day06.in").mkString.split("\n").toList
  val in1 = in.map(_.trim.split(" +")).reverse.transpose

  println(in1.map {
    case "+" :: args => args.map(_.toLong).sum
    case "*" :: args => args.map(_.toLong).product
    case line => throw Exception(s"Invalid input: $line")
  }.sum)

  val (args2, ops2) = {
    val args = in.init.transpose.map(_.mkString.trim) :+ ""
    val ops = in.last.trim.split(" +").toList
    (args, ops)
  }

  println(args2.foldLeft((0L, List.empty[Long], ops2)) {
    case ((total, currs, "+" :: ops), "") => (total + currs.sum, Nil, ops)
    case ((total, currs, "*" :: ops), "") => (total + currs.product, Nil, ops)
    case ((total, currs, ops), nStr) => (total, nStr.toLong :: currs, ops)
  }._1)
}
