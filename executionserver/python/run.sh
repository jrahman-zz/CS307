#!/bin/sh 
groupadd -f -g 1000 executor
useradd -u 1000 -g executor executor
chown -R executor /srv
su -m executor -c" python3 /srv/scripts/restserver.py"


