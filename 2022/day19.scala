import scala.io.Source

case class Blueprint(id: Int, recipes: List[List[Int]])

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
        List(b.toInt, 0, 0),
        List(c.toInt, 0, 0),
        List(d.toInt, e.toInt, 0),
        List(f.toInt, 0, g.toInt)
      )
    )
  }.toList

  def potential(t: Int): Int =
    t * (t - 1) / 2

  def cdiv(num: Int, denom: Int) =
    if (denom == 0) Int.MinValue else (num + denom - 1) / denom

  def optimize(bp: Blueprint, maxTime: Int): Int = {
    var mem = Map[Any, Int]()
    var best = 0

    def aux(t: Int, qnts: List[Int], rates: List[Int], geo: Int): Int = {
      if (t <= 1) { best = best.max(geo); geo }
      else if (geo + potential(t) <= best) 0
      else {
        mem.get((t, qnts, rates)) match {
          case Some(geoAdd) => geo + geoAdd
          case None =>
            best = best.max(geo)

            val res = bp.recipes
              .filter(_.zip(rates).forall { (req, rate) => req == 0 || rate > 0 })
              .zipWithIndex
              .map { (reqs, i) =>
                val dt = (0 :: reqs.zip(qnts).map(_ - _).zip(rates).map(cdiv)).max + 1
                val newQnts = qnts.zip(rates).map(_ + _ * dt).zip(reqs).map(_ - _)

                if (i == 3) aux(t - dt, newQnts, rates, geo + (t - dt))
                else aux(t - dt, newQnts, rates.updated(i, rates(i) + 1), geo)
              }
              .max

            mem = mem + ((t, qnts, rates) -> (res - geo))
            res
        }
      }
    }
    aux(maxTime, List(0, 0, 0), List(1, 0, 0), 0)
  }

  println(in.map { bp => bp.id * optimize(bp, 24) }.sum)
  println(in.take(3).map(optimize(_, 32)).product)
}
