import scala.io.Source
import scala.collection.mutable

object Day21 extends App {
  val in = Source.fromFile("day21.in").getLines.toVector

  // format: off
  val numericMap = Map(
    '7' -> (0, 0), '8' -> (0, 1), '9' -> (0, 2),
    '4' -> (1, 0), '5' -> (1, 1), '6' -> (1, 2),
    '1' -> (2, 0), '2' -> (2, 1), '3' -> (2, 2),
    ' ' -> (3, 0), '0' -> (3, 1), 'A' -> (3, 2)
  )
  val dirMap = Map(
    ' ' -> (0, 0), '^' -> (0, 1), 'A' -> (0, 2),
    '<' -> (1, 0), 'v' -> (1, 1), '>' -> (1, 2)
  )
  // format: on

  val mem = mutable.Map[(Char, Char, Int, Int), Long]()

  def cost(code: String, maxLevel: Int): Long = {
    def aux(fromCh: Char, toCh: Char, level: Int = 0): Long = mem.getOrElseUpdate(
      (fromCh, toCh, maxLevel, level), {
        if (level == maxLevel) 1
        else {
          val keyMap = if (level == 0) numericMap else dirMap
          val ((fromY, fromX), (toY, toX)) = (keyMap(fromCh), keyMap(toCh))
          val (dy, dx) = (toY - fromY, toX - fromX)

          val chY = if (dy < 0) "^" else "v"
          val chX = if (dx < 0) "<" else ">"

          val xThenY =
            if (keyMap(' ') == (fromY, fromX + dx)) None
            else Some(chX * Math.abs(dx) + chY * Math.abs(dy))
          val yThenX =
            if (keyMap(' ') == (fromY + dy, fromX)) None
            else Some(chY * Math.abs(dy) + chX * Math.abs(dx))

          List(xThenY, yThenX).flatten.map { c =>
            ("A" + c + "A").sliding(2).map { str => aux(str(0), str(1), level + 1) }.sum
          }.min
        }
      }
    )
    ("A" + code).sliding(2).map { case str => aux(str(0), str(1)) }.sum
  }

  println(in.map { code => code.init.toInt * cost(code, 3) }.sum)
  println(in.map { code => code.init.toInt * cost(code, 26) }.sum)
}
