#!/usr/bin/bash


cd "$1" || exit

if [ "$2" != "none"  ]; then
npm create vite@latest frontend -- --template "$2"-ts
fi

cp -r "$(dirname "${BASH_SOURCE[0]}")"/skeletons/"$3" .


if [ "$2" == "none" ]; then
cd .. && mv ./"$1"/"$3" ./ && rm -rf ./"$1"
mv "$3" "$1"
fi






