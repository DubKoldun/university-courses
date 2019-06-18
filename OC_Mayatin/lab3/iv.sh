#!/bin/bash

ps -e -o pid | tail -n +2 |
gawk '{f1="/proc/"$1"/statm"; getline str<f1; split(str, a); close(f1); print $1, ":", a[2]-a[3], "lists"}' |
sort -r -n -t ":" -k 2 > out4.txt


