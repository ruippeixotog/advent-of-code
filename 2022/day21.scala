import scala.io.Source

object Day21 extends App {
  val patt = """([a-z]+): (?:([0-9]+)|([a-z]+) ([+-\\*/]) ([a-z]+))""".r

  type OpTree = Map[String, Option[Long] | (String, String, String)]

  val in: OpTree = Source.fromFile("2022/day21.in").getLines.map {
    case patt(id, num, null, null, null) => (id, Some(num.toLong))
    case patt(id, null, lhs, op, rhs) => (id, (lhs, op, rhs))
  }.toMap

  val ops: Map[String, (Long, Long) => Long] =
    Map("+" -> { _ + _ }, "-" -> { _ - _ }, "*" -> { _ * _ }, "/" -> { _ / _ })

  val leftInv = Map("+" -> ops("-"), "-" -> ops("+"), "*" -> ops("/"), "/" -> ops("*"))
  val rightInv = leftInv +
    ("-" -> { (res, lhs) => ops("-")(lhs, res) }) +
    ("/" -> { (res, lhs) => ops("/")(lhs, res) })
  
  def calc(tree: OpTree, curr: String): Option[Long] = tree(curr) match {
    case num: Option[_] => num
    case (lhs, op, rhs) => calc(tree, lhs).zip(calc(tree, rhs)).map(ops(op).tupled)
  }

  def solve(tree: OpTree, curr: String, expected: Long): Long = tree(curr) match {
    case None => expected
    case (lhs, op, rhs) =>
      (calc(tree, lhs), op, calc(tree, rhs)) match {
        case (None, "=", Some(v)) => solve(tree, lhs, v)
        case (Some(v), "=", None) => solve(tree, rhs, v)
        case (None, op, Some(v)) => solve(tree, lhs, leftInv(op)(expected, v))
        case (Some(v), op, None) => solve(tree, rhs, rightInv(op)(expected, v))
        case (l, op, r) => throw new Exception(s"Cannot solve $l $op $r = $expected")
      }
    case res => throw Exception(s"Cannot solve $res = $expected")
  }
  
  println(calc(in, "root").get)
  println {
    val (lhs, _, rhs) = in("root"): @unchecked
    val tree = in.updated("humn", None).updated("root", (lhs, "=", rhs))
    solve(tree, "root", 0)
  }
}
