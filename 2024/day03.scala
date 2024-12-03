import scala.io.Source

object Day03 extends App {
  val in = Source.fromFile("day03.in").mkString

  println {
    "mul\\((\\d+),(\\d+)\\)".r.findAllMatchIn(in)
      .map { m => m.group(1).toLong * m.group(2).toLong }
      .sum
  }

  println {
    "(mul\\((\\d+),(\\d+)\\)|do\\(\\)|don't\\(\\))".r.findAllMatchIn(in)
      .foldLeft((true, 0L)) {
        case ((_, sum), m) if m.group(1) == "don't()" => (false, sum)
        case ((_, sum), m) if m.group(1) == "do()" => (true, sum)
        case ((false, sum), m) => (false, sum)
        case ((true, sum), m) => (true, sum + m.group(2).toLong * m.group(3).toLong)
      }._2
  }
}
