import scala.io.Source

object Day02 extends App {
  val gamePatt = """Game ([0-9]+): (.+)""".r
  val drawPatt = """([0-9]+) (.+)""".r

  val in = Source.fromFile("2023/day02.in").getLines.map { case gamePatt(id, games) =>
    id.toInt -> games.split("; ").toList.flatMap(
      _.split(", ").toList.map { case drawPatt(n, color) => (n.toInt, color) }
    )
  }.toList

  def validateDraw(draw: (Int, String)): Boolean = draw match {
    case (n, "red") => n <= 12
    case (n, "green") => n <= 13
    case (n, _) => n <= 14
  }

  def collectDraws(maxs: Map[String, Int], draw: (Int, String)): Map[String, Int] =
    maxs + (draw._2 -> Math.max(draw._1, maxs.getOrElse(draw._2, 0)))

  println(in.collect { case (id, draws) if draws.forall(validateDraw) => id }.sum)
  println(in.map { case (id, draws) => draws.foldLeft(Map())(collectDraws).values.product }.sum)
}
