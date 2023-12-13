import scala.io.Source
import scala.collection.mutable

object Day12 extends App {
  val in = Source.fromFile("2023/day12.in").getLines.toList.map { row =>
    val Array(recStr, nsStr) = row.split(" ")
    (recStr.toList, nsStr.split(",").map(_.toInt).toList)
  }

  val mem = new mutable.HashMap[Any, Long]()

  def numWaysMem(rec: List[Char], ns: List[Int], curr: Int = 0): Long =
    mem.getOrElseUpdate((rec, ns, curr), numWays(rec, ns, curr))

  def numWays(rec: List[Char], ns: List[Int], curr: Int): Long = (rec, ns) match {
    case (Nil, Nil) if curr == 0 => 1
    case (Nil, List(n)) if curr == n => 1
    case ('#' :: rec1, n :: _) if curr < n => numWaysMem(rec1, ns, curr + 1)
    case ('.' :: rec1, _) if curr == 0 => numWaysMem(rec1, ns, 0)
    case ('.' :: rec1, n :: ns1) if curr == n => numWaysMem(rec1, ns1, 0)
    case ('?' :: rec1, _) => numWays('#' :: rec1, ns, curr) + numWays('.' :: rec1, ns, curr)
    case _ => 0
  }

  extension [A](coll: List[List[A]]) {
    def join[B >: A](sep: B): List[B] = coll match {
      case x0 :: x1 :: xs => x0 ::: sep :: (x1 :: xs).join(sep)
      case xs => xs.flatten
    }
  }

  val in2 = in.map { (rec, ns) => (List.fill(5)(rec).join('?'), List.fill(5)(ns).flatten) }

  println(in.map(numWaysMem(_, _)).sum)
  println(in2.map(numWaysMem(_, _)).sum)
}
