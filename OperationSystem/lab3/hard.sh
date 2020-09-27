#!/bin/bash

ps -A -o pid | tail -n +2 |
gawk '{f1="/proc/"$1"/statm"; getline str<f1; split(str, a); close(f1);bt=a[2]-a[3];split("bytes KB MB GB", v); s=1; while(bt>1024){bt/=1024;s++;};print $1, ":", bt, v[s], ":",a[2]-a[3]}' |
sort -r -n -t ":" -k 3 | sed -r 's/.[^:]+$//' > hard4.txt
