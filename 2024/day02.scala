import scala.io.Source

object Day02 extends App {
  val in = Source.fromFile("day02.in").getLines.map(_.split(' ').map(_.toInt).toList).toList

  def validReport(xs: List[Int]) = {
    val xs0 = if (xs(0) < xs(1)) xs else xs.reverse
    xs0.sliding(2).forall { case List(a, b) => b - a >= 1 && b - a <= 3 }
  }

  println(in.count(validReport))
  println {
    in.count { case report =>
      validReport(report) || report.indices.exists { i =>
        validReport(report.take(i) ++ report.drop(i + 1))
      }
    }
  }
}
