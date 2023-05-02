#!/bin/bash

echo "Installing SDL2, SDL2_image, SDL2_ttf ..."

sudo apt-get update && sudo apt-get install -y \
 libsdl2-dev \
 libsdl2-image-dev \
 libsdl2-ttf-dev

echo "Done!"
