#!/bin/sh
set +e
echo $JAVA_HOME
find / -iname libjvm.so
java -version
export VAR=`find / -iname libjvm.so`
export DIR=$(dirname "${VAR}")
export LD_LIBRARY_PATH=$DIR

CLASSPATHNEW=`find / -iname "artemis-0.8.2-SNAPSHOT" -type d | head -n +1`
echo $CLASSPATHNEW
CLEANCLASSPATH=`find / -iname "artemis" -type f -exec grep "CLASSPATH=" {} \; | head -n +1 | cut -d'=' -f 2 | sed 's@\$APP_HOME@'"${CLASSPATHNEW}"'@g'`

rm java.c
cat java.ctemplate

cat java.ctemplate | sed 's@|CLASSPATH|@'"${CLEANCLASSPATH}"'@' > java.c

cat java.c

rm jfuzz
make && gdb -batch ./jfuzz -ex "handle SIGSEGV nostop noprint pass" -ex "r" -ex "bt" -ex "kill" -ex "quit"

