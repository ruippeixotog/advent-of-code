name := "advent-of-code"

ThisBuild / scalaVersion := "3.2.1"
ThisBuild / libraryDependencies += "org.scala-lang.modules" %% "scala-parser-combinators" %  "2.1.1"

lazy val y2022 = project in file("2022")
