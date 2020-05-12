#!/bin/bash

# kill ./Agent
# |: the output of left side is passed to the right side as input
# ps -ef: get all environmental parameters
# grep Agent: get the process with name "Agent"
# grep -v grep: this filter out the row with "grep"
# awk '{print $2}': print the second column, which is PID
# xargs sudo kill -SIGINT: kill the process by giving a signal interrupt

ps -ef | grep Agent | grep -v grep | awk '{print $2}' | xargs sudo kill -SIGINT


# kill LightControl.py
ps -ef |grep LightControl | grep -v grep | awk '{print $2}' | xargs sudo kill -9
