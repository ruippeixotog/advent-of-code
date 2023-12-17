#!/usr/bin/env scala

import java.security.MessageDigest

val input = args(0)
val digest = MessageDigest.getInstance("MD5")
def md5(s: String) = digest.digest(s.getBytes).map("%02x".format(_)).mkString

val res = Iterator.from(0)
  .map { i => md5(s"$input$i") }
  .filter(_.startsWith("00000"))
  .take(8)
  .map(_(5))
  .mkString

println(res)
