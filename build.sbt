name := "advent-of-code"

ThisBuild / scalaVersion := "3.3.1"
ThisBuild / libraryDependencies += "org.scala-lang.modules" %% "scala-parser-combinators" %  "2.3.0"


lazy val y2022 = project in file("2022")
lazy val y2023 = project in file("2023")

run / fork := true
