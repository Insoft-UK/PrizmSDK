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


export FXCGSDK=$(pwd)/PrizmSDK
HOMEBREW=/opt/homebrew

BINUTILS="binutils-2.43"
GCC="gcc-14.2.0"

LIBFXCG="libfxcg-0.6"
MKG3A="mkg3a-0.5.0"

# Detect operating system
OS=$(uname -s)

# Detect hardware architecture
ARCH=$(uname -m)

echo "Operating System: $OS"
echo "Architecture: $ARCH"

export CC=gcc
export CXX=g++

#if [ ! -d "$HOMEBREW/Cellar/gcc" ]; then
#    brew install gcc
#fi

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


if [ ! -d "/opt/homebrew" ]; then
    /bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
fi

if [ -d "/Applications/CASIO/PrizmSDK" ]; then
    echo "Setting-up 'PrimeSDK'"
    if [ ! -d "$HOMEBREW/Cellar/gmp" ]; then
        brew install gmp
    fi
    
    if [ ! -d "$HOMEBREW/Cellar/mpfr" ]; then
        brew install mpfr
    fi
    
    if [ ! -d "$HOMEBREW/Cellar/mpc" ]; then
        brew install mpc
    fi
    
    if [ ! -d "$HOMEBREW/Cellar/libmpc" ]; then
        brew install libmpc
    fi
    
    if [ ! -d "$HOMEBREW/Cellar/libxdmcp" ]; then
        brew install libxdmcp
    fi
    
    if [ ! -d "$HOMEBREW/Cellar/ppl" ]; then
        brew install ppl
    fi
    
    if [ ! -d "$HOMEBREW/Cellar/texinfo" ]; then
        brew install texinfo
    fi
    
    if [ ! -d "$HOMEBREW/Cellar/libpng" ]; then
        brew install libpng
    fi
    
    exit
fi

# For multicore CPU with RAM to spare, to speed up builds use `make -j$(nproc)` instead of `make` for this guide.
# NOTE! for macOS use make -j$(sysctl -n hw.ncpu)

# Compiling binutils

if [ ! -d "$BINUTILS" ]; then
    if [ ! -f "$BINUTILS.tar.gz" ]; then
        curl -O https://sourceware.org/pub/binutils/releases/$BINUTILS.tar.gz
    fi
    tar -xzvf $BINUTILS.tar.gz
fi
if [ -d "build-binutils" ]; then
    # Ask the user a question
    result=$(osascript -e 'display dialog "Do you want to re-build binutils?" buttons {"Yes", "No"} default button "No"' 2>/dev/null) >/dev/null
    if [[ "$result" == *"Yes"* ]]; then
        rm -rf build-binutils
    fi
else
    read -p "Press Enter to continue..."
fi
if [ ! -d "build-binutils" ]; then
    if [ ! -d "$HOMEBREW/Cellar/texinfo" ]; then
        brew install texinfo
    fi
    
    if [ ! -d "$HOMEBREW/Cellar/binutils" ]; then
        brew install binutils
    fi
    
    mkdir build-binutils
    cd build-binutils
    echo "Compiling binutils"
    
    ../$BINUTILS/./configure \
    --target=sh3eb-elf \
    --prefix=$FXCGSDK \
    --disable-nls
    
    make -j$(sysctl -n hw.ncpu)
    make install
    
    cd ..
fi
echo "binutils: Done!"


# Compiling GCC

if [ ! -d "$GCC" ]; then
    if [ ! -f "$GCC.tar.gz" ]; then
        curl -O https://ftp.gnu.org/gnu/gcc/$GCC/$GCC.tar.gz
    fi
    tar -xzvf $GCC.tar.gz
fi
if [ -d "build-gcc" ]; then
    # Ask the user a question
    result=$(osascript -e 'display dialog "Do you want to re-build gcc?" buttons {"Yes", "No"} default button "No"' 2>/dev/null) >/dev/null
    if [[ "$result" == *"Yes"* ]]; then
        rm -rf build-gcc
    fi
else
    read -p "Press Enter to continue..."
fi
if [ ! -d "build-gcc" ]; then
    export PATH=$PATH:$FXCGSDK/bin
    
    if [ ! -d "$HOMEBREW/Cellar/gmp" ]; then
        brew install gmp
    fi
    
    if [ ! -d "$HOMEBREW/Cellar/mpfr" ]; then
        brew install mpfr
    fi
    
    if [ ! -d "$HOMEBREW/Cellar/mpc" ]; then
        brew install mpc
    fi
    
    if [ ! -d "$HOMEBREW/Cellar/ppl" ]; then
        brew install ppl
    fi
    
    
    mkdir build-gcc
    cd build-gcc
    echo "Compiling gcc"
    
    ../$GCC/./configure \
    --target=sh3eb-elf \
    --prefix=$FXCGSDK \
    --with-gmp=/opt/homebrew/Cellar/gmp/6.3.0 \
    --with-mpfr=/opt/homebrew/Cellar/mpfr/4.2.1 \
    --with-mpc=/opt/homebrew/Cellar/libmpc/1.3.1 \
    --disable-nls \
    --enable-languages=c,c++ \
    --without-headers
    
    make -j$(sysctl -n hw.ncpu) all-gcc
    make install-gcc
    
#    make -j$(sysctl -n hw.ncpu) all-target-libgcc
#    make install-target-libgcc
    
    cd ..
fi
echo "gcc: Done!"


# Compiling mkg3a
if [ -d "$MKG3A" ]; then
    # Ask the user a question
    result=$(osascript -e 'display dialog "Do you want to upgrade mkg3a?" buttons {"Yes", "No"} default button "No"' 2>/dev/null) >/dev/null
    if [[ "$result" == *"Yes"* ]]; then
        rm -rf $MKG3A
    fi
else
    read -p "Press Enter to continue..."
fi

if [ ! -d "$MKG3A" ]; then
    if [ ! -d "$HOMEBREW/Cellar/cmake" ]; then
        brew install cmake
    fi
    
    export PATH=$PATH:$FXCGSDK/bin
    tar -xzvf $MKG3A.tar.gz
    cd $MKG3A
    
    cmake . -DCMAKE_INSTALL_PREFIX=$FXCGSDK
    make
    make install

    cd ..
fi
echo "mkg3a: Done!"

# fx-CG Library
if [ ! -d "$LIBFXCG" ]; then
    tar -xzvf $LIBFXCG.tar.gz
fi

if [ -d "$LIBFXCG" ]; then
    rm -rf $LIBFXCG
    echo "Upgrading libfxcg"
fi

if [ ! -d "$LIBFXCG" ]; then
    tar -xzvf $LIBFXCG.tar.gz
    cp prizm_rules $LIBFXCG/toolchain/prizm_rules
    cd $LIBFXCG
    
    export PATH=$PATH:$FXCGSDK/bin
    make
    
    cp lib/*.a $FXCGSDK/lib/
    cp -a toolchain $FXCGSDK/
    cp -a include $FXCGSDK/
    
    cd ..
fi
echo "libfxcg: Done!"

find $FXCGSDK -type f -exec file {} \; | grep Mach-O | cut -d: -f1 | xargs strip > /dev/null 2>&1

if [ ! -d "$HOMEBREW/Cellar/imagemagick" ]; then
    brew install imagemagick
fi

if [ ! -d "~/Document/Prizm" ]; then
    cp -r Prizm ~/Documents
fi

./check.sh
