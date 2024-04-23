#!/bin/sh

javac com/craftinginterpreters/lox/*.java

jar -vcfm Lox.jar MANIFEST.MF com/craftinginterpreters/lox/*.class

javac com/craftinginterpreters/tool/*.java
jar -vcfm GenerateAst.jar MANIFEST-GENERATE-AST.MF com/craftinginterpreters/tool/*.class
