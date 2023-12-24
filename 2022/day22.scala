import scala.io.Source

object Day22 extends App {
  val Array(in1, in2) = Source.fromFile("day22.in").mkString.split("\n\n")
  val inMap = in1.split("\n").map(_.toVector).toVector
  val inPath = """(R|L|\d+)""".r.findAllMatchIn(in2).map(_.group(1)).toList

  val dirs = Vector((0, 1), (1, 0), (0, -1), (-1, 0))

  def mapBounds(vec: Vector[Char]) = vec.indexWhere(_ != ' ') to vec.lastIndexWhere(_ != ' ')
  def getColumn(j: Int) = inMap.map(_.lift(j).getOrElse(' '))

  val jBounds = inMap.map(mapBounds)
  val iBounds = inMap.maxBy(_.length).indices.map(getColumn.andThen(mapBounds))
  val faceSize = Math.sqrt(jBounds.map(_.size).sum / 6).toInt

  def sim(moveFun: (Int, Int, Int) => (Int, Int, Int)): Int = {
    val (iFinal, jFinal, dirFinal) = inPath.foldLeft((0, jBounds(0).start, 0)) {
      case ((i, j, dir), "L") => (i, j, (dir + 3) % 4)
      case ((i, j, dir), "R") => (i, j, (dir + 1) % 4)
      case ((i, j, dir), num) =>
        (1 to num.toInt).foldLeft((i, j, dir)) { case ((i, j, dir), _) =>
          val (i1, j1, dir1) = moveFun(i, j, dir)
          if (inMap(i1)(j1) == '#') (i, j, dir) else (i1, j1, dir1)
        }
    }
    1000 * (iFinal + 1) + 4 * (jFinal + 1) + dirFinal
  }

  def move1(i: Int, j: Int, dir: Int): (Int, Int, Int) =
    (
      Math.floorMod(i - iBounds(j).start + dirs(dir)._1, iBounds(j).size) + iBounds(j).start,
      Math.floorMod(j - jBounds(i).start + dirs(dir)._2, jBounds(i).size) + jBounds(i).start,
      dir
    )

  def jumpFace(i: Int, j: Int, dir: Int): (Int, Int, Int) = (i, j, dir) match {
    case (0, 2, 0) => (2, 1, 2)
    case (1, 1, 0) => (0, 2, 3)
    case (2, 1, 0) => (0, 2, 2)
    case (3, 0, 0) => (2, 1, 3)

    case (3, 0, 1) => (0, 2, 1)
    case (2, 1, 1) => (3, 0, 2)
    case (0, 2, 1) => (1, 1, 2)

    case (0, 1, 2) => (2, 0, 0)
    case (1, 1, 2) => (2, 0, 1)
    case (2, 0, 2) => (0, 1, 0)
    case (3, 0, 2) => (0, 1, 1)

    case (2, 0, 3) => (1, 1, 0)
    case (0, 1, 3) => (3, 0, 0)
    case (0, 2, 3) => (3, 0, 3)
  }

  def rotate(i: Int, j: Int) = (j, faceSize - i - 1)

  def jumpCoords(i: Int, j: Int, dir: Int): (Int, Int, Int) = {
    val (iFace, jFace) = (i / faceSize, j / faceSize)
    val (iMod, jMod) = (i % faceSize, j % faceSize)
    val (iFaceNext, jFaceNext, dirNext) = jumpFace(iFace, jFace, dir)

    val (iModNext, jModNext) = {
      val initial = (iMod - dirs(dir)._1 * faceSize, jMod - dirs(dir)._2 * faceSize)
      LazyList.iterate(initial)(rotate.tupled)(Math.floorMod(dirNext - dir, 4))
    }
    (iFaceNext * faceSize + iModNext, jFaceNext * faceSize + jModNext, dirNext)
  }

  def move2(i: Int, j: Int, dir: Int): (Int, Int, Int) = {
    val (di, dj) = dirs(dir)
    if (iBounds(j).contains(i + di) && jBounds(i).contains(j + dj)) (i + di, j + dj, dir)
    else {
      val (iJump, jJump, newDir) = jumpCoords(i, j, dir)
      (iJump + dirs(newDir)._1, jJump + dirs(newDir)._2, newDir)
    }
  }

  println(sim(move1))
  println(sim(move2))
}
