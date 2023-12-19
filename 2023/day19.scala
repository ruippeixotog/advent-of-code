import scala.io.Source
import scala.util.parsing.combinator._

object Day19 extends App {
  sealed trait Action
  case object Accept extends Action
  case object Reject extends Action
  case class WfRef(name: String) extends Action

  sealed trait Op
  case object Lt extends Op
  case object Gt extends Op

  sealed trait Rule
  case class Direct(action: Action) extends Rule
  case class Cond(attr: Char, op: Op, arg: Int, action: Action) extends Rule

  object WorkflowParser extends RegexParsers {
    val wfRef: Parser[WfRef] = "[a-z]+".r ^^ WfRef.apply
    val action: Parser[Action] = wfRef | "A" ^^^ Accept | "R" ^^^ Reject
    val op: Parser[Op] = "<" ^^^ Lt | ">" ^^^ Gt
    val direct: Parser[Direct] = action ^^ Direct.apply
    val cond: Parser[Cond] = "[xmas]".r ~ op ~ "\\d+".r ~ (":" ~> action) ^^ {
      case at ~ o ~ ar ~ ac => Cond(at.head, o, ar.toInt, ac)
    }
    val rule: Parser[Rule] = cond | direct
    val workflow: Parser[(String, List[Rule])] = wfRef ~ ("{" ~> repsep(rule, ",") <~ "}") ^^ {
      case ref ~ rules => (ref.name, rules)
    }

    def parse(str: String): Map[String, List[Rule]] = parse(rep(workflow), str).get.toMap
  }

  val partRegex = """\{x=([0-9]+),m=([0-9]+),a=([0-9]+),s=([0-9]+)\}""".r

  val (wfs, parts) = Source.fromFile("2023/day19.in").mkString.split("\n\n") match {
    case Array(wfsStr, partsStr) =>
      val parts = partsStr.split("\n").toList.map { case partRegex(x, m, a, s) =>
        Map('x' -> x.toInt, 'm' -> m.toInt, 'a' -> a.toInt, 's' -> s.toInt)
      }
      (WorkflowParser.parse(wfsStr), parts)
  }

  def splitRange(rng: Range, break: Int): (Range, Range) =
    (rng.start to Math.min(rng.end, break - 1), Math.max(rng.start, break) to rng.end)

  def run(part: Map[Char, Int], rs: List[Rule]): Boolean =
    combinations(part.mapValues(v => v to v).toMap, rs) != 0

  def combinations(partRng: Map[Char, Range], r: List[Rule]): Long = {
    if (partRng.values.exists(_.isEmpty)) 0L
    else
      r.head match {
        case Direct(Accept) => partRng.values.map(_.length.toLong).product
        case Direct(Reject) => 0
        case Direct(WfRef(wf)) => combinations(partRng, wfs(wf))
        case Cond(attr, Lt, arg, action) =>
          val (ifRng, elseRng) = splitRange(partRng(attr), arg)
          combinations(partRng + (attr -> ifRng), List(Direct(action))) +
            combinations(partRng + (attr -> elseRng), r.tail)
        case Cond(attr, Gt, arg, action) =>
          val (elseRng, ifRng) = splitRange(partRng(attr), arg + 1)
          combinations(partRng + (attr -> ifRng), List(Direct(action))) +
            combinations(partRng + (attr -> elseRng), r.tail)
      }
  }

  println(parts.filter(run(_, wfs("in"))).flatMap(_.values).sum)
  println(combinations("xmas".map((_, 1 to 4000)).toMap, wfs("in")))
}
