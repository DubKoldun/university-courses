#!/bin/bash

ps -a -u $USER -o pid,command | tail -n +2 | awk '{printf $1 ": " $2 "\n"}' > out1.txt
wc -l out1.txt >> out1.txt
