import scala.io.Source

object Day19 extends App {
  val Array(pattStr, towelsStr) = Source.fromFile("day19.in").mkString.split("\n\n")
  val patts = pattStr.split(", ").toList
  val towels = towelsStr.split("\n").toList

  def countCombinations(towel: String): Long = {
    val dp = Array.ofDim[Long](towel.length + 1)
    dp(0) = 1

    towel.toList.tails.zipWithIndex.foreach { (str, i) =>
      if (dp(i) > 0) {
        patts.filter(str.startsWith(_)).foreach { p =>
          dp(i + p.length) += dp(i)
        }
      }
    }
    dp(towel.length)
  }

  val res = towels.map(countCombinations)
  println(res.count(_ > 0))
  println(res.sum)
}
