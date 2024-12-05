import scala.io.Source

object Day05 extends App {
  val Array(rulesStr, updsStr) = Source.fromFile("day05.in").mkString
    .split("\n\n")
    .map(_.split("\n").toList)

  val rules = rulesStr
    .map { r =>
      val Array(a, b) = r.split("\\|")
      (a.toInt, b.toInt)
    }
    .groupBy(_._2)
    .view.mapValues(_.map(_._1).toSet).toMap
    .withDefaultValue(Set())

  val upds = updsStr.map(_.split(",").map(_.toInt).toList)

  def isValid(upd: List[Int], left: Set[Int]): Boolean = upd match {
    case Nil => true
    case x :: rest if (rules(x) & left).isEmpty => isValid(rest, left - x)
    case _ => false
  }

  def solve(left: Set[Int], idx: Int): Int = {
    val x = left.find { x => (rules(x) & left).isEmpty }.get
    if (idx == 0) x else solve(left - x, idx - 1)
  }

  val (sol1, sol2) = upds.map { upd =>
    val updSet = upd.toSet
    if (isValid(upd, updSet)) (upd(updSet.size / 2), 0)
    else (0, solve(updSet, updSet.size / 2))
  }.unzip

  println(sol1.sum)
  println(sol2.sum)
}
