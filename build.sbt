name := "advent-of-code"
scalaVersion := "3.2.1"

lazy val y2022 = project in file("2022")

inScope(Global) {
  libraryDependencies += "org.scala-lang.modules" %% "scala-parser-combinators" %  "2.1.1"
}
