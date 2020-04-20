#!/bin/sh
set +e

SCRIPTDIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"
echo "DIR:" $SCRIPTDIR

echo $JAVA_HOME
find / -iname libjvm.so
java -version
export VAR=`find / -iname libjvm.so`
export DIR=$(dirname "${VAR}")
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$DIR

rm -rf /eth2/artemis-0.8.2-SNAPSHOT
cd /eth2/artemis && gradle assemble --stacktrace
cd /eth2 && (yes | cp /eth2/artemis/build/distributions/artemis-0.8.2-SNAPSHOT.zip .)
cd /eth2 && unzip -o /eth2/artemis/build/distributions/artemis-0.8.2-SNAPSHOT.zip

# Ensure we are in the same directory as this script (the project root).
cd $SCRIPTDIR || exit

CLASSPATHNEW=`find /eth2 -iname "artemis-0.8.2-SNAPSHOT" -type d | head -n +1`
echo $CLASSPATHNEW
CLEANCLASSPATH=`find /eth2 -iname "artemis" -type f -exec grep "CLASSPATH=" {} \; | head -n +1 | cut -d'=' -f 2 | sed 's@\$APP_HOME@'"${CLASSPATHNEW}"'@g'`

rm java.c
cat java.ctemplate

cat java.ctemplate | sed 's@|CLASSPATH|@'"${CLEANCLASSPATH}"'@' > java.c

cat java.c

rm jfuzz
make && gdb -batch ./jfuzz -ex "handle SIGSEGV nostop noprint pass" -ex "r" -ex "bt" -ex "kill" -ex "quit"

