#!/bin/bash

ps -o pid,stime | tail -n +2 | sort -r -k1 | head -n 1 | awk '{print $1 ": " $2}'
