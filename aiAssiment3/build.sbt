import Dependencies._

lazy val root = (project in file(".")).
  settings(
    inThisBuild(List(
      organization := "com.example",
      scalaVersion := "2.11.8",
      version      := "0.1.0-SNAPSHOT"
    )),
    name := "Hello",
    libraryDependencies += "org.apache.spark" %% "spark-mllib" % "2.2.0",
    libraryDependencies += "org.apache.spark" %% "spark-core" % "2.2.0"

  )
