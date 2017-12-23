import scala.io.Source

type Image = Vector[String]

def flipV(img: Image): Image = img.reverse

def rotate(img: Image, rots: Int): Image = {
  if(rots == 0) img
  else rotate(img.transpose.map(_.reverse.mkString), rots - 1)
}

def allPositions(img: Image): Seq[Image] =
  (0 to 3).flatMap { r => Seq(rotate(img, r), flipV(rotate(img, r))) }

val rules: Map[Vector[String], Vector[String]] = {
  Source.fromInputStream(System.in).getLines.flatMap { line =>
    val spl = line.split(" => ").map(_.split("/"))
    allPositions(spl(0).toVector).map(_ -> spl(1).toVector)
  }.toMap
}

def applyRules(img: Image, iters: Int): Image = {
  (1 to iters).foldLeft(img) { (img, _) =>
    val grpSize = if(img.length % 2 == 0) 2 else 3

    img.grouped(grpSize).flatMap { lines =>
      val groups = lines.map(_.grouped(grpSize).toVector).transpose
      val transformed = groups.map(rules(_))
      transformed.transpose.map(_.mkString)
    }.toVector
  }
}

def countPixelsOn(img: Image): Int =
  img.map(_.count(_ == '#')).sum

val startImg = Vector(".#.", "..#", "###")
val resImg1 = applyRules(startImg, 5)
val resImg2 = applyRules(resImg1, 18 - 5)
println(s"${countPixelsOn(resImg1)} ${countPixelsOn(resImg2)}")
