FROM ubuntu:18.04

RUN apt-get update
RUN apt-get -y install curl gcc-5 csh make file gdb
RUN update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-5 1

WORKDIR /mud/moosehead
COPY area area
COPY newareas newareas
COPY clan clan
#COPY olc olc
COPY deps deps
COPY src src

WORKDIR /mud/moosehead/deps/libatomic_ops-7.4.0
RUN ./configure --prefix=/usr
RUN make
RUN make install

WORKDIR /mud/moosehead/deps/gc-7.4.2
RUN ln -s ../libatomic_ops-7.4.0 libatomic_ops
RUN ./configure --prefix=/usr
RUN make
RUN make install && ldconfig

WORKDIR /mud/moosehead/src
RUN make

WORKDIR /mud/moosehead/area
EXPOSE 4000
CMD ["./startup"]
