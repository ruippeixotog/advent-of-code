import scala.io.Source
import scala.annotation.tailrec
import scala.collection.immutable.BitSet

final case class Tetris(
  grid: BitSet, height: Int, trimHeight: Long, pieceIdx: Int, windPatt: Vector[Int], windIdx: Int) {

  def get(x: Int, y: Int): Boolean =
    if(y <= 0 || x <= 0 || x >= 8) true else grid(y * 7 + (x - 1))
  
  def set(x: Int, y: Int): Tetris =
    copy(grid = grid + (y * 7 + (x - 1)), height = height.max(y))

  def nextPiece: (List[(Int, Int)], Tetris) =
    (Tetris.pieces(pieceIdx), copy(pieceIdx = (pieceIdx + 1) % Tetris.pieces.length))

  def nextWind: (Int, Tetris) =
    (windPatt(windIdx), copy(windIdx = (windIdx + 1) % windPatt.length))

  def collides(piece: List[(Int, Int)], x: Int, y: Int): Boolean =
    piece.exists { case (dx, dy) => get(x + dx, y + dy) }

  def place(piece: List[(Int, Int)], x: Int, y: Int): Tetris =
    piece.foldLeft(this) { case (tetris, (dx, dy)) => tetris.set(x + dx, y + dy) }

  def moveAndPlace(piece: List[(Int, Int)], x: Int, y: Int): Tetris = {
    val (wx, tet) = nextWind
    val (x0, y0) = if(collides(piece, x + wx, y)) (x, y) else (x + wx, y)
    if(collides(piece, x0, y0 - 1)) tet.place(piece, x0, y0)
    else tet.moveAndPlace(piece, x0, y0 - 1)
  }

  def placeNext: Tetris = {
    val (piece, tet) = nextPiece
    tet.moveAndPlace(piece, 3, height + 4).trim
  }

  def run(its: Long, mem: Map[(BitSet, Int, Int), (Long, Long)] = Map()): Tetris = its match {
    case 0 => this
    case _ =>
      val tNext = this.placeNext
      val memKey = (tNext.grid, tNext.pieceIdx, tNext.windIdx)
      mem.get(memKey) match {
        case None =>
          tNext.run(its - 1, mem + (memKey -> (its, tNext.trimHeight)))
        case Some((memIts, memTrimHeight)) =>
          val cycleIts = memIts - its
          val cycleHeight = tNext.trimHeight - memTrimHeight
          val ffCycles = its / cycleIts
          tNext.copy(trimHeight = tNext.trimHeight + ffCycles * cycleHeight)
            .run(its - 1 - ffCycles * cycleIts, mem)
      }
  }

  def totalHeight: Long = trimHeight + height

  def trim: Tetris = (height - Tetris.maxHeight).max(0) match {
    case 0 => this
    case adj =>
      val shifted = grid.filter(_ - adj * 7 >= 0).map(_ - adj * 7)
      copy(grid = shifted, height = Tetris.maxHeight, trimHeight = trimHeight + adj)
  }
}

object Tetris {
  val maxHeight = 100

  val pieces = Vector(
    List((0, 0), (1, 0), (2, 0), (3, 0)),
    List((0, 1), (1, 0), (1, 1), (1, 2), (2, 1)),
    List((0, 0), (1, 0), (2, 0), (2, 1), (2, 2)),
    List((0, 0), (0, 1), (0, 2), (0, 3)),
    List((0, 0), (0, 1), (1, 0), (1, 1))
  )

  def apply(windPatt: Seq[Int]): Tetris =
    Tetris(BitSet(), 0, 0, 0, windPatt.toVector, 0)
}

object Day17 extends App {
  val in = Source.fromFile("2022/day17.in").mkString.trim.map { ch => if(ch == '<') -1 else 1 }

  println(Tetris(in).run(2022).totalHeight)
  println(Tetris(in).run(1000000000000L).totalHeight)
}
