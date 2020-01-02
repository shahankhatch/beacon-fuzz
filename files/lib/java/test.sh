#!/bin/sh
set +e
echo $JAVA_HOME
find / -iname libjvm.so
java -version
#ls -la $JAVA_HOME/*
export VAR=`find / -iname libjvm.so`
export DIR=$(dirname "${VAR}")
export LD_LIBRARY_PATH=$DIR
cd / && javac Hello.java
cd / && make && gdb -batch ./jfuzz -ex "handle SIGSEGV nostop noprint pass" -ex "r" -ex "bt" -ex "kill" -ex "quit"
