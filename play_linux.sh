#!/bin/bash

bash +x install_dependencies_linux.sh

echo "Build started"
mkdir build && cd build || exit
cmake ..
make
echo "Build completed"

./SpaceInvaders
