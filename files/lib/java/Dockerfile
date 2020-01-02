#FROM gradle:jdk10
FROM openjdk:8-jdk

RUN apt-get update
RUN apt-get install -y build-essential
RUN apt-get install -y gdb
RUN apt-get install -y man

ADD java.c /java.c
ADD Makefile /Makefile
ADD Hello.java /Hello.java
ADD Hello.class /Hello.class
ADD test.sh /test.sh

RUN chmod +x /test.sh

ENTRYPOINT ["/test.sh"]
