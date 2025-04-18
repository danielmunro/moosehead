#!/bin/bash

ENV_FILE=$1

docker run --volume mud-data:/backup/data \
           --env-file $ENV_FILE \
           --rm \
           --entrypoint backup \
           offen/docker-volume-backup:v2