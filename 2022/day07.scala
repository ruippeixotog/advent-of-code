import scala.io.Source

case class Dir(files: Map[String, Int] = Map(), dirs: Map[String, Dir] = Map()) {

  def insert(path: List[String], child: Dir): Dir = path match {
    case Nil => child
    case p :: rest => copy(dirs = dirs + (p -> dirs(p).insert(rest, child)))
  }

  def dirSizes: (Int, List[Int]) = {
    val (szs, ls) = dirs.values.map(_.dirSizes).unzip
    val sz = files.values.sum + szs.sum
    (sz, sz :: ls.toList.flatten)
  }
}

object Day07 extends App {
  val in = Source.fromFile("2022/day07.in").mkString.split("(\n|^)\\$ ").tail
    .map(_.split("\n").toList.map(_.split(" ").toList))

  val (fs, _) = in.foldLeft((Dir(), List.empty[String])) {
    case ((fs, cwd), List("cd", "/") :: _) => (fs, Nil)
    case ((fs, cwd), List("cd", "..") :: _) => (fs, cwd.tail)
    case ((fs, cwd), List("cd", dir) :: _) => (fs, dir :: cwd)
    case ((fs, cwd), List("ls") :: lsEntries) =>
      val dir = lsEntries.foldLeft(Dir()) {
        case (dir, List("dir", name)) => dir.copy(dirs = dir.dirs + (name -> Dir()))
        case (dir, List(size, name)) => dir.copy(files = dir.files + (name -> size.toInt))
        case other => throw IllegalArgumentException(other.toString)
      }
      (fs.insert(cwd.reverse, dir), cwd)
    case other =>
      throw IllegalArgumentException(other.toString)
  }
  val (rootSize, dirSizes) = fs.dirSizes

  println(dirSizes.filter(_ <= 100000).sum)
  println(dirSizes.filter(_ >= 30000000 - (70000000 - rootSize)).min)
}
