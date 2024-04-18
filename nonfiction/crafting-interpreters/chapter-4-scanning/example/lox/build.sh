#!/bin/sh

javac com/craftinginterpreters/lox/*.java

jar -vcfm Lox.jar MANIFEST.MF com/craftinginterpreters/lox/*.class
