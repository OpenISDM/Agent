#!/bin/bash

echo "upgarde configuration file"
sudo chmod 755 /home/bedis/Agent/bin/upgrade_agent_config.sh
sudo /home/bedis/Agent/bin/upgrade_agent_config.sh

echo "upgrate other things"

echo "start process"
cd /home/bedis/Agent/bin/
sudo chmod 755 /home/bedis/Agent/bin/auto_Agent.sh
sudo /home/bedis/Agent/bin/auto_Agent.sh
