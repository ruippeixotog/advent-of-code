import scala.io.Source
import scala.util.matching.Regex

case class Monkey(items: List[Long], inspect: Long => Long, test: Int, ifTrue: Int, ifFalse: Int) {
  def afterInspect(f: Long => Long) = copy(inspect = inspect.andThen(f))

  def inspectAll: List[(Int, Long)] = {
    val newItems = items.map(inspect)
    newItems.map(_ % test == 0).map(if (_) ifTrue else ifFalse).zip(newItems)
  }
}

object Day11 extends App {
  val patt = """
    |Monkey \d+:
    |  Starting items: (\d+(?:, \d+)*)
    |  Operation: new = (old|\d+) (\*|\+) (old|\d+)
    |  Test: divisible by (\d+)
    |    If true: throw to monkey (\d+)
    |    If false: throw to monkey (\d+)
    """.trim.stripMargin.r

  def op(str: String): (Long, Long) => Long = if (str == "+") _ + _ else _ * _
  def opArg(str: String): Long => Long = if (str == "old") identity else _ => str.toLong

  val in = patt.findAllMatchIn(Source.fromFile("day11.in").mkString).map {
    case Regex.Groups(itemsStr, opLhsStr, opStr, opRhsStr, test, ifTrue, ifFalse) =>
      def inspect(old: Long) = op(opStr)(opArg(opLhsStr)(old), opArg(opRhsStr)(old))
      val items = itemsStr.split(", ").toList.map(_.toLong)
      Monkey(items, inspect, test.toInt, ifTrue.toInt, ifFalse.toInt)
  }.toVector

  def monkeyBusiness(monkeys: Vector[Monkey], numIters: Int): Long = {
    val commonMult = monkeys.map(_.test).product
    val initialState = (
      monkeys.map(_.afterInspect(_ % commonMult)),
      Vector.fill[Long](monkeys.length)(0)
    )
    val turns = Iterator.fill(numIters)(0 until monkeys.length).flatten

    val (finalState, cnts) = turns.foldLeft(initialState) { case ((st, cnts), i) =>
      val newCnts = cnts.updated(i, cnts(i) + st(i).items.length)
      val newSt = st(i).inspectAll
        .foldLeft(st) { case (st, (to, item)) =>
          st.updated(to, st(to).copy(items = item :: st(to).items))
        }
        .updated(i, st(i).copy(items = Nil))

      (newSt, newCnts)
    }
    cnts.sortBy(-_).take(2).product
  }

  println(monkeyBusiness(in.map(_.afterInspect(_ / 3)), 20))
  println(monkeyBusiness(in, 10000))
}
