import scala.io.Source

object Day13 extends App {
  val in = Source.fromFile("day13.in").mkString.split("\n\n").toList
    .map(_.split("\n").map(_.toVector).toVector)

  def findVertMirror(v: Vector[Vector[Char]], smudges: Int): Option[Int] =
    (1 until v.length).find { i =>
      v.view(0, i).reverse.zip(v.view(i, v.length)).flatMap(_.zip(_)).count(_ != _) == smudges
    }

  def findMirror(v: Vector[Vector[Char]], smudges: Int): Option[Int] =
    findVertMirror(v, smudges).map(_ * 100).orElse(findVertMirror(v.transpose, smudges))

  println(in.flatMap(findMirror(_, 0)).sum)
  println(in.flatMap(findMirror(_, 1)).sum)
}
