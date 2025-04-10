#!/bin/bash

set -e
set -o xtrace

TAG=$1

docker pull $IMAGE_REPO:$TAG

CONTAINER=$(docker ps --quiet --filter label=mhs)

docker stop $CONTAINER
docker rm $CONTAINER

./run.sh $IMAGE_REPO $TAG