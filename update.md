# Update PrizmSDK for macOS

### Environment Paths
>[!IMPORTANT]
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
cd ~/sh3eb-toolchain

### Build & Update libfxcg
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
You will require that PrizmSDK is currently installed.

