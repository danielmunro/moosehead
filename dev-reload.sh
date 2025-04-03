#!/bin/bash

set -e
set -o xtrace

CONTAINER=$(docker ps --quiet --filter label=mhs)

if [ ! -z "$CONTAINER" ]; then
  docker stop $CONTAINER
fi

docker build --progress=plain -t mhs:latest . &> build.log

./run.sh mhs latest
