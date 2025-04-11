#!/bin/bash

set -e
set -o xtrace

DIR=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )

docker build -t mhs:latest .

CONTAINER=$(docker ps --quiet --filter label=mhs)

if [ ! -z "$CONTAINER" ]; then
  docker stop $CONTAINER
  docker rm $CONTAINER
fi

CONTAINER=$($DIR/run.sh mhs latest)

docker logs -f $CONTAINER
