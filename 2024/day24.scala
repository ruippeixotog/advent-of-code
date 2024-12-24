import java.io.PrintStream
import scala.io.Source
import scala.collection.mutable
import scala.util.Random

object Day24 extends App {
  val gateRegex = """([a-z0-9]+) ([A-Z]+) ([a-z0-9]+) -> ([a-z0-9]+)""".r

  val Array(initialsStr, gatesStr) = Source.fromFile("day24.in").mkString.split("\n\n")

  val initials0 = initialsStr.split("\n").map { line =>
    val Array(p, v) = line.split(": ")
    (p, v.toInt)
  }.toMap

  val gates0 = gatesStr.split("\n").map { case gateRegex(arg1, op, arg2, res) =>
    res -> (arg1, op, arg2)
  }.toMap

  val inBits = initials0.size / 2
  val outBits = gates0.keys.filter(_.startsWith("z")).size

  def sim(initials: Map[String, Int], swaps: List[(String, String)] = Nil): Long = {
    val mem = mutable.Map[String, Int]() ++ initials
    val gates = swaps.foldLeft(gates0) { case (acc, (t1, t2)) =>
      acc + (t1 -> acc(t2)) + (t2 -> acc(t1))
    }
    def aux(tgt: String): Int = mem.getOrElseUpdate(
      tgt, {
        gates(tgt) match {
          case (arg1, "AND", arg2) => aux(arg1) & aux(arg2)
          case (arg1, "OR", arg2) => aux(arg1) | aux(arg2)
          case (arg1, "XOR", arg2) => aux(arg1) ^ aux(arg2)
        }
      }
    )
    (0 until outBits).map { i => aux(f"z$i%02d").toLong << i }.sum
  }

  def mkDot(initials: Map[String, Int], swaps: List[(String, String)]): String = {
    val gates = swaps.foldLeft(gates0) { case (acc, (t1, t2)) =>
      acc + (t1 -> acc(t2)) + (t2 -> acc(t1))
    }
    val initialsLines = initials.keys.map { v => s"""$v [color="red"]""" }
    val gatesLines = gates.map { case (res, (arg1, op, arg2)) =>
      val color = if (res.startsWith("z")) """,color="green"""" else ""
      s"""$res [label="$op ($res)"$color]; $arg1 -> $res; $arg2 -> $res;"""
    }
    (initialsLines ++ gatesLines).mkString("digraph G { ", "\n", " }")
  }

  def checkSwap(swaps: List[(String, String)]): Boolean = {
    (1 to 100000).forall { _ =>
      val x, y = Random.nextLong() & ((1 << inBits) - 1)
      val initials = (0 until inBits).flatMap { i =>
        List(f"x$i%02d" -> ((x >> i) & 1).toInt, f"y$i%02d" -> ((y >> i) & 1).toInt)
      }.toMap
      val z = sim(initials, swaps) & ((1 << outBits) - 1)
      z == (x + y)
    }
  }

  println(sim(initials0))

  val swaps = List("hwk" -> "z06", "qmd" -> "tnt", "hpc" -> "z31", "z37" -> "cgr")
  new PrintStream("target/day24.dot").println(mkDot(initials0, swaps))
  // if (!checkSwap(swaps)) throw new Exception("Testing failed")
  println(swaps.flatMap { (a, b) => List(a, b) }.sorted.mkString(","))
}
