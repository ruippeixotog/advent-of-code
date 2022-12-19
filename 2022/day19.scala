import scala.io.Source

case class Blueprint(id: Int, recipes: List[(String, Map[String, Int])])

object Day19 extends App {
  val patt =
    ("""Blueprint (\d+): Each ore robot costs (\d+) ore. """ +
      """Each clay robot costs (\d+) ore. """ +
      """Each obsidian robot costs (\d+) ore and (\d+) clay. """ +
      """Each geode robot costs (\d+) ore and (\d+) obsidian.""").r

  val in = Source.fromFile("2022/day19.in").getLines.map { case patt(a, b, c, d, e, f, g) =>
    Blueprint(
      a.toInt,
      List(
        "geode" -> Map("ore" -> f.toInt, "obsidian" -> g.toInt),
        "obsidian" -> Map("ore" -> d.toInt, "clay" -> e.toInt),
        "clay" -> Map("ore" -> c.toInt),
        "ore" -> Map("ore" -> b.toInt)
      )
    )
  }.toList

  def potential(t: Int): Int =
    t * (t - 1) / 2

  def cdiv(num: Int, denom: Int) =
    (num + denom - 1) / denom

  def optimize(bp: Blueprint, target: String, maxTime: Int): Int = {
    var mem = Map[Any, Int]()
    var best = 0

    def aux(t: Int, qnts: Map[String, Int], rates: Map[String, Int], geo: Int): Int = {
      if (t <= 1) { best = best.max(geo); geo }
      else if (geo + potential(t) <= best) 0
      else {
        mem.get((t, qnts, rates)) match {
          case Some(geoAdd) => geo + geoAdd
          case None =>
            best = best.max(geo)

            val res = bp.recipes
              .filter(_._2.forall { req => rates(req._1) > 0 })
              .map { (to, reqs) =>
                val dt = reqs.map { (r, req) => cdiv((req - qnts(r)).max(0), rates(r)) }.max + 1
                val newQnts =
                  qnts.map { (r, qnt) => (r, qnt + rates(r) * dt - reqs.getOrElse(r, 0)) }

                if (to == target) aux(t - dt, newQnts, rates, geo + (t - dt))
                else aux(t - dt, newQnts, rates + (to -> (rates(to) + 1)), geo)
              }
              .max

            mem = mem + ((t, qnts, rates) -> (res - geo))
            res
        }
      }
    }
    val empty = bp.recipes.map { (o, _) => (o, 0) }.toMap - target
    aux(maxTime, empty, empty + ("ore" -> 1), 0)
  }

  println(in.map { bp => bp.id * optimize(bp, "geode", 24) }.sum)
  println(in.take(3).map(optimize(_, "geode", 32)).product)
}
