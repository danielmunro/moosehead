#!/bin/bash

# Usage
# ./run.sh <image-to-run>

export IMAGE=$1
docker run --publish 4000:4000 \
           --mount type=bind,src=$PWD/clan,dst=/mud/moosehead/clan \
           --mount type=bind,src=$PWD/gods,dst=/mud/moosehead/gods \
           --mount type=bind,src=$PWD/jail,dst=/mud/moosehead/jail \
           --mount type=bind,src=$PWD/jerks,dst=/mud/moosehead/jerks \
           --mount type=bind,src=$PWD/player,dst=/mud/moosehead/player \
           --restart unless-stopped \
           --detach \
           --user $UID \
           --tty \
           $IMAGE
