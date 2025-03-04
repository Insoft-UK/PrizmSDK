```
export FXCGSDK=/Applications/CASIO/PrizmSDK
grep -qxF 'export PATH=/Applications/CASIO/PrizmSDK:/Applications/CASIO/PrizmSDK/bin:/Applications/CASIO/PrizmSDK/sh3eb-elf/bin:$PATH' ~/.zshrc || echo 'export PATH=/Applications/CASIO/PrizmSDK:/Applications/CASIO/PrizmSDK/bin:/Applications/CASIO/PrizmSDK/sh3eb-elf/bin:$PATH' >> ~/.zshrc
grep -qxF 'export FXCGSDK=/Applications/CASIO/PrizmSDK' ~/.zshrc || echo 'export FXCGSDK=/Applications/CASIO/PrizmSDK' >> ~/.zshrc
source ~/.zshrc
```

```
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
```

```
brew install libpng cmake gmp mpfr libmpc isl wget make gcc

mkdir -p ~/sh3eb-toolchain
cd ~/sh3eb-toolchain
```

#Download gcc, binutils, mkg3a & libfxcg
```
wget https://ftp.gnu.org/gnu/gcc/gcc-14.2.0/gcc-14.2.0.tar.gz
mkdir -p gcc
tar -xzvf gcc-14.2.0.tar.gz --strip-components=1 -C gcc

wget https://ftp.gnu.org/gnu/binutils/binutils-2.36.tar.gz
mkdir -p binutils
tar -xvzf binutils-2.36.tar.gz --strip-components=1 -C binutils

git clone https://github.com/Insoft-UK/mkg3a.git
git clone https://github.com/Insoft-UK/libfxcg.git
```

#BUILD
```
mkdir ~/sh3eb-toolchain/binutils/build
cd ~/sh3eb-toolchain/binutils/build
../configure --target=sh3eb-elf --prefix=/Applications/CASIO/PrizmSDK --disable-nls --disable-werror
make -j$(sysctl -n hw.ncpu)
make install

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


cd ~/sh3eb-toolchain/mkg3a
cmake . -DCMAKE_INSTALL_PREFIX=/Applications/CASIO/PrizmSDK
make
make install

cd ~/sh3eb-toolchain/libfxcg
make
make install

rm ~/sh3eb-toolchain
```
