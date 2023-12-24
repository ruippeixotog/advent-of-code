import scala.io.Source

object Day07 extends App {
  val in = Source.fromFile("day07.in").getLines.toList.map { line =>
    val List(handStr, bidStr) = line.split(" ").toList
    handStr -> bidStr.toInt
  }

  val ranks1 = "AKQJT98765432".zipWithIndex.toMap
  val ranks2 = "AKQT98765432J".zipWithIndex.toMap

  def strengthHist(hist: List[Int]): Int = hist match {
    case 5 :: _ => 1
    case 4 :: _ => 2
    case 3 :: 2 :: _ => 3
    case 3 :: _ => 4
    case 2 :: 2 :: _ => 5
    case 2 :: _ => 6
    case _ => 7
  }

  def strength1(hand: String): Int =
    strengthHist(hand.groupBy(identity).values.map(_.length).toList.sortBy(-_))

  def strength2(hand: String): Int = {
    val histMap = hand.groupBy(identity).mapValues(_.length).toMap
    val hist = (histMap - 'J').values.toList.sortBy(-_)
    strengthHist(
      if (hist.isEmpty) List(5)
      else hist.updated(0, hist(0) + histMap.getOrElse('J', 0))
    )
  }

  def totalWinnings(strengthFunc: String => Int, rankMap: Map[Char, Int]): Int =
    in.sortBy { case (hand, _) => (strengthFunc(hand), hand.map(rankMap): Iterable[Int]) }
      .reverse.zipWithIndex
      .map { case ((_, bid), i) => bid * (i + 1) }
      .sum

  println(totalWinnings(strength1, ranks1))
  println(totalWinnings(strength2, ranks2))
}
