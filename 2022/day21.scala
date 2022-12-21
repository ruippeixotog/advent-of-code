import scala.io.Source

object Day21 extends App {
  val patt = """([a-z]+): (?:([0-9]+)|([a-z]+) ([+-\\*/]) ([a-z]+))""".r

  type OpTree = Map[String, Option[Long] | (String, String, String)]

  sealed trait OpResult
  case class Solved(v: Long) extends OpResult { override def toString = v.toString }
  case class Unsolved(fun: Long => Long) extends OpResult { override def toString = "???" }

  val in: OpTree = Source.fromFile("2022/day21.in").getLines.map {
    case patt(id, num, null, null, null) => id -> Some(num.toLong)
    case patt(id, null, lhs, op, rhs) => id -> (lhs, op, rhs)
  }.toMap

  val ops: Map[String, (Long, Long) => Long] =
    Map("+" -> { _ + _ }, "-" -> { _ - _ }, "*" -> { _ * _ }, "/" -> { _ / _ })

  val leftInv = Map("+" -> ops("-"), "-" -> ops("+"), "*" -> ops("/"), "/" -> ops("*"))
  val rightInv = leftInv +
    ("-" -> { (res, lhs) => ops("-")(lhs, res) }) +
    ("/" -> { (res, lhs) => ops("/")(lhs, res) })

  def solve(tree: OpTree, curr: String): OpResult = tree(curr) match {
    case None => Unsolved(identity)
    case Some(v) => Solved(v)
    case (lhs, op, rhs) =>
      (solve(tree, lhs), op, solve(tree, rhs)) match {
        case (Solved(l), op, Solved(r)) => Solved(ops(op)(l, r))
        case (Unsolved(fun), "=", Solved(v)) => Solved(fun(v))
        case (Solved(v), "=", Unsolved(fun)) => Solved(fun(v))
        case (Unsolved(fun), op, Solved(v)) => Unsolved(exp => fun(leftInv(op)(exp, v)))
        case (Solved(v), op, Unsolved(fun)) => Unsolved(exp => fun(rightInv(op)(exp, v)))
        case _ => throw Exception(s"Cannot solve $lhs $op $rhs")
      }
  }

  println(solve(in, "root"))
  println {
    val (lhs, _, rhs) = in("root"): @unchecked
    val tree = in + ("humn" -> None) + ("root" -> (lhs, "=", rhs))
    solve(tree, "root")
  }
}
