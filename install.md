# Build and Install PrizmSDK for macOS

### Environment Paths
> Ensure macOS can locate the PrizmSDK by adding it to your system’s environment paths.

```export FXCGSDK=/Applications/CASIO/PrizmSDK
grep -qxF 'export PATH=/Applications/CASIO/PrizmSDK:/Applications/CASIO/PrizmSDK/bin:/Applications/CASIO/PrizmSDK/sh3eb-elf/bin:$PATH' ~/.zshrc || echo 'export PATH=/Applications/CASIO/PrizmSDK:/Applications/CASIO/PrizmSDK/bin:/Applications/CASIO/PrizmSDK/sh3eb-elf/bin:$PATH' >> ~/.zshrc
grep -qxF 'export FXCGSDK=/Applications/CASIO/PrizmSDK' ~/.zshrc || echo 'export FXCGSDK=/Applications/CASIO/PrizmSDK' >> ~/.zshrc
source ~/.zshrc
```

### Download PrizmSDK
```
mkdir -p ~/sh3eb-toolchain
cp -a libfxcg ~/sh3eb-toolchain/
cp -a mkg3a ~/sh3eb-toolchain/
cd ~/sh3eb-toolchain
wget https://ftp.gnu.org/gnu/binutils/binutils-2.36.1.tar.gz
mkdir -p binutils
tar -xvzf binutils-*.tar.gz --strip-components=1 -C binutils
wget https://ftp.gnu.org/gnu/gcc/gcc-10.3.0/gcc-10.3.0.tar.gz
mkdir -p gcc
tar -xzvf gcc-*.tar.gz --strip-components=1 -C gcc
```

### Build & Install BINUTILS
```
mkdir ~/sh3eb-toolchain/binutils/build
cd ~/sh3eb-toolchain/binutils/build
../configure --target=sh3eb-elf --prefix=$FXCGSDK --disable-nls --disable-werror
make -j$(sysctl -n hw.ncpu) # Use all CPU cores
make install
```

### Build & Install GCC
```
mkdir ~/sh3eb-toolchain/gcc/build
cd ~/sh3eb-toolchain/gcc/build
../configure \
--prefix=$FXCGSDK \
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
$FXCGSDK/bin/sh3eb-elf-gcc --version
```

### Build & Install mkg3a
```
cd ~/sh3eb-toolchain/mkg3a
cmake . -DCMAKE_INSTALL_PREFIX=$FXCGSDK
make
make install
```

### Build & Install libfxcg
```
cd ~/sh3eb-toolchain/libfxcg
make CC=$FXCGSDK/sh3eb-elf/bin/sh3eb-elf-gcc
make
make install
cp lib/*.a $FXCGSDK/lib/
cp -a toolchain $FXCGSDK/
cp -a include $FXCGSDK/
```
### Cleanup!
```
rm -r ~/sh3eb-toolchain
```

>[!NOTE]
You will require `libpng gmp mpfr libmpc` are installed.
`brew install libpng gmp mpfr libmpc`.
