import scala.io.Source

object Day25 extends App {
  val in = Source.fromFile("day25.in").getLines.map { line =>
    val Array(src, dests) = line.split(": ")
    (src, dests.split(" ").toList)
  }.toList

  val adjMat: Array[Array[Int]] = {
    val ids = in.flatMap { (k, adjs) => k :: adjs }.distinct.zipWithIndex.toMap
    val mat = Array.ofDim[Int](ids.size, ids.size)
    in.foreach { (k, adjs) =>
      adjs.foreach { adj =>
        mat(ids(k))(ids(adj)) = 1
        mat(ids(adj))(ids(k)) = 1
      }
    }
    mat
  }

  def minCut(mat: Array[Array[Int]]): (Int, Vector[Int]) = {
    val n = mat.size
    val co = Array.tabulate(n)(Vector(_))
    var best = (Int.MaxValue, Vector.empty[Int])

    for (ph <- 1 until n) {
      val w = mat(0).clone()
      var s, t = 0

      for (it <- 0 until n - ph) {
        w(t) = Int.MinValue
        s = t
        t = w.zipWithIndex.maxBy(_._1)._2
        for (i <- 0 until n) w(i) += mat(t)(i)
      }
      best = List(best, (w(t) - mat(t)(t), co(t))).min
      co(s) = co(s) ++ co(t)
      for (i <- 0 until n) mat(s)(i) += mat(t)(i)
      for (i <- 0 until n) mat(i)(s) = mat(s)(i)
      mat(0)(t) = Int.MinValue
    }
    best
  }

  val (3, part) = minCut(adjMat): @unchecked
  println(part.length * (adjMat.length - part.length))
}
