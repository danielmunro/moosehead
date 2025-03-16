FROM ubuntu:24.04

RUN apt update
RUN apt install -y -- curl gcc libgc-dev libatomic-ops-dev csh make file gdb

WORKDIR /mud/moosehead
COPY area area
COPY newareas newareas
COPY clan clan
# COPY olc olc
COPY src src

WORKDIR /mud/moosehead/src
RUN make

WORKDIR /mud/moosehead/area
EXPOSE 4000
CMD ["./startup"]
