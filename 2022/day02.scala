import scala.io.Source

object Day02 extends App {
  val in = Source.fromFile("day02.in").getLines.map(_.split(" ")).toList

  def score(moveFunc: (Int, Char) => Int): Int = {
    in.map { case Array(left, right) =>
      val leftMove = left(0) - 'A'
      val rightMove = moveFunc(leftMove, right(0))

      val winScore = (rightMove - leftMove + 3) % 3 match {
        case 0 => 3
        case 1 => 6
        case 2 => 0
      }
      winScore + rightMove + 1
    }.sum
  }

  println(score { (_, r) => r - 'X' })

  println(score {
    case (l, 'X') => (l + 2) % 3
    case (l, 'Y') => l
    case (l, 'Z') => (l + 1) % 3
  })
}
