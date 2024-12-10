import scala.io.Source

object Day09 extends App {
  val in = Source.fromFile("day09.in").mkString

  case class Sector(pos: Int, sz: Int, id: Int)

  val files = in.trim.map(_.asDigit).zipWithIndex.foldLeft((0, List[Sector]())) {
    case ((pos, acc), (sz, i)) =>
      (pos + sz, Sector(pos, sz, if (i % 2 == 0) i / 2 else -1) :: acc)
  }._2.reverse.toVector

  def checksum(files: Seq[Sector]): Long =
    files.filter(_.id >= 0).map { s => (0 until s.sz).map(k => s.id.toLong * (s.pos + k)).sum }.sum

  def fixPos(files: List[Sector]): List[Sector] =
    files.foldLeft((List[Sector](), 0)) { case ((acc, pos), s) =>
      (s.copy(pos = pos) :: acc, pos + s.sz)
    }._1.reverse

  def defrag(files: Vector[Sector], acc: List[Sector] = Nil): List[Sector] = files match {
    case f +: rest if f.id >= 0 => defrag(rest, f :: acc)
    case rest :+ sp if sp.id < 0 => defrag(rest, acc)
    case sp +: rest :+ f if sp.sz == f.sz => defrag(rest, f :: acc)
    case sp +: rest :+ f if sp.sz > f.sz => defrag(sp.copy(sz = sp.sz - f.sz) +: rest, f :: acc)
    case sp +: rest :+ f => defrag(rest :+ f.copy(sz = f.sz - sp.sz), f.copy(sz = sp.sz) :: acc)
    case _ => fixPos(acc.reverse)
  }

  def defrag2(
      files: Vector[Sector],
      id: Int = files.last.id,
      hdAcc: List[Sector] = Nil,
      tlAcc: List[Sector] = Nil
  ): List[Sector] = files match {
    case file +: rest if file.id >= 0 => defrag2(rest, id, file :: hdAcc, tlAcc)
    case rest :+ file if file.id != id => defrag2(rest, id, hdAcc, file :: tlAcc)
    case rest :+ file => defrag2(defrag2Place(rest, file), id - 1, hdAcc, tlAcc)
    case _ => fixPos(hdAcc.reverse ++ tlAcc)
  }

  def defrag2Place(
      files: Vector[Sector],
      s: Sector,
      acc: Vector[Sector] = Vector()
  ): Vector[Sector] = files match {
    case f +: rest if f.id >= 0 => defrag2Place(rest, s, acc :+ f)
    case sp +: rest if sp.sz == s.sz => acc :+ s :++ rest :+ sp
    case sp +: rest if sp.sz < s.sz => defrag2Place(rest, s, acc :+ sp)
    case sp +: rest => acc :+ s :+ sp.copy(sz = sp.sz - s.sz) :++ rest :+ sp.copy(sz = s.sz)
    case Vector() => acc :+ s
  }

  println(checksum(defrag(files)))
  println(checksum(defrag2(files)))
}
