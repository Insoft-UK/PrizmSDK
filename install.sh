#!/bin/bash
# Installer

# Use All Available CPU Cores
# CPU cores dynamically using the sysctl command: make -j$(sysctl -n hw.ncpu)
# This runs as many jobs as there are CPU cores.

# Use a Fixed Number of Jobs:
# If you want to manually specify the number of jobs: make j4

# Unlimited Jobs:
# You can specify -j without a number to allow make to run as many jobs as it wants:


export DIR=$(pwd)

export FXCGSDK=$DIR/Prizm/SDK
export PATH=$PATH:$FXCGSDK/bin
HOMEBREW=/opt/homebrew

BINUTILS="binutils-2.37"
GCC="gcc-14.2.0"

#BINUTILS="binutils-2.34"
#GCC="gcc-10.0.0"

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

if [ ! -d "$HOMEBREW/Cellar/gcc" ]; then
    brew install gcc
fi

# Example: Check platform
if [[ "$OS" == "Linux" && "$ARCH" == "x86_64" ]]; then
    echo "Running on a 64-bit Linux platform."
    exit
elif [[ "$OS" == "Darwin" ]]; then
    echo "Running on macOS."
else
    echo "Platform: $OS $ARCH"
    exit
fi

if [[ "$ARCH" == *"arm64"* ]]; then
    result=$(osascript -e 'display dialog "AppleSilicon, do you want to compile for x86_64 instead." buttons {"Yes", "No"} default button "No"' 2>/dev/null) >/dev/null
    if [[ "$result" == *"Yes"* ]]; then
        arch arch -x86_64 /bin/zsh
    fi
fi

if [ ! -d "/opt/homebrew" ]; then
    /bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
fi

if [ ! -d "$FXCGSDK" ]; then
    mkdir $FXCGSDK
    if [ ! -d "$FXCGSDK" ]; then
        echo "Failed to create the 'SDK' directory!"
        exit
    fi
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
    
    ../$BINUTILS/configure \
    --target=sh3eb-elf \
    --prefix=$FXCGSDK \
    --disable-nls \
    --disable-multilib
    
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
#    cd $GCC
#    ./contrib/download_prerequisites
#    cd ..
    
    if [ ! -d "$HOMEBREW/Cellar/gmp" ]; then
        brew install gmp
    fi
    
    if [ ! -d "$HOMEBREW/Cellar/mpfr" ]; then
        brew install mpfr
    fi
    
    if [ ! -d "$HOMEBREW/Cellar/mpc" ]; then
        brew install mpc
    fi
    
    mkdir build-gcc
    cd build-gcc
    echo "Compiling gcc"

    ../$GCC/configure \
    --target=sh3eb-elf \
    --prefix=$FXCGSDK \
    --with-gmp=/opt/homebrew/Cellar/gmp/6.3.0 \
    --with-mpfr=/opt/homebrew/Cellar/mpfr/4.2.1 \
    --with-mpc=/opt/homebrew/Cellar/libmpc/1.3.1 \
    --disable-nls \
    --enable-languages=c,c++ \
    --disable-multilib \
    --without-headers
    
    make -j$(sysctl -n hw.ncpu) all
    make install-gcc
    
    cd ..
fi
echo "gcc: Done!"


# Compiling mkg3a
if [ ! -d "$MKG3A" ]; then
    tar -xzvf $MKG3A.tar.gz
fi

if [ -d "build-mkg3a" ]; then
    # Ask the user a question
    result=$(osascript -e 'display dialog "Do you want to re-build mkg3a?" buttons {"Yes", "No"} default button "No"' 2>/dev/null) >/dev/null
    if [[ "$result" == *"Yes"* ]]; then
        rm -rf build-mkg3a
    fi
else
    read -p "Press Enter to continue..."
fi

if [ ! -d "build-mkg3a" ]; then
    if [ ! -d "$HOMEBREW/Cellar/cmake" ]; then
        brew install cmake
    fi

    mkdir build-mkg3a
    cd build-mkg3a
    
    cmake ../$MKG3A -DCMAKE_INSTALL_PREFIX=$FXCGSDK
    make -j$(sysctl -n hw.ncpu)
    make install

    cd ..
fi
echo "mkg3a: Done!"


# fx-CG Library
if [ ! -d "$LIBFXCG" ]; then
    tar -xzvf $LIBFXCG.tar.gz
fi

if [ -d "$LIBFXCG" ]; then
    # Ask the user a question
    result=$(osascript -e 'display dialog "Do you want to re-install libfxcg?" buttons {"Yes", "No"} default button "No"' 2>/dev/null) >/dev/null
    if [[ "$result" == *"Yes"* ]]; then
        rm -rf $LIBFXCG
    fi
else
    read -p "Press Enter to continue..."
fi
if [ ! -d "build-libfxcg" ]; then
    tar -xzvf $LIBFXCG.tar.gz
    cd $LIBFXCG
    
    make -j$(sysctl -n hw.ncpu)
    
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
    cp -r Prizm ~/Document
fi

