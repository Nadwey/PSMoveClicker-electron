#!/bin/sh

COMPILER=clang++

mkdir -p build
echo "Building..."
$COMPILER *.cpp -o build/PSMoveClicker -lpsmoveapi -Lpsmoveapi-build/build -lX11 -lXtst -std=c++17 \
    `pkg-config gtkmm-4.0 --cflags --libs`
echo "Copying lib..."
cp -v psmoveapi-build/build/libpsmoveapi.so build/