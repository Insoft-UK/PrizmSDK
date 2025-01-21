#!/bin/bash
clear
export NAME=$(basename $(pwd))
export VERSION=$(head -n 1 version.txt | sed 's/^[[:space:]]*//;s/[[:space:]]*$//')
export FXCGSDK=/Applications/CASIO/PrizmSDK
export PATH=$FXCGSDK/bin:$PATH

if [ -f "$NAME.g3a" ]; then
    rm "$NAME.g3a"
fi

if [ -f "Icon~uns.bmp" ]; then
    magick Icon/Icon~uns.png -ordered-dither o4x4,32,64,32 Icon~uns.bmp
fi
if [ -f "Icon~sel.bmp" ]; then
    magick Icon/Icon~sel.png -ordered-dither o4x4,32,64,32 Icon~sel.bmp
fi

make

if [ -d "build" ]; then
    rm -rf build
    if [ -f "$NAME.bin" ]; then
        rm "$NAME.bin"
    fi
fi
