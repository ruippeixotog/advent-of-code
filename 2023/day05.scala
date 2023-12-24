import scala.annotation.unchecked
import scala.io.Source

object Day05 extends App {
  val seedsPatt = """seeds: (.+)""".r
  val rulePatt = """(?s)(.+)-to-(.+) map:\n(.+)""".r

  val (seeds, rules) = Source.fromFile("day05.in").mkString.split("\n\n").toList match {
    case seedsPatt(seedsStr) :: rulesStrs =>
      val seeds = seedsStr.split(" ").toList.map(_.toLong)
      val rules = rulesStrs.map { case rulePatt(srcObj, destObj, rulesStr) =>
        ((srcObj, destObj)) -> rulesStr.split("\n").toList.map { rule =>
          val List(dest, src, len) = rule.split(" ").map(_.toLong).toList
          (dest, src, len)
        }
      }.toMap
      (seeds, rules)
  }

  extension [A](xs: List[List[A]]) {
    def collectPairs: List[(A, A)] = xs.collect { case List(a, b) => (a, b) }
  }

  def orderFrom(curr: String): List[String] =
    curr :: rules.keys.find(_._1 == curr).fold(Nil) { case (_, dst) => orderFrom(dst) }

  def applyMapping(src: String, dest: String)(srcSt: Long, len: Long): List[(Long, Long)] = {
    rules(src -> dest)
      .find { case (rDestSt, rSrcSt, rLen) => rSrcSt < srcSt + len && srcSt < rSrcSt + rLen }
      .fold(List((srcSt, len))) { case (rDestSt, rSrcSt, rLen) =>
        val rngSrcSt = srcSt.max(rSrcSt)
        val rngSrcEnd = (srcSt + len).min(rSrcSt + rLen)

        val mappedRng = (rngSrcSt + (rDestSt - rSrcSt), rngSrcEnd - rngSrcSt)
        val rest =
          List((srcSt, rngSrcSt - srcSt), (rngSrcEnd, len - rngSrcEnd - srcSt)).filter(_._2 > 0)

        mappedRng :: rest.flatMap(applyMapping(src, dest))
      }
  }

  def solve(seedsSt: List[(Long, Long)]): Long = {
    orderFrom("seed")
      .sliding(2).toList.collectPairs
      .foldLeft(seedsSt) { case (currs, (src, dest)) =>
        currs.flatMap { case (srcSt, len) => applyMapping(src, dest)(srcSt, len) }
      }
      .map(_._1).min
  }

  println(solve(seeds.map(_ -> 1L)))
  println(solve(seeds.grouped(2).toList.collectPairs))
}
