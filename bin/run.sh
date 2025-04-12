#!/bin/bash

# Usage
# ./run.sh <image-to-run> <tag>

export IMAGE=$1
export TAG=$2
docker run --publish 4000:4000 \
           --publish 4080:4080 \
           --mount type=volume,src=mud-data,dst=/mud/moosehead/data \
           --restart unless-stopped \
           --detach \
           --label mhs=true \
           --tty \
           $IMAGE:$TAG $TAG 4000
