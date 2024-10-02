#!/usr/bin/zsh

cd "$1" || exit
git clone https://github.com/zhivko-kocev/backend.git
npm create vite@latest frontend -- --template "$2"-ts
