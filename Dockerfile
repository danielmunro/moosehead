FROM ubuntu:16.04

RUN apt-get update
RUN apt-get -y install curl gcc-5 csh make file gdb
RUN update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-5 1

WORKDIR /mud/moosehead
COPY . .

WORKDIR /mud/moosehead/deps/gc-7.4.2/libatomic_ops

RUN ./configure --prefix=/usr
RUN make
RUN make install

WORKDIR /mud/moosehead/deps/gc-7.4.2

RUN ./configure --prefix=/usr
RUN make
RUN make install && ldconfig

WORKDIR /mud/moosehead/src

RUN make

WORKDIR /mud/moosehead/area

EXPOSE 4000
CMD ["./startup"]
