#!/usr/bin/env bash

set -e

# @describe A cli for common tasks

run() {
  IMAGE_REPO=$1
  TAG=$2
  docker run --publish 4000:4000 \
             --publish 4080:4080 \
             --mount type=volume,src=mud-data,dst=/mud/moosehead/data \
             --restart unless-stopped \
             --detach \
             --label mhs=true \
             --tty \
             $IMAGE_REPO:$TAG $TAG 4000 4080
}

# @cmd Create a backup of MHS data
# @arg env_file!
backup() {
  docker run --volume mud-data:/backup/data \
             --env-file $argc_env_file \
             --rm \
             --entrypoint backup \
             offen/docker-volume-backup:v2
}

# @cmd Build the current source and reload the running container
# @flag -t --tail Tail the container log
# @flag -o --olc  Run as OLC
dev_reload() {
  if [ "$argc_olc" == "1" ]; then
    RUN_VERSION="OLC_VERSION"
  else
    RUN_VERSION="GAME_VERSION"
  fi

  echo "building the container with run version ${RUN_VERSION}"

  docker build --build-arg RUN_VERSION=$RUN_VERSION -t mhs:latest .

  CONTAINER=$(docker ps --quiet --filter label=mhs)

  if [ ! -z "$CONTAINER" ]; then
    echo "stopping and removing the running container"
    docker stop $CONTAINER
    docker rm $CONTAINER
  fi

  echo "running the new container"

  CONTAINER=$(run mhs latest)

  echo "done"

  if [ "$argc_tail" ]; then
    docker logs -f $CONTAINER
  fi
}

# @cmd Run the tests
test() {
  docker build --build-arg RUN_VERSION=GAME_VERSION -f Dockerfile-test -t mhs:test .
  docker run mhs:test
}

# @cmd Build a production image
# @arg username!
# @arg cr_pat!
# @arg image!
prod_build() {
  docker build -t $argc_image .
  echo "$argc_cr_pat" | docker login -u $argc_username ghcr.io --password-stdin
  docker push $argc_image
}

# @cmd Stop the running container and start a new one
# @arg image!
# @arg tag!
reload() {
  CONTAINER=$(docker ps --quiet --filter label=mhs)

  if [ ! -z "$CONTAINER" ]; then
    echo "stopping and removing the running container"
    docker stop $CONTAINER
    docker rm $CONTAINER
  fi

  run $argc_image $argc_tag
}

# @cmd Deploy a production image
# @arg ssh_keyfile!
# @arg ssh_destination!
# @arg ssh_port!
# @arg image!
# @arg tag!
# @flag -rv --run-version The version to run, either GAME_VERSION or OLC_VERSION
prod_deploy() {
  RUN_VERSION=${argc_run_version:-"GAME_VERSION"}

  echo "check for valid image: ${argc_image:$argc_tag}"

  docker manifest inspect $argc_image:$argc_tag > /dev/null

  if [ $? -ne 0 ]; then
    echo "image $argc_image:$argc_tag does not exist"
    exit 1
  fi

  echo "ssh to prod machine"

  ssh -i $argc_ssh_keyfile $argc_ssh_destination -p $argc_ssh_port << EOF

echo "pulling the latest code

cd github/moosehead

git pull

echo "pulling the docker image"

docker pull $argc_image:$argc_tag

echo "running the new image"

./bin/mhs reload $argc_image $argc_tag

echo "done"

EOF
}

eval "$(argc --argc-eval "$0" "$@")"
