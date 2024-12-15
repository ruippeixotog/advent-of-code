import scala.io.Source
import java.util.Arrays

object Day14 extends App {
  val regex = "p=([-0-9]+),([-0-9]+) v=([-0-9]+),([-0-9]+)".r

  val in = Source.fromFile("day14.in").getLines.collect { case regex(px, py, vx, vy) =>
    (px.toInt, py.toInt, vx.toInt, vy.toInt)
  }.toList

  val sx = 101
  val sy = 103

  val quads = in
    .map { (px, py, vx, vy) => ((px + 100 * (vx + sx)) % sx, (py + 100 * (vy + sy)) % sy) }
    .groupBy { (x, y) => (Math.signum(x - sx / 2), Math.signum(y - sy / 2)) }

  println(
    quads((-1, -1)).length * quads((-1, 1)).length * quads((1, -1)).length * quads((1, 1)).length
  )

  Iterator.from(0).foreach { it =>
    val grid = Array.fill(sy, sx)('.')

    if (it % 1000 == 0) {
      println(s"At step ${it}")
    }
    in.foreach { (px, py, vx, vy) =>
      val px1 = (px + it * (vx + sx)) % sx
      val py1 = (py + it * (vy + sy)) % sy
      grid(py1)(px1) = '*'
    }
    if (grid.exists(new String(_).contains("***********"))) {
      println(s"At step ${it}")
      grid.foreach { line => println(new String(line)) }
    }
  }
}
