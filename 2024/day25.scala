import scala.io.Source

object Day25 extends App {
  val (locks, keys) = Source.fromFile("day25.in").mkString.split("\n\n").toList
    .map(_.split("\n").toList.transpose).partition(_(0)(0) == '#')

  val maxHeight = locks.head.head.length
  val locksHeights = locks.map(_.map(_.indexOf('.')))
  val keysHeights = keys.map(_.map(maxHeight - _.indexOf('#')))

  val checks =
    for { lock <- locksHeights.iterator; key <- keysHeights } yield lock.zip(key).map(_ + _)

  println(checks.toList.count(_.forall(_ <= maxHeight)))
}
