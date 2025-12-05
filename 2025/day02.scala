import scala.io.Source

object Day02 extends App {
  val in = Source.fromFile("day02.in").mkString.trim.split(",")
    .map { case s"${n1}-${n2}" => (n1.toLong, n2.toLong) }
    .toList

  println {
    in.map { (n1, n2) =>
      (n1 to n2).filter { n =>
        val nStr = n.toString
        nStr.substring(0, nStr.length / 2) == nStr.substring(nStr.length / 2)
      }.sum
    }.sum
  }

  println {
    in.map { (n1, n2) =>
      (n1 to n2).filter { n =>
        val nStr = n.toString
        (1 to nStr.length / 2).exists { k =>
          nStr.length % k == 0 && nStr.grouped(k).forall(_ == nStr.substring(0, k))
        }
      }.sum
    }.sum
  }
}
