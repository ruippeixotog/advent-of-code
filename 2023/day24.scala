import scala.io.Source
import scala.sys.process._

object Day24 extends App {
  val patt = """([0-9]+), ([0-9]+), ([0-9]+) @ ([-0-9]+), ([-0-9]+), ([-0-9]+)""".r

  val in = Source.fromFile("day24.in").getLines.map { case patt(x, y, z, vx, vy, vz) =>
    ((x.toLong, y.toLong, z.toLong), (vx.toLong, vy.toLong, vz.toLong))
  }.toList

  val low = 200000000000000.0
  val high = 400000000000000.0

  val lineInfo = in.map { case ((x, y, _), (vx, vy, _)) =>
    val m = vy.toDouble / vx.toDouble
    (x.toDouble, vx.toDouble, m, -1.0, y.toDouble - m * x.toDouble)
  }
  val intersects = lineInfo.combinations(2).count {
    case List((x1, vx1, a1, b1, c1), (x2, vx2, a2, b2, c2)) =>
      val x = (b1 * c2 - b2 * c1) / (a1 * b2 - a2 * b1)
      val y = (a2 * c1 - a1 * c2) / (a1 * b2 - a2 * b1)
      val t1 = (x - x1) / vx1
      val t2 = (x - x2) / vx2
      t1 >= 0 && t2 >= 0 && x >= low && x <= high && y >= low && y <= high
  }
  println(intersects)

  val maximaEqs = in.take(3).zipWithIndex.flatMap { case (((x, y, z), (vx, vy, vz)), i) =>
    List(
      s"x + vx * t$i = $x + ($vx) * t$i",
      s"y + vy * t$i = $y + ($vy) * t$i",
      s"z + vz * t$i = $z + ($vz) * t$i"
    )
  }.mkString("[", ",", "]")

  val maximaExpr = List(
    s"res: solve($maximaEqs, [x, y, z, vx, vy, vz, t0, t1, t2])[1]",
    "rhs(res[1]) + rhs(res[2]) + rhs(res[3])"
  ).mkString("", ";", ";")

  val maximaOut = s"maxima --very-quiet --batch-string '$maximaExpr'".!!
  println(maximaOut.split("\n").last.trim)
}
