#JAVA_HOME:=`/usr/libexec/java_home`
CPPFLAGS:=-I$(JAVA_HOME)/include -I$(JAVA_HOME)/include/linux -L$(DIR)
#-I $(JAVA_HOME)/include/darwin

jfuzz:
	gcc -g $(CPPFLAGS) -o jfuzz java.c -ljvm

	#-framework JavaVM

#