import scala.io.Source
import scala.collection.mutable

object Day22 extends App {
  val patt = """([0-9]+),([0-9]+),([0-9]+)~([0-9]+),([0-9]+),([0-9]+)""".r

  val in = Source.fromFile("day22.in").getLines.map { case patt(x1, y1, z1, x2, y2, z2) =>
    ((x1.toInt, y1.toInt, z1.toInt), (x2.toInt, y2.toInt, z2.toInt))
  }.toVector.sortBy(_._1._3)

  val top = mutable.Map[(Int, Int), (Int, Int)]()
  val supportedBy = in.indices.map(_ -> mutable.Set[Int]()).toMap

  in.zipWithIndex.foreach { case (((x1, y1, z1), (x2, y2, z2)), idx) =>
    val coords = for (x <- x1 to x2; y <- y1 to y2) yield (x, y)
    val sups = coords.map(top.getOrElse(_, (0, -1)))
    val maxTop = sups.map(_._1).max

    supportedBy(idx) ++= sups.filter { (h, idx1) => h == maxTop && idx1 >= 0 }.map(_._2)
    coords.foreach { top(_) = (maxTop + (z2 - z1 + 1), idx) }
  }

  println {
    val singles = supportedBy.values.filter(_.size == 1).toSet.flatten
    in.indices.filterNot(singles).size
  }

  def processFall(idx0: Int): Int = {
    val supports =
      supportedBy.toSeq.flatMap { (k, vs) => vs.map(_ -> k) }.groupBy(_._1).mapValues(_.map(_._2))
    val currSupportedBy = supportedBy.mapValues(_.clone()).toMap
    val q = mutable.Queue[Int]() += idx0

    var cnt = 0
    while (!q.isEmpty) {
      val idx = q.dequeue()
      cnt += 1
      supports.getOrElse(idx, Nil).foreach { idx1 =>
        val sb = currSupportedBy(idx1) -= idx
        if (sb.isEmpty) q += idx1
      }
    }
    cnt - 1
  }

  println(in.indices.map(processFall).sum)
}
