import scala.io.Source

object Day05 extends App {
  val patt = """move (\d+) from (\d) to (\d)""".r

  val (initialSt, cmds) = {
    val Array(in1, in2) = Source.fromFile("2022/day05.in").mkString.split("\n\n")

    val st = in1.split("\n").toList.transpose.map(_.filter(_.isUpper)).filter(_.nonEmpty)
    val inCmds = in2.split("\n").map { case patt(n, from, to) =>
      (n.toInt, from.toInt - 1, to.toInt - 1)
    }
    (st.toVector, inCmds)
  }

  def sim(crateTransform: List[Char] => List[Char]): String = {
    cmds.foldLeft(initialSt) { case (st, (n, from, to)) =>
      val (part, newFrom) = st(from).splitAt(n)
      st.updated(from, newFrom).updated(to, crateTransform(part) ++ st(to))
    }.map(_.head).mkString
  }

  println(sim(_.reverse))
  println(sim(identity))
}
