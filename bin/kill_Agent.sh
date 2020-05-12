#!/bin/bash

# |: the output of left side is passed to the right side as input
# ps -ef: get all environmental parameters
# grep Agent: get the process with name "Agent"
# grep -v grep: this filter out the row with "grep"
# awk '{print $2}': print the second column, which is PID
# xargs sudo kill -SIGINT: kill the process by PID




ps -ef | grep Agent | grep -v grep | awk '{print $2}' | xargs sudo kill -SIGINT
