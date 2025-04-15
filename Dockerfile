FROM ubuntu:24.04

RUN apt update
RUN apt install -y -- curl gcc libgc-dev libatomic-ops-dev libjansson-dev make file gdb git

RUN git clone https://github.com/jacketizer/libyuarel.git

WORKDIR /libyuarel
RUN make
RUN make install

WORKDIR /mud/moosehead
COPY src src

WORKDIR /mud/moosehead/src
RUN make

# Mud port
EXPOSE 4000

# HTTP server port
EXPOSE 4080

ENTRYPOINT ["./moose"]
