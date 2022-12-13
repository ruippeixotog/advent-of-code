import scala.io.Source
import scala.util.parsing.combinator._

object Day13 extends App {
  sealed trait Packet extends Ordered[Packet] {
    def compare(that: Packet): Int = (this, that) match {
      case (PInt(n1), PInt(n2)) => n1 compare n2
      case (PInt(_), PList(_)) => PList(List(this)) compare that
      case (PList(_), PInt(_)) => this compare PList(List(that))
      case (PList(Nil), PList(Nil)) => 0
      case (PList(Nil), PList(_)) => -1
      case (PList(_), PList(Nil)) => 1
      case (PList(p1 :: ps1), PList(p2 :: ps2)) => p1 compare p2 match {
        case 0 => PList(ps1) compare PList(ps2)
        case res => res
      }
    }
  }
  case class PInt(n: Int) extends Packet
  case class PList(ps: List[Packet]) extends Packet

  object PacketParser extends RegexParsers {
    val number: Parser[PInt] = "\\d+".r ^^ { _.toInt } ^^ PInt.apply
    val list: Parser[PList] = "[" ~> repsep(packet, ",") <~ "]" ^^ PList.apply
    val packet: Parser[Packet] = number | list

    def parse(str: String): Packet = parse(packet, str).get
  }

  val in = Source.fromFile("2022/day13.in").getLines
    .filterNot(_.isEmpty).map(PacketParser.parse).toList

  println {
    in.grouped(2).zipWithIndex.collect { case (List(p1, p2), i) if p1 < p2 => i + 1 }.sum
  }
  println {
    val dividers = List("[[2]]", "[[6]]").map(PacketParser.parse)
    val packets = (dividers ++ in).sorted
    dividers.map(packets.indexOf(_) + 1).product
  }
}
