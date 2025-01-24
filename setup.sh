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
    exit
fi

export FXCGSDK=/Applications/CASIO/PrizmSDK
grep -qxF 'export PATH=/Applications/CASIO/PrizmSDK:/Applications/CASIO/PrizmSDK/bin:/Applications/CASIO/PrizmSDK/sh3eb-elf/bin:$PATH' ~/.zshrc || echo 'export PATH=/Applications/CASIO/PrizmSDK:/Applications/CASIO/PrizmSDK/bin:/Applications/CASIO/PrizmSDK/sh3eb-elf/bin:$PATH' >> ~/.zshrc
grep -qxF 'export FXCGSDK=/Applications/CASIO/PrizmSDK' ~/.zshrc || echo 'export FXCGSDK=/Applications/CASIO/PrizmSDK' >> ~/.zshrc
source ~/.zshrc

if [ ! -d "/opt/homebrew" ]; then
    /bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
fi

brew install cmake gmp mpfr libmpc isl wget make gcc imagemagick


mkdir -p ~/sh3eb-toolchain
cp prizm_rules ~/sh3eb-toolchain/prizm_rules
if [ ! -d "~/Document/Prizm" ]; then
    cp -r Prizm ~/Documents
fi
cd ~/sh3eb-toolchain

if [ ! -d "gcc" ]; then
    if [ ! -f "gcc-14.2.0.tar.gz" ]; then
        wget https://ftp.gnu.org/gnu/gcc/gcc-14.2.0/gcc-14.2.0.tar.gz
    fi
    mkdir -p gcc
    tar -xzvf gcc-14.2.0.tar.gz --strip-components=1 -C gcc
fi


if [ ! -d "binutils" ]; then
    if [ ! -f "binutils-2.36.tar.gz" ]; then
        wget https://ftp.gnu.org/gnu/binutils/binutils-2.36.tar.gz
    fi
    mkdir -p binutils
    tar -xvzf binutils-2.36.tar.gz --strip-components=1 -C binutils
fi

if [ ! -d "binutils/build" ]; then
    mkdir ~/sh3eb-toolchain/binutils/build
    cd ~/sh3eb-toolchain/binutils/build
    ../configure --target=sh3eb-elf --prefix=/Applications/CASIO/PrizmSDK --disable-nls --disable-werror
    make -j$(sysctl -n hw.ncpu) # Use all CPU cores
    make install
fi

/Applications/CASIO/PrizmSDK/bin/sh3eb-elf-as --version
/Applications/CASIO/PrizmSDK/bin/sh3eb-elf-ld --version
read -p "Press Enter to continue..."

if [ ! -d "gcc/build" ]; then
    mkdir ~/sh3eb-toolchain/gcc/build
    cd ~/sh3eb-toolchain/gcc/build
    ../configure \
    --prefix=/Applications/CASIO/PrizmSDK \
    --target=sh3eb-elf \
    --enable-languages=c,c++ \
    --with-gmp=/opt/homebrew/opt/gmp \
    --with-mpfr=/opt/homebrew/opt/mpfr \
    --with-mpc=/opt/homebrew/opt/libmpc \
    --without-headers \
    --disable-nls \
    --disable-libssp

    make -j$(sysctl -n hw.ncpu) all-gcc
    make install-gcc
    
    
fi
/Applications/CASIO/PrizmSDK/bin/sh3eb-elf-gcc --version
find /Applications/CASIO/PrizmSDK -name "sh3eb-elf-gcc"
read -p "Press Enter to continue..."

if [ ! -d "mkg3a" ]; then
    git clone https://github.com/tari/mkg3a.git
fi
cd ~/sh3eb-toolchain/mkg3a
cmake . -DCMAKE_INSTALL_PREFIX=/Applications/CASIO/PrizmSDK
make
make install
read -p "Press Enter to continue..."

if [ ! -d "libfxcg" ]; then
    git clone https://github.com/Insoft-UK/libfxcg.git
fi
cd ~/sh3eb-toolchain/libfxcg
#make CC=/Applications/CASIO/PrizmSDK/sh3eb-elf/bin/sh3eb-elf-gcc
make
make install

cp lib/*.a /Applications/CASIO/PrizmSDK/lib/
cp -a toolchain /Applications/CASIO/PrizmSDK/
cp -a include /Applications/CASIO/PrizmSDK/
cd ~/sh3eb-toolchain
cp prizm_rules $LIBFXCG/toolchain
read -p "Press Enter to continue..."

export PATH=/Applications/CASIO/PrizmSDK/sh3eb-elf/bin:/Applications/CASIO/PrizmSDK/bin:$PATH
# Add this line to your ~/.zshrc or ~/.bashrc to make the change permanent.


find /Applications/CASIO/PrizmSDK -type f -exec file {} \; | grep Mach-O | cut -d: -f1 | xargs strip > /dev/null 2>&1
rm ~/sh3eb-toolchain

