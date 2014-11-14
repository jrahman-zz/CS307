#!/bin/bash

#LEVEL="../../appserver/app/assets/images/tilemaps/level1.json"
LEVEL="data.json"
ls "${LEVEL}"
if [ $? != 0 ]; then
    echo "No level found"
    exit 1
fi

wget -O- --post-file="${LEVEL}" --header="Content-Type: application/json" localhost:5000/initialize

wget -O- --post-data='{"codelines": "hero.moveUp()\nhero.moveDown(2)"}' --header="Content-Type: application/json" localhost:5000/level/submit

wget -O- --post-data='{"codelines": "hero.moveUp()\nhero.moveDown(2)"}' --header="Content-Type: application/json" localhost:5000/level/submit
