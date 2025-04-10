#!/bin/bash

set -e
set -o xtrace

DIR=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )
IMAGE_REPO=$1
TAG=$2

docker pull $IMAGE_REPO:$TAG

CONTAINER=$(docker ps --quiet --filter label=mhs)

docker stop $CONTAINER
docker rm $CONTAINER

$DIR/run.sh $IMAGE_REPO $TAG