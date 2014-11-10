#!/bin/bash

# Basic testing script for the server

BASE_URL="localhost:8088"
CREATE_SESSION="session/create"
DELETE_SESSION="session/delete/\${SESSION}"
PING_SERVER="ping"

PING_URL="${BASE_URL}/${PING_SERVER}"
wget -O output "${PING_URL}"
if [ $? == 0 ]; then
    echo "Passed ping test"
    cat output
else
    echo "Failed ping test"
    exit 1
fi

URL="${BASE_URL}/${CREATE_SESSION}"
wget -O output --method="POST" --header="user_token: test" --header="Content-Type: application/json" "${URL}" 
if [ $? == 0 ]; then
    echo "Passed create session test"
    cat output
else
    echo "Failed create session test"
    exit 1
fi
