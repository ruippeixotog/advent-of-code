import scala.collection.mutable
import scala.io.Source
import java.io.PrintStream

object Day20 extends App {
  val in = Source.fromFile("day20.in").getLines.map { line =>
    line.split(" -> ") match {
      case Array("broadcaster", toStr) => ("broadcaster" -> (' ', toStr.split(", ").toList))
      case Array(name, toStr) => (name.tail -> (name.head, toStr.split(", ").toList))
    }
  }.toMap

  def writeDot(): Unit = {
    new PrintStream("2023/target/day20.dot").println {
      (in.collect { case (node, ('%', _)) => s"$node [shape=rectangle]" } ++
        in.map { case (node, (_, nexts)) => s"$node -> ${nexts.mkString(",")}" }).mkString(
        "digraph G {\n",
        "\n",
        "\n}"
      )
    }
  }

  extension [A](coll: IterableOnce[A]) {
    def toMutableMap[K, V](implicit ev: A <:< (K, V)): mutable.Map[K, V] =
      mutable.Map.from(coll.asInstanceOf[IterableOnce[(K, V)]])
  }

  class State[S](userStateInit: S)(userStateFunc: (S, Boolean, String) => S) {
    var userState = userStateInit
    var ffState = mutable.Map[String, Boolean]()
    var conjState = in
      .collect { case (name, ('&', _)) => name }
      .map { name =>
        name -> in.collect {
          case (from, (_, tos)) if tos.contains(name) => from -> false
        }.toMutableMap
      }.toMutableMap

    def record(sig: Boolean, node: String): Unit =
      userState = userStateFunc(userState, sig, node)
  }

  def press[S](st: State[S]): State[S] = {
    val q = mutable.Queue[(String, Boolean, String)]()
    q.enqueue(("button", false, "broadcaster"))

    while (!q.isEmpty) {
      val (from, sig, node) = q.dequeue()
      val (nodeTy, nexts) = in.getOrElse(node, (' ', Nil))
      st.record(sig, node)

      val newSig = (sig, nodeTy) match {
        case (false, '%') =>
          val newState = !st.ffState.getOrElse(node, false)
          st.ffState(node) = newState
          Some(newState)
        case (true, '%') =>
          None
        case (sig, '&') =>
          st.conjState(node)(from) = sig
          Some(st.conjState(node).values.exists(!_))
        case (sig, _) =>
          Some(sig)
      }
      newSig.foreach { sig =>
        nexts.foreach { to => q.enqueue((node, sig, to)) }
      }
    }
    st
  }

  println {
    val st = new State((0, 0))({ case ((h, l), sig, _) => if (sig) (h + 1, l) else (h, l + 1) })
    for (i <- 1 to 1000) press(st)
    st.userState.toList.product
  }

  writeDot()
  val cycleNodes = List("nx", "sp", "jq", "cc")

  println {
    cycleNodes.map { node =>
      val st = new State(false)({
        case (_, false, `node`) => true
        case (found, _, _) => found
      })
      Iterator.iterate(st)(press).indexWhere(_.userState).toLong
    }.product
  }
}
