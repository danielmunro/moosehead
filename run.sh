#!/bin/bash

# Usage
# ./run.sh <image-to-run>

export IMAGE=$1
docker run --publish 4000:4000 \
           --mount type=volume,src=mud-data,dst=/mud/moosehead/data \
           --restart unless-stopped \
           --detach \
           --tty \
           $IMAGE
