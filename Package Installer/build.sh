#!/bin/bash

# Your AppleID, TeamID, Password and Name (An app-specific password NOT! AppleID password)
if [ -z "$APPLE_ID" ]; then
    source notarization.sh
fi

PACKAGEROOT=package-root
PRIZMSDK=Applications/CASIO/PrizmSDK
NAME=prizmsdk
IDENTIFIER=uk.insoft.$NAME

find . -name '*.DS_Store' -type f -delete

chmod 644 resources/background.png resources/background@2x.png

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
                        
# Staple
xcrun stapler staple $NAME-signed.pkg

# Verify
xcrun stapler validate $NAME-signed.pkg

# Gatekeeper
spctl --assess --type install --verbose $NAME-signed.pkg

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
                        
# Staple
xcrun stapler staple $NAME-installer-signed.pkg

# Verify
xcrun stapler validate $NAME-installer-signed.pkg

# Gatekeeper
spctl --assess --type install --verbose $NAME-installer-signed.pkg

rm -r $NAME.pkg
rm -r $NAME-signed.pkg
rm -r $NAME-installer.pkg
mv $NAME-installer-signed.pkg $NAME.pkg
