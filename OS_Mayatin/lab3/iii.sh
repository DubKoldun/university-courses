#!/bin/bash

ps -e --format pid,command | grep -P "^\s*\d+ /sbin/" | awk '{print $1}' > out3.txt
