import scala.collection.mutable
import scala.collection.immutable.Queue
import scala.io.Source

object Day16 extends App {
  val patt = """Valve ([A-Z]+) has flow rate=(\d+); tunnels? leads? to valves? ([A-Z, ]+)""".r

  val in = Source.fromFile("2022/day16.in").getLines.map { case patt(v, flow, edges) =>
    v -> (flow.toInt, edges.split(", ").toList)
  }.toMap

  def bfs(from: String): Map[String, Int] = {
    def aux(q: Queue[(Int, String)], acc: Map[String, Int]): Map[String, Int] = {
      q.dequeueOption match {
        case None => acc
        case Some(((_, v), q)) if acc.contains(v) => aux(q, acc)
        case Some(((dist, v), q)) => aux(q ++ in(v)._2.map((dist + 1, _)), acc + (v -> dist))
      }
    }
    aux(Queue((0, from)), Map())
  }

  val dists = in.keys.map { from => from -> bfs(from) }.toMap
  val valves = in.mapValues(_._1).filter(_._2 > 0).toMap

  def run(maxTime: Int): Map[(String, Set[String]), Int] = {
    val dp = Array.fill(maxTime + 1)(mutable.Map[(String, Set[String]), Int]().withDefaultValue(0))
    dp(0)(("AA", Set())) = 0

    (1 to maxTime).foreach { t =>
      dp(t - 1).foreach { case ((prev, visited), released) =>
        dp(t)((prev, visited)) = dp(t)((prev, visited)).max(released)

        valves.foreach { case (next, flow) =>
          val nextT = t + dists(prev)(next)

          if (!visited(next) && nextT < maxTime) {
            dp(nextT)((next, visited + next)) =
              dp(nextT)((next, visited + next)).max(released + (maxTime - nextT) * flow)
          }
        }
      }
    }
    dp(maxTime).toMap
  }

  println(run(30).values.max)

  println {
    val dp = run(26).groupMapReduce(_._1._2)(_._2)(Math.max)

    dp.iterator.flatMap { case (visited1, released1) =>
      dp.iterator.flatMap { case (visited2, released2) =>
        if ((visited1 & visited2).isEmpty) Some(released1 + released2)
        else None
      }
    }.max
  }
}
