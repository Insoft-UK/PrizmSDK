#!/bin/bash
clear
magick Icon/Icon~uns.png -ordered-dither o4x4,32,64,32 Icon~uns.bmp
magick Icon/Icon~sel.png -ordered-dither o4x4,32,64,32 Icon~sel.bmp

if [ build ]; then
    rm -rf build
fi
rm *.g3a

export NAME=$(basename $(pwd))
export VERSION=$(head -n 1 version.txt | sed 's/^[[:space:]]*//;s/[[:space:]]*$//')
make
#rm -rf build *.bin *.bmp
