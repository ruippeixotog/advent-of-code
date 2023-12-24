import scala.io.Source

object Day15 extends App {
  val minusPatt = "(.+)-".r
  val eqPatt = "(.+)=([0-9]+)".r

  val in = Source.fromFile("day15.in").mkString.trim.split(",").toList

  def hash(str: String) = str.foldLeft(0) { (acc, c) => (acc + c) * 17 % 256 }

  println(in.map(hash).sum)

  class HMap {
    private val arr: Array[List[(String, Int)]] = Array.fill(256)(Nil)

    private def bInsert[K, V](kvs: List[(K, V)], k: K, v: V): List[(K, V)] = kvs match {
      case (`k`, _) :: kvs1 => (k, v) :: kvs1
      case kv :: kvs1 => kv :: bInsert(kvs1, k, v)
      case Nil => List(k -> v)
    }

    def +=(kv: (String, Int)) = arr(hash(kv._1)) = bInsert(arr(hash(kv._1)), kv._1, kv._2)
    def -=(k: String) = arr(hash(k)) = arr(hash(k)).filter(_._1 != k)
    def power = {
      val vs = for (i <- arr.indices; j <- arr(i).indices) yield arr(i)(j)._2 * (i + 1) * (j + 1)
      vs.sum
    }
  }

  val hm = HMap()
  in.foreach {
    case minusPatt(k) => hm -= k
    case eqPatt(k, vStr) => hm += k -> vStr.toInt
  }
  println(hm.power)
}
