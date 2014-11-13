#!/bin/bash

wget -O- --post-file=level.json --header="Content-Type: application/json" localhost:5000/initialize

wget -O- --post-data='{"codelines": "hero.moveUp()\nhero.moveDown(2)"}' --header="Content-Type: application/json" localhost:5000/level/submit

wget -O- --post-data='{"codelines": "hero.moveUp()\nhero.moveDown(2)"}' --header="Content-Type: application/json" localhost:5000/level/submit
