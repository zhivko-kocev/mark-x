#!/usr/bin/bash

npm install -g inquirer

echo "export NODE_PATH=$(npm root -g)" >> ~/.profile

cmake -B ./build -S .
cmake --build ./build --target mark_x -j 6
cmake --build ./build --target mark -j 6
cmake --install ./build --prefix "$HOME"/.local/

source "$HOME"/.profile
