# Installer

#SDK=/Applications/CASIO/SDK
export DIR=$(pwd)

export SDK=$DIR/PrizmSDK
export PATH=$PATH:$SDK/bin
HOMEBREW=/opt/homebrew

if [ ! -d "/opt/homebrew" ]; then
    /bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
fi

if [ ! -d "PrizmSDK" ]; then
    mkdir $SDK
    if [ ! -d "PrizmSDK" ]; then
        echo "Failed to create PrizmSDK directory!"
        exit
    fi
fi

# For multicore CPU with RAM to spare, to speed up builds use `make -j$(nproc)` instead of `make` for this guide.
# NOTE! for macOS use make -j$(sysctl -n hw.ncpu)

# Compiling binutils
if [ ! -d "binutils-2.43" ]; then
    if [ ! -f "binutils-2.43.tar.gz" ]; then
        curl -O https://sourceware.org/pub/binutils/releases/binutils-2.43.tar.gz
    fi
    tar -xzvf binutils-2.43.tar.gz
fi
if [ "$(ls -A build-binutils)" ]; then
    echo "binutils: Done!"
else
    if [ ! -d "$HOMEBREW/Cellar/texinfo" ]; then
        brew install texinfo
    fi
    
    if [ ! -d "$HOMEBREW/Cellar/binutils" ]; then
        brew install binutils
    fi
    
    
    
    mkdir build-binutils
    cd build-binutils
    echo "Compiling binutils"
    
    ../binutils-2.43/configure --target=sh3eb-elf --prefix=$SDK --disable-nls --disable-multilib
    make -j$(sysctl -n hw.ncpu)
    make install
    
    cd ..
fi

read -p "Press Enter to continue..."

# Compiling GCC
if [ ! -d "gcc-14.2.0" ]; then
    if [ ! -f "gcc-14.2.0.tar.gz" ]; then
        curl -O https://ftp.gnu.org/gnu/gcc/gcc-14.2.0/gcc-14.2.0.tar.gz
    fi
    tar -xzvf gcc-14.2.0.tar.gz
fi

if [ "$(ls -A build-gcc)" ]; then
    echo "gcc: Done!"
else
    cd gcc-14.2.0
    ./contrib/download_prerequisites
    cd ..
    
    if [ ! -d "$HOMEBREW/Cellar/gcc" ]; then
        brew install gcc
    fi
    
#    if [ ! -d "$HOMEBREW/Cellar/libisl" ]; then
#        brew install libisl
#    fi
    
    mkdir build-gcc
    cd build-gcc
    echo "Compiling gcc"

    ../gcc-14.2.0/configure \
    --target=sh3eb-elf \
    --prefix=$SDK \
    --disable-nls \
    --enable-languages=c,c++ \
    --disable-multilib \
    --without-headers
    
    
# Use All Available CPU Cores
# CPU cores dynamically using the sysctl command: make -j$(sysctl -n hw.ncpu)
# This runs as many jobs as there are CPU cores.

# Use a Fixed Number of Jobs:
# If you want to manually specify the number of jobs: make j4

# Unlimited Jobs:
# You can specify -j without a number to allow make to run as many jobs as it wants:

    make -j$(sysctl -n hw.ncpu) all-gcc
    make install-gcc

    make -j$(sysctl -n hw.ncpu) all-target-libgcc
    make install-target-libgcc
    
    cd ..
fi

read -p "Press Enter to continue..."

# Compiling mkg3a
if [ ! -d "mkg3a-0.5.0" ]; then
    tar -xzvf mkg3a-0.5.0.tar.gz
fi

if [ "$(ls -A build-mkg3a)" ]; then
    echo "mkg3a: Done!"
else
    if [ ! -d "$HOMEBREW/Cellar/cmake" ]; then
        brew install cmake
    fi

    mkdir build-mkg3a
    cd build-mkg3a
    
    cmake ../mkg3a-0.5.0 -DCMAKE_INSTALL_PREFIX=$SDK
    make -j$(sysctl -n hw.ncpu)
    make install

    cd ..
fi

read -p "Press Enter to continue..."

# fx-CG Library
if [ ! -d "libfxcg-0.6" ]; then
    tar -xzvf libfxcg-0.6.tar.gz
fi

if [ "$(ls -A libfxcg-0.6/lib)" ]; then
    echo "libfxcg: Done!"
else
    cd libfxcg-0.6
    
    make -j$(sysctl -n hw.ncpu)

    cp lib/*.a $SDK/lib/
    cp -a toolchain $SDK/
    cp -a include $SDK/
    
    cd ..
fi

if [ ! -d "$HOMEBREW/Cellar/imagemagick" ]; then
    brew install imagemagick
fi

if [ ! -d "~/Document/Prizm" ]; then
    cp -r Prizm ~/Document
fi

