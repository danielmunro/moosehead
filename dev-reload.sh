#!/bin/bash

set -e
set -o xtrace

CONTAINER=$(docker ps --quiet --filter label=mhs)

if [ ! -z "$CONTAINER" ]; then
  docker stop $CONTAINER
fi

docker build -t mhs:latest .

RUNNING_CONTAINER=$(./run.sh mhs latest)

docker logs -f $RUNNING_CONTAINER
