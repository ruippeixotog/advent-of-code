import scala.io.Source

object Day23 extends App {
  val in = Source.fromFile("day23.in").getLines.zipWithIndex.flatMap { (row, i) =>
    row.zipWithIndex.collect { case (ch, j) if ch == '#' => (i, j) }
  }.toSet

  def adjs(i: Int, j: Int, di: Int, dj: Int) =
    if (di != 0) List((i + di, j), (i + di, j + di), (i + di, j - di))
    else List((i, j + dj), (i + dj, j + dj), (i - dj, j + dj))

  type State = (Set[(Int, Int)], Vector[(Int, Int)])

  def step(st: State): Option[(Set[(Int, Int)], State)] = {
    val (elves, order) = st
    val newElves = elves.toList
      .groupBy { (i, j) =>
        val opts = order.filter { (di, dj) => !adjs(i, j, di, dj).exists(elves) }
        if (order.length == opts.length) None
        else opts.headOption.map { (di, dj) => (i + di, j + dj) }
      }.foldLeft(Set[(Int, Int)]()) {
        case (acc, (Some(newPos), List(_))) => acc + newPos
        case (acc, (_, poss)) => acc ++ poss
      }
    if (elves == newElves) None
    else Some((newElves, (newElves, order.tail :+ order.head)))
  }

  val dirs = Vector((-1, 0), (1, 0), (0, -1), (0, 1))
  val states = in #:: LazyList.unfold((in, dirs))(step)

  println {
    val st = states(10)
    (st.map(_._1).max - st.map(_._1).min + 1) * (st.map(_._2).max - st.map(_._2).min + 1) - st.size
  }
  println(states.length)
}
