import scala.io.Source

object Day17 extends App {
  val regex =
    "(?s).*Register A: ([0-9]+)\nRegister B: ([0-9]+)\nRegister C: ([0-9]+).*Program: ([0-9,]+).*".r

  val (initialReg, prog) = Source.fromFile("day17.in").mkString match {
    case regex(aStr, bStr, cStr, progStr) =>
      (Vector(aStr.toLong, bStr.toLong, cStr.toLong), progStr.split(",").map(_.toInt).toVector)
  }

  def run(ip: Int, reg: Vector[Long], outs: List[Int] = Nil): List[Int] = {
    def combo(op: Int): Long = if (op < 4) op else reg(op - 4)

    if (ip < 0 || ip >= prog.length) outs.reverse
    else
      (prog(ip), prog(ip + 1)) match {
        case (0, op) => run(ip + 2, reg.updated(0, reg(0) / (1 << combo(op))), outs)
        case (1, op) => run(ip + 2, reg.updated(1, reg(1) ^ op), outs)
        case (2, op) => run(ip + 2, reg.updated(1, combo(op) % 8), outs)
        case (3, op) => run(if (reg(0) == 0) ip + 2 else op, reg, outs)
        case (4, op) => run(ip + 2, reg.updated(1, reg(1) ^ reg(2)), outs)
        case (5, op) => run(ip + 2, reg, (combo(op) % 8).toInt :: outs)
        case (6, op) => run(ip + 2, reg.updated(1, reg(0) / (1 << combo(op))), outs)
        case (7, op) => run(ip + 2, reg.updated(2, reg(0) / (1 << combo(op))), outs)
      }
  }

  def runOptimized(a: Long, outs: List[Int] = Nil): List[Int] =
    if (a == 0) outs
    else {
      val aMod = a % 8
      runOptimized(a / 8, ((aMod ^ 1 ^ (a / (1 << (aMod ^ 2)))) % 8).toInt :: outs)
    }

  def progToString(prog: Vector[Int]): String = {
    def combo(op: Int): String = if (op < 4) op.toString else ('A' + (op - 4)).toChar.toString

    prog.grouped(2).collect {
      case Vector(0, op) => s"A = A / (1 << ${combo(op)})"
      case Vector(1, op) => s"B = B xor $op"
      case Vector(2, op) => s"B = ${combo(op)} mod 8"
      case Vector(3, op) => s"if A != 0 then goto $op"
      case Vector(4, op) => s"B = B xor C"
      case Vector(5, op) => s"print ${combo(op)} mod 8"
      case Vector(6, op) => s"B = A / (1 << ${combo(op)})"
      case Vector(7, op) => s"C = A / (1 << ${combo(op)})"
    }.zipWithIndex.map { (str, idx) => s"$idx: $str" }.mkString("\n")
  }

  def compare(expected: List[Int], outs: List[Int], acc: Int = 0): Long = (expected, outs) match {
    case (e :: es, x :: xs) if e == x => compare(es, xs, acc + 1)
    case _ => acc
  }

  def findA(expected: List[Int], base: Long = 0, target: Int = 1): Option[Long] =
    (base until base + (1 << 11)).toStream
      .filter { curr => compare(expected, runOptimized(curr)) >= target }
      .flatMap { curr =>
        if (target == expected.length) Some(curr)
        else findA(expected, curr / (1 << 8) * (1 << 11), target + 1)
      }.headOption

  println(run(0, initialReg).mkString(","))
  println(findA(prog.toList.reverse).get)
}
