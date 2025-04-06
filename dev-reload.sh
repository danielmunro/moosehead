#!/bin/bash

set -e
set -o xtrace

docker build -t mhs:latest .

CONTAINER=$(docker ps --quiet --filter label=mhs)

if [ ! -z "$CONTAINER" ]; then
  docker stop $CONTAINER
  docker rm $CONTAINER
fi

CONTAINER=$(./run.sh mhs latest)

docker logs -f $CONTAINER
