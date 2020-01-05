FROM gradle:jdk11 as artemis
WORKDIR /eth2

#RUN apt-get update && apt-get upgrade -y
RUN apt-get update
RUN apt-get install -y build-essential gdb clang-8 git zlib1g-dev libssl-dev libboost-all-dev wget locales curl python3-pip g++-8 gcc-8

#RUN wget https://services.gradle.org/distributions/gradle-6.0.1-bin.zip
#RUN mkdir /opt/gradle
#RUN unzip -d /opt/gradle gradle-6.0.1-bin.zip

# Artemis - start

# OR even more basic docker image
#FROM openjdk:11.0.2-jre-slim-stretch
#RUN wget https://services.gradle.org/distributions/gradle-6.0.1-bin.zip
#RUN mkdir -p /opt/gradle
#RUN unzip -d /opt/gradle gradle-6.0.1-bin.zip

ADD artemis /eth2/artemis
#RUN git clone --branch beacon-fuzz https://github.com/shahankhatch/artemis
#ADD ../artemis /eth2/artemis # will never work due to context out of scope
RUN cd artemis && gradle assemble -x test --stacktrace
#RUN ls -a artemis/*

#RUN ls -a -R ./artemis/build/*
RUN unzip ./artemis/build/distributions/artemis-0.8.2-SNAPSHOT.zip
RUN cp ./artemis/build/distributions/artemis-0.8.2-SNAPSHOT.zip .

#RUN apt-get install -y gdb
# Artemis - end

#*RUN apt-get install -y build-essential clang-8 git zlib1g-dev libssl-dev libboost-all-dev wget locales curl python3-pip g++-8 gcc-8
# For trinity
# TODO trinity has cmake in its dockerfile, needed?
#*RUN apt-get install -y libleveldb1v5 libleveldb-dev libgmp3-dev libsnappy-dev

#*RUN wget -q https://dl.google.com/go/go1.12.linux-amd64.tar.gz
#*RUN tar -zxf go1.12.linux-amd64.tar.gz

# To clear cache when branch updates
#*ADD https://api.github.com/repos/gnattishness/cpython/git/refs/heads/fuzzing meta/cpython_version.json
#*RUN git clone --branch fuzzing --depth 1 https://github.com/gnattishness/cpython.git

# TODO use tag when possible
# This is a tag, so fine to always cache
#RUN git clone --branch v0.8.3 --depth 1 https://github.com/sigp/lighthouse lighthouse
#*RUN git clone --branch master https://github.com/sigp/lighthouse lighthouse && cd lighthouse && git checkout c04026d073d12a98499c9cebd6d6134fc75355a9

# TODO(gnattishness) add other git clones here so they get cached

ADD files /eth2

RUN locale-gen en_US.UTF-8
ENV LANG en_US.UTF-8
ENV LANGUAGE en_US:en
ENV LC_ALL en_US.UTF-8
CMD ["/bin/bash"]
#ENTRYPOINT ["/eth2/build.sh"]
#RUN /eth2/build.sh
