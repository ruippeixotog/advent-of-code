#!/usr/bin/env scala

import java.security.MessageDigest

val input = args(0)
val digest = MessageDigest.getInstance("MD5")
def md5(s: String) = digest.digest(s.getBytes).map("%02x".format(_)).mkString

var res = "........"

Iterator.from(0)
  .map { i => md5(s"$input$i") }
  .filter(_.startsWith("00000"))
  .filter { h => h(5) >= '0' && h(5) <= '7' && res(h(5).asDigit) == '.' }
  .take(8)
  .foreach { h => res = res.updated(h(5).asDigit, h(6)) }

println(res)
