import scala.io.Source
import scala.collection.mutable

object Day22 extends App {
  val in = Source.fromFile("day22.in").getLines.map(_.toLong).toList

  val secrets = in.map(List.iterate(_, 2001) { prev =>
    val a1 = (prev ^ (prev * 64)) % 16777216
    val a2 = (a1 ^ (a1 / 32)) % 16777216
    (a2 ^ (a2 * 2048)) % 16777216
  })

  println(secrets.map(_.last).sum)

  val seqIndex = mutable.Map[List[Int], mutable.Map[Int, Int]]()

  secrets.zipWithIndex.foreach { (buyer, i) =>
    buyer.map { s => (s % 10).toInt }.sliding(5).foreach { seq =>
      val diffs = seq.sliding(2).map { x => x(1) - x(0) }.toList
      seqIndex.getOrElseUpdate(diffs, mutable.Map()).getOrElseUpdate(i, seq.last)
    }
  }

  println(seqIndex.mapValues(_.values.sum).values.max)
}
