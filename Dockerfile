FROM ubuntu:24.04

RUN apt update
RUN apt install -y -- curl gcc libgc-dev libatomic-ops-dev csh make file gdb

WORKDIR /mud/moosehead
COPY area area
COPY src src

WORKDIR /mud/moosehead/src
RUN make
EXPOSE 4000
CMD ["./moose", "4000"]
