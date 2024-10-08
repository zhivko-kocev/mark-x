#!/usr/bin/bash

cd "$1" || exit

git clone https://github.com/zhivko-kocev/"$3".git

if [ "$2" != "none"  ]; then
npm create vite@latest frontend -- --template "$2"-ts
fi
