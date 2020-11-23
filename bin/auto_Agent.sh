#!/bin/bash

cd "$(dirname "$0")"

sudo python /home/bedis/Agent/bin/LightControl.py &
sudo ./Agent >/dev/null 2>&1 &

exit 0
