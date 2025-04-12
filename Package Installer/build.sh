#!/bin/bash

# Your AppleID, TeamID and Password (An app-specific password NOT! AppleID password)
APPLE_ID="apple_id@icloud.com"
TEAM_ID="0AB11C3DEF"
PASSWORD="aaaa-bbbb-cccc-dddd"

PACKAGEROOT=package-root
NAME=PrizmSDK
IDENTIFIER=your.domain.$NAME
YOUR_NAME="Your Name"

# re-sign all binarys
find "$PACKAGEROOT/$PRIZMSDK/bin" -type f -exec codesign --remove-signature {} \;
find "$PACKAGEROOT/$PRIZMSDK/bin" -type f -exec codesign --sign "Developer ID Application: $YOUR_NAME ($TEAM_ID)" --options runtime --timestamp {} \;

find "$PACKAGEROOT/$PRIZMSDK/sh3eb-elf/bin" -type f -exec codesign --remove-signature {} \;
find "$PACKAGEROOT/$PRIZMSDK/sh3eb-elf/bin" -type f -exec codesign --sign "Developer ID Application: $YOUR_NAME ($TEAM_ID)" --options runtime --timestamp {} \;

find "$PACKAGEROOT/$PRIZMSDK/libexec/gcc/sh3eb-elf" -type f -exec codesign --remove-signature {} \;
find "$PACKAGEROOT/$PRIZMSDK/libexec/gcc/sh3eb-elf" -type f -exec codesign --sign "Developer ID Application: $YOUR_NAME ($TEAM_ID)" --options runtime --timestamp {} \;


pkgbuild --root package-root \
         --identifier $IDENTIFIER \
         --version 1.0 --install-location / \
         --scripts scripts \
         $NAME.pkg
         
productsign --sign "Developer ID Installer: $YOUR_NAME ($TEAM_ID)" $NAME.pkg $NAME-signed.pkg

xcrun notarytool submit --apple-id $APPLE_ID \
                        --password $PASSWORD \
                        --team-id $TEAM_ID \
                        --wait $NAME-signed.pkg

./update_distribution.sh
productbuild --distribution distribution.xml \
             --resources resources \
             --package-path $NAME-signed.pkg \
             $NAME-installer.pkg
             
productsign --sign "Developer ID Installer: $YOUR_NAME ($TEAM_ID)" $NAME-installer.pkg $NAME-installer-signed.pkg

xcrun notarytool submit --apple-id $APPLE_ID \
                        --password $PASSWORD \
                        --team-id $TEAM_ID \
                        --wait $NAME-installer-signed.pkg
                        

rm -r $NAME.pkg
rm -r $NAME-signed.pkg
rm -r $NAME-installer.pkg

spctl -a -v $NAME-installer-signed.pkg
mv $NAME-installer-signed.pkg $NAME.pkg
