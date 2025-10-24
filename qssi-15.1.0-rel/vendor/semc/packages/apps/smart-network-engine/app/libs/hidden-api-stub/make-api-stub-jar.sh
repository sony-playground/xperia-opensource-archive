#!/bin/bash

# The path to mkstubs.jar (cf. development/tools/mkstubs/README.txt)
MKSTUBS_JAR=./mkstubs.jar

# The path to target jar
TARGET_JAR=$1

java -jar ${MKSTUBS_JAR} ${TARGET_JAR} stub.jar @${2}
