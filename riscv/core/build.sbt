// val spinalVersion = "1.4.3"

// name := "VexRiscvStream"

// version := "0.1"

// scalaVersion := "2.11.12"

// libraryDependencies ++= Seq(
//   "org.scalatest" % "scalatest_2.11" % "2.2.1",
//   "com.github.spinalhdl" % "spinalhdl-core_2.11" % spinalVersion,
//   "com.github.spinalhdl" % "spinalhdl-lib_2.11" % spinalVersion
// )

// lazy val vexRiscV = RootProject(uri("https://github.com/SpinalHDL/VexRiscv.git"))
// lazy val root = Project("root", file(".")).dependsOn(vexRiscV)

// fork := true

val spinalVersion = "1.4.3"

lazy val root = (project in file(".")).
  settings(
    inThisBuild(List(
      organization := "com.github.icgrp",
      scalaVersion := "2.11.12",
      version      := "0.1"
    )),
    libraryDependencies ++= Seq(
      "com.github.spinalhdl" % "spinalhdl-core_2.11" % spinalVersion,
      "com.github.spinalhdl" % "spinalhdl-lib_2.11" % spinalVersion,
      compilerPlugin("com.github.spinalhdl" % "spinalhdl-idsl-plugin_2.11" % spinalVersion),
      "org.scalatest" % "scalatest_2.11" % "2.2.1",
      "org.yaml" % "snakeyaml" % "1.8"
    ),
    name := "VexRiscvStream"
  )
  .dependsOn(vexRiscV)
lazy val vexRiscV = RootProject(uri("https://github.com/SpinalHDL/VexRiscv.git"))


fork := true
