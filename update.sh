#!/bin/bash

# MIT License
# 
# Copyright (c) 2025 insoft
# 
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
# 
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
# 
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.


# Detect operating system
OS=$(uname -s)

# Detect hardware architecture
ARCH=$(uname -m)

echo "Operating System: $OS"
echo "Architecture: $ARCH"

# Example: Check platform
if [[ "$OS" == "Linux" && "$ARCH" == "x86_64" ]]; then
    echo "Running on a 64-bit Linux platform."
    exit
elif [[ "$OS" == "Darwin" ]]; then
    echo "Running on macOS."
    if [[ "$ARCH" == *"arm64"* ]]; then
        echo "AppleSilicon"
    else
        echo "Intel"
    fi
else
    echo "Platform: $OS $ARCH"
    exit
fi

if [ ! -d "/Applications/CASIO/PrizmSDK" ]; then
    echo "PrizmSDK Not Installed!"
    exit
fi

mkdir -p ~/sh3eb-toolchain
cp -a libfxcg ~/sh3eb-toolchain/
cd ~/sh3eb-toolchain/libfxcg
make
make install

cp lib/*.a /Applications/CASIO/PrizmSDK/lib/
cp -a toolchain /Applications/CASIO/PrizmSDK/
cp -a include /Applications/CASIO/PrizmSDK/
cd ~/sh3eb-toolchain
cp prizm_rules $LIBFXCG/toolchain

rm -r ~/sh3eb-toolchain

read -p "PrizmSDK updated."

