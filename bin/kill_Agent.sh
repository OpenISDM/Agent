#!/bin/bash

ps -ef | grep Agent | grep -v grep | awk '{print $2}' | xargs sudo kill -SIGINT
