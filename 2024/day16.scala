import scala.io.Source
import scala.collection.mutable

object Day16 extends App {
  val in = Source.fromFile("day16.in").getLines.toVector

  val di = Vector(-1, 0, 1, 0)
  val dj = Vector(0, 1, 0, -1)

  def dijkstra2(i0: Int, j0: Int): (Int, Int) = {
    type State = (Int, Int, Int)

    val q = mutable.PriorityQueue[(Int, State)]((0, (i0, j0, 1)))
    val prev = mutable.Map[State, (Int, List[State])]((i0, j0, 1) -> (0, Nil))

    def addToQueue(curr: State, dist: Int, next: State): Unit = {
      prev.get(next) match {
        case Some((prevDist, _)) if dist < prevDist =>
        // do nothing
        case Some((prevDist, prevLocs)) if dist == prevDist =>
          prev(next) = (dist, curr :: prevLocs)
        case _ =>
          prev(next) = (dist, List(curr))
          q += ((dist, next))
      }
    }

    def collectTiles(st: State): Set[(Int, Int)] = prev.get(st) match {
      case None => Set(st.init)
      case Some((_, prevs)) => prevs.toSet.flatMap(collectTiles) + st.init
    }

    while (!q.isEmpty) {
      val (dist, curr @ (i, j, d)) = q.dequeue()

      if (in(i)(j) == 'E') {
        return (-dist, collectTiles(curr).size)
      }
      if (in(i + di(d))(j + dj(d)) != '#') {
        addToQueue(curr, dist - 1, (i + di(d), j + dj(d), d))
      }
      addToQueue(curr, dist - 1000, (i, j, (d + 1) % 4))
      addToQueue(curr, dist - 1000, (i, j, (d + 3) % 4))
    }
    return (-1, 0)
  }

  val (i0, j0) = in.indices.flatMap(i => in(i).indices.map((i, _))).find(in(_)(_) == 'S').get
  val (dist, numTiles) = dijkstra2(i0, j0)
  println(dist)
  println(numTiles)
}
