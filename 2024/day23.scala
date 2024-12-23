import scala.io.Source

object Day23 extends App {
  val in = Source.fromFile("day23.in").getLines.map { line =>
    val Array(a, b) = line.split("-")
    (a, b)
  }.toList

  val adjs = in.flatMap { (a, b) => List((a, b), (b, a)) }
    .groupMap(_._1)(_._2).mapValues(_.toSet).toMap

  val trigs = for {
    c1 <- adjs.keySet if c1(0) == 't'; c2 <- adjs(c1); c3 <- adjs(c1) & adjs(c2)
  } yield Set(c1, c2, c3)

  println(trigs.size)

  def dfs(curr: Set[String], candidates: Set[String]): Set[String] = {
    if (candidates.isEmpty) curr
    else
      candidates.foldLeft((Set[String](), Set[String]())) { case ((seen, best), c) =>
        if (seen(c)) (seen, best)
        else {
          val res = dfs(curr + c, candidates & adjs(c))
          (seen ++ res, if (best.size < res.size) res else best)
        }
      }._2
  }

  println(dfs(Set(), adjs.keySet).toList.sorted.mkString(","))
}
