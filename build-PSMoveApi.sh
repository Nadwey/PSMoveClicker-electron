#!/bin/sh
# hell yeah bash

if [ ! -d psmoveapi-build ]; then
  echo "Cloning psmoveapi..."
  git clone --recursive https://github.com/thp/psmoveapi.git psmoveapi-build
else
  echo "psmoveapi arleady cloned"
fi

cd psmoveapi-build
mkdir -p build
cd build
cmake ..
make