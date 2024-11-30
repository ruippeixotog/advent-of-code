name := "advent-of-code"

ThisBuild / scalaVersion := "3.5.2"
ThisBuild / libraryDependencies += "org.scala-lang.modules" %% "scala-parser-combinators" %  "2.4.0"

lazy val y2022 = project in file("2022")
lazy val y2023 = project in file("2023")
lazy val y2024 = project in file("2024")

ThisBuild / fork := true
