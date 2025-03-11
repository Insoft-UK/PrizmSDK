#!/bin/bash
IDENTITY=security find-identity -v -p basic | awk -F'"' '/Developer ID Installer:/ {print $2}'

# Your AppleID, TeamID and Password (An app-specific password NOT! AppleID password)
APPLE_ID="apple_id@icloud.com"
TEAM_ID="0AB11C3DEF"
PASSWORD="aaaa-bbbb-cccc-dddd"

PACKAGEROOT=package-root
NAME=PrizmSDK
IDENTIFIER=uk.insoft.$NAME

pkgbuild --root package-root \
         --identifier $IDENTIFIER \
         --version 1.0 --install-location / \
         --scripts scripts \
         $NAME.pkg
         
productsign --sign "$IDENTITY" $NAME.pkg $NAME-signed.pkg
#xcrun notarytool submit --apple-id $APPLE_ID \
#                        --password $PASSWORD \
#                        --team-id $TEAM_ID \
#                        --wait $NAME-signed.pkg

productbuild --distribution distribution.xml \
             --resources resources \
             --package-path $NAME.pkg \
             $NAME-installer.pkg
             
productsign --sign "$IDENTITY" $NAME-installer.pkg $NAME-installer-signed.pkg
#productbuild --distribution distribution.xml \
#             --resources resources \
#             --package-path $NAME-signed.pkg \
#             $NAME-installer.pkg

rm -rf $NAME.pkg
rm -rf $NAME-signed.pkg
rm -rf $NAME-installer.pkg

spctl -a -v $NAME-installer-signed.pkg
