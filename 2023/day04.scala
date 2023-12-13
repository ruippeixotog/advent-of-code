import scala.collection.mutable
import scala.io.Source

object Day04 extends App {
  type Card = (Array[Int], Array[Int])

  val patt = """Card +[0-9]+: ([0-9 ]+) \| ([0-9 ]+)""".r

  val in: List[Card] = Source.fromFile("2023/day04.in").getLines.map {
    case patt(winners, numbers) =>
      (winners.trim.split(" +").map(_.trim.toInt), numbers.trim.split(" +").map(_.trim.toInt))
  }.toList

  def numWinners(card: Card): Int =
    card._1.intersect(card._2).length

  println {
    in.map(numWinners).map { nw => if (nw == 0) 0 else 1 << (nw - 1) }.sum
  }

  def processCards(cards: List[Card], mults: Map[Int, Int] = Map()): Int = cards match {
    case Nil => 0
    case card :: rest =>
      val nc = 1 + mults.values.sum
      val nw = numWinners(card)
      val updMults = mults.map { case (k, v) => (k - 1, v) }
      val newMults = updMults + (nw -> (updMults.getOrElse(nw, 0) + nc)) - 0
      nc + processCards(rest, newMults)
  }
  println(processCards(in))
}
